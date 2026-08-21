#ifndef CPU_CPP
#define CPU_CPP

#include <systemc.h>
#include <iostream>
#include "ISA.h"
#include "BusModule.cpp"

SC_MODULE(CPU) {
    sc_in<bool> clk;
    BusModule* bus;

    uint32_t PC;   // Program Counter
    uint32_t IR;   // Instruction Register
    uint32_t ACC;  // Accumulator Register
    bool halted;

    enum State { FETCH, DECODE, EXECUTE };
    State state;

    // Định nghĩa Constructor chuẩn cho SystemC 3.0+
    SC_CTOR(CPU) {
        PC = 0x0000;
        IR = 0;
        ACC = 0;
        halted = false;
        state = FETCH;

        SC_METHOD(step);
        sensitive << clk.pos();
        dont_initialize();
    }

    // Constructor tùy chỉnh nhận thêm con trỏ bus
    CPU(sc_module_name name, BusModule* bus_ptr) : sc_module(name), bus(bus_ptr) {
        PC = 0x0000;
        IR = 0;
        ACC = 0;
        halted = false;
        state = FETCH;

        SC_METHOD(step);
        sensitive << clk.pos();
        dont_initialize();
    }

    void step() {
        if (halted) return;

        switch (state) {
            case FETCH: {
                std::cout << "\n==========================================" << std::endl;
                std::cout << "[CPU FETCH] PC = 0x" << std::hex << PC << std::dec 
                          << " @ " << sc_time_stamp() << std::endl;
                
                IR = bus->read(PC);
                PC += 4;
                state = DECODE;
                break;
            }

            case DECODE: {
                uint8_t opcode = (IR >> 24) & 0xFF;
                uint32_t operand_addr = IR & 0x00FFFFFF;

                std::cout << "[CPU DECODE] Opcode = 0x" << std::hex << (int)opcode 
                          << ", Operand Addr = 0x" << operand_addr << std::dec << std::endl;
                
                state = EXECUTE;
                break;
            }

            case EXECUTE: {
                uint8_t opcode = (IR >> 24) & 0xFF;
                uint32_t operand_addr = IR & 0x00FFFFFF;

                std::cout << "[CPU EXECUTE] ";

                switch (opcode) {
                    case OP_LOAD: {
                        ACC = bus->read(operand_addr);
                        std::cout << "LOAD -> ACC = " << ACC << std::endl;
                        break;
                    }
                    case OP_ADD: {
                        uint32_t val = bus->read(operand_addr);
                        std::cout << "ADD  -> " << ACC << " + " << val << " = " << (ACC + val) << std::endl;
                        ACC += val;
                        break;
                    }
                    case OP_STORE: {
                        std::cout << "STORE -> Save ACC (" << ACC << ") to 0x" << std::hex << operand_addr << std::dec << std::endl;
                        bus->write(operand_addr, ACC);
                        break;
                    }
                    case OP_HALT: {
                        std::cout << "HALT -> Stop execution." << std::endl;
                        halted = true;
                        break;
                    }
                    default:
                        std::cout << "UNKNOWN INSTRUCTION!" << std::endl;
                        halted = true;
                }

                state = FETCH;
                break;
            }
        }
    }
};

#endif
