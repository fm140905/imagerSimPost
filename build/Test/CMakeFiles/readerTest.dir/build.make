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
include Test/CMakeFiles/readerTest.dir/depend.make

# Include the progress variables for this target.
include Test/CMakeFiles/readerTest.dir/progress.make

# Include the compile flags for this target's objects.
include Test/CMakeFiles/readerTest.dir/flags.make

Test/CMakeFiles/readerTest.dir/test.cpp.o: Test/CMakeFiles/readerTest.dir/flags.make
Test/CMakeFiles/readerTest.dir/test.cpp.o: ../Test/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/ming/DATA/projects/Postprocessing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Test/CMakeFiles/readerTest.dir/test.cpp.o"
	cd /media/ming/DATA/projects/Postprocessing/build/Test && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/readerTest.dir/test.cpp.o -c /media/ming/DATA/projects/Postprocessing/Test/test.cpp

Test/CMakeFiles/readerTest.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readerTest.dir/test.cpp.i"
	cd /media/ming/DATA/projects/Postprocessing/build/Test && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/ming/DATA/projects/Postprocessing/Test/test.cpp > CMakeFiles/readerTest.dir/test.cpp.i

Test/CMakeFiles/readerTest.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readerTest.dir/test.cpp.s"
	cd /media/ming/DATA/projects/Postprocessing/build/Test && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/ming/DATA/projects/Postprocessing/Test/test.cpp -o CMakeFiles/readerTest.dir/test.cpp.s

# Object files for target readerTest
readerTest_OBJECTS = \
"CMakeFiles/readerTest.dir/test.cpp.o"

# External object files for target readerTest
readerTest_EXTERNAL_OBJECTS =

Test/readerTest: Test/CMakeFiles/readerTest.dir/test.cpp.o
Test/readerTest: Test/CMakeFiles/readerTest.dir/build.make
Test/readerTest: lib/libgtest_maind.a
Test/readerTest: Sources/libreader.so
Test/readerTest: lib/libgtestd.a
Test/readerTest: Test/CMakeFiles/readerTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/ming/DATA/projects/Postprocessing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable readerTest"
	cd /media/ming/DATA/projects/Postprocessing/build/Test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readerTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Test/CMakeFiles/readerTest.dir/build: Test/readerTest

.PHONY : Test/CMakeFiles/readerTest.dir/build

Test/CMakeFiles/readerTest.dir/clean:
	cd /media/ming/DATA/projects/Postprocessing/build/Test && $(CMAKE_COMMAND) -P CMakeFiles/readerTest.dir/cmake_clean.cmake
.PHONY : Test/CMakeFiles/readerTest.dir/clean

Test/CMakeFiles/readerTest.dir/depend:
	cd /media/ming/DATA/projects/Postprocessing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/ming/DATA/projects/Postprocessing /media/ming/DATA/projects/Postprocessing/Test /media/ming/DATA/projects/Postprocessing/build /media/ming/DATA/projects/Postprocessing/build/Test /media/ming/DATA/projects/Postprocessing/build/Test/CMakeFiles/readerTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Test/CMakeFiles/readerTest.dir/depend

