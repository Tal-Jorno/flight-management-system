#include <fstream>
#include <iostream>
#include <sstream>
#include "FlightCompany.h"
#include "FlightCompException.h"
#include "PlaneCrewFactory.h"
#include "Pilot.h"
#include "Host.h"
#include "Cargo.h"
#include "Flight.h"

CFlightCompany::CFlightCompany(std::string companyName)
    : companyName(std::move(companyName)) {}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
    : companyName(other.companyName) {}

CFlightCompany::CFlightCompany(const std::string& fileName, int) {
    int planeCountInFile;
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        throw CCompFileException(fileName);
    }

    // Read company name
    std::getline(inFile, companyName);
    if (companyName.empty()) {
        throw CCompStringException("Company name cannot be empty.");
    }

    // Read crew members
    int crewCountInFile;
    inFile >> crewCountInFile;
    if (inFile.fail() || crewCountInFile < 0) {
        std::cerr << "String Error: Failed to read valid crew count." << std::endl;
        return;
    }
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore newline after the integer

    for (int i = 0; i < crewCountInFile; ++i) {
        CCrewMember* crew = CPlaneCrewFactory::GetCrewMemberFromFile(inFile);
        if (crew) {
            if (AddCrewMember(*crew)) {
            }
            else {
                std::cerr << "Error: Failed to add crew member: " << crew->getEmployName() << std::endl;
            }
            delete crew; // Avoid memory leaks
        }
        else {
            std::cerr << "String Error: Failed to create crew member from file." << std::endl;
        }
    }

    // Clear the stream and reset to beginning of planes section
    inFile.clear(); // Clear EOF flag after printing
    inFile.seekg(0, std::ios::beg);
    // Move past company name and crew member information
    std::getline(inFile, companyName);
    inFile >> crewCountInFile;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < crewCountInFile; ++i) {
        std::string temp;
        std::getline(inFile, temp);
    }

    // Read planes
    std::string planeCountStr;
    std::getline(inFile, planeCountStr);
    try {
        planeCountInFile = std::stoi(planeCountStr);
        if (planeCountInFile < 0) {
            throw std::invalid_argument("Plane count cannot be negative.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "String Error: Failed to read valid plane count. " << e.what() << std::endl;
        return;
    }

    for (int i = 0; i < planeCountInFile; ++i) {
        CPlane* plane = CPlaneCrewFactory::GetPlaneFromFile(inFile, i);
        if (plane) {
            if (AddPlane(*plane)) {
            }
            else {
                std::cerr << "String Error: Failed to add plane from file." << std::endl;
            }
            delete plane; // Clean up to avoid leaks
        }
        else {
            std::cerr << "String Error: Failed to create plane from file." << std::endl;
        }
    }

    // Read flights and their additional crew members
    std::string flightCountStr;
    std::getline(inFile, flightCountStr);
    int flightCountInFile;
    try {
        flightCountInFile = std::stoi(flightCountStr);
        if (flightCountInFile < 0) {
            throw std::invalid_argument("Flight count cannot be negative.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "String Error: Failed to read valid flight count. " << e.what() << std::endl;
        return;
    }

    for (int i = 0; i < flightCountInFile; ++i) {
        std::string line;
        std::getline(inFile, line); // Read entire flight line
        std::istringstream lineStream(line);

        std::string destination;
        int flightNumber, flightDuration, distance, hasPlane;
        lineStream >> destination >> flightNumber >> flightDuration >> distance >> hasPlane;

        if (lineStream.fail() || flightNumber <= 0 || flightDuration <= 0 || distance <= 0) {
            std::cerr << "String Error: Invalid flight details provided." << std::endl;
            continue;
        }

        CFlightInfo flightInfo(destination, flightNumber, flightDuration, distance);
        CPlane* assignedPlane = nullptr;
        if (hasPlane == 1) {
            int planeId;
            lineStream >> planeId;
            int planeIndex = -1;
            for (int k = 0; k < planesCount; k++) {
                if (planes[k]->getSerialNumber() == planeId)
                    planeIndex = k;
            }
            if (planeIndex >= 0 && planeIndex < planesCount) {
                assignedPlane = planes[planeIndex];
            }
            else {
                std::cerr << "String Error: Invalid plane index for flight." << std::endl;
            }
        }

        // Create the flight and add it to the company
        CFlight* flight = new CFlight(flightInfo, assignedPlane);
        if (!AddFlight(*flight)) {
            std::cerr << "String Error: Failed to add flight from file." << std::endl;
            delete flight; // Clean up to avoid leaks
            continue;
        }

        // Read additional crew members associated with this flight
        int additionalCrewCount;
        inFile >> additionalCrewCount;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int j = 0; j < additionalCrewCount; ++j) {
            CCrewMember* flightCrew = CPlaneCrewFactory::GetCrewMemberFromFile(inFile);
            if (flightCrew) {

                // Use the operator+= or AddCrew method to add the crew to the flight
                if (flight->AddCrew(flightCrew)) {
                }
                else {
                    std::cerr << "Error: Failed to add flight-specific crew member: " << flightCrew->getEmployName() << std::endl;
                    delete flightCrew; // Clean up if not added
                }
            }
            else {
                std::cerr << "String Error: Failed to create flight-specific crew member from file." << std::endl;
            }
        }


        // Clean up if no longer needed after adding to the company flights list
        delete flight;
    }

    inFile.close();
}


CFlightCompany::~CFlightCompany() {
    for (int i = 0; i < crewCount; ++i) {
        delete crewMembers[i];
    }
    for (int i = 0; i < planesCount; ++i) {
        delete planes[i];
    }
    for (int i = 0; i < flightCount; ++i) {
        delete flights[i];
    }
}

std::string CFlightCompany::getCompanyName() {
    return companyName;
}

CFlight* CFlightCompany::GetFlightByNum(int num) {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i] != nullptr && flights[i]->GetFNum() == num) {
            return flights[i];
        }
    }
    return nullptr;
}

