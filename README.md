# Voxel Game rendering engine using OpenGL
![valleys](VoxelGame/res/textures/valleys.PNG)

## Controls
  - Fly around the world using `WSAD` and your mouse.
  - Zoom in by scrolling the mouse wheel.
  - Maximize the window by pressing `F`.
  - Pause the camera movement by pressing `P`.
  - Exit the game by pressing `ESC`.

You can export the scene by passing `-e` (`--export`) to the executable.

## Project structure

This is Visual studio project running on Windows.

Includes for extra dependencies `/Dependencies`
  - GLAD
  - GLFW
  
Dependencies wich are compiled are placed in `/VoxelGame/src/vendor`
  - glad
  - glm
  - stb_image
  - perlin_noise
  - simplex_noise
  
Game engine resources are placed in `/VoxelGame/res`
  - textures
  - shaders

## Building the app
Engine supports only x86 architecture and uses features from C++20. If you are using Visual studio, please update to version 16.7+.
