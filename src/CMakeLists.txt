cmake_minimum_required(VERSION 3.21)
project(one)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_SOURCES
	${PROJECT_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/structures/matrix/matrix.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/structures/matrix/matrix.h

	${CMAKE_CURRENT_SOURCE_DIR}/structures/vector/vector.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/structures/vector/vector.h

	${CMAKE_CURRENT_SOURCE_DIR}/linear_systems_solvers/base_linear_system_solver.h
	${CMAKE_CURRENT_SOURCE_DIR}/linear_systems_solvers/gaussian/gaussian.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/linear_systems_solvers/gaussian/gaussian.h

	${CMAKE_CURRENT_SOURCE_DIR}/file_processors/file_processors.h
	${CMAKE_CURRENT_SOURCE_DIR}/file_processors/base_file_processor.h
	${CMAKE_CURRENT_SOURCE_DIR}/file_processors/matrix_file_processor.cpp
	PARENT_SCOPE
)
