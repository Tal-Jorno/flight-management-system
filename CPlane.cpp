#include "Plane.h"
#include "FlightCompException.h"
#include <utility>
#include <iostream> // For debug output

int CPlane::countSerialNumber = 100;

// Constructor with plane type
CPlane::CPlane(const int chairNumber, std::string model, planeType type)
    : chairNumber(chairNumber), model(std::move(model)), type(type), serialNumber(countSerialNumber++) {
    if (chairNumber <= 0) {
        throw CCompStringException("Invalid plane: number of chairs must be positive.");
    }
    if (this->model.empty()) { // Check the model after it has been set
        throw CCompStringException("Invalid plane: model cannot be empty.");
    }
}

// Constructor for regular plane (no type provided)
CPlane::CPlane(const int chairNumber, std::string model)
    : chairNumber(chairNumber), model(std::move(model)), serialNumber(countSerialNumber++) {
    // Ensure proper validation after initialization
    if (chairNumber <= 0) {
        throw CCompStringException("Invalid plane: number of chairs must be positive.");
    }

    if (this->model.empty()) {
        throw CCompStringException("Invalid plane: model cannot be empty.");
    }

}

// Copy constructor
CPlane::CPlane(const CPlane& other)
    : model(other.model), chairNumber(other.chairNumber), serialNumber(other.serialNumber), type(other.type) {}

// Assignment operator
CPlane& CPlane::operator=(const CPlane& other) {
    if (this != &other) {
        model = other.model;
        chairNumber = other.chairNumber;
        serialNumber = other.serialNumber;
        type = other.type;
    }
    return *this;
}

std::string CPlane::getModel() const {
    return model;
}

int CPlane::getSerialNumber() const {
    return serialNumber;
}

int CPlane::getChairNumber() const {
    return chairNumber;
}

CPlane::planeType CPlane::getType() const {
    return type;
}

CPlane::planeType CPlane::getPlaneType() const {
    return type;
}

bool CPlane::setModel(std::string model) {
    if (!model.empty()) {
        this->model = model;
        return true;
    }
    return false;
}

bool CPlane::setChairNumber(int chairNumber) {
    if (chairNumber >= 0) {
        this->chairNumber = chairNumber;
        return true;
    }
    return false;
}

void CPlane::Print() const {
    std::cout << "Model: " << model << "\n"
        << "Chairs: " << chairNumber << "\n"
        << "Serial Number: " << serialNumber << "\n"
        << "Type: " << (type == CARGO ? "Cargo" : "Passenger") << std::endl;
}

bool CPlane::IsEqual(const CPlane& other) const {
    return serialNumber == other.serialNumber;
}

std::ostream& operator<<(std::ostream& os, const CPlane& plane) {
    os << "Model: " << plane.model << ", Serial Number: " << plane.serialNumber;
    return os;
}

CPlane& CPlane::operator++() {
    ++chairNumber;
    return *this;
}

CPlane CPlane::operator++(int) {
    CPlane temp = *this;
    ++chairNumber;
    return temp;
}
