#include <systemc.h>
#include "src/SimulationManager.cpp"

int sc_main(int argc, char* argv[]) {
    SimulationManager sim_mgr;
    sim_mgr.init();

    sim_mgr.logger->log("Starting Execution CPU Instruction Cycles...");

    // Cho chương trình chạy trong 200 ns (đủ chu kỳ cho các lệnh Fetch-Decode-Execute)
    sc_start(200, SC_NS);

    sim_mgr.logger->log("Simulation Finished.");
    return 0;
}
