set(THIS linear_algebra_lib)
set(CMAKE_CXX_STANDARD 17)

set(SRC_SOURCES
	structures/matrix/matrix.cpp
	structures/matrix/matrix.h

	structures/vector/vector.cpp
	structures/vector/vector.h

	linear_systems_solvers/base_linear_system_solver.h
	linear_systems_solvers/base_linear_system_solver.cpp
	linear_systems_solvers/gaussian/gaussian.cpp
	linear_systems_solvers/gaussian/gaussian.h

	file_processors/file_processors.h
	file_processors/base_file_processor.h
	file_processors/matrix_file_processor.cpp
	file_processors/gaussian_file_processor.cpp
)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

add_library(${THIS} STATIC ${SRC_SOURCES})
target_include_directories(${THIS} PUBLIC ${CMAKE_SOURCE_DIR}/src)
