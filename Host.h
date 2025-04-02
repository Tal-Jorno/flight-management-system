#ifndef HOST_H
#define HOST_H

#include "CrewMember.h"
#include <iostream>
#include <string>

enum class HostType {
    Regular,
    Senior,
    Economist
};

class CHost : public CCrewMember {
private:
    HostType type;

public:
    CHost(const std::string& name, HostType type);
    CHost(const CHost& other);
    CHost& operator=(const CHost& other);
    ~CHost();

    HostType getHostType() const;

    void takeoff(int minutes) override;
    void takeoffNotification(int minutes) const override;
    void receiveHolidayGift() const override;
    void updateUniform() const override;
    CCrewMember* clone() const override;
    bool operator==(const CHost& other) const;

    const static HostType eRegular = HostType::Regular;
    const static HostType eSuper = HostType::Senior;
    const static HostType eCalcelan = HostType::Economist;
};

#endif // HOST_H
