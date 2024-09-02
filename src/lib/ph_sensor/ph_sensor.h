#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <cstdint>
#include <string>
#include <chrono>
#include <utility>

class Ph_Sensor {
private:

    std::pair<float, std::chrono::time_point<std::chrono::system_clock>> phValue;
    uint8_t phAddress;

public:

    Ph_Sensor(uint8_t phAddress);
    void read(float temp);
    void calibrateLow();
    void calibrateMid();
    void calibrateHigh();
    std::pair<float, std::chrono::time_point<std::chrono::system_clock>> getPh();
    void setTempComp(float temp);
};

#endif /* PH_SENSOR_H */