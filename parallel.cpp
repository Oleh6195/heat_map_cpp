#include <iostream>
#include <string>
#include <chrono>
#include "headers/helpers.h"
#include "headers/equetion.h"
#include <vector>
#include <thread>
#include "headers/plot.h"


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
    boost::barrier barrier(static_cast<unsigned int>(config.thr_num));
    std::vector<std::thread> threads_v;
    threads_v.reserve(static_cast<unsigned long>(config.thr_num));
    auto printing_result_time = get_current_time_fenced();
    for (int k = 0; k < (int) config.iterations; ++k) {
        for (int i = 0; i < config.thr_num; i++) {
            threads_v.emplace_back(
                    std::thread(parallel_calculation, ref(matrix), ref(new_matrix), alpha,
                                config.delta_x, config.delta_y, config.delta_t, config.thr_num, i + 1, ref(mtx)));
        }
        for (int i = 0; i < config.thr_num; i++) {
            if (threads_v[i].joinable()) {
                threads_v[i].join();
            }
        }

        threads_v.clear();
        move_matrix(matrix, new_matrix);
        auto interval = get_current_time_fenced() - printing_result_time;
        auto d = std::chrono::duration_cast<s>(interval);
        if (d.count() >= config.interval_printing) {
//            create_image(matrix, k, maxi, mini);

            std::vector<std::vector<double >> matrix_for_image(matrix);
            std::thread create_image_thread(create_image, ref(matrix_for_image), k, maxi, mini);
            if (create_image_thread.joinable()) {
                create_image_thread.join();
            }
            write_matrix(k, matrix);
            printing_result_time = get_current_time_fenced();
            std::cout << "Results saved" << std::endl;
        }
    }
    auto finish = get_current_time_fenced() - start;
    std::cout << finish.count() << std::endl;
    return 0;
}