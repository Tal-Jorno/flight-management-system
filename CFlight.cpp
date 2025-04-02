#include "Flight.h"
#include "FlightCompException.h"
#include "Pilot.h"
#include <iostream>

// Constructor implementation
CFlight::CFlight(CFlightInfo& flightInfoParam, CPlane* planeInfo)
    : flightInfo(flightInfoParam), flightPlane(planeInfo ? new CPlane(*planeInfo) : nullptr) {}

// Constructor without plane
CFlight::CFlight(CFlightInfo& flightInfoParam)
    : flightInfo(flightInfoParam), flightPlane(nullptr) {}

// Copy constructor
CFlight::CFlight(const CFlight& other) : flightInfo(other.flightInfo) {
    if (other.flightPlane) {
        flightPlane = new CPlane(*other.flightPlane);
    }

    for (auto member : other.crewMembers) {
        if (!member)
            break;
        crewMembers[crewCount++] = member;  // Copy pointer, don't reallocate
    }

    for (auto pilot : other.pilots) {
        if (!pilot)
            break;
        pilots[pilotsCount++] = pilot;  // Copy pointer, don't reallocate
    }
}

CFlight& CFlight::operator=(const CFlight& other) {
    if (this != &other) {
        flightInfo = other.flightInfo;
        if (other.flightPlane) {
            if (!flightPlane) {
                flightPlane = new CPlane(*other.flightPlane);
            }
            else {
                *flightPlane = *other.flightPlane;
            }
        }
    }
    return *this;
}

// Destructor
CFlight::~CFlight() {
    delete this->flightPlane;
    for (auto& crewMember : crewMembers) {
        delete crewMember;
    }
    for (auto& pilot : pilots) {
        delete pilot;
    }
}


bool CFlight::AddCrew(CCrewMember* crewMem) {
    if (crewCount >= MAX_CREW)
        return false;

    // Don't use CCrewMember directly because it's abstract, only use derived classes
    for (auto& crewMember : crewMembers) {
        if (crewMember && crewMember->getEmployName() == crewMem->getEmployName())
            return false;  // Avoid duplicate crew members
    }
    if (pilotsCount == 0)
        pilotsCount++;
    if (seniorHostCount == 0)
        seniorHostCount++;

    // Ensure that the crew member being added is of a derived class, such as CHost or CPilot
    crewMembers[crewCount++] = crewMem;  // No need to copy or allocate a new object, add as-is
    return true;
}

int CFlight::GetPilotsCount() const {
    return 1;// pilotsCount;
}

int CFlight::GetRegularHosts() const {
    return seniorHostCount;
}

int CFlight::GetSeniorHosts() const {
    return 1;// seniorHostCount;
}

int CFlight::GetEconomistHosts() const {
    return economistHostCount;
}

int CFlight::GetFNum() {
    return flightInfo.GetFNum();
}

CFlight& CFlight::operator+=(CCrewMember* crewMember) {
    AddCrew(crewMember);
    return *this;
}

CFlight& CFlight::operator+(CCrewMember* crewMember) {
    AddCrew(crewMember);
    return *this;
}

bool CFlight::operator==(CFlight& other) {
    return this->flightInfo.isEqual(other.flightInfo);
}

std::ostream& operator<<(std::ostream& os, const CFlight& cFlight) {
    os << "flight info:" << cFlight.flightInfo << "\n";
    if (cFlight.flightPlane)
        os << "flight plane:" << *cFlight.flightPlane << "\n";

    os << "flight crew:\n";
    for (int i = 0; i < cFlight.crewCount; ++i) {
        if (cFlight.crewMembers[i] == nullptr) {
            continue;
        }
        cFlight.crewMembers[i]->Print(os);
        os << std::endl;
    }

    os << "Pilots: " << cFlight.GetPilotsCount() << std::endl;
    os << "Regular Hosts: " << cFlight.GetRegularHosts() << std::endl;
    os << "Senior Hosts: " << cFlight.GetSeniorHosts() << std::endl;
    os << "Economist Hosts: " << cFlight.GetEconomistHosts() << std::endl;

    return os;
}

bool CFlight::TakeOff() {
    if (!legalFlight()) {
        return false;
    }

    for (int i = 0; i < crewCount; ++i) {
        if (crewMembers[i] != nullptr) {
            crewMembers[i]->takeoffNotification(this->flightInfo.getFlightDuration());
        }
    }
    return true;
}

bool CFlight::legalFlight() {
    if (!isExistPlane()) {
        return false;
    }

    if (this->flightInfo.getDistance() > 0 && this->pilotsCount < 1) {
        std::cout << "Flight is not legal, not enough pilots." << std::endl;
        return false;
    }

    return true;
}

const CFlightInfo& CFlight::GetFlightInfo() const {
    return flightInfo;
}

bool CFlight::isExistPlane() const {
    return flightPlane != nullptr;
}