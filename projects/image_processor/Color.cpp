#include "Color.h"


Color::Color() : red(0), green(0), blue(0) {
}
Color::Color(unsigned char red, unsigned char green, unsigned char blue) : red(red), green(green), blue(blue) {
}
Color::~Color() {
}
bool Color::operator==(const Color& other) const {
    if (red == other.red && green == other.green && blue == other.blue) {
        return true;
    }
    return false;
}
