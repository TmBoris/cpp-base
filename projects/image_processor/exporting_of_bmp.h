#pragma once

#include "appearance_of_image.h"
#include "bmp_header_consts.h"
#include "fstream"
#include "iostream"
#include "exception"

struct Export {
    static void exporting(const char* path, Image& picture);
};
