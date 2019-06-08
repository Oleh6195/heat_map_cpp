//
// Created by Олег on 2019-06-05.
//

#ifndef TALON_PLOT_H
#define TALON_PLOT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <png.h>
using std::max;

double get_max(std::vector<std::vector<double > > matrix);
double get_min(std::vector<std::vector<double > > matrix);

std::vector<int> temp_to_rgb(double min, double max, double temp);


void create_image(std::vector<std::vector<double > > matrix, int i, double maxi, double mini);
#endif //TALON_PLOT_H
