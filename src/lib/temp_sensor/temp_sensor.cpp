#include "temp_sensor.h"
#include <wiringPi.h>
#include <wiringPiI2C.h> 
#include <stdexcept>


const char readCommand = 'R';
const std::string calibrateCommand = "Cal,100";
const std::string calibrateCheck = "Cal,?";
const std::string scaleCheck = "S,?";


Temp_Sensor::Temp_Sensor(uint8_t tempAddress) : tempAddress(tempAddress), tempValue(0.0, std::chrono::system_clock::now()) {

    int8_t result = wiringPiI2CSetup(tempAddress);
    if (result == -1) {
        std::string error = "Error setting up I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }

};


void Temp_Sensor::read() {

    /* Send read command */
    int8_t result = wiringPiI2CWrite(tempAddress, readCommand);
    if (result == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }
    delay(600); /* Delay for 600ms to allow the sensor to respond */

    /* Record temperature */
    tempValue.first = wiringPiI2CRead(tempAddress);

    /* Add a timestamp to the sensor reading */
    tempValue.second = std::chrono::system_clock::now();
}


void Temp_Sensor::calibrate() {

    /* Start Calibration */
    int8_t message = wiringPiI2CWrite(tempAddress, std::stoi(calibrateCommand));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }

    delay(600); /* Delay for 600ms for calibration to complete */

    /* Check if Calibration is complete */
    int8_t message = wiringPiI2CWrite(tempAddress, std::stoi(calibrateCheck));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }

    delay(600); /* Delay for 600ms to allow the sensor to respond */

    /* Read the response from the sensor */
    uint8_t response = wiringPiI2CRead(tempAddress);
    if (response == -1) {
        std::string error = "Error reading from I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }

    
}


std::string Temp_Sensor::checkScale() {

    /* Check the scale of the sensor */
    int8_t message = wiringPiI2CWrite(tempAddress, std::stoi(scaleCheck));
    if (message == -1) {
        std::string error = "Error writing to I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);
    }

    delay(300); /* Delay for 300ms to allow the sensor to respond */


    /* Read the response from the sensor */
     uint8_t response = wiringPiI2CRead(tempAddress);
    if (response == -1) {
        std::string error = "Error reading from I2C device at address: " + std::to_string(tempAddress);
        throw std::runtime_error(error);

    /* Convert the response to a string */
    std::string scale = std::to_string(response);

    return scale;
}
}

    /* Get the temperature value */
std::pair<float, std::chrono::system_clock::time_point> Temp_Sensor::getTemp() {
    return tempValue; 
}
