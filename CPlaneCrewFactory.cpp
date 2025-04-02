#include "PlaneCrewFactory.h"
#include "Plane.h"
#include "Cargo.h"
#include "Pilot.h"
#include "Host.h"
#include "FlightCompany.h"
#include "FlightCompException.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Determine the type of a plane (Regular or Cargo)
PlaneType CPlaneCrewFactory::GetPlaneType(const CPlane* pPlane) {
    if (dynamic_cast<const CCargo*>(pPlane) != nullptr) {
        return eCargo;
    }
    return eRegular;
}

// Determine the type of a crew member (Host or Pilot)
CrewType CPlaneCrewFactory::GetCrewType(const CCrewMember* pCrew) {
    if (dynamic_cast<const CPilot*>(pCrew) != nullptr) {
        return ePilot;
    }
    return eHost;
}

// Get complete data for a company from the user
void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp) {
    int planeCount, crewCount;

    std::cout << "Enter the number of planes to add: ";
    while (!(std::cin >> planeCount) || planeCount < 0) {
        std::cout << "Invalid input. Please enter a non-negative number of planes: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int i = 0; i < planeCount; ++i) {
        CPlane* plane = GetPlaneFromUser();
        if (plane) {
            if (!comp.AddPlane(*plane)) {
                std::cerr << "Failed to add the plane. It might already exist or exceed the limit." << std::endl;
            }
            delete plane; // Release memory
        }
    }

    std::cout << "Enter the number of crew members to add: ";
    while (!(std::cin >> crewCount) || crewCount < 0) {
        std::cout << "Invalid input. Please enter a non-negative number of crew members: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int i = 0; i < crewCount; ++i) {
        CCrewMember* crew = GetCrewFromUser();
        if (crew) {
            if (!comp.AddCrewMember(*crew)) {
                std::cerr << "Failed to add the crew member. They might already exist or exceed the limit." << std::endl;
            }
            delete crew; // Release memory
        }
    }
}

// Get plane data from the user
CPlane* CPlaneCrewFactory::GetPlaneFromUser() {
    int planeType;
    std::cout << "Enter plane type (0 for Regular, 1 for Cargo): ";
    while (!(std::cin >> planeType) || (planeType != eRegular && planeType != eCargo)) {
        std::cout << "Invalid input. Please enter 0 for Regular or 1 for Cargo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (planeType == eRegular) {
        int seats;
        std::string model;
        std::cout << "Enter model and seat count: ";
        std::cin >> std::ws; // Ignore leading whitespace
        std::getline(std::cin, model); // Read the entire line for the model
        std::cin >> seats;

        // Debug statement
        std::cout << "Creating Regular Plane: Model = " << model << ", Seats = " << seats << std::endl;

        return new CPlane(seats, model);
    }
    else if (planeType == eCargo) {
        int seats;
        std::string model;
        float maxWeight, maxVolume;
        std::cout << "Enter model, seat count, max weight, max volume: ";
        std::cin >> std::ws; // Ignore leading whitespace
        std::getline(std::cin, model); // Read the entire line for the model
        std::cin >> seats >> maxWeight >> maxVolume;

        // Debug statement
        std::cout << "Creating Cargo Plane: Model = " << model << ", Seats = " << seats
            << ", Max Weight = " << maxWeight << ", Max Volume = " << maxVolume << std::endl;

        return new CCargo(seats, model, maxWeight, maxVolume);
    }
    return nullptr;
}


