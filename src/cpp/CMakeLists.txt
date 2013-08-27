cmake_minimum_required (VERSION 2.6)
project (CppCA)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories("/usr/users/cbu/hartleym/local/include")

add_executable(griddev griddev.cpp gridmanager.cpp)
add_executable(time_ca time_ca.cpp cppca.cpp)
add_executable(cppserver cppserver.cpp)
add_executable(make_states make_states.cpp cppca.cpp)
#add_executable(mpica mpica.cc gridmanager.cpp cppca.cpp)

target_link_libraries(cppserver zmq)								

add_subdirectory(tests)
