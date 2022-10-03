# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hb/cpp_server_frame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hb/cpp_server_frame

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hb/cpp_server_frame/CMakeFiles /home/hb/cpp_server_frame//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hb/cpp_server_frame/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named aboo

# Build rule for target.
aboo: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 aboo
.PHONY : aboo

# fast build rule for target.
aboo/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/build
.PHONY : aboo/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named test_config

# Build rule for target.
test_config: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_config
.PHONY : test_config

# fast build rule for target.
test_config/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/build
.PHONY : test_config/fast

#=============================================================================
# Target rules for targets named test_thread

# Build rule for target.
test_thread: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_thread
.PHONY : test_thread

# fast build rule for target.
test_thread/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/build
.PHONY : test_thread/fast

#=============================================================================
# Target rules for targets named test_util

# Build rule for target.
test_util: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_util
.PHONY : test_util

# fast build rule for target.
test_util/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/build
.PHONY : test_util/fast

#=============================================================================
# Target rules for targets named test_fiber

# Build rule for target.
test_fiber: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_fiber
.PHONY : test_fiber

# fast build rule for target.
test_fiber/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/build
.PHONY : test_fiber/fast

#=============================================================================
# Target rules for targets named test_scheduler

# Build rule for target.
test_scheduler: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_scheduler
.PHONY : test_scheduler

# fast build rule for target.
test_scheduler/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/build
.PHONY : test_scheduler/fast

#=============================================================================
# Target rules for targets named test_iomanager

# Build rule for target.
test_iomanager: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_iomanager
.PHONY : test_iomanager

# fast build rule for target.
test_iomanager/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/build
.PHONY : test_iomanager/fast

#=============================================================================
# Target rules for targets named test_hook

# Build rule for target.
test_hook: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_hook
.PHONY : test_hook

# fast build rule for target.
test_hook/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/build
.PHONY : test_hook/fast

#=============================================================================
# Target rules for targets named test_address

# Build rule for target.
test_address: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_address
.PHONY : test_address

# fast build rule for target.
test_address/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/build
.PHONY : test_address/fast

aboo/address.o: aboo/address.cpp.o
.PHONY : aboo/address.o

# target to build an object file
aboo/address.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/address.cpp.o
.PHONY : aboo/address.cpp.o

aboo/address.i: aboo/address.cpp.i
.PHONY : aboo/address.i

# target to preprocess a source file
aboo/address.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/address.cpp.i
.PHONY : aboo/address.cpp.i

aboo/address.s: aboo/address.cpp.s
.PHONY : aboo/address.s

# target to generate assembly for a file
aboo/address.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/address.cpp.s
.PHONY : aboo/address.cpp.s

aboo/config.o: aboo/config.cpp.o
.PHONY : aboo/config.o

# target to build an object file
aboo/config.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/config.cpp.o
.PHONY : aboo/config.cpp.o

aboo/config.i: aboo/config.cpp.i
.PHONY : aboo/config.i

# target to preprocess a source file
aboo/config.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/config.cpp.i
.PHONY : aboo/config.cpp.i

aboo/config.s: aboo/config.cpp.s
.PHONY : aboo/config.s

# target to generate assembly for a file
aboo/config.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/config.cpp.s
.PHONY : aboo/config.cpp.s

aboo/fd_manager.o: aboo/fd_manager.cpp.o
.PHONY : aboo/fd_manager.o

# target to build an object file
aboo/fd_manager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fd_manager.cpp.o
.PHONY : aboo/fd_manager.cpp.o

aboo/fd_manager.i: aboo/fd_manager.cpp.i
.PHONY : aboo/fd_manager.i

# target to preprocess a source file
aboo/fd_manager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fd_manager.cpp.i
.PHONY : aboo/fd_manager.cpp.i

aboo/fd_manager.s: aboo/fd_manager.cpp.s
.PHONY : aboo/fd_manager.s

# target to generate assembly for a file
aboo/fd_manager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fd_manager.cpp.s
.PHONY : aboo/fd_manager.cpp.s

aboo/fiber.o: aboo/fiber.cpp.o
.PHONY : aboo/fiber.o

# target to build an object file
aboo/fiber.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fiber.cpp.o
.PHONY : aboo/fiber.cpp.o

aboo/fiber.i: aboo/fiber.cpp.i
.PHONY : aboo/fiber.i

