//
// Created by Nathan Levigne on 8/2/17.
//

#ifndef BMP180_H
#define BMP180_H

class BMP180 {
public:
    BMP180();

    void Begin();

    float GetTemperature();

private:

    unsigned short ReadU16(int reg);

    short ReadS16(int reg);

    int fd_;
};

#endif //WEATHER_STATION_BMP180_H
