cmake_minimum_required(VERSION 3.21)
project(UkkoShakki)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_executable(UkkoShakki src/main.cc src/Globals.hh src/Window.cc src/Window.hh src/Renderer.cc src/Renderer.hh src/ScreenSize.hh src/ScreenSize.cc src/Texture.cc src/Texture.hh src/Board.hh src/Board.cc)
target_link_libraries(UkkoShakki ${SDL2_LIBRARIES} -lSDL2_image)
