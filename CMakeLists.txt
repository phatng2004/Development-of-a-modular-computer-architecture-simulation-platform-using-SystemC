cmake_minimum_required(VERSION 3.12)
project(SystemC_Simulation)

# Thiết lập chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Đường dẫn SystemC theo lệnh biên dịch của bạn
set(SYSTEMC_HOME "/opt/systemc")

# Thêm include directory
include_directories(${SYSTEMC_HOME}/include)

# Thêm link directory
link_directories(${SYSTEMC_HOME}/lib)

# Tự động thêm RPATH vào binary (tương đương -Wl,-rpath,/opt/systemc/lib)
set(CMAKE_INSTALL_RPATH "${SYSTEMC_HOME}/lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Tạo file thực thi
add_executable(sim_app main.cpp)

# Link với thư viện systemc và pthread
target_link_libraries(sim_app systemc pthread)
