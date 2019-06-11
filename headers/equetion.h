//
// Created by Олег on 2019-06-04.
//

#ifndef TALON_EQUETION_H
#define TALON_EQUETION_H

#include <iostream>
#include <vector>
#include <math.h>
#include <boost/thread/barrier.hpp>
using namespace std;

void calcul(std::vector<std::vector<double > >& matrix,std::vector<std::vector<double > >& new_matrix, float alpha, float delta_x,
            float delta_y, float delta_t);
void parallel_calculation(std::vector<std::vector<double > > &matrix,std::vector<std::vector<double > >& new_matrix, float alpha, float delta_x,
                          float delta_y, float delta_t,
                          int thr_num, int thr_cur, std::mutex& mtx);
#endif //TALON_EQUETION_H
