cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(PROJECT_NAMESPACE "cya")
project("PR4-CYA-2425"
	VERSION 1.0.0
	DESCRIPTION "Práctica 4 de Cya 2024-2025"
	LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SHORTNAME "cya")
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory("src")
