cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

find_package(GTest)
if(GTest_FOUND)
    include_directories(${gtest_INCLUDE_DIRS})
    add_executable(ut EXCLUDE_FROM_ALL main.cpp
            GpioDriverTests.cpp
            SysfsTestUtils/SysfsHelperStub.cpp
            SysfsTestUtils/Journal.cpp
            SysfsTestUtils/Journal.hpp
            SysfsTestUtils/SequenceVerifier.hpp
            SysfsTestUtils/GpioSequences.hpp
            SysfsTestUtils/SysFsDriverBase.hpp
            PwmDriverTest.cpp
            SysfsTestUtils/PwmSequences.hpp
            SysfsTestUtils/SequenceVerifier.cpp
            MotorDriverTests.cpp
            SysfsTestUtils/GpioSequences.cpp
            SysfsTestUtils/PwMSequences.cpp)
    target_link_libraries(ut ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} drivers)
endif(GTest_FOUND)
