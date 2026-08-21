#include <systemc.h>
#include <iostream>
#include <unordered_map>

SC_MODULE(Memory) {
    // Sử dụng map mô phỏng không gian bộ nhớ RAM
    std::unordered_map<uint32_t, uint32_t> ram;

    SC_CTOR(Memory) {}

    void write(uint32_t addr, uint32_t data) {
        ram[addr] = data;
        std::cout << "   [RAM Write] Mem[0x" << std::hex << addr << "] = 0x" << data << std::dec << std::endl;
    }

    uint32_t read(uint32_t addr) {
        uint32_t val = ram[addr];
        std::cout << "   [RAM Read]  Mem[0x" << std::hex << addr << "] -> 0x" << val << std::dec << std::endl;
        return val;
    }
};
