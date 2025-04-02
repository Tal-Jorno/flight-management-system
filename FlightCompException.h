#ifndef FLIGHT_COMP_EXCEPTION_H
#define FLIGHT_COMP_EXCEPTION_H

#include <iostream>
#include <string>

// Abstract Base Class for Flight Company Exceptions
class CFlightCompException {
public:
    virtual void Show() const = 0;  // Pure virtual function
    virtual ~CFlightCompException() = default;  // Ensure proper cleanup of derived classes
};

// Exception class for handling string-related errors
class CCompStringException : public CFlightCompException {
private:
    std::string errorMsg;
public:
    explicit CCompStringException(const std::string& msg) : errorMsg(msg) {}

    void Show() const override {
        std::cout << "String Error: " << errorMsg << std::endl;
    }
};

// Exception class for handling limit-related errors
class CCompLimitException : public CFlightCompException {
private:
    int maxLimit;
public:
    explicit CCompLimitException(int limit) : maxLimit(limit) {}

    void Show() const override {
        std::cout << "Limit Error: Exceeded maximum limit of " << maxLimit << std::endl;
    }
};

// Exception class for handling file-related errors
class CCompFileException : public CFlightCompException {
private:
    std::string fileName;
public:
    explicit CCompFileException(const std::string& file) : fileName(file) {}

    void Show() const override {
        std::cout << "File Error: Issue encountered with file " << fileName << std::endl;
    }
};

#endif // FLIGHT_COMP_EXCEPTION_H
