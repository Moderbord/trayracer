# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oem/Repos/trayracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oem/Repos/trayracer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/oem/Repos/trayracer/CMakeFiles /home/oem/Repos/trayracer/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/oem/Repos/trayracer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named trayracer

# Build rule for target.
trayracer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 trayracer
.PHONY : trayracer

# fast build rule for target.
trayracer/fast:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/build
.PHONY : trayracer/fast

#=============================================================================
# Target rules for targets named glew

# Build rule for target.
glew: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 glew
.PHONY : glew

# fast build rule for target.
glew/fast:
	$(MAKE) -f exts/glew/CMakeFiles/glew.dir/build.make exts/glew/CMakeFiles/glew.dir/build
.PHONY : glew/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) -f exts/glfw/src/CMakeFiles/glfw.dir/build.make exts/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

code/main.o: code/main.cc.o

.PHONY : code/main.o

# target to build an object file
code/main.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main.cc.o
.PHONY : code/main.cc.o

code/main.i: code/main.cc.i

.PHONY : code/main.i

# target to preprocess a source file
code/main.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main.cc.i
.PHONY : code/main.cc.i

code/main.s: code/main.cc.s

.PHONY : code/main.s

# target to generate assembly for a file
code/main.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main.cc.s
.PHONY : code/main.cc.s

code/main_copy.o: code/main_copy.cc.o

.PHONY : code/main_copy.o

# target to build an object file
code/main_copy.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main_copy.cc.o
.PHONY : code/main_copy.cc.o

code/main_copy.i: code/main_copy.cc.i

.PHONY : code/main_copy.i

# target to preprocess a source file
code/main_copy.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main_copy.cc.i
.PHONY : code/main_copy.cc.i

code/main_copy.s: code/main_copy.cc.s

.PHONY : code/main_copy.s

# target to generate assembly for a file
code/main_copy.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/main_copy.cc.s
.PHONY : code/main_copy.cc.s

code/material.o: code/material.cc.o

.PHONY : code/material.o

# target to build an object file
code/material.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/material.cc.o
.PHONY : code/material.cc.o

code/material.i: code/material.cc.i

.PHONY : code/material.i

# target to preprocess a source file
code/material.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/material.cc.i
.PHONY : code/material.cc.i

code/material.s: code/material.cc.s

.PHONY : code/material.s

# target to generate assembly for a file
code/material.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/material.cc.s
.PHONY : code/material.cc.s

code/random.o: code/random.cc.o

.PHONY : code/random.o

# target to build an object file
code/random.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/random.cc.o
.PHONY : code/random.cc.o

code/random.i: code/random.cc.i

.PHONY : code/random.i

# target to preprocess a source file
code/random.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/random.cc.i
.PHONY : code/random.cc.i

code/random.s: code/random.cc.s

.PHONY : code/random.s

# target to generate assembly for a file
code/random.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/random.cc.s
.PHONY : code/random.cc.s

code/raytracer.o: code/raytracer.cc.o

.PHONY : code/raytracer.o

# target to build an object file
code/raytracer.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/raytracer.cc.o
.PHONY : code/raytracer.cc.o

code/raytracer.i: code/raytracer.cc.i

.PHONY : code/raytracer.i

# target to preprocess a source file
code/raytracer.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/raytracer.cc.i
.PHONY : code/raytracer.cc.i

code/raytracer.s: code/raytracer.cc.s

.PHONY : code/raytracer.s

# target to generate assembly for a file
code/raytracer.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/raytracer.cc.s
.PHONY : code/raytracer.cc.s

code/window.o: code/window.cc.o

.PHONY : code/window.o

# target to build an object file
code/window.cc.o:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/window.cc.o
.PHONY : code/window.cc.o

code/window.i: code/window.cc.i

.PHONY : code/window.i

# target to preprocess a source file
code/window.cc.i:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/window.cc.i
.PHONY : code/window.cc.i

code/window.s: code/window.cc.s

.PHONY : code/window.s

# target to generate assembly for a file
code/window.cc.s:
	$(MAKE) -f CMakeFiles/trayracer.dir/build.make CMakeFiles/trayracer.dir/code/window.cc.s
.PHONY : code/window.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... trayracer"
	@echo "... glew"
	@echo "... glfw"
	@echo "... code/main.o"
	@echo "... code/main.i"
	@echo "... code/main.s"
	@echo "... code/main_copy.o"
	@echo "... code/main_copy.i"
	@echo "... code/main_copy.s"
	@echo "... code/material.o"
	@echo "... code/material.i"
	@echo "... code/material.s"
	@echo "... code/random.o"
	@echo "... code/random.i"
	@echo "... code/random.s"
	@echo "... code/raytracer.o"
	@echo "... code/raytracer.i"
	@echo "... code/raytracer.s"
	@echo "... code/window.o"
	@echo "... code/window.i"
	@echo "... code/window.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

