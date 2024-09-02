#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <wiringPi.h>
#include <cstdint>

class Ph_Sensor {
private:

    int phValue;
    uint8_t phAddress;

public:

    Ph_Sensor(uint8_t phAddress);
    void read();
    void calibrate();
    void getPh();
    void setTempComp(float temp);
};
#endif /* PH_SENSOR_H */