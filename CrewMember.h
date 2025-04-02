#ifndef __CrewMember_H
#define __CrewMember_H

#include "Address.h"
#include <string>
#include <iostream>

class CCrewMember {
protected:
    std::string employName;
    int airTime;
    int employNumber;
    static int countEmployNumber;
    CAddress* employAddress = nullptr;

public:
    static const int START_ID = 1000;

    CCrewMember(std::string employName, const CAddress& employAddress, int airTime);
    CCrewMember(std::string employName, const CAddress& employAddress);
    explicit CCrewMember(std::string employName);
    CCrewMember(std::string employName, int airtime);
    CCrewMember(const CCrewMember& other);
    virtual ~CCrewMember();

    std::string getEmployName() const;
    int getEmployNumber() const;

    virtual CCrewMember* clone() const = 0;
    void Print(std::ostream& os) const;
    bool IsEqual(const CCrewMember& other) const;
    virtual int operator+=(int min);
    virtual void takeoffNotification(int minutes) const = 0;
    virtual void receiveHolidayGift() const = 0;
    virtual void updateUniform() const = 0;
    virtual void takeoff(int minutes) = 0;
};

#endif // __CrewMember_H
