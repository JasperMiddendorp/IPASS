#ifndef V1OOPC_EXAMPLES_SI7021_H
#define V1OOPC_EXAMPLES_SI7021_H
#include "hwlib.hpp"

#define ADDRESS 0x40
#define MEASURE_HUM_NOHOLD 0xF5
#define MEASURE_TEMP_NOHOLD 0xF3
#define WRITE_REGISTER 0xE6
#define READ_REGISTER 0xE7

/// @file

/// \brief
/// SI7021 temperatuur en luchtvochtigheids meter klasse
/// \details
/// Dit is een klasse die de SI7021 aanstuurt.
/// Deze klasse communiceert met de chip door gebruik te maken van de hwlib i2c transacties.
class SI7021 {
private:
    hwlib::i2c_bus_bit_banged_scl_sda bus;
    uint8_t address = ADDRESS;

    /// \brief
    /// Read Register
    /// \details
    /// Deze functie schrijft als eerste byte het chip ADDRESS en volgt daarna met het
    /// schrijven van het READREGISTER byte.
    /// Daarna schrijft hij weer als eerste byte het chip ADDRESS en volgt daarna door het volgend verstuurde byte uit te lezen.
    uint8_t readRegister();

    /// \brief
    /// Write Register
    /// \details
    /// Deze functie maakt gebruik van één meegegeven 'byte' en schrijft het naar het register.
    /// Eerst schrijft hij het ADDRESS byte naar de chip en daarna schrijft hij het WRITEREGISTER byte en
    /// het argument 'byte'
    void writeRegister(uint8_t byte);

    /// \brief
    /// Read Data
    /// \details
    /// Deze functie begint het met sturen van het ADDRESS byte en daarna schrijft hij het meegegeven 'command'
    /// Dan wacht hij 100ms (ruim gegrepen, chip heeft +- 22ms nodig om te meten).
    /// Daarna schrijft hij weer het ADDRESS byte en ontvangt hij 2 bytes van de chip (de msb en lsb).
    /// Over de lsb doe je een &= mask (0b11111100) en schuif je de 2 bytes naast elkaar om er 1x 16 bits van te maken.
    uint16_t readData(uint8_t command);

public:

    /// \brief
    /// Constructor
    /// \details
    /// In de constructor geef je twee hwlib waardes mee, de SCL pin en de SDA.
    /// De constructor zet het om naar een bit banged i2c bus.
    SI7021(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda) : bus(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)) {}

    /// \brief
    /// Read Temperatuur
    /// \details
    /// Deze functie roept de 'readData' functie aan met als argument MEASURE_TEMP_NOHOLD (nohold gebruiken, anders gebruikt hij clock stretching)
    /// Daarna maakt het gebruik van deze formule uit de datasheet om er een leesbaar getal van te maken:
    /// ((175.72*xxx/65536)-46.85) en geeft het leesbare getal in graden celsius terug.
    int readTemp();

    /// \brief
    /// Read Humidity
    /// \details
    /// Deze functie roept de 'readData' functie aan met als argument MEASURE_HUM_NOHOLD (nohold gebruiken, anders gebruikt hij clock stretching)
    /// Daarna maakt het gebruik van deze formule uit de datasheet om er een leesbaar getal van te maken:
    /// ((125.0*Hum/65536)-6) en geeft het leesbare getal in percentage luchtvochtigheid terug.
    int readHum();

    /// \brief
    /// Set Mode
    /// \details
    /// Deze functie leest het huidige register en zet er een &= mask overheen.
    /// Deze mask kan je veranderen om de 'readData' in andere vormen bits te krijgen.
    /// Daarna schrijft het de nieuwe getal naar het register.
    void setMode();
};


#endif
