cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

find_package(GTest)
if(GTest_FOUND)
    find_package(Protobuf REQUIRED)

    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    include_directories(${gtest_INCLUDE_DIRS})

    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
            proto/SimpleProto.proto
            proto/SplitableProto.proto)
    add_custom_target(ut_comunication_protocol_generated DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})
    add_executable(ut_comunication_protocol EXCLUDE_FROM_ALL
            main.cpp
            MessageTests.cpp
            MessageFormatTests.cpp
            ${PROTO_SRCS}
            ${PROTO_HDRS})
    add_dependencies(ut_comunication_protocol ut_comunication_protocol_generated)

    target_link_libraries(ut_comunication_protocol
            ${GTEST_LIBRARIES}
            ${GTEST_MAIN_LIBRARIES}
            CommunicationProtocol
            ${Protobuf_LIBRARIES})
endif(GTest_FOUND)
