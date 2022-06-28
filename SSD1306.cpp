#include "SSD1306.h"

void SSD1306::printBottom(hwlib::string<15> str, int integer) {
    clear(bottom);
    bottom << str << integer << hwlib::flush;

}

void SSD1306::printTop(hwlib::string<15> str, int integer) {
    clear(top);
    top << str << integer << hwlib::flush;
}

void SSD1306::clear(hwlib::terminal_from & screen) {
    screen << "\f" << hwlib::flush;
}