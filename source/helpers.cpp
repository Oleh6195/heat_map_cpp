//
// Created by Олег on 2019-06-03.
//
#include "../headers/helpers.h"

using namespace boost::locale::boundary;
using std::ios;

configuration_t read_conf(std::istream& cf){

    ios::fmtflags flags( cf.flags() );
    cf.exceptions(std::ifstream::failbit);

    configuration_t res{};
    std::string temp;

    try {
        cf >> res.filename;
        getline(cf, temp);
        cf >> res.c;
        getline(cf, temp);
        cf >> res.ro;
        getline(cf, temp);
        cf >> res.k;
        getline(cf, temp);
        cf >> res.x;
        getline(cf, temp);
        cf >> res.y;
        getline(cf, temp);
        cf >> res.thr_num;
        getline(cf, temp);
        cf >> res.iterations;
        getline(cf, temp);
        cf >> res.delta_x;
        getline(cf, temp);
        cf >> res.delta_y;
        getline(cf, temp);
        cf >> res.delta_t;
        getline(cf, temp);
        cf >> res.interval_printing;
        getline(cf, temp);
    }catch(std::ios_base::failure &fail)
    {
        cf.flags( flags );
        throw;
    }
    cf.flags( flags );


    return res;
}


void load_matrix(const std::string &filename, std::vector<std::vector<double >>& matrix, double x, double y) {
    //stackoverflow - функція для зчитуванняня матриці з файлу
    std::ifstream ifs(filename);
    std::string tempstr;
    double tempint;
    char delimiter;

    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<double > tempv;
        while (iss >> tempint) {
            tempv.push_back(tempint);
            iss >> delimiter;
        }
        matrix.push_back(tempv);
    }
}

//void move_matrix(std::vector<std::vector<double >>& matrix, std::vector<std::vector<double >>& new_matrix){
//
////    matrix = new_matrix;
////    new_matrix.clear();
//}

void printmatrix(std::vector<std::vector<double >>& matrix){
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << "    ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}
void write_matrix(int i, std::vector<std::vector<double >> matrix){
    std::string filename = "matrixes/m_"+ std::to_string(i) + ".txt";
    std::ofstream output(filename);
    for (int j = 0; j < matrix.size(); ++j) {
        for (int k = 0; k < matrix.size(); ++k) {
            output << matrix[j][k] << " ";
        }
        output << "\n";
    }
}