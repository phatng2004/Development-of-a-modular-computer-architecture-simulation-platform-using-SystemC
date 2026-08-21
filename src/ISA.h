#ifndef ISA_H
#define ISA_H

#include <cstdint>

// Opcodes
constexpr uint8_t OP_LOAD  = 0x01;
constexpr uint8_t OP_ADD   = 0x02;
constexpr uint8_t OP_STORE = 0x03;
constexpr uint8_t OP_HALT  = 0xFF;

// Helper tạo từ lệnh 32-bit: [8-bit Opcode][24-bit Address]
inline uint32_t MAKE_INST(uint8_t opcode, uint32_t addr) {
    return (static_cast<uint32_t>(opcode) << 24) | (addr & 0x00FFFFFF);
}

#endif
