cmake_minimum_required(VERSION 3.25.1)

project(tp5)

set(CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_compile_options(-Wall -Wextra -O2 -g)

set(SRC_FILES
    src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib/Random/build/include/)
link_directories(${CMAKE_SOURCE_DIR}/lib/Random/build/lib/)

add_executable(tp5 ${SRC_FILES})

# enable librarie
if (EXISTS ${CMAKE_SOURCE_DIR}/lib/Random/build/lib/libCLHEP-Random-2.1.0.0.a)
    target_link_libraries(tp5 CLHEP-Random-2.1.0.0)
else()
    message(FATAL_ERROR "CLHEP-Random is not available")
endif()
