cmake_minimum_required(VERSION 3.21)
project(one)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_SOURCES
	${PROJECT_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/constants.h
	PARENT_SCOPE
)
