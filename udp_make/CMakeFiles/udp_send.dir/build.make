# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/chalumpol-linux/Autonomous_no_ros/udp_make

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chalumpol-linux/Autonomous_no_ros/udp_make

# Include any dependencies generated for this target.
include CMakeFiles/udp_send.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/udp_send.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/udp_send.dir/flags.make

CMakeFiles/udp_send.dir/udp_send.cpp.o: CMakeFiles/udp_send.dir/flags.make
CMakeFiles/udp_send.dir/udp_send.cpp.o: udp_send.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chalumpol-linux/Autonomous_no_ros/udp_make/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/udp_send.dir/udp_send.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/udp_send.dir/udp_send.cpp.o -c /home/chalumpol-linux/Autonomous_no_ros/udp_make/udp_send.cpp

CMakeFiles/udp_send.dir/udp_send.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/udp_send.dir/udp_send.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chalumpol-linux/Autonomous_no_ros/udp_make/udp_send.cpp > CMakeFiles/udp_send.dir/udp_send.cpp.i

CMakeFiles/udp_send.dir/udp_send.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/udp_send.dir/udp_send.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chalumpol-linux/Autonomous_no_ros/udp_make/udp_send.cpp -o CMakeFiles/udp_send.dir/udp_send.cpp.s

CMakeFiles/udp_send.dir/udp_send.cpp.o.requires:
.PHONY : CMakeFiles/udp_send.dir/udp_send.cpp.o.requires

CMakeFiles/udp_send.dir/udp_send.cpp.o.provides: CMakeFiles/udp_send.dir/udp_send.cpp.o.requires
	$(MAKE) -f CMakeFiles/udp_send.dir/build.make CMakeFiles/udp_send.dir/udp_send.cpp.o.provides.build
.PHONY : CMakeFiles/udp_send.dir/udp_send.cpp.o.provides

CMakeFiles/udp_send.dir/udp_send.cpp.o.provides.build: CMakeFiles/udp_send.dir/udp_send.cpp.o

# Object files for target udp_send
udp_send_OBJECTS = \
"CMakeFiles/udp_send.dir/udp_send.cpp.o"

# External object files for target udp_send
udp_send_EXTERNAL_OBJECTS =

udp_send: CMakeFiles/udp_send.dir/udp_send.cpp.o
udp_send: CMakeFiles/udp_send.dir/build.make
udp_send: CMakeFiles/udp_send.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable udp_send"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udp_send.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/udp_send.dir/build: udp_send
.PHONY : CMakeFiles/udp_send.dir/build

CMakeFiles/udp_send.dir/requires: CMakeFiles/udp_send.dir/udp_send.cpp.o.requires
.PHONY : CMakeFiles/udp_send.dir/requires

CMakeFiles/udp_send.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/udp_send.dir/cmake_clean.cmake
.PHONY : CMakeFiles/udp_send.dir/clean

CMakeFiles/udp_send.dir/depend:
	cd /home/chalumpol-linux/Autonomous_no_ros/udp_make && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chalumpol-linux/Autonomous_no_ros/udp_make /home/chalumpol-linux/Autonomous_no_ros/udp_make /home/chalumpol-linux/Autonomous_no_ros/udp_make /home/chalumpol-linux/Autonomous_no_ros/udp_make /home/chalumpol-linux/Autonomous_no_ros/udp_make/CMakeFiles/udp_send.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/udp_send.dir/depend
