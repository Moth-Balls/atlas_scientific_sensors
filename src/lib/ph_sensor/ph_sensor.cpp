#include "ph_sensor.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdexcept>

const char readCommand = 'R';
const std::string readValue_TempComp = "RT,";
const std::string calibrateLowCommand = "Cal,mid,4.00";
const std::string calibrateMidCommand = "Cal,mid,7.00";
const std::string calibrateHighCommand = "Cal,mid,10.00";
const std::string calibrateCheck = "Cal,?";
const std::string tempCompCommand = "T,";

Ph_Sensor::Ph_Sensor(uint8_t phAddress) : phAddress(phAddress), phValue(0.0, std::chrono::system_clock::now()) {

    int8_t result = wiringPiI2CSetup(phAddress);
    if (result == -1) {
        std::string error = "Error setting up I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }

};

void Ph_Sensor::read(float temp) {

    /* Add temperature to read command */
    std::string command = readValue_TempComp + std::to_string(temp);

    /* Send read command */
    int8_t result = wiringPiI2CWrite(phAddress, std::stoi(command));
    if (result == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }
    delay(900); /* Delay for 900ms to allow the sensor to respond */

    /* Record pH */
    phValue.first = wiringPiI2CRead(phAddress);

    /* Add a timestamp to the sensor reading */
    phValue.second = std::chrono::system_clock::now();
}

    /* Calibrating low pH point (4.00) */
void Ph_Sensor::calibrateLow() {

    /* Start calibrate low command */
    int8_t message = wiringPiI2CWrite(phAddress, std::stoi(calibrateLowCommand));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }

    delay(900); /* Delay for 900ms before next command */
}

    /* Calibrating mid pH point (7.00) */
void Ph_Sensor::calibrateMid() {


    /* Send calibrate mid command */
    int8_t message = wiringPiI2CWrite(phAddress, std::stoi(calibrateMidCommand));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }

    delay(900); /* Delay for 900ms before next command */
}

    /* Calibrating high pH point (10.00) */
void Ph_Sensor::calibrateHigh() {

    /* Send calibrate high command */
    int8_t message = wiringPiI2CWrite(phAddress, std::stoi(calibrateHighCommand));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }

    delay(900); /* Delay for 900ms before next command */
}

void Ph_Sensor::setTempComp(float temp) {

    /* Add temperature to tempComp command */
    std::string command = tempCompCommand + std::to_string(temp);

    /* Set temp comp */
    int8_t result = wiringPiI2CWrite(phAddress, std::stoi(command));
    if (result == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(phAddress);
        throw std::runtime_error(error);
    }
    delay(900); /* Delay for 900ms to allow the sensor to respond */

}

std::pair<float, std::chrono::time_point<std::chrono::system_clock>> Ph_Sensor::getPh() {
    return phValue;
}

