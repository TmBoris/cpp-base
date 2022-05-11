#include "appearance_of_image.h"
#include "exporting_of_bmp.h"
#include "reading_of_bmp.h"
#include "Crop.h"
#include "Negative.h"
#include "Grayscale.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gauss_filter.h"
#include <cstring>
#include <typeinfo>
#include "iomanip"
#include "memory"
#include "emboss_filter.h"

bool IsIntNumber(char* str) {
    for (size_t i = 0; i < std::strlen(str); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool IsDoubleNumber(char* str) {
    size_t digits_counter = 0;
    size_t dots_counter = 0;
    for (size_t i = 0; i < std::strlen(str); ++i) {
        if (isdigit(str[i])) {
            digits_counter++;
        } else if (str[i] == '.') {
            dots_counter++;
        }
    }
    if ((dots_counter == 1 && digits_counter == std::strlen(str) - 1) || (digits_counter == std::strlen(str))) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    try {
        std::vector<Filter*> filters;
        if (argc == 2 && strcmp(argv[1], "--help") == 0) {
            std::cout << "This program contains 6 filters. To use them you need to write down names of input file and output file at first." << std::endl;
            std::cout << "Then you can choose which filters from the following list you want to use, and write appropriate commands." << std::endl;
            std::cout << std::left << std::setw(17) << "NAME IN TERMINAL" << std::right << std::setw(50) << "PARAMETERS" << std::setw(30) << "NAME OF THE FILTER" << std::endl;
            std::cout << std::left << std::setw(17) << "-crop" << std::right << std::setw(50) << "(integer number, integer number) width, height" << std::setw(30) << "Crop filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-neg" << std::right << std::setw(50) << "no parameters" << std::setw(30) << "Negative filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-emb" << std::right << std::setw(50) << "no parameters" << std::setw(30) << "Emboss filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-gs" << std::right << std::setw(50) << "no parameters" << std::setw(30) << "Grayscale filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-sharp" << std::right << std::setw(50) << "no parameters" << std::setw(30) << "Sharpening filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-edge" << std::right << std::setw(50) << "(number) threshold" << std::setw(30) << "Edge detection filter" << std::endl;
            std::cout << std::left << std::setw(17) << "-blur" << std::right << std::setw(50) << "(number) sigma" << std::setw(30) << "Gaussian blur filter" << std::endl;
        } else if (argc < 2) {
            std::cout << "write down --help to know possible usage of program" << std::endl;
            std::cout << "There are no input and output file" << std::endl;
            throw std::exception();
        } else {
            Image picture = Import::import(argv[1]);
            for (int i = 3; i < argc; ++i) {
                if (strcmp(argv[i], "-crop") == 0) {
                    size_t width = 0;
                    size_t height = 0;
                    if (i == argc - 1) {
                        std::cout << "Not enough arguments for crop filter" << std::endl;
                        throw std::exception();
                    } else {
                        if (!IsIntNumber(argv[i + 1])) {
                            std::cout << "Incorrect type of the first argument for crop" << std::endl;
                            throw std::exception();
                        } else {
                            width = std::atoi(argv[i + 1]);
                        }
                        if (i == argc - 2) {
                            std::cout << "Not enough arguments for crop filter" << std::endl;
                            throw std::exception();
                        } else {
                            if (!IsIntNumber(argv[i + 2])) {
                                std::cout << "Not a correct type of the second argument for crop" << std::endl;
                                throw std::exception();
                            } else {
                                height = std::atoi(argv[i + 2]);
                            }
                        }
                    }
                    i += 2;
                    Filter* filter = new CropFilter(width, height);
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-gs") == 0) {
                    Filter* filter = new GrayscaleFilter;
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-neg") == 0) {
                    Filter* filter = new NegativeFilter;
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-sharp") == 0) {
                    Filter* filter = new SharpeningFilter;
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-emb") == 0) {
                    Filter* filter = new EmbossFilter;
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-edge") == 0) {
                    double threshold;
                    if (i == argc - 1) {
                        std::cout << "Not enough arguments for edge filter" << std::endl;
                        throw std::exception();
                    } else {
                        if (!IsDoubleNumber(argv[i + 1])) {
                            std::cout << "Not a correct type of the first argument for edge detection" << std::endl;
                            throw std::exception();
                        } else {
                            threshold = std::atof(argv[i + 1]);
                        }
                    }
                    i++;
                    Filter* filter = new EdgeDetectionFilter(threshold);
                    filters.push_back(filter);
                } else if (strcmp(argv[i], "-blur") == 0) {
                    double sigma = 0;
                    if (i == argc - 1) {
                        std::cout << "Not enough arguments for gaussian blur" << std::endl;
                        throw std::exception();
                    } else {
                        if (!IsDoubleNumber(argv[i + 1])) {
                            std::cout << "Not a correct type of the first argument for blur" << std::endl;
                            throw std::exception();
                        } else {
                            sigma = std::atof(argv[i + 1]);
                        }
                    }
                    i++;
                    Filter* filter = new GaussFilter(sigma);
                    filters.push_back(filter);
                } else {
                    std::cout << "There is no filter with such name" << std::endl;
                    throw std::exception();
                }
            }
            for (auto filter : filters) {
                filter->Apply(picture);
            }
            for (auto filter : filters) {
                delete filter;
            }
            Export::exporting(argv[2], picture);
        }
    } catch (...) {}
    return 0;
}

