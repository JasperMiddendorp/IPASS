#include "hwlib.hpp"
#include "SI7021.h"
#include "SSD1306.h"
#include "Servo.h"

int main (){

    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto chip = SI7021(scl, sda);
    chip.setMode();

    auto oled = SSD1306(scl, sda);

    auto pinTempServo = hwlib::target::pin_out(hwlib::target::pins::d3);
    auto pinHumServo = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto tempServo = Servo(pinTempServo);
    auto humServo = Servo(pinHumServo);

    for (;;) {
        int hum = chip.readHum();
        int temp = chip.readTemp();

        hwlib::wait_ms(250);
        humServo.writeHum(hum);
        hwlib::wait_ms(100);
        tempServo.writeTemp(temp);
        hwlib::wait_ms(250);

        oled.printTemp(temp);
        oled.printHum(hum);
    }



}
