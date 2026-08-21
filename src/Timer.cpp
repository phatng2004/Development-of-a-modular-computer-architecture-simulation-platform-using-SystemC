#include <systemc.h>
#include <iostream>

SC_MODULE(Timer) {
    sc_in<bool> clk;

    SC_CTOR(Timer) {
        SC_METHOD(on_tick);
        sensitive << clk.pos();
        dont_initialize();
    }

    void on_tick() {
        // Logics khi clock lên mức cao (pos edge)
    }
};
