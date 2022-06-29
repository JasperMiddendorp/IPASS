#ifndef V1OOPC_EXAMPLES_SERVO_H
#define V1OOPC_EXAMPLES_SERVO_H
#include "hwlib.hpp"

/// @file

/// \brief
/// Servo klasse
/// \details
/// Dit is een klasse die de Servo's aanstuurt met gebruik van hwlib::servo_background.
class Servo {
private:
    hwlib::servo_background servo;

public:

    /// \brief
    /// Constructor
    /// \details
    /// In de constructor geef je een de pin mee die je wilt aansturen.
    Servo(hwlib::pin_out & pin) : servo(pin) {}

    /// \brief
    /// Write Temperatuur
    /// \details
    /// Deze functie neemt één argument, de temperatuur en zet het om doormiddels van de 'map' functie te gebruiken.
    /// De nieuwe geschaalde angle is dan van 0 tot 180 --> 15 tot 30
    void writeTemp(int temperature);

    /// \brief
    /// Write Humidity
    /// \details
    /// Deze functie neemt één argument, de humidity en zet het om doormiddels van de 'map' functie te gebruiken.
    /// De nieuwe geschaalde angle is dan van 0 tot 180 --> 0 tot 100
    void writeHum(int humidity);

    /// \brief
    /// Map
    /// \details
    /// Deze functie heb ik gebruikt van de originele arduino IDE die de output kan schalen naar een nieuwe
    /// schaal.
    /// link : https://www.arduino.cc/reference/en/language/functions/math/map/
    static long map(long x, long in_min, long in_max, long out_min, long out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

};


#endif
