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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2

# Include any dependencies generated for this target.
include CMakeFiles/GrayscaleFilter.o.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GrayscaleFilter.o.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GrayscaleFilter.o.dir/flags.make

CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o: CMakeFiles/GrayscaleFilter.o.dir/flags.make
CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o: grayscalefilter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o -c /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/grayscalefilter.cpp

CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/grayscalefilter.cpp > CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.i

CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/grayscalefilter.cpp -o CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.s

# Object files for target GrayscaleFilter.o
GrayscaleFilter_o_OBJECTS = \
"CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o"

# External object files for target GrayscaleFilter.o
GrayscaleFilter_o_EXTERNAL_OBJECTS =

GrayscaleFilter.o: CMakeFiles/GrayscaleFilter.o.dir/grayscalefilter.cpp.o
GrayscaleFilter.o: CMakeFiles/GrayscaleFilter.o.dir/build.make
GrayscaleFilter.o: /usr/local/lib/libopencv_gapi.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_stitching.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_aruco.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_bgsegm.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_bioinspired.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_ccalib.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_dnn_objdetect.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_dnn_superres.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_dpm.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_face.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_freetype.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_fuzzy.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_hfs.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_img_hash.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_line_descriptor.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_quality.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_reg.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_rgbd.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_saliency.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_sfm.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_stereo.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_structured_light.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_superres.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_surface_matching.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_tracking.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_videostab.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_xfeatures2d.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_xobjdetect.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_xphoto.4.2.0.dylib
GrayscaleFilter.o: /usr/local/Cellar/open-mpi/4.0.2/lib/libmpi.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_highgui.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_shape.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_datasets.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_plot.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_text.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_dnn.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_ml.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_phase_unwrapping.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_optflow.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_ximgproc.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_video.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_videoio.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_imgcodecs.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_objdetect.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_calib3d.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_features2d.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_flann.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_photo.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_imgproc.4.2.0.dylib
GrayscaleFilter.o: /usr/local/lib/libopencv_core.4.2.0.dylib
GrayscaleFilter.o: CMakeFiles/GrayscaleFilter.o.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GrayscaleFilter.o"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GrayscaleFilter.o.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GrayscaleFilter.o.dir/build: GrayscaleFilter.o

.PHONY : CMakeFiles/GrayscaleFilter.o.dir/build

CMakeFiles/GrayscaleFilter.o.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GrayscaleFilter.o.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GrayscaleFilter.o.dir/clean

CMakeFiles/GrayscaleFilter.o.dir/depend:
	cd /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2 /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2 /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2 /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2 /Users/ggoteciuc/Documents/University-work/ppd/project/project/project/task2/CMakeFiles/GrayscaleFilter.o.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GrayscaleFilter.o.dir/depend

