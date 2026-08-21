#include <systemc.h>
#include "Managers.cpp"
#include "CPU.cpp"

class SimulationManager {
public:
    ModuleManager* module_mgr;
    Scheduler*     scheduler;
    Logger*        logger;
    ConfigManager* config_mgr;
    sc_clock*      system_clock;
    CPU*           cpu;

    SimulationManager() {
        module_mgr   = new ModuleManager();
        scheduler    = new Scheduler();
        logger       = new Logger();
        config_mgr   = new ConfigManager();
        system_clock = new sc_clock("SystemClock", 10, SC_NS); // Clock 100MHz (Chu kỳ 10ns)

        // Khởi tạo CPU và kết nối bus/clock
        cpu = new CPU("CPU", module_mgr->bus);
        cpu->clk(*system_clock);
        module_mgr->bus->timer->clk(*system_clock);
    }

    ~SimulationManager() {
        delete cpu;
        delete module_mgr;
        delete scheduler;
        delete logger;
        delete config_mgr;
        delete system_clock;
    }

    void init() {
        config_mgr->load_config("config.ini");
        logger->log("Simulation System Initialized.");

        // --- KHÔNG GIAN BỘ NHỚ RAM (MEMORY MAP) ---
        // 1. Dữ liệu số nguyên (Data Segment)
        uint32_t DATA_A = 0x0100; // Lưu số 5
        uint32_t DATA_B = 0x0104; // Lưu số 7
        uint32_t RESULT = 0x0200; // Nơi lưu kết quả

        module_mgr->bus->write(DATA_A, 5);
        module_mgr->bus->write(DATA_B, 7);

        // 2. Mã chương trình (Code Segment) từ địa chỉ 0x0000
        module_mgr->bus->write(0x0000, MAKE_INST(OP_LOAD, DATA_A));  // LOAD Mem[0x100] (Lấy số 5)
        module_mgr->bus->write(0x0004, MAKE_INST(OP_ADD,  DATA_B));  // ADD  Mem[0x104] (Cộng số 7)
        module_mgr->bus->write(0x0008, MAKE_INST(OP_STORE, RESULT)); // STORE Mem[0x200] (Lưu 12)
        module_mgr->bus->write(0x000C, MAKE_INST(OP_HALT, 0));       // HALT
        
        logger->log("Program loaded into Memory (LOAD 5, ADD 7, STORE to 0x200, HALT).");
    }
};
