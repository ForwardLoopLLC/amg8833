#ifndef AMG883_H
#define AMG8833_H
#define AMG8833_I2CADDR 0x69
// Registers
//// Power control
#define AMG8833_PCTL 0x00
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
//// Interrupt table (only define first and last)
#define AMG8833_INT0 0x10
#define AMG8833_INT7 0x17
//// Temperature table (only define first)
#define AMG8883_T01LH 0x80
#endif
