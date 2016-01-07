cmake_minimum_required(VERSION 3.3)
project(SuperMario)

# The output has to be stored in the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Compile C Project
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

# Compile C++ Project
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Configure SDL2
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Build the executable and link it with SDL2
set(SOURCE_FILES src/main.c src/entity.h src/component.h src/entity.c)
add_executable(SuperMario ${SOURCE_FILES})
target_link_libraries(SuperMario SDL2main SDL2)
