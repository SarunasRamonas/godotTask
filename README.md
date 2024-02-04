# Assignment Project

## Project Overview
The Assignment Project is a Godot-based project designed to extract and return the raw values (RGB struct) of a selected pixel and visualize these values using a GLSL shader.
![screenshot](doc/images/screenshot1.png "screenshot")

## Project Structure
The project is structured into three main directories:
- **Source:** contains the main Godot project files and a C++ project for integrating FFmpeg along with all dependencies.
- **Builds:** includes the built versions of the Godot project, alongside FFmpeg dynamic libraries and a test video.
- **Doc:** Contains materials used for the README.

**Shortcuts:**
- The C++ component code is located in the [Source/src](Source/src/) folder. The main code is on [gdexample.h ](Source/src/gdexample.h) and [gdexample.cpp ](Source/src/gdexample.cpp)
- Godot project source is in the [Source/demo/](Source/demo) folder.

## Project Architecture
**Full system architecture**

![Sys Architecture](doc/images/sys_arch_diagram.png "System Architecture")

**Main algorithm diagram**

![Sys Architecture](doc/images/algorithm.png "System Architecture")

## How to use it
![screenshot](doc/images/info1.png "screenshot")
![screenshot](doc/images/info2.png "screenshot")
![screenshot](doc/images/info3.png "screenshot")
![screenshot](doc/images/info4.png "screenshot")

## KNOWN BUG and lack of feature

**#1**
The RGB values may be off, with the offset increasing over the duration of the video. This may lead to the inability to obtain RGB values after a certain point. This issue is suspected to be related to frame seeking inaccuracies, where seeking to a specific frame may not land precisely on the requested frame.

**#2**
The task was to visualize row[] and col[] as 1D textures. However, Godot does not yet support 1D textures, and despite attempting various workarounds, I have not been able to resolve this issue. As an alternative, I have implemented a shader that visualizes animation using two colors selected by the user from row[] and col[].
