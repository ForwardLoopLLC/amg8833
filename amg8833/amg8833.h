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
//// Frames per second 
#define AMG8833_FPSC 0x02
//// Interrupt control
#define AMG8833_INTC 0x03
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
//// Interrupt pixel table (only define first and last)
describe the layout concisely here
#define AMG8833_INT0 0x10
//// Temperature pixel table (only define first)
#define AMG8883_T01LH 0x80

class AMG8833 { 
    public:
        AMG8833(const uint8_t bus);
        ~AMG8833();
        bool error();
        bool setNormalMode();
        bool setMovingAverageMode();
        bool enableInterrupt();
        bool disableinterrupt();
        bool setInterruptLevelHigh(float high);
        bool setInterruptLevelLow(float low);
        bool setInterruptLevelHysteresis(float hyst);
    private:
        I2C i2c;
        bool err = false;
};

AMG8833::AMG8833(const uint8_t bus) : i2c(bus, AMG8833_I2CADDR) {
    if (i2c.error()) {
        err = true;
    }
    // all statuses should be zero on start up
    if (i2c.read_byte(AMG8833_STAT) != 0x00) {
        err = true;
    }
}

AMG8833::~AMG8833() {}

bool AMG8833::error() {
    return err;
}

bool AMG8833::setNormalMode() {
    if(!i2c.write_byte(AMG8833_PCTL, (uint8_t)AMG8833_PCTL_MODE::NORMAL)) {
        return false;
    }
    return true;
}
#endif
