#include "ec_sensor.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdexcept>

const char readCommand = 'R';
const std::string readValue_TempComp = "RT,";
const std::string calibrateNCommand = "Cal,";
const std::string calibrateDryCommand = "Cal,dry";
const std::string calibrateLowCommand = "Cal,low";
const std::string calibrateHighCommand = "Cal,high";
const std::string calibrateCheck = "Cal,?";
const std::string tempCompCommand = "T,";


EC_Sensor::EC_Sensor(uint8_t ecAddress) : ecAddress(ecAddress), ecValue(0.0, std::chrono::system_clock::now()) {

    int8_t result = wiringPiI2CSetup(ecAddress);
    if (result == -1) {
        std::string error = "Error setting up I2C device at address: " + std::to_string(ecAddress);
        throw std::runtime_error(error);
    }

};

void EC_Sensor::read(float temp) {

    /* Add temperature to read command */
    std::string command = readValue_TempComp + std::to_string(temp);

    /* Send read command */
    int8_t result = wiringPiI2CWrite(ecAddress, std::stoi(command));
    if (result == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(ecAddress);
        throw std::runtime_error(error);
    }
    delay(900); /* Delay for 900ms to allow the sensor to respond */

    /* Record EC */
    ecValue.first = wiringPiI2CRead(ecAddress);

    /* Add a timestamp to the sensor reading */
    ecValue.second = std::chrono::system_clock::now();
}

    /* Calibrating any point */

void EC_Sensor::calibrate_n() {}

void EC_Sensor::calibrateDry() {

    /* Start calibrate dry command */
    int8_t message = wiringPiI2CWrite(ecAddress, std::stoi(calibrateDryCommand));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(ecAddress);
        throw std::runtime_error(error);
    }

    delay(600); /* Delay for 600ms before next command */
}

    /* Calibrating low EC point */

void EC_Sensor::calibrateLow() {
    
        /* Start calibrate low command */
        int8_t message = wiringPiI2CWrite(ecAddress, std::stoi(calibrateLowCommand));
        if (message == -1) {
            std::string error = "Error writing to I2C device at address: " + std::to_string(ecAddress);
            throw std::runtime_error(error);
        }
    
        delay(900); /* Delay for 900ms before next command */
    }
    
    /* Calibrating high EC point */

void EC_Sensor::calibrateHigh() {
    
        /* Start calibrate high command */
        int8_t message = wiringPiI2CWrite(ecAddress, std::stoi(calibrateHighCommand));
        if (message == -1) {
            std::string error = "Error writing to I2C device at address: " + std::to_string(ecAddress);
            throw std::runtime_error(error);
        }
    
        delay(900); /* Delay for 900ms before next command */
    }

void EC_Sensor::setTempComp(float temp) {
    
        /* Add temperature to temp comp command */
        std::string command = tempCompCommand + std::to_string(temp);
    
        /* Send temp comp command */
        int8_t result = wiringPiI2CWrite(ecAddress, std::stoi(command));
        if (result == -1) {
            std::string error = "Error writing to I2C device at address: " + std::to_string(ecAddress);
            throw std::runtime_error(error);
        }
        delay(900); /* Delay for 900ms to allow the sensor to respond */
}

std::pair<float, std::chrono::time_point<std::chrono::system_clock>> EC_Sensor::getEC() {
    return ecValue;
}




