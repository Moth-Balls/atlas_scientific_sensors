#ifndef EC_SENSOR_H
#define EC_SENSOR_H

#include <cstdint>
#include <string>
#include <chrono>
#include <utility>

class EC_Sensor {
private:

    std::pair<float, std::chrono::time_point<std::chrono::system_clock>> ecValue;
    uint8_t ecAddress;
  
public:

    EC_Sensor(uint8_t ecAddress);
    void read(float temp);
    void calibrate_n();
    void calibrateDry();
    void calibrateLow();
    void calibrateHigh();
    std::pair<float, std::chrono::time_point<std::chrono::system_clock>> getEC();
    void setTempComp(float temp);

};

#endif /* EC_SENSOR_H */