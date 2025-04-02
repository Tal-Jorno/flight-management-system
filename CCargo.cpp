#include "Cargo.h"
#include "Plane.h"
#include "FlightCompException.h"


CCargo::CCargo(int seatCount, std::string model, float maxWeight, float maxVolume)
    : CPlane(seatCount, model, CARGO), maxWeight(maxWeight), maxVolume(maxVolume) {
    if (maxWeight <= 0 || maxVolume <= 0) {
        throw CCompStringException("Invalid cargo plane: weight and volume must be positive.");
    }
}

CCargo& CCargo::operator=(const CCargo& other) {
    CPlane::operator=(other);
    if (this != &other) {
        maxWeight = other.maxWeight;
        maxVolume = other.maxVolume;
        currentWeight = other.currentWeight;
        currentVolume = other.currentVolume;
    }
    return *this;
}

CCargo::~CCargo() {}

bool CCargo::Load(float weight, float volume) {
    if ((currentWeight + weight <= maxWeight) && (currentVolume + volume <= maxVolume)) {
        currentWeight += weight;
        currentVolume += volume;
        return true;
    }
    return false;
}

void CCargo::takeoff(int minutes) {
    std::cout << "Need to add " << minutes << " to my log book" << std::endl;
}
