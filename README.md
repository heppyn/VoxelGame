# Voxel Game rendering engine using OpenGL
![valleys](VoxelGame/res/textures/valleys.PNG)

## Controls
  - Fly around the world using `WSAD` and your mouse.
  - Zoom in by scrolling the mouse wheel.
  - Maximize the window by pressing `F`.
  - Pause the camera movement by pressing `P`.
  - Exit the game by pressing `ESC`.

You can export the scene by passing `-e` (`--export`) as an argument to the executable.

## Project structure

Includes for already compiled dependencies `/Dependencies`
  - GLAD
  - GLFW
  - GLFW_x64
  
Dependencies that have to be compiled are placed in `/VoxelGame/src/vendor`
  - glad
  - glm
  - stb_image
  - perlin_noise
  - simplex_noise
  
Game resources are placed in `/VoxelEplorer/res`
  - textures
  - shaders

Engine part is compiled as static library and included by VoxelExplorer.

## Building on Windows
The engine uses features from C++20. If you are using Visual studio, please update to version 16.7+.

For Visual studio there are prepared configurations for building the app:
  - Release x86 and x64. The preferred configuration for fast chunk generation.
  - Debug x86 and x64. 
  - Export x86. Just passes `--export` as an argument.
  - Test x86. Runs only tests.

## Building on Linux
If you are using linux you have to compile GLFW by yourself as the pre-compiled binaries are not available.
You can find the source to GLFW [here](https://www.glfw.org/download.html). If you are compiling with gcc and running into problems
these command line options might help `-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl`

If you compiled and replaced GLFW you can use CMake to build the project like:
`cmake --build "build"`

## First app  
For creating your first app see [getting started](GettingStarted.md).

## Issues
If you are running into issues with L-system parsing make sure you are using the proper file endings for your system.
Not using `CRLF` could cause problems on Windows. 
