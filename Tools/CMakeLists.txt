add_library(tools STATIC
    SingletonAddOn.hpp
    StringAlgorithms.cpp
    SingletonAddOn.hpp
    CreateTimmer.hpp
    CreateTimmer.cpp
    ExecutionTimeMeasurement.hpp
    CurrentTime.hpp
    CurrentTime.cpp
    Checksum.hpp
    Coders/Base64.hpp
    Coders/Base64.cpp
    Coders/HuffmanCoding.hpp
    Coders/HuffmanCoding.cpp
    Coders/detail/heap.hpp
    Coders/HuffmanDecoding.cpp
)

add_subdirectory(test EXCLUDE_FROM_ALL)
