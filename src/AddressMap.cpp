#include <cstdint>

class AddressMap {
public:
    enum Device { DEV_UNKNOWN, DEV_MEMORY, DEV_UART, DEV_TIMER };

    Device decode(uint32_t addr) {
        if (addr >= 0x0000 && addr < 0x1000) return DEV_MEMORY;
        if (addr >= 0x1000 && addr < 0x1050) return DEV_UART;
        if (addr >= 0x2000 && addr < 0x2020) return DEV_TIMER;
        return DEV_UNKNOWN;
    }
};
