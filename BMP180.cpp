//
// Created by Nathan Levigne on 8/2/17.
//

#include <wiringPiI2C.h>
#include "BMP180.h"
#include "common.h"

void BMP180::Begin() {
    if(wiringPiSetup() < 0) {
        ERROR_LOG('Problem with setting up wiringPi');
    }
    fd_ = wiringPiI2CSetup(BMP180_Address);
    AC1 = ReadS16(BMP180_CAL_AC1);
    AC2 = ReadS16(BMP180_CAL_AC2);
    AC3 = ReadS16(BMP180_CAL_AC3);
    AC4 = ReadU16(BMP180_CAL_AC4);
    AC5 = ReadU16(BMP180_CAL_AC5);
    AC6 = ReadU16(BMP180_CAL_AC6);
    B1  = ReadS16(BMP180_CAL_B1);
    B2  = ReadS16(BMP180_CAL_B2);
    MB  = ReadS16(BMP180_CAL_MB);
    MC  = ReadS16(BMP180_CAL_MC);
    MD  = ReadS16(BMP180_CAL_MD);
}

unsigned short ReadU16(int reg) {
    int msb, lsb;
    msb = wiringPiI2CReadReg8(fd_, reg);
    lsb = wiringPiI2CReadReg8(fd_ , reg+1);
    int result = (msb << 8) + lsb;
    return (unsigned short) result;
}

short ReadS16(int reg) {
    int result;
    result = ReadU16(reg, BMP180_TEMPDATA);
    if (result > 32767)result -= 65536;
    return (short) result;
}

float GetTemperature() {
    float temperature;
    int UT, X1, X2, B5;

    wiringPiI2CWriteReg8(fd_ , BMP180_CONTROL, BMP180_READTEMPCMD);
    delay(5);
    UT = (wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA)  << 8) + wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA + 1);

    X1 = ((UT - AC6) * AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    T = ((B5 + 8) >> 4) / 10.0;

    return temperature;
}