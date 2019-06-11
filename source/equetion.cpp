//
// Created by Олег on 2019-06-04.
//
#include <boost/thread/barrier.hpp>
#include "../headers/equetion.h"
#include "../headers/plot.h"

int DELTA_T = 1000;


void calcul(std::vector<std::vector<double > >& matrix,std::vector<std::vector<double > >& new_matrix, float alpha, float delta_x,
            float delta_y, float delta_t) {
    for (int i = 0; i < matrix.size(); ++i) {
        std::vector<double> new_pmatrix;
        for (int j = 0; j < matrix[i].size(); ++j) {
            int m = (i == 0) ? 1 : i;
            int n = (j == 0) ? 1 : j;
            int z = (i == matrix.size() - 1) ? i - 1 : i;
            int l = (j == matrix[i].size() - 1) ? j - 1 : j;
            new_pmatrix.emplace_back(
                    matrix[i][j] + (alpha * DELTA_T * ((matrix[m - 1][j] - (2 * matrix[i][j]) + matrix[z + 1][j]) +
                                                        (matrix[i][n - 1] - (2 * matrix[i][j]) + matrix[i][l + 1]))));
        }
        new_matrix.emplace_back(new_pmatrix);
    }



}

void parallel_calculation(std::vector<std::vector<double > > &matrix,std::vector<std::vector<double > >& new_matrix, float alpha, float delta_x,
                          float delta_y, float delta_t,
                          int thr_num, int thr_cur, std::mutex& mtx) {
    int thr_delta = (int) matrix.size() / thr_num,
            thr_start = thr_delta * (thr_cur - 1),
            thr_end = thr_cur == thr_num ? (int) matrix.size() : thr_delta * thr_cur;

    for (int i = thr_start; i < thr_end; ++i) {
        std::vector<double> new_pmatrix;
        for (int j = 0; j < matrix[i].size(); ++j) {
            int m = (i == 0) ? 1 : i;
            int n = (j == 0) ? 1 : j;
            int z = (i == matrix.size() - 1) ? i - 1 : i;
            int l = (j == matrix[i].size() - 1) ? j - 1 : j;
            new_pmatrix.emplace_back(
                    matrix[i][j] + (alpha * delta_t * ((matrix[m - 1][j] - (2 * matrix[i][j]) + matrix[z + 1][j])/pow(delta_x,2) +
                                                       (matrix[i][n - 1] - (2 * matrix[i][j]) + matrix[i][l + 1])/pow(delta_y, 2))));
        }
        mtx.lock();
        new_matrix[i] = new_pmatrix;
        mtx.unlock();
    }


}
