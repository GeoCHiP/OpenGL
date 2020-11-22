cmake_minimum_required(VERSION 3.17)
project(stb_image)

add_library(stb_image stb_image.cpp stb_image.h)
message(STATUS "stb_image: v2.26")