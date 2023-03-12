set(THIS utils_lib)
set(CMAKE_CXX_STANDARD 23)

set(UTILS_SOURCES
	constants.h
	comparators.h
	math.h
)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

add_library(${THIS} STATIC ${UTILS_SOURCES})
target_include_directories(${THIS} PUBLIC ${CMAKE_SOURCE_DIR}/utils)
