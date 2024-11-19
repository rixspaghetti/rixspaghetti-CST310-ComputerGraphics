#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>

const int NUM_PARTICLES = 500; // Number of particles
const float TIME_STEP = 0.01f; // Simulation timestep
const float BOUNDARY = 5.0f;   // Boundary limit
const float ATTRACTOR_STRENGTH = 2.0f; // Strength of the central attractor
const float DAMPING = 0.99f;   // Damping factor

struct Particle {
    float x, y, z;    // Position
    float vx, vy, vz; // Velocity
    float r, g, b;    // Color
};

std::vector<Particle> particles;

// Random float generator
float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

// Initialize particles
void initParticles() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        Particle p = {
            randomFloat(-BOUNDARY, BOUNDARY), randomFloat(-BOUNDARY, BOUNDARY), randomFloat(-BOUNDARY, BOUNDARY), // Position
            randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), // Velocity
            randomFloat(0.5f, 1.0f), randomFloat(0.5f, 1.0f), randomFloat(0.5f, 1.0f)  // Color
        };
        particles.push_back(p);
    }
}

// Update particle positions
void updateParticles() {
    for (auto &p : particles) {
        // Central attractor force
        float fx = -ATTRACTOR_STRENGTH * sin(p.x) * sin(p.y) * sin(p.z);
        float fy = -ATTRACTOR_STRENGTH * sin(p.x) * sin(p.y) * sin(p.z);
        float fz = -ATTRACTOR_STRENGTH * sin(p.x) * sin(p.y) * sin(p.z);

        // Update velocity and position
        p.vx += fx * TIME_STEP;
        p.vy += fy * TIME_STEP;
        p.vz += fz * TIME_STEP;

        p.x += p.vx * TIME_STEP;
        p.y += p.vy * TIME_STEP;
        p.z += p.vz * TIME_STEP;

        // Apply damping
        p.vx *= DAMPING;
        p.vy *= DAMPING;
        p.vz *= DAMPING;

        // Boundary constraints
        if (p.x > BOUNDARY || p.x < -BOUNDARY) p.vx = -p.vx;
        if (p.y > BOUNDARY || p.y < -BOUNDARY) p.vy = -p.vy;
        if (p.z > BOUNDARY || p.z < -BOUNDARY) p.vz = -p.vz;
    }
}

// Display particles
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -50.0f); // Move camera further back to fit particles

    glBegin(GL_POINTS);
    for (const auto &p : particles) {
        glColor3f(p.r, p.g, p.b); // Set particle color
        glVertex3f(p.x, p.y, p.z); // Draw particle
    }
    glEnd();

    glutSwapBuffers();
}

// Idle function to continuously update and redisplay
void idle() {
    updateParticles();
    glutPostRedisplay();
}

// Setup OpenGL settings
void setupOpenGL() {
    glEnable(GL_DEPTH_TEST);    // Enable depth testing
    glPointSize(2.0f);          // Set particle size
    glEnable(GL_POINT_SMOOTH);  // Smooth points

    // Setup the viewport and projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
}

// Main function
int main(int argc, char **argv) {
    srand(static_cast<unsigned>(time(0))); // Seed for random numbers

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Newtonian Particle Animation");

    setupOpenGL();
    initParticles();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
