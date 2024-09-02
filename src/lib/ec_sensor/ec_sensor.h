#ifndef EC_SENSOR_H
#define EC_SENSOR_H

#include <wiringPi.h>
#include <cstdint>
#include <utility>

class EC_Sensor {
private:

    int ecValue;
    uint8_t ecAddress;

public:

    EC_Sensor(uint8_t ecAddress);
    void read();
    void calibrate();
    void getEC();
    void setTempComp(float temp);
};
#endif /* EC_SENSOR_H */