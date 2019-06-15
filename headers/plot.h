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

typedef struct {
    int red;
    int green;
    int blue;
} pixel_t;

double get_max(std::vector<std::vector<double> > matrix);

double get_min(std::vector<std::vector<double> > matrix);

pixel_t temp_to_rgb(double min, double max, double temp);


void create_image(std::vector<std::vector<double>> matrix, int i, double maxi, double mini);

void write_png_file(std::vector<std::vector<pixel_t>> &image, const std::string &filename);

#endif //TALON_PLOT_H
