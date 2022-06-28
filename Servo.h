#ifndef V1OOPC_EXAMPLES_SERVO_H
#define V1OOPC_EXAMPLES_SERVO_H
#include "hwlib.hpp"


class Servo {
private:
    hwlib::servo_background servo;

public:

    Servo(hwlib::pin_out & pin) : servo(pin) {}

    void writeTemp(int temperature);
    void writeHum(int humidity);

    static long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

};


#endif