bool CFlightCompany::SetName(const std::string name) {
    if (name.empty()) {
        return false;
    }
    this->companyName = name;
    return true;
}

void CFlightCompany::Print(std::ostream& os) const {
    if (companyName.empty()) {
        throw CCompStringException("Flight company name is missing.");
    }
    os << "Company Name: " << companyName << std::endl;
    os << "There are " << crewCount << " crew members:" << std::endl;
    for (int i = 0; i < crewCount; ++i) {
        crewMembers[i]->Print(os);
    }
    os << std::endl;
    os << "There are " << flightCount << " flights:" << std::endl;
    for (int i = 0; i < flightCount; ++i) {
        os << *flights[i] << std::endl;
    }
    os << "There are " << planesCount << " planes:" << std::endl;
    for (int i = 0; i < planesCount; ++i) {
        os << *planes[i] << std::endl;
    }
}

bool CFlightCompany::AddCrewMember(CCrewMember& crewMem) {
    if (crewCount >= MAX_CREWS)
        return false;
    for (int i = 0; i < crewCount; ++i) {
        if (crewMembers[i]->IsEqual(crewMem))
            return false;
    }
    CCrewMember* c = crewMem.clone();
    crewMembers[crewCount++] = c;
    return true;
}

CCrewMember* CFlightCompany::GetCrewMember(int i) {
    if (i >= crewCount || i < 0)
        return nullptr;
    return crewMembers[i];
}

bool CFlightCompany::AddPlane(CPlane& plane) {
    if (planesCount >= MAX_PLANES) {
        std::cerr << "Limit Error: Exceeded maximum plane limit of " << MAX_PLANES << std::endl;
        return false;
    }
    for (int i = 0; i < planesCount; ++i) {
        if (planes[i]->IsEqual(plane)) {
            std::cerr << "String Error: Duplicate plane detected." << std::endl;
            return false;
        }
    }

    planes[planesCount] = new CPlane(plane);
    if (planes[planesCount] == nullptr) {
        std::cerr << "Memory Error: Failed to allocate memory for new plane." << std::endl;
        return false;
    }
    if (plane.getPlaneType() == CPlane::CARGO)
        cargoPlaneCount++;

    planesCount++;
    return true;
}

bool CFlightCompany::AddFlight(CFlight& flight) {
    if (flightCount >= MAX_FLIGHTS) {
        std::cerr << "Limit Error: Exceeded maximum flight limit of " << MAX_FLIGHTS << std::endl;
        return false;
    }
    for (int i = 0; i < flightCount; ++i) {
        if (*flights[i] == flight) {
            std::cerr << "String Error: Duplicate flight detected." << std::endl;
            return false;
        }
    }

    flights[flightCount] = new CFlight(flight);
    if (flights[flightCount] == nullptr) {
        std::cerr << "Memory Error: Failed to allocate memory for new flight." << std::endl;
        return false;
    }

    flightCount++;
    return true;
}

CPlane* CFlightCompany::operator[](int index) {
    if (index < 0 || index >= planesCount) {
        throw CCompLimitException(planesCount);
    }
    return planes[index];
}

const CPlane* CFlightCompany::operator[](int index) const {
    if (index < 0 || index >= planesCount) {
        throw CCompLimitException(planesCount);
    }
    return planes[index];
}

// Function to notify all pilots to attend the simulator
void CFlightCompany::PilotsToSimulator() const {
    for (int i = 0; i < crewCount; ++i) {
        CPilot* pilot = dynamic_cast<CPilot*>(crewMembers[i]);
        if (pilot != nullptr) {
            pilot->simulatorNotification();  // Notify the pilot to attend the simulator
        }
    }
}

// Function to give holiday gifts to all crew members
void CFlightCompany::CrewGetPresent() const {
    for (int i = 0; i < crewCount; ++i) {
        if (crewMembers[i] != nullptr) {
            crewMembers[i]->receiveHolidayGift();
        }
    }
}

// Function to update uniforms for all crew members
void CFlightCompany::CrewGetUniform() const {
    for (int i = 0; i < crewCount; ++i) {
        if (crewMembers[i] != nullptr) {
            crewMembers[i]->updateUniform();
        }
    }
}

int CFlightCompany::GetCargoCount() {
    return cargoPlaneCount;
}

void CFlightCompany::SaveToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw CCompFileException("Unable to open file for writing: " + fileName);
    }

    // Write company details to the file
    outFile << companyName << std::endl;
    outFile << crewCount << std::endl;
    for (int i = 0; i < crewCount; ++i) {
        crewMembers[i]->Print(outFile);
        outFile << std::endl;
    }

    outFile << planesCount << std::endl;
    for (int i = 0; i < planesCount; ++i) {
        // Serialize the plane details
        outFile << *planes[i] << std::endl;
    }

    outFile << flightCount << std::endl;
    for (int i = 0; i < flightCount; ++i) {
        // Serialize the flight details
        outFile << *flights[i] << std::endl;
    }

    outFile.close();
}