#ifndef V1OOPC_EXAMPLES_SSD1306_H
#define V1OOPC_EXAMPLES_SSD1306_H
#include "hwlib.hpp"


/// @file

/// \brief
/// SSD1306 Oled klasse
/// \details
/// Dit is een klasse die de SSD1306 128x64 aanstuurt.
/// Deze klasse is speciaal gemaakt om 2 waardes naast elkaar weer te geven, met daarboven text wat het is.
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

    /// \brief
    /// Constructor
    /// \details
    /// In de constructor geef je twee hwlib waardes mee, de SCL pin en de SDA.
    /// De constructor zet het om naar een bit banged i2c bus.
    /// Ook wordt er bij het aanmaken alle schermen geleegd en wordt de tekst aan de bovenkant weergegeven en nooit meer refreshed.
    /// Dit zorgt ervoor dat het scherm niet steeds dat deel hoeft te updaten en dus ook niet knippert.
    SSD1306(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda) : bus(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {
        clear(top);
        clear(bottom);
        clear(header);
        header << "Temp:    Hum:" << hwlib::flush;
    }

    /// \brief
    /// Print Temperatuur
    /// \details
    /// Deze functie heeft als argument één integer (in dit geval 'temperatuur') nodig.
    /// Dat geeft hij dan weer op het linker kant van het scherm.
    void printTemp(int temp);

    /// \brief
    /// Print Humidity
    /// \details
    /// Deze functie heeft als argument één integer (in dit geval 'humidity') nodig.
    /// Dat geeft hij dan weer op het rechter kant van het scherm.
    void printHum(int hum);

    /// \brief
    /// Clear
    /// \details
    /// Deze functie heeft als argument één terminal (deel van het scherm) en leegt dat terminal.
    void clear(hwlib::terminal_from & screen);
};


#endif