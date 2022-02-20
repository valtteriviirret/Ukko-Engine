cmake_minimum_required(VERSION 3.21)
project(UkkoShakki)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug) # debug mode
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
add_executable(UkkoShakki
	src/main.cc 
	src/Window.cc
	src/Renderer.cc
	src/ScreenSize.cc
	src/Texture.cc 
	src/Board.cc 
	src/PieceFactory.cc
	src/PieceRenderer.cc
	src/Game.cc
	src/GUI.cc
	src/SquareManager.cc
	src/LegalMoves.cc
	src/Settings.cc
	src/Pieces.cc
	src/Move.cc
	src/Engine.cc
	src/Global.cc
	src/FontLoader.cc
	src/Text.cc
	src/GameManager.cc
	src/MinMax.cc
	)

target_link_libraries(UkkoShakki ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_ttf)
