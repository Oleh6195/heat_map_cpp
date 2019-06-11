//
// Created by Олег on 2019-06-03.
//
#include <iostream>
#include <fstream>

#ifndef TALON_HELPERS_H
#define TALON_HELPERS_H

#include <boost/locale.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using std::vector;
struct configuration_t
{
    std::string filename;
    double ro, k,x,y;
    float c,delta_y, delta_x, delta_t;
    int thr_num, iterations, interval_printing;
};

inline std::chrono::steady_clock::time_point get_current_time_fenced() {
    static_assert(std::chrono::steady_clock::is_steady, "Timer should be steady (monotonic).");
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::steady_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

void load_matrix(const std::string &filename, std::vector<std::vector<double >>& matrix, double x, double y);
configuration_t read_conf(std::istream& cf);

void move_matrix(std::vector<std::vector<double >>& matrix, std::vector<std::vector<double >>& new_matrix);
void printmatrix(std::vector<std::vector<double >>& matrix);
void write_matrix(int i, std::vector<std::vector<double >> matrix);
#endif //TALON_HELPERS_H
