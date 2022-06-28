#ifndef V1OOPC_EXAMPLES_SSD1306_H
#define V1OOPC_EXAMPLES_SSD1306_H
#include "hwlib.hpp"


class SSD1306 {
private:
    hwlib::i2c_bus_bit_banged_scl_sda bus;
    hwlib::glcd_oled oled = hwlib::glcd_oled(bus, 0x3c);

    hwlib::window_part_t topScreen = hwlib::window_part_t(oled, hwlib::xy(5,28), hwlib::xy(63, 64));
    hwlib::window_part_t bottomScreen = hwlib::window_part_t(   oled, hwlib::xy(70,28), hwlib::xy(128, 64));
    hwlib::window_part_t headerScreen = hwlib::window_part_t(oled, hwlib::xy(10,0), hwlib::xy(128, 10));

    hwlib::font_default_8x8 font8 = hwlib::font_default_8x8();
    hwlib::font_default_16x16 font16 = hwlib::font_default_16x16();

    hwlib::terminal_from top = hwlib::terminal_from(topScreen, font16);
    hwlib::terminal_from bottom = hwlib::terminal_from(bottomScreen, font16);
    hwlib::terminal_from header = hwlib::terminal_from(headerScreen, font8);


public:

    SSD1306(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda) : bus(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {
        clear(top);
        clear(bottom);
        clear(header);
        header << "Temp:    Hum:" << hwlib::flush;
    }

    void printTemp(int temp);
    void printHum(int hum);
    void clear(hwlib::terminal_from & screen);
};


#endif