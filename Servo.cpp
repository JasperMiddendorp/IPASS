#include "Servo.h"

void Servo::writeTemp(int temperature) {
    int angle;
    if(temperature < 15)
        angle = 180;
    else if(temperature > 30)
        angle = 0;
    else{
        angle = map(temperature, 15, 30, 180, 0);
    }
    servo.write_angle(angle);
}

void Servo::writeHum(int humidity){
    int angle;
    angle = map(humidity, 0, 100, 180, 0);
    servo.write_angle(angle);
}
