#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <csignal>

#include "BMP180.h"
#include "common.h"

BMP180::BMP180() {};

void BMP180::Begin(unsigned short pressure_mode) {
    mode_ = pressure_mode;
    if(wiringPiSetup() < 0) {
        ERROR_EXIT("Problem with setting up wiringPi");
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
    INFO_LOG("Calibration complete! \nNow recording...");
}

unsigned short BMP180::ReadU16(int reg) {
    int msb, lsb;
    msb = wiringPiI2CReadReg8(fd_, reg);
    lsb = wiringPiI2CReadReg8(fd_, reg+1);
    int result = (msb << 8) + lsb;
    return (unsigned short) result;
}

short BMP180::ReadS16(int reg) {
    int result;
    result = ReadU16(reg);
    if (result > 32767)result -= 65536;
    return (short) result;
}

float BMP180::GetTemperature() {
    float temperature;
    int UT, X1, X2, B5;

    wiringPiI2CWriteReg8(fd_, BMP180_CONTROL, BMP180_READTEMPCMD);
    delay(5);
    UT = (wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA)  << 8) + wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA + 1);

    X1 = ((UT - AC6) * AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    temperature = ((B5 + 8) >> 4) / 10.0;

    return temperature;
}

int BMP180::GetPressure() {
    int pressure, UT, UP, X1, X2, X3, B3, B5, B6, B7, msb, lsb, xlsb;;
    unsigned int B4;

    wiringPiI2CWriteReg8(fd_, BMP180_CONTROL, BMP180_READTEMPCMD);
    delay(5);

    UT = (wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA)  << 8) + wiringPiI2CReadReg8(fd_ , BMP180_TEMPDATA + 1);

    wiringPiI2CWriteReg8(fd_, BMP180_CONTROL, BMP180_READPRESSURECMD + (mode_ << 6));

    switch(mode_) {
        case BMP180_ULTRALOWPOWER:
            delay(5);
            break;
        case BMP180_HIGHRES:
            delay(14);
            break;
        case BMP180_ULTRAHIGHRES:
            delay(26);
            break;
        default :
            delay(8);
    }

    msb  = wiringPiI2CReadReg8(fd_, BMP180_PRESSUREDATA);
    lsb  = wiringPiI2CReadReg8(fd_, BMP180_PRESSUREDATA + 1);
    xlsb = wiringPiI2CReadReg8(fd_, BMP180_PRESSUREDATA + 2);
    UP = ((msb << 16) + (lsb << 8) + xlsb) >> (8 - mode_);

    X1 = ((UT - AC6) * AC5) >> 15;
    X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;

    //Pressure Calculations
    B6 = B5 - 4000;
    X1 = (B2 * (B6 * B6) >> 12) >> 11;
    X2 = (AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((AC1 * 4 + X3) << mode_) + 2) / 4;
    X1 = (AC3 * B6) >> 13;
    X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (AC4 * (X3 + 32768)) >> 15;
    B7 = (UP - B3) * (50000 >> mode_);
    if (B7 < 0x80000000) {
        pressure = (B7 * 2) / B4;
    } else {
        pressure = (B7 / B4) * 2;
    }
    X1 = (pressure >> 8) * (pressure >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * pressure) >> 16;
    pressure = pressure + ((X1 + X2 + 3791) >> 4);
    return pressure;
}
