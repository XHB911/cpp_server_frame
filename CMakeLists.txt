cmake_minimum_required(VERSION 3.2)
project(aboo)

#include (cmake/utils.cmake) # 遗留问题

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

link_directories(/usr/local/lib)

set(LIB_SRC
	aboo/log.cpp
	aboo/util.cpp
	aboo/config.cpp
	)

add_library(aboo SHARED ${LIB_SRC})
#force_redefine_file_macro_for_sources(aboo) #__FILE__ 遗留问题
#add_library(aboo_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (aboo_static PROPERTIES OUTPUT_NAME "aboo")

add_executable(test tests/test.cpp)
#force_redefine_file_macro_for_sources(test) #__FILE__
add_dependencies(test aboo)
target_link_libraries(test aboo -lyaml-cpp)

add_executable(test_config tests/test_config.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_config aboo)
target_link_libraries(test_config aboo -lyaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
