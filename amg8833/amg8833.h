#ifndef AMG883_H
#define AMG8833_H
#include <math.h>
#include "i2c/i2c.h"
#define AMG8833_I2CADDR 0x69
// Registers
//// Power control
#define AMG8833_PCTL 0x00
enum class AMG8833_PCTL_MODE {
    NORMAL = 0x00,
    SLEEP = 0x01,
    STAND_BY_60 = 0x20,
    STAND_BY_10 = 0x21
};
//// Reset
#define AMG8833_RST 0x01
enum class AMG8833_RST_MODE {
    FLAG = 0x30,
    INITIAL = 0x3F
};
//// Frames per second 
#define AMG8833_FPSC 0x02
enum class AMG8833_FPSC_MODE {
    _10HZ = 0x00,
    _1HZ = 0x01
};
//// Interrupt control
#define AMG8833_INTC 0x03
enum class AMG8833_INTC_MODE {
    DISABLED = 0x00,
    ENABLED = 0x01
};
//// Status
#define AMG8833_STAT 0x04
//// Status clear
#define AMG8833_SCLR 0x05
//// Moving average
#define AMG8833_AVE 0x07
//// Interrupt levels
////// High level (12 bits: 8 on HL, 4 on HH)
#define AMG8833_INTHL 0x08
#define AMG8833_INTHH 0x09
////// Low level (12 bits: 8 on LL, 4 on LH)
#define AMG8833_INTLL 0x0A
#define AMG8833_INTLH 0x0B
////// Hysteresis level (12 bits: 8 on L, 4 on H)
#define AMG8833_IHYSL 0x0C
#define AMG8833_IHYSH 0x0D
//// Thermistor temperature (12 bits: 8 on HL, 4 on HH)
#define AMG8833_TTHL 0x0E
#define AMG8833_TTHH 0x0F
//// Interrupt table (only define first and last)
#define AMG8833_INT0 0x10
#define AMG8833_INT7 0x17
//// Temperature table (only define first)
#define AMG8883_T01LH 0x80

// Conversion constants for temperatures
#define AMG8833_THERMISTOR_CONVERSION 0.0625
#define AMG8833_PIXEL_TEMPERATURE_CONVERSION 0.25

class AMG8833 { 
    public:
        AMG8833(const uint8_t bus);
        ~AMG8833();
        void wait(const int delay);
        bool error();
        bool setNormalMode();
        bool resetInitial();
        bool disableInterrupt();
        bool enableInterrupt();
        bool setFrameRate10Hz();
        bool setFrameRate1Hz();
        bool setMovingAverageMode();
        bool setInterruptLevelHigh(float high);
        bool setInterruptLevelLow(float low);
        bool setInterruptLevelHysteresis(float hyst);
        double thermistorTemperature();
        bool gridTemperature(double grid[64]);
    private:
        I2C i2c;
        bool err = false;
        double signed12BitToDouble(const uint16_t val);
};

AMG8833::AMG8833(const uint8_t bus) : i2c(bus, AMG8833_I2CADDR) {
    if (i2c.error()) {
        err = true;
    }
}

AMG8833::~AMG8833() {}

void AMG8833::wait(const int delay) {
    i2c.wait(delay);
}

bool AMG8833::error() {
    return err;
}

bool AMG8833::setNormalMode() {
    if(!i2c.write_byte(AMG8833_PCTL, (uint8_t)AMG8833_PCTL_MODE::NORMAL)) {
        return false;
    }
    return true;
}

bool AMG8833::resetInitial() {
    if(!i2c.write_byte(AMG8833_RST, (uint8_t)AMG8833_RST_MODE::INITIAL)) {
        return false;
    } 
    return true;
}

bool AMG8833::disableInterrupt() {
    if(!i2c.write_byte(AMG8833_INTC, (uint8_t)AMG8833_INTC_MODE::DISABLED)) {
        return false;
    } 
    return true;
}

bool AMG8833::setFrameRate10Hz() {
    if(!i2c.write_byte(AMG8833_FPSC, (uint8_t)AMG8833_FPSC_MODE::_10HZ)) {
        return false;
    } 
    return true;
}

bool AMG8833::setFrameRate1Hz() {
    if(!i2c.write_byte(AMG8833_FPSC, (uint8_t)AMG8833_FPSC_MODE::_1HZ)) {
        return false;
    } 
    return true;
}

double AMG8833::signed12BitToDouble(const uint16_t val) {
    uint16_t abs = (val & 0x7FF);
    return (val & 0x8000) ? 0.0 - (double)abs : (double)abs;
}

double AMG8833::thermistorTemperature() {
    return AMG8833_THERMISTOR_CONVERSION*signed12BitToDouble(i2c.read_word(AMG8833_TTHL));
}

bool AMG8833::gridTemperature(double grid[64]) {
    for (int i = 0; i < 64; i++) {
        uint8_t offset = AMG8883_T01LH+2*i;
        grid[i] = AMG8833_PIXEL_TEMPERATURE_CONVERSION*signed12BitToDouble(
                (uint16_t)(i2c.read_byte(offset+1) << 8 | i2c.read_byte(offset)));
    }
    return true;
};

#endif
