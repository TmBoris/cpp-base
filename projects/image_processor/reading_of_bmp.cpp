//
// Created by User on 03.03.2022.
//
#include "reading_of_bmp.h"
Image Import::import(const char* path) {
    std::fstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "There is no file for opening" << std::endl;
        throw std::exception();
    } else {
        unsigned char file_header[FILE_HEADER_SIZE];
        file.read(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
        if (file_header[0] != 'B' || file_header[1] != 'M') {
            std::cout << "It's not a bmp file!" << std::endl;
            file.close();
            throw std::exception();
        } else {
            unsigned char information_header[INFORMATION_HEADER_SIZE];
            file.read(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

            size_t width = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) + (information_header[7] << 24);
            size_t height = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) + (information_header[11] << 24);

            Image image(width, height);

            const int padding = (4 - (width * 3) % 4) % 4;

            for (size_t i = 0; i < height; ++i) {
                for (size_t j = 0; j < width; ++j) {
                    unsigned char color[3];
                    file.read(reinterpret_cast<char*>(color), 3);

                    Color tmp;
                    tmp.red = static_cast<unsigned char>(color[2]);
                    tmp.green = static_cast<unsigned char>(color[1]);
                    tmp.blue = static_cast<unsigned char>(color[0]);

                    image.SetColor(j, i, tmp);
                }
                file.ignore(padding);
            }
            file.close();
            return image;
        }
    }
}
