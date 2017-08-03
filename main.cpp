#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>

#include "common.h"
#include "BMP180.h"

int main(int argc, char* argv[]) {
    printf("Welcome to the weather station!\n");
    printf("--------------------------------------------\n");
    BMP180 station;
    station.Begin();

    while(1) {
        printf("Temperature: %.2f C\n", station.GetTemperature());
        printf("Pressure:    %.2f Pa\n\n", station.GetPressure());
        delay(1000);
    }
}
