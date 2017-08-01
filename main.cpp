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
    char error = wiringPiI2CSetup(BMP180_ADDR);
    if(!error) {
        std::cout << "[E]: Problem in I2C setup." << std::endl;
        return -1;
    }
    unsigned char data[2], result;

    data[0] = BMP180_REG_CONTROL;
    data[1] = BMP180_COMMAND_TEMPERATURE;

    error = wiringPiI2CWrite(BMP180_ADDR, data);
    if(!error) {
        std::cout << "[E]: Problem in writing." << std::endl;
        return -1;
    }

    char temperature = wiringPiI2CReadReg8(BMP180_ADDR, BMP180_REG_RESULT);
    std::cout << "Temperature: " << temperature << std::endl;
}