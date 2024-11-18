# Animated Scene with Procedural Clouds, Celestial Animations, Waves, and Raindrops

By Atuhaire Ambala and Ricardo Escarcega
CST 310

## Overview

This project demonstrates a 2D animated scene created using **OpenGL** and **GLFW**. The animation features dynamically moving clouds, a sun and moon cycling across the sky, water with realistic waves, and falling raindrops. The scene highlights procedural generation, animation techniques, and color transitions to simulate day-night cycles.

## Features

- **Dynamic Clouds**: Clouds are procedurally generated with random positions and sizes, and they sway gently back and forth, simulating natural movement.
- **Celestial Animation**: The sun and moon follow parabolic paths across the sky, with transitions smoothly adjusting the background color to represent the time of day.
- **Realistic Water Waves**: The water surface is animated using sine wave functions, creating the appearance of rippling waves.
- **Falling Raindrops**: Raindrops are generated as dashed lines, simulating rain over the animated scene.
- **Dynamic Background**: The background color shifts dynamically based on the sun and moon's positions, transitioning through sunrise, daytime, sunset, and nighttime.

## Key Concepts and Components

### Procedural Generation
- **Clouds**: Clouds are procedurally generated with random positions within specified ranges for realistic sky coverage. Their sizes vary to add diversity and realism.
- **Raindrops**: Raindrops are randomly positioned across the screen, with each drop rendered as a vertical dashed line.

### 2D Transformations
- **Cloud Animation**: Clouds sway horizontally using sine wave functions, mimicking natural wind movement.
- **Celestial Movement**: The sun and moon follow parabolic trajectories, calculated dynamically based on elapsed time.

### Color Management
- **Dynamic Background**: The background transitions through color gradients to represent different times of day:
  - Sunrise: Dark grey to bright blue.
  - Daytime: Bright blue.
  - Sunset: Bright blue back to dark grey.
  - Nighttime: Dark grey to light grey.
- **Element Colors**:
  - Sun: Bright yellow.
  - Moon: White with a crescent shadow matching the background color.

### Drawing Techniques
- **Clouds**: Constructed from overlapping circles rendered as polygons with multiple vertices for smooth edges.
- **Raindrops**: Rendered as dashed lines with adjustable thickness and length.
- **Water Waves**: The water is a rectangle with a wavy top edge animated using sine wave functions, creating realistic rippling effects.
- **Celestial Bodies**: The sun and moon are drawn as circles, with the moon featuring an overlapping shadow for a crescent effect.

### Relationships
- Clouds, raindrops, and water waves interact visually to create a cohesive scene.
- The background color transitions seamlessly with the celestial movement, unifying the atmosphere.

## Usage

### Prerequisites
- **OpenGL**
- **GLFW**
- **GLEW**

### Compilation and Execution
1. Clone the repository or copy the code into a file, e.g., `animated_scene.cpp`.
2. Compile the code using a C++ compiler with OpenGL support:
   ```bash
   g++ -o scene scene.cpp -lGL -lGLEW -lglfw -lGLU -lglut
   ```
3. Run the program:
   ```bash
   ./animated_scene
   ```

### Controls
- The animation runs automatically in a loop. There are no user inputs required.

## Implementation Details

### Animation Flow
1. **Celestial Cycle**:
   - The sun and moon alternate their animations, with each completing a full parabolic path across the screen.
   - When one completes its path, the other begins.
2. **Cloud Movement**:
   - Clouds sway back and forth, with their positions recalculated in each frame.
3. **Raindrop Animation**:
   - Raindrops are rendered at random positions and fall vertically to simulate rain.
4. **Wave Animation**:
   - The water's wavy top edge is animated using sine wave functions, creating dynamic ripples.

### Code Highlights
- **Procedural Generation**:
  - Clouds and raindrops are generated using random functions for positions and sizes.
- **2D Transformations**:
  - Sine functions are used to animate cloud swaying and wave movement.
- **Dynamic Rendering**:
  - Background colors and celestial animations are updated based on the time of day.

## Example Output
The scene features:
- A sun rising and setting across a bright blue sky.
- Clouds swaying gently while rain falls over rippling water.
- A moon cycling through the nighttime sky, transitioning the background to darker tones.

## Future Enhancements
- Add sound effects for rain or ambient day/night sounds.
- Introduce interactive elements, such as controlling the time of day or weather conditions.
- Extend the animation to include stars during nighttime.

