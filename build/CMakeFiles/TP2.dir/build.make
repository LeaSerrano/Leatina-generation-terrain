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
CMAKE_SOURCE_DIR = /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build

# Include any dependencies generated for this target.
include CMakeFiles/TP2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TP2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TP2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP2.dir/flags.make

CMakeFiles/TP2.dir/TP2/TP2.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/TP2/TP2.cpp.o: ../TP2/TP2.cpp
CMakeFiles/TP2.dir/TP2/TP2.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP2.dir/TP2/TP2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/TP2/TP2.cpp.o -MF CMakeFiles/TP2.dir/TP2/TP2.cpp.o.d -o CMakeFiles/TP2.dir/TP2/TP2.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/TP2/TP2.cpp

CMakeFiles/TP2.dir/TP2/TP2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/TP2/TP2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/TP2/TP2.cpp > CMakeFiles/TP2.dir/TP2/TP2.cpp.i

CMakeFiles/TP2.dir/TP2/TP2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/TP2/TP2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/TP2/TP2.cpp -o CMakeFiles/TP2.dir/TP2/TP2.cpp.s

CMakeFiles/TP2.dir/common/shader.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/common/shader.cpp.o: ../common/shader.cpp
CMakeFiles/TP2.dir/common/shader.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TP2.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/common/shader.cpp.o -MF CMakeFiles/TP2.dir/common/shader.cpp.o.d -o CMakeFiles/TP2.dir/common/shader.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/shader.cpp

CMakeFiles/TP2.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/shader.cpp > CMakeFiles/TP2.dir/common/shader.cpp.i

CMakeFiles/TP2.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/shader.cpp -o CMakeFiles/TP2.dir/common/shader.cpp.s

CMakeFiles/TP2.dir/common/controls.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/common/controls.cpp.o: ../common/controls.cpp
CMakeFiles/TP2.dir/common/controls.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TP2.dir/common/controls.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/common/controls.cpp.o -MF CMakeFiles/TP2.dir/common/controls.cpp.o.d -o CMakeFiles/TP2.dir/common/controls.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/controls.cpp

CMakeFiles/TP2.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/common/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/controls.cpp > CMakeFiles/TP2.dir/common/controls.cpp.i

CMakeFiles/TP2.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/common/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/controls.cpp -o CMakeFiles/TP2.dir/common/controls.cpp.s

CMakeFiles/TP2.dir/common/texture.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/common/texture.cpp.o: ../common/texture.cpp
CMakeFiles/TP2.dir/common/texture.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TP2.dir/common/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/common/texture.cpp.o -MF CMakeFiles/TP2.dir/common/texture.cpp.o.d -o CMakeFiles/TP2.dir/common/texture.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/texture.cpp

CMakeFiles/TP2.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/common/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/texture.cpp > CMakeFiles/TP2.dir/common/texture.cpp.i

CMakeFiles/TP2.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/common/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/texture.cpp -o CMakeFiles/TP2.dir/common/texture.cpp.s

CMakeFiles/TP2.dir/common/objloader.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/common/objloader.cpp.o: ../common/objloader.cpp
CMakeFiles/TP2.dir/common/objloader.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TP2.dir/common/objloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/common/objloader.cpp.o -MF CMakeFiles/TP2.dir/common/objloader.cpp.o.d -o CMakeFiles/TP2.dir/common/objloader.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/objloader.cpp

CMakeFiles/TP2.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/common/objloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/objloader.cpp > CMakeFiles/TP2.dir/common/objloader.cpp.i

CMakeFiles/TP2.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/common/objloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/objloader.cpp -o CMakeFiles/TP2.dir/common/objloader.cpp.s

CMakeFiles/TP2.dir/common/vboindexer.cpp.o: CMakeFiles/TP2.dir/flags.make
CMakeFiles/TP2.dir/common/vboindexer.cpp.o: ../common/vboindexer.cpp
CMakeFiles/TP2.dir/common/vboindexer.cpp.o: CMakeFiles/TP2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TP2.dir/common/vboindexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TP2.dir/common/vboindexer.cpp.o -MF CMakeFiles/TP2.dir/common/vboindexer.cpp.o.d -o CMakeFiles/TP2.dir/common/vboindexer.cpp.o -c /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/vboindexer.cpp

CMakeFiles/TP2.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2.dir/common/vboindexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/vboindexer.cpp > CMakeFiles/TP2.dir/common/vboindexer.cpp.i

CMakeFiles/TP2.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2.dir/common/vboindexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/common/vboindexer.cpp -o CMakeFiles/TP2.dir/common/vboindexer.cpp.s

# Object files for target TP2
TP2_OBJECTS = \
"CMakeFiles/TP2.dir/TP2/TP2.cpp.o" \
"CMakeFiles/TP2.dir/common/shader.cpp.o" \
"CMakeFiles/TP2.dir/common/controls.cpp.o" \
"CMakeFiles/TP2.dir/common/texture.cpp.o" \
"CMakeFiles/TP2.dir/common/objloader.cpp.o" \
"CMakeFiles/TP2.dir/common/vboindexer.cpp.o"

# External object files for target TP2
TP2_EXTERNAL_OBJECTS =

TP2: CMakeFiles/TP2.dir/TP2/TP2.cpp.o
TP2: CMakeFiles/TP2.dir/common/shader.cpp.o
TP2: CMakeFiles/TP2.dir/common/controls.cpp.o
TP2: CMakeFiles/TP2.dir/common/texture.cpp.o
TP2: CMakeFiles/TP2.dir/common/objloader.cpp.o
TP2: CMakeFiles/TP2.dir/common/vboindexer.cpp.o
TP2: CMakeFiles/TP2.dir/build.make
TP2: /usr/lib/x86_64-linux-gnu/libGL.so
TP2: /usr/lib/x86_64-linux-gnu/libGLU.so
TP2: external/glfw-3.1.2/src/libglfw3.a
TP2: external/libGLEW_1130.a
TP2: /usr/lib/x86_64-linux-gnu/librt.a
TP2: /usr/lib/x86_64-linux-gnu/libm.so
TP2: /usr/lib/x86_64-linux-gnu/libX11.so
TP2: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP2: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP2: /usr/lib/x86_64-linux-gnu/libXi.so
TP2: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
TP2: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP2: /usr/lib/x86_64-linux-gnu/librt.a
TP2: /usr/lib/x86_64-linux-gnu/libm.so
TP2: /usr/lib/x86_64-linux-gnu/libX11.so
TP2: /usr/lib/x86_64-linux-gnu/libXrandr.so
TP2: /usr/lib/x86_64-linux-gnu/libXinerama.so
TP2: /usr/lib/x86_64-linux-gnu/libXi.so
TP2: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
TP2: /usr/lib/x86_64-linux-gnu/libXcursor.so
TP2: /usr/lib/x86_64-linux-gnu/libGL.so
TP2: /usr/lib/x86_64-linux-gnu/libGLU.so
TP2: CMakeFiles/TP2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable TP2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP2.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/./TP2 /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/TP2/

# Rule to build all files generated by this target.
CMakeFiles/TP2.dir/build: TP2
.PHONY : CMakeFiles/TP2.dir/build

CMakeFiles/TP2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP2.dir/clean

CMakeFiles/TP2.dir/depend:
	cd /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build /home/lea/M2-IMAGINE/Projet3D/Leatina-generation-terrain/build/CMakeFiles/TP2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP2.dir/depend

