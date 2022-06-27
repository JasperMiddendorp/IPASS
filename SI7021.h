#ifndef V1OOPC_EXAMPLES_SI7021_H
#define V1OOPC_EXAMPLES_SI7021_H
#include "hwlib.hpp"


#define MEASURE_HUM_NOHOLD 0xF5
#define MEASURE_TEMP_NOHOLD 0xF3
#define WRITE_REGISTER 0xE6
#define READ_REGISTER 0xE7


class SI7021 {
private:
    hwlib::i2c_bus_bit_banged_scl_sda bus;
    uint8_t address = 0x40;

public:
    // Constructor
    SI7021(hwlib::target::pin_oc & scl, hwlib::target::pin_oc & sda, uint8_t address = 0x15) : bus(hwlib::i2c_bus_bit_banged_scl_sda(scl, sda)), address(0x40) {}

    uint8_t readRegister();
    void writeRegister(uint8_t byte);
    int readTemp();
    int readHum();
    uint16_t readData(uint8_t command);
    void setMode();
};


#endif
