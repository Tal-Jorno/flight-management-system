#include "Host.h"

CHost::CHost(const std::string& name, HostType type)
    : CCrewMember(name), type(type) {}

CHost::CHost(const CHost& other)
    : CCrewMember(other), type(other.type) {}

CHost& CHost::operator=(const CHost& other) {
    if (this != &other) {
        CCrewMember::operator=(other);
        type = other.type;
    }
    return *this;
}

CHost::~CHost() {}

void CHost::takeoff(int minutes) {
    airTime += minutes;
    std::cout << employName << " is ready for takeoff. Updated air time: " << airTime << " minutes." << std::endl;
}

void CHost::receiveHolidayGift() const {
    std::cout << employName << " thanking the company for receiving the holiday gift. I wasnt expecting it." << std::endl;
}

void CHost::updateUniform() const {
    std::cout << "I think the new uniform is very nice!" << std::endl;
}

HostType CHost::getHostType() const {
    return type;
}

bool CHost::operator==(const CHost& other) const {
    return employName == other.employName;
}

void CHost::takeoffNotification(int minutes) const {
    std::cout << "host " << employName << " notified about takeoff. Estimated flight time: " << minutes << " minutes." << std::endl;
}

CCrewMember* CHost::clone() const {
    return new CHost(*this);
}
