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

configure_file(bin/player.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/back.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/mushroom.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/gumba.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/brick.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/pyro.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)
configure_file(img/fireball.bmp ${CMAKE_SOURCE_DIR}/bin COPYONLY)

# Build the executable and link it with SDL2
set(SOURCE_FILES src/main.c src/system/collision.h src/system/collision.c src/entity/entity.h src/entity/entity.c src/entity/player.h src/entity/player.c src/component/component.h src/graphic/sprite.h src/graphic/sprite.c src/graphic/tile.h src/graphic/tile.c src/system/system.h src/system/system.c src/graphic/texture.c src/graphic/texture.h src/game/level.c src/game/level.c src/game/level.h src/game/game.c src/game/game.h src/entity/enemy.c src/entity/enemy.h src/entity/mushroom.c src/entity/mushroom.h src/entity/pyro.c src/entity/pyro.h src/entity/fireball.c src/entity/fireball.h src/entity/fireflower.c src/entity/fireflower.h src/entity/coin.c src/entity/coin.h)
add_executable(SuperMario ${SOURCE_FILES})
target_link_libraries(SuperMario SDL2main SDL2 SDL2_image)