# target to preprocess a source file
aboo/fiber.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fiber.cpp.i
.PHONY : aboo/fiber.cpp.i

aboo/fiber.s: aboo/fiber.cpp.s
.PHONY : aboo/fiber.s

# target to generate assembly for a file
aboo/fiber.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/fiber.cpp.s
.PHONY : aboo/fiber.cpp.s

aboo/hook.o: aboo/hook.cpp.o
.PHONY : aboo/hook.o

# target to build an object file
aboo/hook.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/hook.cpp.o
.PHONY : aboo/hook.cpp.o

aboo/hook.i: aboo/hook.cpp.i
.PHONY : aboo/hook.i

# target to preprocess a source file
aboo/hook.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/hook.cpp.i
.PHONY : aboo/hook.cpp.i

aboo/hook.s: aboo/hook.cpp.s
.PHONY : aboo/hook.s

# target to generate assembly for a file
aboo/hook.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/hook.cpp.s
.PHONY : aboo/hook.cpp.s

aboo/iomanager.o: aboo/iomanager.cpp.o
.PHONY : aboo/iomanager.o

# target to build an object file
aboo/iomanager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/iomanager.cpp.o
.PHONY : aboo/iomanager.cpp.o

aboo/iomanager.i: aboo/iomanager.cpp.i
.PHONY : aboo/iomanager.i

# target to preprocess a source file
aboo/iomanager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/iomanager.cpp.i
.PHONY : aboo/iomanager.cpp.i

aboo/iomanager.s: aboo/iomanager.cpp.s
.PHONY : aboo/iomanager.s

# target to generate assembly for a file
aboo/iomanager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/iomanager.cpp.s
.PHONY : aboo/iomanager.cpp.s

aboo/log.o: aboo/log.cpp.o
.PHONY : aboo/log.o

# target to build an object file
aboo/log.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/log.cpp.o
.PHONY : aboo/log.cpp.o

aboo/log.i: aboo/log.cpp.i
.PHONY : aboo/log.i

# target to preprocess a source file
aboo/log.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/log.cpp.i
.PHONY : aboo/log.cpp.i

aboo/log.s: aboo/log.cpp.s
.PHONY : aboo/log.s

# target to generate assembly for a file
aboo/log.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/log.cpp.s
.PHONY : aboo/log.cpp.s

aboo/scheduler.o: aboo/scheduler.cpp.o
.PHONY : aboo/scheduler.o

# target to build an object file
aboo/scheduler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/scheduler.cpp.o
.PHONY : aboo/scheduler.cpp.o

aboo/scheduler.i: aboo/scheduler.cpp.i
.PHONY : aboo/scheduler.i

# target to preprocess a source file
aboo/scheduler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/scheduler.cpp.i
.PHONY : aboo/scheduler.cpp.i

aboo/scheduler.s: aboo/scheduler.cpp.s
.PHONY : aboo/scheduler.s

# target to generate assembly for a file
aboo/scheduler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/scheduler.cpp.s
.PHONY : aboo/scheduler.cpp.s

aboo/thread.o: aboo/thread.cpp.o
.PHONY : aboo/thread.o

# target to build an object file
aboo/thread.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/thread.cpp.o
.PHONY : aboo/thread.cpp.o

aboo/thread.i: aboo/thread.cpp.i
.PHONY : aboo/thread.i

# target to preprocess a source file
aboo/thread.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/thread.cpp.i
.PHONY : aboo/thread.cpp.i

aboo/thread.s: aboo/thread.cpp.s
.PHONY : aboo/thread.s

# target to generate assembly for a file
aboo/thread.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/thread.cpp.s
.PHONY : aboo/thread.cpp.s

aboo/timer.o: aboo/timer.cpp.o
.PHONY : aboo/timer.o

# target to build an object file
aboo/timer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/timer.cpp.o
.PHONY : aboo/timer.cpp.o

aboo/timer.i: aboo/timer.cpp.i
.PHONY : aboo/timer.i

# target to preprocess a source file
aboo/timer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/timer.cpp.i
.PHONY : aboo/timer.cpp.i

aboo/timer.s: aboo/timer.cpp.s
.PHONY : aboo/timer.s

# target to generate assembly for a file
aboo/timer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/timer.cpp.s
.PHONY : aboo/timer.cpp.s

aboo/util.o: aboo/util.cpp.o
.PHONY : aboo/util.o

# target to build an object file
aboo/util.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/util.cpp.o
.PHONY : aboo/util.cpp.o

