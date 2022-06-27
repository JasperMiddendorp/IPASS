#include "SI7021.h"

uint8_t SI7021::readRegister() {
    uint8_t result;
    { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(address);
        wtrans.write(READ_REGISTER);
        }
    { hwlib::i2c_read_transaction rtrans = ((hwlib::i2c_bus*)(&bus))->read(address);
        rtrans.read(result);}
    return result;
}

void SI7021::writeRegister(uint8_t byte) {
    { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(address);
        wtrans.write(WRITE_REGISTER);
        wtrans.write(byte);}
}

int SI7021::readTemp() {
    uint16_t temp = readData(MEASURE_TEMP_NOHOLD);
    float result = ((175.72*temp/65536)-46.85);
    return int(result);
}

int SI7021::readHum()
{
    uint16_t Hum = readData(MEASURE_HUM_NOHOLD);
    float result = ((125.0*Hum/65536)-6);
    return int(result);
}

uint16_t SI7021::readData(uint8_t command) {
    uint8_t results[3];

    { hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(address);
        wtrans.write(command);}
    hwlib::wait_ms(100);
    { hwlib::i2c_read_transaction rtrans = ((hwlib::i2c_bus*)(&bus))->read(address);
        rtrans.read(results, 3);}

    uint8_t msb = results[0];
    uint8_t lsb = results[1];
    lsb &= 0b11111100;
    unsigned int data = msb << 8 | lsb;

    return data;
}

void SI7021::setMode() {
    uint8_t regVal = readRegister();
    regVal &= 0b011111110;
    writeRegister(regVal);
}