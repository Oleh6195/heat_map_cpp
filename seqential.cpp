#include <iostream>
#include <string>

#include "headers/helpers.h"
#include "headers/equetion.h"
#include "headers/plot.h"
#include <vector>

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
    double maxi = get_max(matrix);
    double mini = get_min(matrix);
    double alpha = config.k/(config.ro * config.c);

    for (int k = 0; k < config.iterations; ++k) {
        calcul(matrix,new_matrix, alpha);
        move_matrix(matrix, new_matrix);
        create_image(matrix, k, maxi, mini);
    }
    auto time = get_current_time_fenced() - start;
    std::cout << time.count() << std::endl;
    return 0;
}