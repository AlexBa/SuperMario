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

configure_file(img/player.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)

# Build the executable and link it with SDL2
set(SOURCE_FILES src/main.c src/entity/entity.h src/entity/entity.c src/entity/player.h src/entity/player.c src/component/component.h src/graphic/sprite.h src/graphic/sprite.c src/graphic/tile.h src/graphic/tile.c src/system/system.h src/system/system.c src/graphic/texture.c src/graphic/texture.h src/game/level.c src/game/level.c src/game/level.h)
add_executable(SuperMario ${SOURCE_FILES})
target_link_libraries(SuperMario SDL2main SDL2 SDL2_image)
