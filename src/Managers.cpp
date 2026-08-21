#ifndef MANAGERS_CPP
#define MANAGERS_CPP

#include <systemc.h>
#include <iostream>
#include <string>
#include "BusModule.cpp"

// --- MODULE MANAGER ---
class ModuleManager {
public:
    BusModule* bus;
    ModuleManager() {
        bus = new BusModule("BusModule");
    }
    ~ModuleManager() { 
        delete bus; 
    }
};

// --- SCHEDULER ---
class Scheduler {
public:
    void schedule_task(const std::string& task_name, double delay_ns) {
        std::cout << "[Scheduler] Task '" << task_name << "' scheduled in " << delay_ns << " ns" << std::endl;
    }
};

// --- LOGGER ---
class Logger {
public:
    void log(const std::string& msg) {
        std::cout << "[Log @" << sc_time_stamp() << "] " << msg << std::endl;
    }
};

// --- CONFIG MANAGER ---
class ConfigManager {
public:
    void load_config(const std::string& file) {
        std::cout << "[ConfigManager] Loaded configuration from " << file << std::endl;
    }
};

#endif
