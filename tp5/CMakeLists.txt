cmake_minimum_required(VERSION 3.25.1)

project(tp5)

set(CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_compile_options(-Wall -Wextra -O2 -g)

set(SRC_FILES
    src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib/CLHEP-lib/include/)
link_directories(${CMAKE_SOURCE_DIR}/lib/CLHEP-lib/lib/)

add_executable(tp5 ${SRC_FILES})

# enable librarie
if (EXISTS ${CMAKE_SOURCE_DIR}/lib/CLHEP-lib/lib/libCLHEP-Random-2.4.7.1.a)
    target_link_libraries(tp5 CLHEP-Random-2.4.7.1)
else()
    message(FATAL_ERROR "CLHEP-Random is not available")
endif()
