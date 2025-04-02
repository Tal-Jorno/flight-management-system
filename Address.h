#ifndef __Address_H
#define __Address_H

#include <string>
#include <iostream>
#include <utility>

class CAddress {
private:
    std::string city;
    std::string street;
    int houseNumber;

public:
    CAddress(const int houseNumber, const std::string* street, const std::string* city);
    CAddress(const int houseNumber, const char* street);
    CAddress(int houseNumber, const std::string& street, const std::string& city)
        : houseNumber(houseNumber), street(street), city(city) {}
    CAddress(const CAddress& other);
    ~CAddress();

    int getHouseNumber() const;
    std::string getCity() const;
    std::string getStreet() const;
    bool setHouseNumber(int houseNumber);
    bool setCity(std::string city);
    bool setStreet(std::string street);

    friend std::ostream& operator<<(std::ostream& os, const CAddress& address);
    friend std::istream& operator>>(std::istream& is, CAddress& address);
    bool operator==(const CAddress& other) const;
    bool operator!=(const CAddress& other) const;

};



#endif
