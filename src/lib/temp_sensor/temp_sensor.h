#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <cstdint>
#include <string>
#include <chrono>
#include <utility>

class Temp_Sensor {
private:

    std::pair<float, std::chrono::system_clock::time_point> tempValue;
    uint8_t tempAddress;

public:

    Temp_Sensor(uint8_t tempAddress);
    void read();
    void calibrate();
    std::string checkScale();
    std::pair<float, std::chrono::system_clock::time_point> getTemp();
};

#endif /* TEMP_SENSOR_H */