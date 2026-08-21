#include <systemc.h>
#include <iostream>

SC_MODULE(UART) {
    SC_CTOR(UART) {}

    void send_char(char c) {
        std::cout << "[UART] Transmit: " << c << std::endl;
    }
};
