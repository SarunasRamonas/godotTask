# Pixel's raw data visualization

## Project Overview
`Pixel's raw data visualization` is a Godot project designed to extract and return the raw values (RGB struct) of a selected pixel. It then visualizes these values using a GLSL shader. The project is a blend of Godot's powerful game engine capabilities with advanced graphics programming, making it ideal for applications in image processing and visualization.

![screenshot](doc/images/screenshot1.png "screenshot")

## Project Structure
The project is divided into two main parts:
- **Source:** This folder contains the main Godot project files and a C++ project for integrating libVLC.
- **Builds:** This folder includes the built versions of the Godot project, alongside the compiled libVLC and the C++ interface project.
- **Doc:** This folder includes material used for readme

## Project Architecture
![Sys Architecture](doc/images/sys_arch_diagram.png "System Architecture")
