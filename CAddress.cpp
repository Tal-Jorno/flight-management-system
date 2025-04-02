#include <string>
#include <iostream>
#include <limits> // Include the proper header for numeric_limits
#include "Address.h"

CAddress::CAddress(const int houseNumber, const char* street) : city("tel aviv"), houseNumber(houseNumber) {
    if (street == nullptr) {
        this->street = std::string("");
    }
    else {
        this->street = std::string(street);
    }
}

CAddress::CAddress(const int houseNumber, const std::string* street, const std::string* city) : houseNumber(houseNumber) {
    if (street == nullptr) {
        this->street = std::string("");
    }
    else {
        this->street = std::string(*street);
    }
    if (city == nullptr) {
        this->city = std::string("");
    }
    else {
        this->city = std::string(*city);
    }
}

CAddress::CAddress(const CAddress& other) : city(other.city), street(other.street), houseNumber(other.houseNumber) {}

CAddress::~CAddress() {}

int CAddress::getHouseNumber() const {
    return houseNumber;
}

std::string CAddress::getCity() const {
    return city;
}

std::string CAddress::getStreet() const {
    return street;
}

bool CAddress::setHouseNumber(int houseNumber) {
    if (houseNumber <= 0 || houseNumber >= 10000) {
        return false;
    }
    this->houseNumber = houseNumber;
    return true;
}

bool CAddress::setCity(std::string city) {
    if (city.empty()) {
        return false;
    }
    this->city = city;
    return true;
}

bool CAddress::setStreet(std::string street) {
    if (street.empty()) {
        return false;
    }
    this->street = street;
    return true;
}


std::istream& operator>>(std::istream& is, CAddress& address) {
    std::string cityInput, streetInput;
    int houseNumberInput;

    std::cout << "Please enter your city: ";
    std::getline(is, cityInput);
    if (address.setCity(cityInput)) {
        address.city = cityInput;
    }
    else {
        std::cerr << "Invalid city input.\n";
        return is;
    }

    std::cout << "Please enter your street: ";
    std::getline(is, streetInput);
    if (address.setStreet(streetInput)) {
        address.street = streetInput;
    }
    else {
        std::cerr << "Invalid street input.\n";
        return is;
    }

    std::cout << "Please enter your house number: ";
    if (is >> houseNumberInput) {
        if (address.setHouseNumber(houseNumberInput)) {
            address.houseNumber = houseNumberInput;
        }
        else {
            std::cerr << "Invalid house number input.\n";
            return is;
        }
    }
    else {
        std::cerr << "Invalid input format for house number.\n";
        return is;
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return is;
}

std::ostream& operator<<(std::ostream& os, const CAddress& address) {
    os << "City: " << address.getCity() << ", Street: " << address.getStreet()
        << ", House Number: " << address.getHouseNumber();
    return os;
}

bool CAddress::operator==(const CAddress& other) const {
    return (city == other.city) &&
        (street == other.street) &&
        (houseNumber == other.houseNumber);
}

bool CAddress::operator!=(const CAddress& other) const {
    return !(*this == other);
}


