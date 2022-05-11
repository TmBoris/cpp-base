//
// Created by User on 03.03.2022.
//

#pragma once

#include "appearance_of_image.h"
#include "bmp_header_consts.h"
#include "fstream"
#include "iostream"
#include "exception"

struct Import {
    static Image import(const char* path);
};

