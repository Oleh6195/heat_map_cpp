//
// Created by Олег on 2019-06-05.
//
#include "../headers/plot.h"



double get_max(std::vector<std::vector<double>> matrix){
    double max = -10000;
    for (auto &i : matrix) {
        for (double &j : i) {
            max = (j > max) ? j : max;
        }
    }
    return max;
}
double get_min(std::vector<std::vector<double>> matrix){
    double min = 10000;
    for (auto &i : matrix) {
        for (double &j : i) {
            min = (j < min) ? j : min;
        }
    }
    return min;
}
using namespace std;

std::vector<int> temp_to_rgb(double mini, double maxi, double temp){
    //stackoverflow - створення матриці rgb відносно температури
    double ratio = 2*(temp-mini) / (maxi - mini);
    int b = (int) std::max((double)0, 255*(1 - ratio));
    int r = (int) std::max((double)0, 255*(ratio - 1));
    int g = 255 - b - r;
    return {r, g, b};
}

std::vector<std::vector<std::vector<int>>> image_array(std::vector<std::vector<double>> matrix, double maxi, double mini){
    std::vector<std::vector<std::vector<int>>> img;
    for (int i = 0; i < matrix.size(); ++i) {
        std::vector<std::vector<int>> ws;
        for (int j = 0; j < matrix[i].size();++j) {
            ws.emplace_back(temp_to_rgb(mini, maxi, matrix[i][j]));
        }
        img.emplace_back(ws);

    }
    return img;
}

void create_image(std::vector<std::vector<double>> matrix, int i, double maxi, double mini){
    std::vector<std::vector<std::vector<int>>> image = image_array(matrix, maxi, mini);
    std::string filename = "img/pic_"+ std::to_string(i) + ".png";
    ofstream img(filename);
    img << "P3" << endl;
    img << image.size() << " " << image[0].size() << endl;
    img << "255" << endl;
    for (int i = 0; i < image.size(); i++)  {
        for (int j = 0; j < image[i].size(); j++) {
            img << image[i][j][0] << " " << image[i][j][1] << " " << image[i][j][2] << endl;
        }
    }

//    for (int i1 = 0; i1 < image.size(); ++i1) {
//        for (int i = 0; i < image[i1].size(); ++i) {
//            std::cout << image[i1][i][0] << " " << image[i1][i][1]<< " " << image[i1][i][2] <<"     ";
//        }
//        cout<<endl;
//    }
//    cout<< "\n" <<endl;


}