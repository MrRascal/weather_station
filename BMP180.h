//
// Created by Nathan Levigne on 8/2/17.
//

#ifndef WEATHER_STATION_BMP180_H
#define WEATHER_STATION_BMP180_H

class BMP180 {
public:
    void BMP180();

    void Begin();

private:

    unsigned short ReadU16(int reg);

    short ReadS16(int reg);

    float GetTemperature();

    int fd_;
};

#endif //WEATHER_STATION_BMP180_H