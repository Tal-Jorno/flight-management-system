#ifndef CARGO_H
#define CARGO_H

#include <string>
#include <iostream>
#include "Plane.h"

class CCargo : public CPlane {
private:
    float maxWeight;
    float maxVolume;
    float currentWeight = 0;
    float currentVolume = 0;


public:
    CCargo(int seatCount,
        std::string model,
        float maxWeight,
        float maxVolume);

    CCargo(const CCargo& other) : CPlane(other),
        maxWeight(other.maxWeight),
        maxVolume(other.maxVolume),
        currentWeight(other.currentWeight),
        currentVolume(other.currentVolume) {};
    CCargo& operator=(const CCargo& other);
    ~CCargo();
    using CPlane::setSerialNumber;

    bool Load(float weight, float volume);
    void takeoff(int minutes);
};

#endif // CARGO_H
