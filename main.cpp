// main.cpp
// Purpose: Prints and logs temperature and pressure data from a BMP180 sensor connected to a raspberry pi.
// Author: Nathan Levigne

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <time.h>
#include <chrono>

#include "common.h"
#include "BMP180.h"

namespace {
    volatile bool stop_signal_caught = false;

    void SignalHandler(int signum) {
        if(signum == SIGINT || signum == SIGTERM) {
            stop_signal_caught = true;
        }
    }
}

std::string CreateFileName() {
    return "log";
    /*
    char buf[64];
    std::chrono::system_clock::time_point today = system_clock::now();
    time_t tm = system_clock::to_time_t (today);
    return std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", tm);
     */
}

int main(int argc, char* argv[]) {
    float temperature;
    int pressure;

    // Initialize signal handlers
    std::signal(SIGINT, SignalHandler);
    std::signal(SIGTERM, SignalHandler);

    printf("Welcome to the weather station!\n");
    printf("--------------------------------------------\n");

    // Create log file
    std::ostringstream tmp;
    tmp << CreateFileName() << ".txt";
    std::ofstream file_weather(tmp.str());

    // Initialize BMP180 for recording
    BMP180 station;
    station.Begin(1);

    // Constantly read and write to file
    while(!stop_signal_caught) {
        temperature = station.GetTemperature();
        pressure = station.GetPressure();

        file_weather << temperature << " " << pressure << "\n";

        printf("Temperature: %.2f C | Pressure:    %d Pa\r", temperature, pressure);
        delay(1000);
    }
    file_weather.close();
    INFO_LOG("Stop recording and file saved.");
}
