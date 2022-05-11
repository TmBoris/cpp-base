#pragma once

struct Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Color();
    Color(unsigned char red, unsigned char green, unsigned char blue);
    ~Color();

    bool operator==(const Color& other) const;
};
