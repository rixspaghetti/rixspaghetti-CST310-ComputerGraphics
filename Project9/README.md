# Project 9: Advanced Shaders 1 - OpenGL Application
## Authors
Atu Ambala and Rocardo Escarcega

## Overview
This project is an OpenGL-based 3D graphics application that demonstrates camera movement and control using keyboard inputs. The main feature is a **checkerboard scene** with various 3D objects such as a cube, sphere, and cylinder, which can be observed using different camera movements and transformations.

## Features
- **Camera Transformations**: Control the camera's yaw, pitch, roll, and position in 3D space.
- **Keyboard Controls**: Adjust the camera view using standard and special keys.
- **Rendered Scene**: The application renders a checkerboard plane with various 3D shapes positioned on it, including a cube, sphere, and cylinder.

## Project Structure
The following is a simplified flow of the program's operation:

1. **Start Program**: The program starts and initializes **GLUT** and **GLFW**.
2. **Set Window Properties**: Set up the initial window properties such as size and position.
3. **Register Callback Functions**: Callback functions are registered for handling user input, display, and window resizing.
4. **Initialize OpenGL Settings**: Configure OpenGL settings such as depth testing and shading.
5. **Enter GLUT Main Loop**: The application enters the main event loop, continually processing user inputs and rendering the scene.

### Key Handling
- **User Presses Key**: Handles both standard and special keys.
  - **Standard Keys**: Modify camera roll, yaw, pitch, or position using `handleKeypress`.
  - **Special Keys**: Use arrow keys to slide the camera in different directions (`handleSpecialKeypress`).

### Display Rendering
- **Clear Buffers**: Clears the color and depth buffers to prepare for rendering.
- **Set Model-View Matrix**: Resets and sets up the model-view matrix.
- **Apply Camera Transformations**: Adjust the view using yaw, pitch, roll, and position.
- **Render Scene Elements**: Renders the checkerboard and various 3D shapes in the scene.
- **Swap Buffers**: Updates the window with the new frame (double buffering).

### Camera Transformations
- **Apply Camera Roll, Pitch, and Yaw**: Adjust the camera’s orientation.
- **Set View with `gluLookAt`**: Position the camera to look at a specific point in the scene.

### Render Scene Elements
- **Render Checkerboard**: Draws the checkerboard plane.
- **Render Shapes**: Draws 3D shapes (cube, sphere, and cylinder) on the plane.

### Origin Tracking
- **Adjust Origin Position**: Updates the position of the origin to track camera movement when necessary.

## Controls
- **Standard Keys**:
  - `<` / `>`: Adjust camera roll.
  - `W` / `S`: Adjust camera pitch.
  - `A` / `D`: Adjust camera yaw.
  - `+` / `-`: Move the camera along the Z-axis.
  - `R`: Reset the camera to the default position.

- **Special Keys**:
  - **Arrow Keys**: Move the camera along the X or Y axis.

## Required Libraries
The following libraries are required to compile and run this project:

- **GLUT**: Used for window creation, input handling, and rendering.
- **GLFW**: Provides cross-platform windowing and input handling.
- **GLEW**: Manages OpenGL extensions.
- **OpenGL**: Core graphics library for rendering.
- **GLU**: Utility library to simplify common OpenGL tasks.

## Software Requirements
The following software is required to compile and run this project:

- **Linux or Windows Operating System**: The project is developed and tested on Linux, but it can be adapted for Windows.
- **C++ Compiler**: A modern C++ compiler such as GCC (version 5.0 or later).
- **OpenGL Development Environment**: Proper drivers and libraries to support OpenGL rendering.
- **Make Utility (Optional)**: For managing build automation.

## Prerequisites
- **GLUT** and **GLFW** libraries are required for windowing and input handling.
- **OpenGL** compatible environment to run the application.

## Compilation
To compile the project in a Linux environment, you can use the following command:

```sh
g++ checkerboard.cpp -o build -std=c++11 -I/usr/include -L/usr/lib -lglfw -lGL -lGLEW -lGLUT -lGLU
```

Ensure that all necessary libraries are installed, and their headers and binaries are available in the system's include and library paths.

Ensure that all necessary libraries are installed and available at the specified paths.

## Running the Application
After successful compilation, run the executable `build` to start the application. Use the keyboard controls to navigate through the scene and explore different camera angles.



