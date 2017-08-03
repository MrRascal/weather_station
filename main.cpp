#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>

#include "common.h"
#include "BMP180.h"

int main(int argc, char* argv[]) {
    printf("Welcome to the weather station!");
    printf("--------------------------------------------");
    BMP180 station;
    station.Begin();

    while(1) {
        printf("Temperature: %.2f C\n", station.GetTemperature());
        delay(1000);
    }
}
