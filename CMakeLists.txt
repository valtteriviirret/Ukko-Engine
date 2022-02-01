cmake_minimum_required(VERSION 3.21)
project(UkkoShakki)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(UkkoShakki
	src/main.cc 
	src/Window.cc
	src/Window.hh
	src/Renderer.cc
	src/Renderer.hh
	src/ScreenSize.hh
	src/ScreenSize.cc
	src/Texture.cc 
	src/Texture.hh 
	src/Board.hh 
	src/Board.cc 
	src/PieceFactory.cc
	src/PieceFactory.hh
	src/PieceRenderer.hh 
	src/PieceRenderer.cc
	src/Game.hh
	src/Game.cc
	src/GUI.cc
	src/GUI.hh
	src/Piece.hh
	src/SquareManager.cc
	src/SquareManager.hh
	src/LegalMoves.cc
	src/LegalMoves.hh
	src/Settings.cc
	src/Settings.hh
	src/Pieces.cc
	src/Pieces.hh
	src/Move.cc
	src/Move.hh
	src/Engine.cc
	src/Engine.hh
	src/Global.hh
	src/Global.cc
	src/FontLoader.cpp
	src/FontLoader.h
	src/Text.cpp
	src/Text.h)


target_link_libraries(UkkoShakki SDL2::Main SDL2::Image SDL2::TTF)
