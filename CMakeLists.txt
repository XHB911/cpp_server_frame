cmake_minimum_required(VERSION 3.2)
project(aboo)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

set(LIB_SRC 
	aboo/log.cpp
	aboo/util.cpp
	)

add_library(aboo SHARED ${LIB_SRC})
#add_library(aboo_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (aboo_static PROPERTIES OUTPUT_NAME "aboo")

add_executable(test tests/test.cpp)
add_dependencies(test aboo)
target_link_libraries(test aboo)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
