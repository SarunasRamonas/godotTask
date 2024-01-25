#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# Set VLC include and library paths
vlc_include_path = 'C:\Projects\GoDotProjects\VLCMisc\libvlcpp\vlcpp'
vlc_lib_path = 'C:\Program Files\VideoLAN\VLC'

env.Append(CPPPATH=[vlc_include_path])
env.Append(LIBPATH=[vlc_lib_path])

# Assuming the VLC library name is 'libvlc'
vlc_lib = 'libvlc'
env.Append(LIBS=[vlc_lib])



# Set OpenCV include and library paths
opencv_include_path = 'C:/Projects/CPPProjects/OpenCVLib/opencv/build/include/opencv2'
opencv_lib_path = 'C:/Projects/CPPProjects/OpenCVLib/opencv/build/x64/vc16/lib'

env.Append(CPPPATH=[opencv_include_path])
env.Append(LIBPATH=[opencv_lib_path])

# Determine the OpenCV library to link based on build configuration
if 'debug' in COMMAND_LINE_TARGETS:
    opencv_lib = 'opencv_world490d'
else:
    opencv_lib = 'opencv_world490'

env.Append(LIBS=[opencv_lib])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/bin/libgdexample{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