aboo/util.i: aboo/util.cpp.i
.PHONY : aboo/util.i

# target to preprocess a source file
aboo/util.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/util.cpp.i
.PHONY : aboo/util.cpp.i

aboo/util.s: aboo/util.cpp.s
.PHONY : aboo/util.s

# target to generate assembly for a file
aboo/util.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/aboo.dir/build.make CMakeFiles/aboo.dir/aboo/util.cpp.s
.PHONY : aboo/util.cpp.s

tests/test.o: tests/test.cpp.o
.PHONY : tests/test.o

# target to build an object file
tests/test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.o
.PHONY : tests/test.cpp.o

tests/test.i: tests/test.cpp.i
.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.i
.PHONY : tests/test.cpp.i

tests/test.s: tests/test.cpp.s
.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.s
.PHONY : tests/test.cpp.s

tests/test_address.o: tests/test_address.cpp.o
.PHONY : tests/test_address.o

# target to build an object file
tests/test_address.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cpp.o
.PHONY : tests/test_address.cpp.o

tests/test_address.i: tests/test_address.cpp.i
.PHONY : tests/test_address.i

# target to preprocess a source file
tests/test_address.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cpp.i
.PHONY : tests/test_address.cpp.i

tests/test_address.s: tests/test_address.cpp.s
.PHONY : tests/test_address.s

# target to generate assembly for a file
tests/test_address.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_address.dir/build.make CMakeFiles/test_address.dir/tests/test_address.cpp.s
.PHONY : tests/test_address.cpp.s

tests/test_config.o: tests/test_config.cpp.o
.PHONY : tests/test_config.o

# target to build an object file
tests/test_config.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.o
.PHONY : tests/test_config.cpp.o

tests/test_config.i: tests/test_config.cpp.i
.PHONY : tests/test_config.i

# target to preprocess a source file
tests/test_config.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.i
.PHONY : tests/test_config.cpp.i

tests/test_config.s: tests/test_config.cpp.s
.PHONY : tests/test_config.s

# target to generate assembly for a file
tests/test_config.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.s
.PHONY : tests/test_config.cpp.s

tests/test_fiber.o: tests/test_fiber.cpp.o
.PHONY : tests/test_fiber.o

# target to build an object file
tests/test_fiber.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.o
.PHONY : tests/test_fiber.cpp.o

tests/test_fiber.i: tests/test_fiber.cpp.i
.PHONY : tests/test_fiber.i

# target to preprocess a source file
tests/test_fiber.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.i
.PHONY : tests/test_fiber.cpp.i

tests/test_fiber.s: tests/test_fiber.cpp.s
.PHONY : tests/test_fiber.s

# target to generate assembly for a file
tests/test_fiber.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_fiber.dir/build.make CMakeFiles/test_fiber.dir/tests/test_fiber.cpp.s
.PHONY : tests/test_fiber.cpp.s

tests/test_hook.o: tests/test_hook.cpp.o
.PHONY : tests/test_hook.o

# target to build an object file
tests/test_hook.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cpp.o
.PHONY : tests/test_hook.cpp.o

tests/test_hook.i: tests/test_hook.cpp.i
.PHONY : tests/test_hook.i

# target to preprocess a source file
tests/test_hook.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cpp.i
.PHONY : tests/test_hook.cpp.i

tests/test_hook.s: tests/test_hook.cpp.s
.PHONY : tests/test_hook.s

# target to generate assembly for a file
tests/test_hook.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_hook.dir/build.make CMakeFiles/test_hook.dir/tests/test_hook.cpp.s
.PHONY : tests/test_hook.cpp.s

tests/test_iomanager.o: tests/test_iomanager.cpp.o
.PHONY : tests/test_iomanager.o

# target to build an object file
tests/test_iomanager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cpp.o
.PHONY : tests/test_iomanager.cpp.o

tests/test_iomanager.i: tests/test_iomanager.cpp.i
.PHONY : tests/test_iomanager.i

# target to preprocess a source file
tests/test_iomanager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cpp.i
.PHONY : tests/test_iomanager.cpp.i

tests/test_iomanager.s: tests/test_iomanager.cpp.s
.PHONY : tests/test_iomanager.s

# target to generate assembly for a file
tests/test_iomanager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_iomanager.dir/build.make CMakeFiles/test_iomanager.dir/tests/test_iomanager.cpp.s
.PHONY : tests/test_iomanager.cpp.s

