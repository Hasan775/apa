cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(apa)
set (CMAKE_CXX_STANDARD 17)
add_executable(apa main.cpp Lexer.cpp Parser.cpp Token.cpp Node.cpp Error.cpp Runner.cpp Lexer.h Parser.h Token.h Node.h Error.h Runner.h)