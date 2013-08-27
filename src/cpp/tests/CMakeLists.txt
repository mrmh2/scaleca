# For gtest
include_directories("/usr/users/cbu/hartleym/local/include")
include_directories("/usr/users/cbu/hartleym/local/lib")
link_directories("/usr/users/cbu/hartleym/local/lib")
include_directories("..")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests/bin)

add_executable (gtca gt.cpp ../cppca.cpp)
add_executable (test_gridman test_gridman.cpp ../gridmanager.cpp)

target_link_libraries(gtca gtest pthread)
target_link_libraries(test_gridman gtest pthread)
