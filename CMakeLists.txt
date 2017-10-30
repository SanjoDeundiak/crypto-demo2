cmake_minimum_required(VERSION 3.8)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/JiffyGenerator.cxx src/JiffyGenerator.h src/LFSR.cxx src/LFSR.h src/JiffyCryptoAnalysis.cxx src/JiffyCryptoAnalysis.h src/Phi.cxx src/Phi.h)
add_executable(lab2 ${SOURCE_FILES})