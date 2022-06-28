#include "SSD1306.h"

void SSD1306::printHum(int hum) {
    clear(bottom);
    bottom << hum << "%" << hwlib::flush;

}

void SSD1306::printTemp(int temp) {
    clear(top);
    top << temp << "C" << hwlib::flush;
}

void SSD1306::clear(hwlib::terminal_from & screen) {
    screen << "\f" << hwlib::flush;
}