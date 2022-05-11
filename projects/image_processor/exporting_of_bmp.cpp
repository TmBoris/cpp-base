#include "exporting_of_bmp.h"

void Export::exporting(const char *path, Image &picture) {
    std::fstream file;
    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "There is no file for opening" << std::endl;
        throw std::exception();
    } else {
        unsigned char pad[3] = {0, 0, 0};
        const int padding = (4 - (picture.GetWidth() * 3) % 4) % 4;


        const int file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + picture.GetHeight() * picture.GetWidth() * 3 + padding * picture.GetHeight();

        unsigned char file_header[FILE_HEADER_SIZE];

        // file type
        file_header[0] = 'B';
        file_header[1] = 'M';
        // file size
        file_header[2] = file_size;
        file_header[3] = file_size >> 8;
        file_header[4] = file_size >> 16;
        file_header[5] = file_size >> 24;
        // Reserved 1 and Reserved 2
        file_header[6] = 0;
        file_header[7] = 0;
        file_header[8] = 0;
        file_header[9] = 0;
        // Pixel data offset
        file_header[10] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
        file_header[11] = 0;
        file_header[12] = 0;
        file_header[13] = 0;

        unsigned char information_header[INFORMATION_HEADER_SIZE];

        // Header size
        information_header[0] = INFORMATION_HEADER_SIZE;
        information_header[1] = 0;
        information_header[2] = 0;
        information_header[3] = 0;
        // Image width
        information_header[4] = picture.GetWidth();
        information_header[5] = picture.GetWidth() >> 8;
        information_header[6] = picture.GetWidth() >> 16;
        information_header[7] = picture.GetWidth() >> 24;
        // Image height
        information_header[8] = picture.GetHeight();
        information_header[9] = picture.GetHeight() >> 8;
        information_header[10] = picture.GetHeight() >> 16;
        information_header[11] = picture.GetHeight() >> 24;
        // Planes
        information_header[12] = 1;
        information_header[13] = 0;
        // Bits per pixel
        information_header[14] = 24;
        information_header[15] = 0;
        // Compression
        information_header[16] = 0;
        information_header[17] = 0;
        information_header[18] = 0;
        information_header[19] = 0;
        // Image size (no compression)
        information_header[20] = 0;
        information_header[21] = 0;
        information_header[22] = 0;
        information_header[23] = 0;
        // X pixel per meter
        information_header[24] = 0;
        information_header[25] = 0;
        information_header[26] = 0;
        information_header[27] = 0;
        // Y pixel per meter
        information_header[28] = 0;
        information_header[29] = 0;
        information_header[30] = 0;
        information_header[31] = 0;
        // Number of colors in the palette
        information_header[32] = 0;
        information_header[33] = 0;
        information_header[34] = 0;
        information_header[35] = 0;
        // Important colors
        information_header[36] = 0;
        information_header[37] = 0;
        information_header[38] = 0;
        information_header[39] = 0;

        file.write(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
        file.write(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

        for (size_t y = 0; y < picture.GetHeight(); ++y) {
            for (size_t x = 0; x < picture.GetWidth(); ++x) {
                unsigned char red = picture.GetColor(x, y).red;
                unsigned char green = picture.GetColor(x, y).green;
                unsigned char blue = picture.GetColor(x, y).blue;

                unsigned char color[] = {blue, green, red};

                file.write(reinterpret_cast<char*>(color), 3);
            }
            file.write(reinterpret_cast<char*>(pad), padding);
        }
    }
    file.close();
}
