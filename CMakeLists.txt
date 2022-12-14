cmake_minimum_required(VERSION 3.2)
project(aboo)

#include (cmake/utils.cmake) # 遗留问题

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function")

link_directories(/usr/local/lib)

set(LIB_SRC
	aboo/address.cpp
	aboo/bytearray.cpp
	aboo/config.cpp
	aboo/fd_manager.cpp
	aboo/fiber.cpp
	aboo/http/http.cpp
	aboo/http/http_parser.cpp
	aboo/http/http11_parser.rl.cpp
	aboo/http/httpclient_parser.rl.cpp
	aboo/iomanager.cpp
	aboo/log.cpp
	aboo/hook.cpp
	aboo/thread.cpp
	aboo/scheduler.cpp
	aboo/socket.cpp
	aboo/timer.cpp
	aboo/util.cpp
	)

add_library(aboo SHARED ${LIB_SRC})
#force_redefine_file_macro_for_sources(aboo) #__FILE__ 遗留问题
#add_library(aboo_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (aboo_static PROPERTIES OUTPUT_NAME "aboo")

set(LIB_LIB
	aboo
	dl
	pthread
	-lyaml-cpp
	)

add_executable(test tests/test.cpp)
#force_redefine_file_macro_for_sources(test) #__FILE__
add_dependencies(test aboo)
target_link_libraries(test ${LIB_LIB})

add_executable(test_config tests/test_config.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_config aboo)
target_link_libraries(test_config ${LIB_LIB})

add_executable(test_thread tests/test_thread.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_thread aboo)
target_link_libraries(test_thread ${LIB_LIB})

add_executable(test_util tests/test_util.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_util aboo)
target_link_libraries(test_util ${LIB_LIB})

add_executable(test_fiber tests/test_fiber.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_fiber aboo)
target_link_libraries(test_fiber ${LIB_LIB})

add_executable(test_scheduler tests/test_scheduler.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_scheduler aboo)
target_link_libraries(test_scheduler ${LIB_LIB})

add_executable(test_iomanager tests/test_iomanager.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_iomanager aboo)
target_link_libraries(test_iomanager ${LIB_LIB})

add_executable(test_hook tests/test_hook.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_hook aboo)
target_link_libraries(test_hook ${LIB_LIB})

add_executable(test_address tests/test_address.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_address aboo)
target_link_libraries(test_address ${LIB_LIB})

add_executable(test_socket tests/test_socket.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_socket aboo)
target_link_libraries(test_socket ${LIB_LIB})

add_executable(test_bytearray tests/test_bytearray.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_bytearray aboo)
target_link_libraries(test_bytearray ${LIB_LIB})

add_executable(test_http tests/test_http.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_http aboo)
target_link_libraries(test_http ${LIB_LIB})

add_executable(test_http_parser tests/test_http_parser.cpp)
#force_redefine_file_macro_for_sources(test_config) #__FILE__
add_dependencies(test_http_parser aboo)
target_link_libraries(test_http_parser ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
