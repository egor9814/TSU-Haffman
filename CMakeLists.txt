cmake_minimum_required(VERSION 3.8)
project(TSU_Haffman)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        haffman.cpp haffman.hpp
        bool_vector.cpp bool_vector.hpp
        binary_io.cpp binary_io.hpp
        )
add_executable(haff ${SOURCE_FILES})
