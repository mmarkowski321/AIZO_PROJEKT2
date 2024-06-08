cmake_minimum_required(VERSION 3.27)
project(AIZO_PROJEKT2)

set(CMAKE_CXX_STANDARD 17)

# Ustawienia kompilatora i linkera
MATH(EXPR stack_size "16 * 1024 * 1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16777216")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# Pliki źródłowe
set(SOURCES
        main.cpp
        Graph.cpp
        Algorithms.cpp
)

# Pliki nagłówkowe
set(HEADERS
        Graph.h
        Algorithms.h
        Utility.h
)

add_executable(AIZO_PROJEKT2 ${SOURCES} ${HEADERS})
