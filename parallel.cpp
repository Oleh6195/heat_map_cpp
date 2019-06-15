#include <iostream>
#include <string>
#include <chrono>
#include "headers/helpers.h"
#include "headers/equetion.h"
#include <vector>
#include <thread>
#include "headers/plot.h"

using std::string;
using std::ifstream;
using std::cerr;
using std::endl;
int main(int argc, char *argv[]) {
    auto start = get_current_time_fenced();
    string filename("config.dat");
    if (argc == 2)
        filename = argv[1];
    if (argc > 2) {
        cerr << "Too many arguments. Usage: \n"
                "<program>\n"
                "or\n"
                "<program> <config-filename>\n" << endl;
        return 1;
    }
    ifstream config_stream(filename);
    if (!config_stream.is_open()) {
        cerr << "Failed to open configuration file " << filename << endl;
        return 2;
    }

    configuration_t config{};
    try {
        config = read_conf(config_stream);
    } catch (std::exception &ex) {
        cerr << "Error: " << ex.what() << endl;
        return 3;
    }
    typedef std::chrono::seconds s;
    std::locale loc = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> new_matrix;
    load_matrix(config.filename, matrix, config.x, config.y);
    new_matrix = matrix;
    double alpha = config.k /config.ro / config.c;
    double maxi = get_max(matrix);
    double mini = get_min(matrix);
    std::mutex mtx;
    std::vector<std::thread> threads_v;
    threads_v.reserve(static_cast<unsigned long>(config.thr_num));
    auto printing_result_time = get_current_time_fenced();
    for (int k = 0; k < (int) config.iterations; ++k) {
        for (int i = 0; i < config.thr_num; i++) {
            threads_v.emplace_back(
                    std::thread(parallel_calculation, ref(matrix), ref(new_matrix), alpha,
                                config.delta_x, config.delta_y, config.delta_t, config.thr_num, i + 1, ref(mtx)));
        }
        auto interval = get_current_time_fenced() - printing_result_time;
        auto d = std::chrono::duration_cast<s>(interval);
        if (d.count() >= config.interval_printing) {
            std::vector<std::vector<double >> matrix_for_image(new_matrix);
            threads_v.emplace_back(create_image, matrix_for_image, k, maxi, mini);
            threads_v.emplace_back(write_matrix, k, matrix_for_image);
            printing_result_time = get_current_time_fenced();
            std::cout << "Results saved" << std::endl;
        }
        for (auto &i : threads_v) {
            if (i.joinable()) {
                i.join();
            }
        }
        threads_v.clear();
        new_matrix[0] = matrix[0];
        new_matrix[new_matrix.size()- 1] = matrix[new_matrix.size()- 1];
        for (int i = 0; i < matrix.size(); ++i) {
            new_matrix[i][0] = matrix[i][0];
            new_matrix[i][matrix[i].size() - 1] = matrix[i][matrix[i].size() - 1];
        }
        matrix.swap(new_matrix);
    }
    auto finish = get_current_time_fenced() - start;
    std::cout << finish.count() << std::endl;
    return 0;
}