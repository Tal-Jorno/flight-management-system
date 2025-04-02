#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "Plane.h"
#include "FlightInfo.h"
#include "CrewMember.h"
#include "Flight.h"
#include "FlightCompany.h"
#include "address.h"
#include "Pilot.h"
#include "Cargo.h"
#include "Host.h"
#include "FlightCompException.h"
#include "PlaneCrewFactory.h"

int main() {
    CFlightCompany* pDelta = nullptr;
    try {
        pDelta = new CFlightCompany("Delta.txt", 0);
        cout << "This was in file " << endl;
        pDelta->Print(cout);
    }
    catch (const CFlightCompException& e) {
        e.Show();
        pDelta = new CFlightCompany("Delta");
    }

    // Checking some of the exception put try and catch for each section	
    try {
        CPlane p1(-34, "AirBus");
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CCargo c1(45, "Jumbo", -560, 200);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CCargo c2(45, "Jumbo", 560, -200);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CFlightInfo f1("London", -23, 120, 5000);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CFlightInfo f2("LondonVeryLong", 23, 120, 5000);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CFlightInfo f3("London", 23, -120, 5000);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CFlightInfo f4("London", 23, 120, -5000);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CCrewMember* pC1 = pDelta->GetCrewMember(-1);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        CCrewMember* pC2 = pDelta->GetCrewMember(0);
        (*pC2) += -4;
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    try {
        // Use a pointer to handle this case instead of converting to CPlane object directly.
        CPlane* p0 = (*pDelta)[9];
        if (p0) {
            cout << "Plane retrieved successfully: " << *p0 << endl;
        }
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    // Call a static function that gets a plane or customer from user.
    CPlaneCrewFactory::GetCompanyDataFromUser(*pDelta);

    // Ensure you are getting a reference and handling `CFlight` correctly.
    CFlightInfo Info("Paris", 343, 320, 5000);
    try {
        CPlane* assignedPlane = (*pDelta)[0];  // Directly get plane pointer
        CFlight flight1(Info, assignedPlane);   // Create flight with plane pointer
        pDelta->AddFlight(flight1);
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    CFlight* pF = pDelta->GetFlightByNum(343);
    CCrewMember* pCmTemp;
    if (pF != nullptr) {
        cout << "flight 343 was found " << endl;
        for (int i = 0; i < pDelta->GetCrewCount(); i++) {
            pCmTemp = pDelta->GetCrewMember(i);
            *pF + pCmTemp;
        }
    }

    try {
        pDelta->SaveToFile("Delta.txt");
    }
    catch (const CFlightCompException& e) {
        e.Show();
    }

    delete pDelta;
    system("pause");
    return 0;
}
