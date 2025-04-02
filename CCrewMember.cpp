#include "CrewMember.h"
#include "FlightCompException.h"
#include <utility>

int CCrewMember::countEmployNumber = 1000;

CCrewMember::CCrewMember(std::string employName, const CAddress& employAddress, const int airTime)
    : employName(std::move(employName)), airTime(airTime),
    employAddress(new CAddress(employAddress)),
    employNumber(START_ID + countEmployNumber++) {}

CCrewMember::CCrewMember(std::string employName, const CAddress& employAddress)
    : employName(std::move(employName)),
    employAddress(new CAddress(employAddress)),
    airTime(0), employNumber(countEmployNumber++) {}

CCrewMember::CCrewMember(std::string employName)
    : employName(std::move(employName)), airTime(0),
    employNumber(countEmployNumber++) {}

CCrewMember::CCrewMember(std::string employName, int airTime)
    : employName(std::move(employName)), airTime(airTime),
    employNumber(countEmployNumber++) {}

CCrewMember::CCrewMember(const CCrewMember& other)
    : employName(other.employName),
    airTime(other.airTime),
    employNumber(other.employNumber) {
    if (other.employAddress != nullptr) {
        this->employAddress = new CAddress(*other.employAddress);
    }
}

CCrewMember::~CCrewMember() {
    delete this->employAddress;
}

std::string CCrewMember::getEmployName() const {
    return employName;
}

int CCrewMember::getEmployNumber() const {
    return employNumber;
}


void CCrewMember::Print(std::ostream& os) const {
    os << "Name: " << employName << "\n"
        << "Air Time: " << airTime << std::endl;
}

bool CCrewMember::IsEqual(const CCrewMember& other) const {
    return other.employNumber == this->employNumber;
}

int CCrewMember::operator+=(int min) {
    if (min <= 0) {
        throw CCompStringException("Invalid air time: time must be positive.");
    }
    airTime += min;
    return airTime;
}


void CCrewMember::receiveHolidayGift() const {
    std::cout << employName << " received a holiday gift." << std::endl;
}

void CCrewMember::updateUniform() const {
    std::cout << employName << " received a new uniform." << std::endl;
}

void CCrewMember::takeoff(int minutes) {
    airTime += minutes;
    std::cout << employName << " updated air time after takeoff: " << airTime << " minutes." << std::endl;
}

void CCrewMember::takeoffNotification(int minutes) const {
    std::cout << employName << " is notified about the takeoff. Estimated flight duration: " << minutes << " minutes." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const CCrewMember& crew) {
    os << crew.getEmployName() << " " << crew.getEmployNumber();
    return os;
}
