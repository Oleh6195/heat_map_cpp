//
// Created by Олег on 2019-06-05.
//
#include "../headers/plot.h"


double get_max(std::vector<std::vector<double>> matrix) {
    double max = -10000;
    for (auto &i : matrix) {
        for (double &j : i) {
            max = (j > max) ? j : max;
        }
    }
    return max;
}

double get_min(std::vector<std::vector<double>> matrix) {
    double min = 10000;
    for (auto &i : matrix) {
        for (double &j : i) {
            min = (j < min) ? j : min;
        }
    }
    return min;
}

using namespace std;

pixel_t temp_to_rgb(double mini, double maxi, double temp) {
    //stackoverflow - створення матриці rgb відносно температури
    pixel_t p;
    double ratio = 2 * (temp - mini) / (maxi - mini);
    p.blue = (int) std::max((double) 0, 255 * (1 - ratio));
    p.red = (int) std::max((double) 0, 255 * (ratio - 1));
    p.green = 255 - p.blue - p.red;
    return p;
}
void image_array(vector<vector<double>>& matrix, vector<vector<pixel_t>>& img, double maxi, double mini) {
    for (int i = 0; i < matrix.size(); ++i) {
        std::vector<pixel_t> ws;
        for (int j = 0; j < matrix[i].size(); ++j) {
            pixel_t p = temp_to_rgb(mini, maxi, matrix[i][j]);
            ws.emplace_back(p);
        }
        img.emplace_back(ws);

    }
}

void create_image(std::vector<std::vector<double>> matrix, int i, double maxi, double mini) {
    std::vector<std::vector<pixel_t>> img;
    image_array(matrix, img, maxi, mini);
    std::string filename = "img/pic_" + std::to_string(i) + ".png";
    write_png_file(img, filename);

}


png_bytep *row_pointers;

void write_png_file(std::vector<std::vector<pixel_t>>& image, const std::string &filename) {
    size_t width = image.size();
    size_t height = image[0].size() & INT_MAX;
    FILE *fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte **row_pointers = NULL;
    /* "status" contains the return value of this function. At first
       it is set to a value which means 'failure'. When the routine
       has finished its work, it is set to a value which means
       'success'. */
    int status = -1;
    /* The following number is set by trial and error only. I cannot
       see where it it is documented in the libpng manual.
    */
    int pixel_size = 3;
    int depth = 8;

    fp = fopen(filename.c_str(), "wb");


    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);


    info_ptr = png_create_info_struct(png_ptr);


    /* Set image attributes. */

    png_set_IHDR(png_ptr,
                 info_ptr,
                 width,
                 height,
                 depth,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = static_cast<png_byte **>(png_malloc(png_ptr, height * sizeof(png_byte *)));
    for (y = 0; y < height; y++) {
        png_byte *row = static_cast<png_byte *>(png_malloc(png_ptr, sizeof(uint8_t) * width * pixel_size));
        row_pointers[y] = row;
        for (x = 0; x < width; x++) {
            pixel_t &pixel = image[x][y];
            *row++ = static_cast<png_byte>(pixel.red);
            *row++ = static_cast<png_byte>(pixel.green);
            *row++ = static_cast<png_byte>(pixel.blue);
        }
    }

    /* Write the image data to "fp". */

    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;

    for (y = 0; y < height; y++) {
        png_free(png_ptr, row_pointers[y]);
    }
    png_free(png_ptr, row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

}

