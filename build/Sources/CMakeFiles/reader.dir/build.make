# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /media/ming/DATA/projects/Postprocessing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/ming/DATA/projects/Postprocessing/build

# Include any dependencies generated for this target.
include Sources/CMakeFiles/reader.dir/depend.make

# Include the progress variables for this target.
include Sources/CMakeFiles/reader.dir/progress.make

# Include the compile flags for this target's objects.
include Sources/CMakeFiles/reader.dir/flags.make

Sources/CMakeFiles/reader.dir/reader.cpp.o: Sources/CMakeFiles/reader.dir/flags.make
Sources/CMakeFiles/reader.dir/reader.cpp.o: ../Sources/reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/ming/DATA/projects/Postprocessing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Sources/CMakeFiles/reader.dir/reader.cpp.o"
	cd /media/ming/DATA/projects/Postprocessing/build/Sources && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/reader.dir/reader.cpp.o -c /media/ming/DATA/projects/Postprocessing/Sources/reader.cpp

Sources/CMakeFiles/reader.dir/reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reader.dir/reader.cpp.i"
	cd /media/ming/DATA/projects/Postprocessing/build/Sources && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/ming/DATA/projects/Postprocessing/Sources/reader.cpp > CMakeFiles/reader.dir/reader.cpp.i

Sources/CMakeFiles/reader.dir/reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reader.dir/reader.cpp.s"
	cd /media/ming/DATA/projects/Postprocessing/build/Sources && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/ming/DATA/projects/Postprocessing/Sources/reader.cpp -o CMakeFiles/reader.dir/reader.cpp.s

# Object files for target reader
reader_OBJECTS = \
"CMakeFiles/reader.dir/reader.cpp.o"

# External object files for target reader
reader_EXTERNAL_OBJECTS =

Sources/libreader.so: Sources/CMakeFiles/reader.dir/reader.cpp.o
Sources/libreader.so: Sources/CMakeFiles/reader.dir/build.make
Sources/libreader.so: Sources/CMakeFiles/reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/ming/DATA/projects/Postprocessing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libreader.so"
	cd /media/ming/DATA/projects/Postprocessing/build/Sources && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Sources/CMakeFiles/reader.dir/build: Sources/libreader.so

.PHONY : Sources/CMakeFiles/reader.dir/build

Sources/CMakeFiles/reader.dir/clean:
	cd /media/ming/DATA/projects/Postprocessing/build/Sources && $(CMAKE_COMMAND) -P CMakeFiles/reader.dir/cmake_clean.cmake
.PHONY : Sources/CMakeFiles/reader.dir/clean

Sources/CMakeFiles/reader.dir/depend:
	cd /media/ming/DATA/projects/Postprocessing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/ming/DATA/projects/Postprocessing /media/ming/DATA/projects/Postprocessing/Sources /media/ming/DATA/projects/Postprocessing/build /media/ming/DATA/projects/Postprocessing/build/Sources /media/ming/DATA/projects/Postprocessing/build/Sources/CMakeFiles/reader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Sources/CMakeFiles/reader.dir/depend

