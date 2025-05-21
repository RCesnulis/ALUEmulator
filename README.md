# Simple Processor Emulator

A lightweight emulator for a basic processor architecture built in C++. It simulates core components like a one-bit ALU, basic logic structures, and allows experimentation with fundamental digital logic design. This emulator is desinged for 8-bit operations
Features

    Simulates digital logic gates (AND, OR, NOT, etc.)

    Implements a One-Bit ALU with functionality for arithmetic and logic operations

    Demonstrates modular hardware-like design using C++ classes and templates

    Expandable and great for educational purposes
    
# Project Structure

.

├── main.cpp                  # Driver file to test the processor logic

├── One_Bit_ALU.h             # One-bit ALU logic (add, subtract, AND, OR, etc.)

└── Digital_logic_structures. # Basic digital components (MUX, gates, etc.)

# Usage

    Clone the repository:

git clone https://github.com/RCesnulis/ALUEmulator.git
cd simple-processor-emulator

Build and run the emulator:

    g++ -o emulator main.cpp
    ./emulator

Edit and extend:
      Add your own test cases in main.cpp
      Introduce registers, memory, or even a control unit!

# Contributions

Feel free to fork, contribute, or submit pull requests! All improvements welcome — whether it’s documentation, bug fixes, or feature enhancements.

# License

This project is open-source and available under the MIT License.
