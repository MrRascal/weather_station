#include <wiringPiI2C.h>
#include <iostream>

#define BMP180_ADDR 0x77 // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4

int main(int argc, char* argv[]) {
    int error = wiringPiI2CSetup(BMP180_ADDR);
    if(!error) {
        std::cout << "[E]: Problem in I2C setup." << std::endl;
        return -1;
    }
    int data[2], result;

    error = wiringPiI2CWrite(BMP180_ADDR, BMP180_REG_CONTROL);
    if(!error) {
        std::cout << "[E]: Problem in writing." << std::endl;
        return -1;
    }

    error = wiringPiI2CWrite(BMP180_ADDR, BMP180_COMMAND_TEMPERATURE);
    if(!error) {
        std::cout << "[E]: Problem in writing." << std::endl;
        return -1;
    }

    int temperature = wiringPiI2CReadReg8(BMP180_ADDR, BMP180_REG_RESULT);
    std::cout << "Temperature: " << temperature << std::endl;
}