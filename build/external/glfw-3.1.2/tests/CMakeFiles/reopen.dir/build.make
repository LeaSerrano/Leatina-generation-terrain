# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_SOURCE_DIR = /home/christina/Documents/M1/hai819i/TP2_code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christina/Documents/M1/hai819i/TP2_code/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/flags.make

external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o: external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/flags.make
external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o: ../external/glfw-3.1.2/tests/reopen.c
external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o: external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christina/Documents/M1/hai819i/TP2_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o"
	cd /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o -MF CMakeFiles/reopen.dir/reopen.c.o.d -o CMakeFiles/reopen.dir/reopen.c.o -c /home/christina/Documents/M1/hai819i/TP2_code/external/glfw-3.1.2/tests/reopen.c

external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/christina/Documents/M1/hai819i/TP2_code/external/glfw-3.1.2/tests/reopen.c > CMakeFiles/reopen.dir/reopen.c.i

external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/christina/Documents/M1/hai819i/TP2_code/external/glfw-3.1.2/tests/reopen.c -o CMakeFiles/reopen.dir/reopen.c.s

# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.o"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

external/glfw-3.1.2/tests/reopen: external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.o
external/glfw-3.1.2/tests/reopen: external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build.make
external/glfw-3.1.2/tests/reopen: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/librt.a
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libXrandr.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libXinerama.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libXi.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libXcursor.so
external/glfw-3.1.2/tests/reopen: /usr/lib/x86_64-linux-gnu/libGL.so
external/glfw-3.1.2/tests/reopen: external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/christina/Documents/M1/hai819i/TP2_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable reopen"
	cd /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reopen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build: external/glfw-3.1.2/tests/reopen
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build

external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/clean:
	cd /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/reopen.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/clean

external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend:
	cd /home/christina/Documents/M1/hai819i/TP2_code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christina/Documents/M1/hai819i/TP2_code /home/christina/Documents/M1/hai819i/TP2_code/external/glfw-3.1.2/tests /home/christina/Documents/M1/hai819i/TP2_code/build /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests /home/christina/Documents/M1/hai819i/TP2_code/build/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend

