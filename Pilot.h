#ifndef PILOT_H
#define PILOT_H

#include "CrewMember.h"
#include <string>
#include <iostream>

class CPilot : public CCrewMember {
private:
    bool isCaptain;

    CAddress* address = nullptr;

public:
    CPilot(const std::string& name, bool isCaptain, CAddress* address = nullptr);
    CPilot(const CPilot& other);
    CPilot& operator=(const CPilot& other);
    ~CPilot() override;

    std::string getName() const;

    CCrewMember* clone() const override;
    void takeoff(int minutes) override;
    void receiveHolidayGift() const override;
    void updateUniform() const override;
    int operator+=(int min) override;
    void simulatorNotification() const;
    void takeoffNotification(int minutes) const override;  // New function
    bool operator==(const CPilot& other) const;

};

#endif // PILOT_H
