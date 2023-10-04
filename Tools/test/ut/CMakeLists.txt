cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

find_package(GTest)
if(GTest_FOUND)
    include_directories(${gtest_INCLUDE_DIRS})
    add_executable(ut_tools EXCLUDE_FROM_ALL main.cpp
            Base64Tests.cpp)
    target_link_libraries(ut_tools
            ${GTEST_LIBRARIES}
            ${GTEST_MAIN_LIBRARIES}
            tools)
endif(GTest_FOUND)
