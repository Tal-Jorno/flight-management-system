#include "FlightInfo.h"
#include "FlightCompException.h"

CFlightInfo::CFlightInfo(const std::string destination, const int flightNumber, const int flightDuration, const int distance)
    : flightNumber(flightNumber), flightDuration(flightDuration), distance(distance) {
    if (!SetDest(destination)) {
        throw CCompStringException("Invalid destination string.");
    }
    if (!setFlightDuration(flightDuration) || !setDistance(distance)) {
        throw CCompStringException("Invalid flight details provided.");
    }
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
    : destination(other.destination), flightNumber(other.flightNumber), flightDuration(other.flightDuration), distance(other.distance) {}

CFlightInfo::~CFlightInfo() {}

int CFlightInfo::getFlightNumber() const {
    return flightNumber;
}

std::string CFlightInfo::getDestination() const {
    return destination;
}

int CFlightInfo::getFlightDuration() const {
    return flightDuration;
}

int CFlightInfo::getDistance() const {
    return distance;
}

int CFlightInfo::GetFNum() {
    return flightNumber;
}

bool CFlightInfo::SetDest(std::string destination) {
    if (destination.empty() || destination.length() > 100) {
        throw CCompStringException("Destination string is either empty or too long.");
    }
    this->destination = destination;
    return true;
}

bool CFlightInfo::setFlightDuration(int flightDuration) {
    if (flightDuration < 15 || flightDuration > 1800) {
        return false;
    }
    this->flightDuration = flightDuration;
    return true;
}

bool CFlightInfo::setDistance(int distance) {
    if (distance < 100 || distance > 20000) {
        return false;
    }
    this->distance = distance;
    return true;
}


void CFlightInfo::Print() const {
    std::cout << "Flight Number: " << flightNumber << "\n"
        << "Destination: " << destination << "\n"
        << "Distance: " << distance << "\n"
        << "Flight Duration: " << flightDuration << std::endl;
}

bool CFlightInfo::isEqual(const CFlightInfo& other) const {
    return other.flightNumber == this->flightNumber;
}

std::ostream& operator<<(std::ostream& os, const CFlightInfo& flightInfo) {
    os << "Flight Number: " << flightInfo.flightNumber << "\n Destination: " << flightInfo.destination << std::endl;
    os << "Flight Duration: " << flightInfo.flightDuration << "\nDistance: " << flightInfo.distance << std::endl;
    return os;
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const {
    return (flightNumber != other.flightNumber) ||
        (distance != other.distance) ||
        (destination != other.destination) ||
        (flightDuration != other.flightDuration);
}

CFlightInfo::operator int() const {
    return flightDuration;
}

