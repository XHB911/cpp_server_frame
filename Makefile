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
	@echo "... aboo/log.o"
	@echo "... aboo/log.i"
	@echo "... aboo/log.s"
	@echo "... aboo/util.o"
	@echo "... aboo/util.i"
	@echo "... aboo/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
