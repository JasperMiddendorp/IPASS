#include "hwlib.hpp"
#include "SI7021.h"

int main (){

    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto chip = SI7021(scl, sda);
    chip.setMode();


    for (;;) {
        hwlib::cout << "Hum: "
        << chip.readHum()
        << "%\n"
        << "Temp: "
        << chip.readTemp()
        << "C\n";
        hwlib::wait_ms(500);
    }



}
