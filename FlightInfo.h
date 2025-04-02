#ifndef __FlightInfo_H
#define __FlightInfo_H

#include <string>
#include <iostream>

class CFlightInfo {

private:
    int flightNumber;
    std::string destination;
    int flightDuration;
    int distance;

public:
    CFlightInfo(const std::string destination, const int flightNumber, const int flightDuration, const int distance);
    CFlightInfo(const CFlightInfo& other);
    ~CFlightInfo();

    std::string getDestination() const;
    int getFlightNumber() const;
    int getFlightDuration() const;
    int getDistance() const;
    int GetFNum();
    bool SetDest(std::string destination);
    bool setFlightDuration(int flightDuration);
    bool setDistance(int distance);

    void Print() const;
    bool isEqual(const CFlightInfo& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CFlightInfo& flightInfo);
    bool operator!=(const CFlightInfo& other) const;
    operator int() const;


};

#endif
