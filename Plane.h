#ifndef __Plane_H
#define __Plane_H

#include <string>
#include <iostream>

class CPlane {

public:
    enum planeType { CARGO, PASSENGERS };  // Type of the plane

private:
    std::string model;
    int chairNumber;
    static int countSerialNumber;
    int serialNumber;
    planeType type = PASSENGERS;  // Type of the plane

public:
    CPlane(const int chairNumber, std::string model);
    CPlane(const int chairNumber, std::string model, planeType type);
    CPlane(const CPlane& other);
    virtual ~CPlane() {}
    CPlane& operator=(const CPlane& other);
    std::string getModel() const;
    int getSerialNumber() const;
    int getChairNumber() const;
    planeType getType() const;
    planeType getPlaneType() const;
    bool setModel(std::string model);
    bool setChairNumber(int chairNumber);
    void setSerialNumber(int serial) { serialNumber = serial; }
    void Print() const;
    bool IsEqual(const CPlane& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CPlane& plane);
    CPlane& operator++();   // prefix
    CPlane operator++(int); // postfix
};

#endif // __Plane_H
