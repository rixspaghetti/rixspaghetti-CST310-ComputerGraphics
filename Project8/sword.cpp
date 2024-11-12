#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

#include <cmath>

// Initialize the environment
void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0); // Set background color
    glEnable(GL_DEPTH_TEST);           // Enable depth testing
}

// Function to draw a curved blade
void drawCurvedBlade() {
    int segments = 80;               // Number of segments for the curve
    float bladeLength = 12.0;         // Total length of the blade
    float curveFactor = 0.00035;        // Adjust for curvature
    float segmentLength = bladeLength / segments;
    
    glPushMatrix();
    glTranslatef(1.7, -10.0, -3.0);   // Lower the starting position of the sword
    glRotatef(13, 0.0, 0.0, 1.0);   // Tilt sword to match the image

    for (int i = 0; i < segments; i++) {
        glPushMatrix();
        glTranslatef(0.0, i * segmentLength, curveFactor * i * i); // Create slight curve
        glScalef(0.25, segmentLength, 0.5);                         // Scale each segment
        glutSolidCube(1.0);                                        // Draw each segment
        glPopMatrix();
    }

    glPopMatrix();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 5.0,  // Eye position (lifted up to create a looking-down angle)
              0.0, 0.0, 0.0,   // Look-at position
              0.0, 1.0, 0.0);  // Up vector

    // Draw the curved sword blade
    drawCurvedBlade();

    glutSwapBuffers();
}

// Handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 800);
    glutCreateWindow("Curved Samurai Sword Emerging");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
