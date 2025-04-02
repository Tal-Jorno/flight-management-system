#pragma once

#include "FlightInfo.h"
#include "Plane.h"
#include "CrewMember.h"
#include "Host.h"
#include "Pilot.h"

#define MAX_CREW 10
#define MAX_PILOTS 5  // Define maximum number of pilots per flight

class CFlight {
private:
    CPlane* flightPlane = nullptr;
    CFlightInfo flightInfo;
    CCrewMember* crewMembers[MAX_CREW] = { nullptr };
    CPilot* pilots[MAX_PILOTS] = { nullptr };  // Array to hold pilots

    int crewCount = 0;
    int pilotsCount = 0;
    int regularHostCount = 0;
    int seniorHostCount = 0;
    int economistHostCount = 0;
    bool legalFlight();

public:
    explicit CFlight(CFlightInfo& flightInfo);  // Constructor for flight without a plane
    CFlight(CFlightInfo& flightInfo, CPlane* planeInfo);  // Constructor using pointer to plane
    CFlight(const CFlight& other);  // Copy constructor
    CFlight& operator=(const CFlight& other);  // Assignment operator
    ~CFlight();

    bool AddCrew(CCrewMember* crewMem);
    int GetRegularHosts() const;
    int GetSeniorHosts() const;
    int GetEconomistHosts() const;
    int GetPilotsCount() const;
    int GetFNum();
    const CFlightInfo& GetFlightInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const CFlight& cFlight);
    CFlight& operator+=(CCrewMember* crewMember);
    CFlight& operator+(CCrewMember* crewMember);
    bool operator==(CFlight& other);
    bool isExistPlane() const;
    bool TakeOff();
};