// Get crew member data from the user
CCrewMember* CPlaneCrewFactory::GetCrewFromUser() {
    int crewType;
    std::cout << "Enter crew type (0 for Host, 1 for Pilot): ";
    while (!(std::cin >> crewType) || (crewType != eHost && crewType != ePilot)) {
        std::cout << "Invalid input. Please enter 0 for Host or 1 for Pilot: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (crewType == eHost) {
        std::string name;
        int hostType;
        std::cout << "Enter host name and type (0 for Regular, 1 for Senior, 2 for Economist): ";
        while (!(std::cin >> name >> hostType) || hostType < 0 || hostType > 2) {
            std::cout << "Invalid input. Please enter a valid name and host type (0 for Regular, 1 for Senior, 2 for Economist): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return new CHost(name, static_cast<HostType>(hostType));
    }
    else if (crewType == ePilot) {
        std::string name;
        int isCaptain;
        std::cout << "Enter pilot name and captain status (0 for No, 1 for Yes): ";
        while (!(std::cin >> name >> isCaptain) || (isCaptain != 0 && isCaptain != 1)) {
            std::cout << "Invalid input. Please enter a valid name and captain status (0 for No, 1 for Yes): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return new CPilot(name, isCaptain == 1);
    }
    return nullptr;
}

// Read crew member from file
CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(std::ifstream& inFile) {
    int crewType;
    inFile >> crewType;

    if (crewType == eHost) {
        std::string name;
        int minutes, hostType;
        inFile >> name >> minutes >> hostType;
        CHost* host = new CHost(name, static_cast<HostType>(hostType));
        *host += minutes;
        return host;
    }
    else if (crewType == ePilot) {
        std::string name;
        int minutes, hasAddress, isCaptain;
        inFile >> name >> minutes >> hasAddress >> isCaptain;
        if (hasAddress == 1) {
            std::string city, street;
            int houseNumber;
            inFile >> houseNumber >> street >> city;
            CAddress address(houseNumber, street, city);
            CPilot* pilot = new CPilot(name, isCaptain == 1, &address);
            *pilot += minutes;
            return pilot;
        }
        else {
            CPilot* pilot = new CPilot(name, isCaptain == 1);
            *pilot += minutes;
            return pilot;
        }
    }
    return nullptr;
}

CPlane* CPlaneCrewFactory::GetPlaneFromFile(std::ifstream& inFile, int number) {
    std::string line;
    std::getline(inFile, line); // Read the entire line for debugging

    // Create a string stream from the line to parse the individual values
    std::istringstream lineStream(line);

    int planeType;
    lineStream >> planeType;

    // Check if we successfully read the plane type and it matches our expected values.
    if (lineStream.fail() || (planeType != eRegular && planeType != eCargo)) {
        std::cerr << "String Error: Unknown plane type encountered. PlaneType = " << planeType << std::endl;
        lineStream.clear();
        lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line
        return nullptr;
    }


    int serialNumber, seats;
    std::string model;

    int lastId = 0;
    if (number == 0)
        lineStream >> lastId;

    // Handle Regular plane type
    if (planeType == eRegular) {
        lineStream >> serialNumber >> model >> seats;

        if (lineStream.fail() || seats <= 0 || model.empty()) {
            std::cerr << "String Error: Invalid regular plane data in file. Seats = " << seats << ", Model = " << model << std::endl;
            lineStream.clear();
            lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line
            return nullptr;
        }

        CPlane* plane = new CPlane(seats, model);
        plane->setSerialNumber(serialNumber);
        return plane;
    }
    // Handle Cargo plane type
    else if (planeType == eCargo) {
        float maxVolume, maxWeight, currentVolume, currentWeight;
        lineStream >> serialNumber >> model >> seats;

        std::getline(inFile, line);
        lineStream = std::istringstream(line);

        lineStream >> maxVolume >> maxWeight >> currentVolume >> currentWeight;


        if (lineStream.fail() || seats <= 0 || maxVolume <= 0 || maxWeight <= 0 || model.empty()) {
            std::cerr << "String Error: Invalid cargo plane data in file. Seats = " << seats
                << ", Model = " << model << ", Max Volume = " << maxVolume
                << ", Max Weight = " << maxWeight << std::endl;
            lineStream.clear();
            lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line
            return nullptr;
        }


        CCargo* cargo = new CCargo(seats, model, maxWeight, maxVolume);
        cargo->setSerialNumber(serialNumber);
        return cargo;
    }
    return nullptr;
}


