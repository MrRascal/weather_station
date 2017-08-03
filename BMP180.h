//
// Created by Nathan Levigne on 8/2/17.
//

#ifndef BMP180_H
#define BMP180_H

//i2c address
#define BMP180_Address 0x77

//Operating Modes
#define BMP180_ULTRALOWPOWER    0
#define BMP180_STANDARD         1
#define BMP180_HIGHRES          2
#define BMP180_ULTRAHIGHRES     3

//BMP185 Registers
#define BMP180_CAL_AC1          0xAA  //Calibration data (16 bits)
#define BMP180_CAL_AC2          0xAC  //Calibration data (16 bits)
#define BMP180_CAL_AC3          0xAE  //Calibration data (16 bits)
#define BMP180_CAL_AC4          0xB0  //Calibration data (16 bits)
#define BMP180_CAL_AC5          0xB2  //Calibration data (16 bits)
#define BMP180_CAL_AC6          0xB4  //Calibration data (16 bits)
#define BMP180_CAL_B1           0xB6  //Calibration data (16 bits)
#define BMP180_CAL_B2           0xB8  //Calibration data (16 bits)
#define BMP180_CAL_MB           0xBA  //Calibration data (16 bits)
#define BMP180_CAL_MC           0xBC  //Calibration data (16 bits)
#define BMP180_CAL_MD           0xBE  //Calibration data (16 bits)
#define BMP180_CONTROL          0xF4
#define BMP180_TEMPDATA         0xF6
#define BMP180_PRESSUREDATA     0xF6

//Commands
#define BMP180_READTEMPCMD      0x2E
#define BMP180_READPRESSURECMD  0x34
#define OSS BMP180_STANDARD

class BMP180 {
public:
    BMP180();

    void Begin();

    float GetTemperature();

private:

    unsigned short ReadU16(int reg);

    short ReadS16(int reg);

    int fd_;
    short AC1,AC2,AC3,B1,B2,MB,MC,MD;
    unsigned short AC4,AC5,AC6;
};

#endif //WEATHER_STATION_BMP180_H
