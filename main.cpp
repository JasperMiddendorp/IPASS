#include "hwlib.hpp"
#include "SI7021.h"
#include "SSD1306.h"

int main (){

    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto chip = SI7021(scl, sda);
    chip.setMode();

    auto oled = SSD1306(scl, sda);


    for (;;) {
        int hum = chip.readHum();
        int temp = chip.readTemp();
        hwlib::string<15> humString = "Hum: ";
        hwlib::string<15> tempString = "Temp: ";

        oled.printTop(humString, hum);,
        oled.printBottom(tempString, temp);
//        hwlib::cout << "Hum: "
//        << hum
//        << "%\n"
//        << "Temp: "
//        << temp
//        << "C\n";
    }



}