tests/test_scheduler.o: tests/test_scheduler.cpp.o
.PHONY : tests/test_scheduler.o

# target to build an object file
tests/test_scheduler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cpp.o
.PHONY : tests/test_scheduler.cpp.o

tests/test_scheduler.i: tests/test_scheduler.cpp.i
.PHONY : tests/test_scheduler.i

# target to preprocess a source file
tests/test_scheduler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cpp.i
.PHONY : tests/test_scheduler.cpp.i

tests/test_scheduler.s: tests/test_scheduler.cpp.s
.PHONY : tests/test_scheduler.s

# target to generate assembly for a file
tests/test_scheduler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_scheduler.dir/build.make CMakeFiles/test_scheduler.dir/tests/test_scheduler.cpp.s
.PHONY : tests/test_scheduler.cpp.s

tests/test_thread.o: tests/test_thread.cpp.o
.PHONY : tests/test_thread.o

# target to build an object file
tests/test_thread.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.o
.PHONY : tests/test_thread.cpp.o

tests/test_thread.i: tests/test_thread.cpp.i
.PHONY : tests/test_thread.i

# target to preprocess a source file
tests/test_thread.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.i
.PHONY : tests/test_thread.cpp.i

tests/test_thread.s: tests/test_thread.cpp.s
.PHONY : tests/test_thread.s

# target to generate assembly for a file
tests/test_thread.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.s
.PHONY : tests/test_thread.cpp.s

tests/test_util.o: tests/test_util.cpp.o
.PHONY : tests/test_util.o

# target to build an object file
tests/test_util.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.o
.PHONY : tests/test_util.cpp.o

tests/test_util.i: tests/test_util.cpp.i
.PHONY : tests/test_util.i

# target to preprocess a source file
tests/test_util.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.i
.PHONY : tests/test_util.cpp.i

tests/test_util.s: tests/test_util.cpp.s
.PHONY : tests/test_util.s

# target to generate assembly for a file
tests/test_util.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.s
.PHONY : tests/test_util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... aboo"
	@echo "... test"
	@echo "... test_address"
	@echo "... test_config"
	@echo "... test_fiber"
	@echo "... test_hook"
	@echo "... test_iomanager"
	@echo "... test_scheduler"
	@echo "... test_thread"
	@echo "... test_util"
	@echo "... aboo/address.o"
	@echo "... aboo/address.i"
	@echo "... aboo/address.s"
	@echo "... aboo/config.o"
	@echo "... aboo/config.i"
	@echo "... aboo/config.s"
	@echo "... aboo/fd_manager.o"
	@echo "... aboo/fd_manager.i"
	@echo "... aboo/fd_manager.s"
	@echo "... aboo/fiber.o"
	@echo "... aboo/fiber.i"
	@echo "... aboo/fiber.s"
	@echo "... aboo/hook.o"
	@echo "... aboo/hook.i"
	@echo "... aboo/hook.s"
	@echo "... aboo/iomanager.o"
	@echo "... aboo/iomanager.i"
	@echo "... aboo/iomanager.s"
	@echo "... aboo/log.o"
	@echo "... aboo/log.i"
	@echo "... aboo/log.s"
	@echo "... aboo/scheduler.o"
	@echo "... aboo/scheduler.i"
	@echo "... aboo/scheduler.s"
	@echo "... aboo/thread.o"
	@echo "... aboo/thread.i"
	@echo "... aboo/thread.s"
	@echo "... aboo/timer.o"
	@echo "... aboo/timer.i"
	@echo "... aboo/timer.s"
	@echo "... aboo/util.o"
	@echo "... aboo/util.i"
	@echo "... aboo/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/test_address.o"
	@echo "... tests/test_address.i"
	@echo "... tests/test_address.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_fiber.o"
	@echo "... tests/test_fiber.i"
	@echo "... tests/test_fiber.s"
	@echo "... tests/test_hook.o"
	@echo "... tests/test_hook.i"
	@echo "... tests/test_hook.s"
	@echo "... tests/test_iomanager.o"
	@echo "... tests/test_iomanager.i"
	@echo "... tests/test_iomanager.s"
	@echo "... tests/test_scheduler.o"
	@echo "... tests/test_scheduler.i"
	@echo "... tests/test_scheduler.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/test_util.o"
	@echo "... tests/test_util.i"
	@echo "... tests/test_util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

