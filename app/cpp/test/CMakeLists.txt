# find GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# include test files
add_executable(tests
    ../src/controllers/rushHour.h
    ../src/utility/string.h
    ../src/utility/string.cpp
    ../src/car.cpp
    ../src/car.h
    ../src/common.h
    ../src/levels.h
    tests.cpp
)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread rushhourlib)