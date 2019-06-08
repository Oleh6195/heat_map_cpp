#include <iostream>
#include <string>

#include "headers/helpers.h"
#include "headers/equetion.h"
#include <vector>
#include <thread>
#include "headers/plot.h"

using namespace std;

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
    std::locale loc = boost::locale::generator().generate("en_US.UTF-8");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> new_matrix;
    load_matrix(config.filename, matrix, config.x, config.y);
    double alpha = config.k /config.ro / config.c;
    double maxi = get_max(matrix);
    double mini = get_min(matrix);
    std::mutex mtx;
    std::vector<std::thread> threads_v;
    threads_v.reserve(static_cast<unsigned long>(config.thr_num));
    for (int k = 0; k < (int) config.iterations; ++k) {
        new_matrix = matrix;
        for (int i = 0; i < config.thr_num; i++) {
            threads_v.emplace_back(
                    std::thread(parallel_calculation, ref(matrix), ref(new_matrix), alpha, config.thr_num, i + 1,
                                ref(mtx)));
        }
        for (int i = 0; i < config.thr_num; i++) {
            if (threads_v[i].joinable()) {
                threads_v[i].join();
            }
        }

        threads_v.clear();
        move_matrix(matrix, new_matrix);
        create_image(matrix,k, maxi, mini);
    }
    auto finish = get_current_time_fenced() - start;
    std::cout << finish.count() << std::endl;
    return 0;
}