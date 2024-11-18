#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>


// Struct to store the base position and size of each cloud
struct Cloud {
    float x, y, size;
};

struct Color {
    float r, g, b;
};

Color darkGrey = {0.1f, 0.1f, 0.1f};   // Dark grey color
Color brightBlue = {0.0f, 0.5f, 1.0f}; // Bright blue color for day
Color lightGrey = {0.35f, 0.35f, 0.35f};  // Light grey color for night

Color bgColor; // Global variable to store the background color


// Generate fixed positions for clouds
std::vector<Cloud> generateClouds(int count) {
    std::vector<Cloud> clouds;
    for (int i = 0; i < count; i++) {
        Cloud cloud;
        cloud.x = (std::rand() % 800) - 400;      // Fixed x position in range -400 to 400
        cloud.y = (std::rand() % 200) + 100;      // Fixed y position in upper half (100 to 300)
        cloud.size = (std::rand() % 40) + 20;     // Random size for each cloud
        clouds.push_back(cloud);
    }
    return clouds;
}

// Function to draw a single circle at a specified position and size
void drawCircle(float cx, float cy, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.14159f * float(i) / 100.0f; // Angle in radians
        float x = radius * cos(angle);                     // x-coordinate
        float y = radius * sin(angle);                     // y-coordinate
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawClouds(const std::vector<Cloud>& clouds, float time) {
    // Set color for clouds
    glColor3f(0.5f, 0.5f, 0.5f); // Grey color for clouds

    // Sway speed and amplitude
    float swaySpeed = 0.5f;    // Controls the speed of the sway
    float swayAmplitude = 10.0f; // Amplitude of the sway motion

    for (size_t i = 0; i < clouds.size(); i++) {
        const Cloud& cloud = clouds[i];

        // Sway effect using a sine wave, applied to the x-axis
        float swayOffset = std::sin(time * swaySpeed + i * 0.3f) * swayAmplitude;

        // Draw cloud as overlapping circles to create a fluffy appearance
        float baseX = cloud.x + swayOffset; // Only sway horizontally, no drifting
        float baseY = cloud.y;
        float size = cloud.size;

        // Draw circles to form the cloud shape
        drawCircle(baseX, baseY, size);                          // Center circle
        drawCircle(baseX - size * 0.6f, baseY - size * 0.3f, size * 0.7f); // Left circle
        drawCircle(baseX + size * 0.6f, baseY - size * 0.3f, size * 0.7f); // Right circle
        drawCircle(baseX, baseY - size * 0.5f, size * 0.6f);     // Bottom circle
    }
}

void drawSun(float x, float y) {
    // Color yellow for the sun
    glColor3f(1.0f, 1.0f, 0.0f);

    float radius = 75.0f; // Sun's radius

    // Draw the sun as a circle
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.14159f * float(i) / 100;
        float cx = radius * std::cos(angle); // Circle x-coordinate
        float cy = radius * std::sin(angle); // Circle y-coordinate
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void animateSun(float time, float& sunX, float& sunY, bool& sunDone, bool& moonDone, float& sunStartTime) {
    if (sunStartTime ==0.0f){
        sunStartTime = time;
    } 

    if (!moonDone) {
        // Wait until the moon is done before starting the sun
        sunX = -500.0f;
        sunY = -150.0f;
        return;
    }

    // Parabolic equation parameters
    float a = -0.001f;      // Controls the steepness of the parabola
    float h = 0.0f;         // x-coordinate of the vertex
    float k = 75.0f;       // y-coordinate of the peak

    // Move the sun from -500 to 500
    float elapsedTime = time - sunStartTime;
    sunX = -500.0f + elapsedTime * 100.0f; // Speed of 100 units per second

    if (sunX >= 500.0f ) {
        sunDone = true;           // Mark the sun animation as complete
        moonDone = false;         // Reset moon to start animating
        sunX = -500.0f;            // Clamp the sun's position
        sunY = -150.0f;           // Clamp the sun's vertical position
        sunStartTime = 0.0f;        // Reset the sun start time
        std::cout << "Sun animation done!" << std::endl;

        return;
    }

    // Calculate the y-coordinate using the parabolic equation
    sunY = a * (sunX - h) * (sunX - h) + k;
}


void drawMoon(float x, float y, float radius) {
    // Color for the main moon body
    glColor3f(1.0f, 1.0f, 1.0f); // White color

    // Draw the full circle for the moon
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.14159f * float(i) / 100.0f;
        float cx = radius * cos(angle);
        float cy = radius * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();

    // Color for the overlapping "shadow" to create crescent should mathc the background set by updateBackgroundColor
    // Set the color to match the background
    glColor3f(bgColor.r, bgColor.g, bgColor.b);

    // Draw the overlapping circle to create the crescent shape
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.14159f * float(i) / 100.0f;
        float offsetX = radius * 0.6f; // Adjust this to control crescent thickness
        float cx = radius * cos(angle) + offsetX;
        float cy = radius * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void animateMoon(float time, float& moonX, float& moonY, bool& moonDone, bool& sunDone, float& moonStartTime) {
    if (moonStartTime == 0.0f) {
        moonStartTime = time;
    }

    if (!sunDone) {
        // Wait until the sun is done before starting the moon
        moonX = 500.0f;
        moonY = -150.0f;
        return;
    }

    // Parabolic equation parameters
    float a = -0.001f;      // Controls the steepness of the parabola
    float h = 0.0f;         // x-coordinate of the vertex
    float k = 75.0f;       // y-coordinate of the peak

    // Move the moon from 500 to -500
    float elapsedTime = time - moonStartTime;
    moonX = 500.0f - elapsedTime * 100.0f; // Speed of 100 units per second
    if (moonX <= -500.0f ) {
        sunDone = false;         // Reset sun to start animating
        moonDone = true;         // Mark the moon animation as complete
        moonX = 500.0f;         // Clamp the moon's position
        moonY = -150.0f;         // Clamp the moon's vertical position
        moonStartTime = 0.0f;    // Reset the moon start time
        std::cout << "Moon animation done!" << std::endl;

        return;
    }

    // Calculate the y-coordinate using the parabolic equation
    moonY = a * (moonX - h) * (moonX - h) + k;
}



// Function to draw a body of water with animated waves
void drawWater(float time) {
    glColor3f(0.0f, 0.0f, 0.8f); // Base blue color for water

    // Draw the base rectangle for the water
    glBegin(GL_QUADS);
    glVertex2f(-400, -300);  // Bottom-left corner
    glVertex2f(400, -300);   // Bottom-right corner
    glVertex2f(400, -150);   // Top-right corner
    glVertex2f(-400, -150);  // Top-left corner
    glEnd();

    float waveHeight = 5.0f;    // Amplitude of the wave
    float waveFrequency1 = 0.05f; // Controls the wavelength
    float waveSpeed1 = 1.5f;      // Controls the speed of the wave animation

    float phaseShift =  10.0f; // Phase shift for the wave effect

    // Draw the wavy top edge
    glBegin(GL_QUAD_STRIP);
    for (float x = -400; x <= 400; x += 10.0f) { // Iterate along the top edge
        float offset = std::sin(time * waveSpeed1 + x * waveFrequency1 + phaseShift) * waveHeight;

        // Bottom vertex of each small quad (fixed at -150)
        glVertex2f(x, -150);

        // Top vertex of each small quad (offset for wave effect)
        glVertex2f(x, -150 + offset);
    }
    glEnd();

    // Set up wave parameters
    float waveAmplitude = 5.0f;     // Height of each wave
    float waveFrequency = 0.05f;    // Frequency of waves (controls the wavelength)
    float waveSpeed = 1.5f;         // Speed at which waves move horizontally
    float waveSpacing = 10.0f;      // Vertical spacing between wave lines

    // Draw multiple wavy lines across the water surface
    glColor3f(0.0f, 0.2f, 1.0f); // A slightly lighter blue for the waves
    for (float y = -150; y >= -300; y -= waveSpacing) {
        glBegin(GL_LINE_STRIP);
        for (float x = -400; x <= 400; x += 5.0f) { // Adjust step size for smoothness
            // Offset the wave phase based on y position to create depth effect
            float offset = std::sin(time * waveSpeed + x * waveFrequency + y * 0.1f ) * waveAmplitude;
            glVertex2f(x, y + offset);
        }
        glEnd();
    }
}


// Draw simple raindrops as dashed lines
void drawRaindrops() {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(20, 0x00FF);  // Dashed pattern

    glColor3f(0.0f, 0.0f, 0.0f); // Black color for raindrops

    //make the lines thicker
    glLineWidth(4.0f); 

    glBegin(GL_LINES);
    for (int i = 0; i < 100; i++) {
        float x = (std::rand() % 800) - 400; // x position between -400 to 400
        float y = (std::rand() % 600) - 300; // y position between -300 to 300
        float length = 50.0f;                // Raindrop length

        glVertex2f(x, y);
        glVertex2f(x, y - length);
    }
    glEnd();

    // Reset line stipple and line width
    glLineWidth(1.0f);

    glDisable(GL_LINE_STIPPLE);
}

// Function to update background color based on celestial progress
void updateBackgroundColor(float celestialProgress) {
    float r, g, b;
    float t = celestialProgress;

    if (t <= 0.25f) {
        // Sunrise (Dark Grey to Bright Blue)
        float local_t = t / 0.25f; // Map t from [0.0, 0.25] to [0.0, 1.0]
        r = (1.0f - local_t) * darkGrey.r + local_t * brightBlue.r;
        g = (1.0f - local_t) * darkGrey.g + local_t * brightBlue.g;
        b = (1.0f - local_t) * darkGrey.b + local_t * brightBlue.b;
    } else if (t <= 0.5f) {
        // Sunset (Bright Blue back to Dark Grey)
        float local_t = (t - 0.25f) / 0.25f; // Map t from [0.25, 0.5] to [0.0, 1.0]
        r = (1.0f - local_t) * brightBlue.r + local_t * darkGrey.r;
        g = (1.0f - local_t) * brightBlue.g + local_t * darkGrey.g;
        b = (1.0f - local_t) * brightBlue.b + local_t * darkGrey.b;
    } else if (t <= 0.75f) {
        // Moonrise (Dark Grey to Light Grey)
        float local_t = (t - 0.5f) / 0.25f; // Map t from [0.5, 0.75] to [0.0, 1.0]
        r = (1.0f - local_t) * darkGrey.r + local_t * lightGrey.r;
        g = (1.0f - local_t) * darkGrey.g + local_t * lightGrey.g;
        b = (1.0f - local_t) * darkGrey.b + local_t * lightGrey.b;
    } else {
        // Moonset (Light Grey back to Dark Grey)
        float local_t = (t - 0.75f) / 0.25f; // Map t from [0.75, 1.0] to [0.0, 1.0]
        r = (1.0f - local_t) * lightGrey.r + local_t * darkGrey.r;
        g = (1.0f - local_t) * lightGrey.g + local_t * darkGrey.g;
        b = (1.0f - local_t) * lightGrey.b + local_t * darkGrey.b;
    }

    glClearColor(r, g, b, 1.0f);

    // Store the background color
    bgColor.r = r;
    bgColor.g = g;
    bgColor.b = b;
}



int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Dashed Line Rain Effect", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();


    std::srand(static_cast<unsigned>(std::time(0)));  // Seed for randomness

    // Generate fixed positions for the clouds
    std::vector<Cloud> clouds = generateClouds(30); // 20 clouds should be sufficient
    
    float sunX = -500.0f, sunY = -150.0f; // Initial sun position
    float moonX = 500.0f, moonY = -150.0f; // Initial moon position
    bool sunDone = false; // Track if the sun animation is complete
    bool moonDone = true; // Initially set to true so the sun starts
    float sunStartTime = 0.0f, moonStartTime = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        //glClear(GL_COLOR_BUFFER_BIT);

        // Calculate time for sway animation
        float time = glfwGetTime();  // Returns time in seconds since the program started
        float cycleProgress = 0.0f;

        // Set up the viewport and projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-400, 400, -300, 300);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        if (!sunDone) {
            // Animate the sun
            animateSun(time, sunX, sunY, sunDone, moonDone, sunStartTime);
            float sunProgress = (sunX + 500.0f) / 1000.0f; // sunX from -500 to 500
            cycleProgress = sunProgress * 0.5f; // cycleProgress from 0 to 0.5
            std::cout << "Sun is animating: X=" << sunX << ", Y=" << sunY << std::endl;
        } else if (!moonDone) {
            // Animate the moon
            animateMoon(time, moonX, moonY, moonDone, sunDone, moonStartTime);
            float moonProgress = (500.0f - moonX) / 1000.0f; // moonX from 500 to -500
            cycleProgress = 0.5f + moonProgress * 0.5f; // cycleProgress from 0.5 to 1.0
            std::cout << "Moon is animating: X=" << moonX << ", Y=" << moonY << std::endl;
        } 
        // Update background color based on cycleProgress
        updateBackgroundColor(cycleProgress);

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the sun
        drawSun(sunX, sunY);

        // Draw the moon
        drawMoon(moonX, moonY, 75.0f);

        // Draw the water
        drawWater(time);

        // Draw the raindrops
        drawRaindrops();

        // Draw the cloud-like leaves
        drawClouds(clouds, time);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
