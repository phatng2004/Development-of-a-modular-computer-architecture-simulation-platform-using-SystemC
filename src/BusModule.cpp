#ifndef BUS_MODULE_CPP
#define BUS_MODULE_CPP

#include <systemc.h>
#include <iostream>
#include "AddressMap.cpp"
#include "Memory.cpp"
#include "UART.cpp"
#include "Timer.cpp"

SC_MODULE(BusModule) {
    AddressMap addr_map;
    Memory* memory;
    UART* uart;
    Timer* timer;

    SC_CTOR(BusModule) {
        memory = new Memory("Memory");
        uart   = new UART("UART");
        timer  = new Timer("Timer");
    }

    ~BusModule() {
        delete memory;
        delete uart;
        delete timer;
    }

    uint32_t read(uint32_t addr) {
        if (addr_map.decode(addr) == AddressMap::DEV_MEMORY) {
            return memory->read(addr);
        }
        return 0;
    }

    void write(uint32_t addr, uint32_t data) {
        switch (addr_map.decode(addr)) {
            case AddressMap::DEV_MEMORY: 
                memory->write(addr, data); 
                break;
            case AddressMap::DEV_UART:   
                uart->send_char(static_cast<char>(data)); 
                break;
            default: 
                break;
        }
    }
};

#endif // BUS_MODULE_CPP
