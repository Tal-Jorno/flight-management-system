#ifndef __FlightCompany_H
#define __FlightCompany_H

#include <string>
#include <iostream>
#include "CrewMember.h"
#include "Plane.h"
#include "Flight.h"
#include "Pilot.h"

#define MAX_CREWS 100
#define MAX_PLANES 100
#define MAX_FLIGHTS 100

class CFlightCompany {

private:
    std::string companyName;
    CCrewMember* crewMembers[MAX_CREWS] = { nullptr };
    CPlane* planes[MAX_PLANES] = { nullptr };
    CFlight* flights[MAX_FLIGHTS] = { nullptr };
    int crewCount = 0;
    int planesCount = 0;
    int flightCount = 0;
    int cargoPlaneCount = 0;

public:
    explicit CFlightCompany(std::string companyName);
    CFlightCompany(const CFlightCompany& other);
    ~CFlightCompany();
    int GetCrewCount() const { return crewCount; }
    std::string getCompanyName();
    CFlight* GetFlightByNum(int num);
    CPlane* operator[](int index);
    const CPlane* operator[](int index) const;
    int GetCargoCount();
    void CrewGetPresent() const;
    void CrewGetUniform() const;
    bool SetName(std::string name);
    CFlightCompany(const std::string& fileName, int);
    void SaveToFile(const std::string& fileName) const;
    bool AddCrewMember(CCrewMember& crewMem);
    bool AddPlane(CPlane& plane);
    bool AddFlight(CFlight& flight);
    void Print(std::ostream& os) const;
    void PilotsToSimulator() const;
    CCrewMember* GetCrewMember(int i);

};

#endif // __FlightCompany_H
