# Project 7: Putting It All Together

# Ricardo Escarcega, Atuharie Ambala
# Professor Ricardo Citro
# CST310: Computer Graphics
# 11/03/2024


This project demonstrates 3D animation, lighting, and user interaction using OpenGL. It consists of two programs, CheckeredTriangles and ColorCubeFlyby, each focusing on different aspects of OpenGL functionalities like rotation, lighting effects, and keyboard-controlled interactivity.

## Installation and Requirements

This project requires OpenGL, GLEW, and GLFW libraries. Ensure these libraries are installed on your system before compiling the code.

## Dependencies

- **OpenGL**: Core graphics library for rendering.
- **GLEW**: Manages OpenGL extensions.
- **GLFW**: Provides window management and input handling.

## Installation on Linux (if not installed)

```bash
sudo apt-get update
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
```
## Running the Program

To compile and run the CheckeredTriangles program, use the following command structure in your terminal:
g++ -o checkered CheckeredTriangles.cpp -lGL -lGLEW -lglfw -lGLU -lglut

Then, run the compiled program:
./checkered

For ColorCubeFlyby, follow a similar compilation process, modifying the filename accordingly:
g++ -o cubes ColorCubeFlyby.cpp -lGL -lGLEW -lglfw -lGLU -lglut
./cubes

Keyboard Controls
Each program includes keyboard controls to enhance interactivity.

## CheckeredTriangles Controls
c: Start rotation
p: Stop rotation
u: Move up
d: Move down
L: Move left
R: Move right
+: Zoom in
-: Zoom out
## ColorCubeFlyby Controls
r: Rotate scene
s: Stop cubes
c: Continue cubes
u: Move up
d: Move down
+: Zoom in
-: Zoom out

## Project Features
360-Degree Rotation: Triangles and cubes can be rotated for a full view of the scene.
Lighting and Shading: The project implements the Phong lighting model, with controls for specular and diffuse lighting effects.
User Interactivity: Users can control the position, rotation, and zoom level of objects, allowing for an immersive 3D experience.
Bounding Planes and Bouncing Effect: The ColorCubeFlyby program includes two vertical planes to create a visual bouncing effect for the cubes.
Mathematical Concepts
This project uses several key mathematical concepts to achieve realistic rendering and lighting:

### Transformation Matrices: 
Used for rotation, scaling, and translation of objects in 3D space.
### Phong Reflection Model: 
Combines ambient, diffuse, and specular lighting components to create realistic lighting effects.
### Shininess Factor: 
Controls the sharpness of specular highlights, allowing for different material appearances.
### Methodology
#### Code Structure Analysis: 
Each file was reviewed to identify major functionalities and control flow.
#### Key Function Identification: 
Essential functions for rendering, input handling, and transformations were identified and analyzed.
#### Shader and Lighting Setup: 
Shader configurations and lighting calculations were examined to understand the Phong model’s implementation.
#### Testing and Documentation: 
Each feature was tested and documented to ensure functionality and enhance code readability.




