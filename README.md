CASP: Computer Architecture Simulation Platform

CASP is a modular and extensible computer architecture simulation framework developed using SystemC (IEEE 1666) and C++. It is designed for educational purposes and computer architecture research, providing an accessible alternative to complex full-system simulators.

Key Features

Modular Architecture: Independent and loosely coupled hardware modules for easy extension and debugging.
Core Components:
•	SimulationManager & Scheduler: Controls simulation execution and event scheduling.
•	BusModule & AddressMap: Handles bus arbitration, routing, and memory-mapped address translation.
•	Hardware Modules: Extensible models for CPU, Memory, UART, and Timer.
C++ / SystemC Standard: Built on top of SystemC for accurate cycle/transaction modeling.

Project Structure

text
.
├── CMakeLists.txt      # Build configuration
├── main.cpp            # Application entry point & simulation run
├── include/            # Header files (.h / .hpp)
├── src/                # Implementation files (.cpp)
└── doc/                # Architecture diagrams and specifications

Build & Run Instructions
- Prerequisites

 C++17 Compiler (GCC / Clang / MSVC)
 CMake 3.15+
 SystemC Library (IEEE 1666 standard)

Building the Project

bash
# Create build directory
mkdir build && cd build

# Configure and compile
cmake ..
cmake --build .

# Run simulation
./sim_app

Author & Acknowledgements

 Developer: Nguyen Tan Phat
 Advisor: Dr. Pham Van Khoa
 Institution: Faculty of Advanced Education - HCMUTE


