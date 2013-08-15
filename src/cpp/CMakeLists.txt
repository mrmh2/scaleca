cmake_minimum_required (VERSION 2.6)
project (CppCA)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable (TestCppCA test_ca.cpp cppca.cpp)

add_subdirectory(tests)
