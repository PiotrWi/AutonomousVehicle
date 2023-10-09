add_library(tools STATIC
    SingletonAddOn.hpp
    StringAlgorithms.cpp
    SingletonAddOn.hpp
    CreateTimmer.hpp
    CreateTimmer.cpp
    ExecutionTimeMeasurement.hpp
    Base64.hpp
    Base64.cpp
        CurrentTime.hpp
        CurrentTime.cpp
        Checksum.hpp
)

add_subdirectory(test EXCLUDE_FROM_ALL)
