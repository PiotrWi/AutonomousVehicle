find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
        proto/CurrentRequestedSpeed.proto
        proto/PublishImage.proto
        proto/SetSpeed.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(CommunicationProtocol_proto_generated DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})

add_library(CommunicationProtocol STATIC
    Message.hpp
    Message.cpp
    MessageIds.hpp
    MessageIds.cpp
    networking/MessageSender.hpp
    networking/MessageDispatcher.hpp
    networking/MessageDispatcher.cpp
    networking/Connection.cpp
    networking/Connection.hpp
    networking/AccessPoint.hpp
    networking/AccessPoint.cpp
    networking/ClientAccessPoint.hpp
    networking/ClientAccessPoint.cpp
    ${PROTO_SRCS} ${PROTO_HDRS}
    MessageFormat.hpp
        networking/detail/MessageReconstruct.hpp
        networking/detail/MessageReconstruct.cpp
)

target_link_libraries(CommunicationProtocol tools)
add_dependencies(CommunicationProtocol CommunicationProtocol_proto_generated)

add_subdirectory(test EXCLUDE_FROM_ALL)
