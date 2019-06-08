//
// Created by Олег on 2019-06-04.
//

#ifndef TALON_EQUETION_H
#define TALON_EQUETION_H

#include <iostream>
#include <vector>
using namespace std;

void calcul(std::vector<std::vector<double> >& matrix, std::vector<std::vector<double > >& new_matrix, float alpha) ;
void parallel_calculation(std::vector<std::vector<double > > &matrix,std::vector<std::vector<double > >& new_matrix, float alpha,
                          int thr_num, int thr_cur, std::mutex& mtx);
#endif //TALON_EQUETION_H
