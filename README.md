Project: Flight Management System 

Description:
------------
This C++ project simulates a full flight management system for an airline company. It includes functionality for managing planes, flights, and crew members (pilots and hosts), with support for both regular and cargo planes. The system handles user interaction, file input/output, and enforces strong data validation using custom exceptions.

The project uses object-oriented design, including inheritance, polymorphism, operator overloading, and encapsulation. Crew members are stored dynamically using abstract base classes and derived types. Planes and flights are managed through arrays with strict bounds checking.

A custom exception hierarchy was implemented to handle invalid input, file access errors, and logic violations. All exceptions are caught and handled gracefully within the application.

The system supports:
- Creating and modifying planes, crew members, and flights
- Saving and loading company data from text files
- Input from user or file via `CPlaneCrewFactory`
- Exception handling for invalid states and file errors
- Operator overloading for intuitive object interactions

- Language: C++  
- IDE: Visual Studio 2017  
