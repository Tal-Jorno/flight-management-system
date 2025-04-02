#include "Pilot.h"

CPilot::CPilot(const std::string& name, bool isCaptain, CAddress* address)
    : CCrewMember(name), isCaptain(isCaptain), address(address ? new CAddress(*address) : nullptr) {}

CPilot::CPilot(const CPilot& other)
    : CCrewMember(other), isCaptain(other.isCaptain),
    address(other.address ? new CAddress(*other.address) : nullptr) {}

CPilot& CPilot::operator=(const CPilot& other) {
    if (this != &other) {
        CCrewMember::operator=(other);
        isCaptain = other.isCaptain;
        delete address;
        address = other.address ? new CAddress(*other.address) : nullptr;
    }
    return *this;
}

CPilot::~CPilot() {
    delete address;
}

void CPilot::takeoff(int minutes) {
    if (isCaptain) {
        airTime += minutes + (minutes / 10);  // Captains get 10% more air time
    }
    else {
        airTime += minutes;
    }
    std::cout << employName << " is ready for takeoff. Updated air time: " << airTime << " minutes." << std::endl;
}

void CPilot::receiveHolidayGift() const {
    std::cout << employName << " thanking the company for receiving the holiday gift." << std::endl;
}

void CPilot::updateUniform() const {
    std::cout << employName << " this is the fifth time I get a new uniform this is a waste of money!" << std::endl;
}

void CPilot::takeoffNotification(int minutes) const {
    std::cout << "Pilot " << employName << " notified about takeoff. Estimated flight time: " << minutes << " minutes."
        << std::endl;
}

std::string CPilot::getName() const {
    return this->employName;
}

void CPilot::simulatorNotification() const {
    std::cout << "Pilot" << employName << " to the simulator";
}

CCrewMember* CPilot::clone() const {
    return new CPilot(*this);
}

int CPilot::operator+=(int minutes) {
    if (isCaptain) {
        airTime += minutes + (minutes / 10);  // Captains get 10% more air time
    }
    else {
        airTime += minutes;
    }
    return airTime;
}
