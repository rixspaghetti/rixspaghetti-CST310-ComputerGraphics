#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <cstdio>
//  /opt/homebrew/bin/g++-14 checkerboard.cpp -o build -std=c++11 -I/opt/homebrew/include -L/usr/local/lib -L/opt/homebrew/lib -lglfw -lGL -lGLEW -lGLUT -lGLU


/* Global variables */
char title[] = "Checkerboard";

float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 10.0f; // Camera position
float cameraAngleX = 0.0f; // Angle for horizontal camera rotation
float cameraAngleY = 0.0f; // Angle for vertical camera rotation
float cameraRoll = 0.0f; // Angle for camera roll
float originX = 0.0f, originY = 0.0f, originZ = 0.0f; // Origin position

// Function to handle standard key presses
void handleKeypress(unsigned char key, int x, int y) {
    // Get the modifier state (e.g., Ctrl, Shift, Alt)
    //int modifier = glutGetModifiers();
    switch (key) {
        case '<': // Change camera roll by 2 degrees
            cameraRoll += 2.0f;
            break;
        case '>': // Change camera roll by -2 degrees
            cameraRoll -= 2.0f;
            break;
        case 'd': // Change camera yaw by 2 degrees
            cameraAngleX += 2.0f;
            break;
        case 'a': // Change camera yaw by -2 degrees
            cameraAngleX += -2.0f;
            break;
        case 's': // Change camera pitch by 2 degrees
            cameraAngleY += 2.0f;
            break;
        case 'w': // Change camera pitch by -2 degrees
            cameraAngleY += -2.0f;
            break;
        case '-': // Slide camera in the negative Y direction
            cameraZ += 1.0f;

            break;
        case '+': // Slide camera in the positive Z direction
            cameraZ -= 1.0f;
    
            break;
        case 'r': // Reset to the default position and orientation
            cameraX = 0.0f;
            cameraY = 1.0f;
            cameraZ = 10.0f;
            cameraAngleX = 0.0f;
            cameraAngleY = 0.0f;
            originX = 0.0f;
            originY = 0.0f;
            originZ = 0.0f;
            cameraRoll = 0.0f;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Request display update
}

// Function to handle special key presses
void handleSpecialKeypress(int key, int x, int y) {
    // Get the modifier state (e.g., Ctrl, Shift, Alt)
    switch (key) {
        case GLUT_KEY_RIGHT: // Slide camera in the positive X direction - right arrow
            cameraX += 1.0f;
            originX += 1.0f;
            break;
        case GLUT_KEY_LEFT: // Slide camera in the negative X direction - left arrow
            cameraX -= 1.0f; 
            originX -= 1.0f;
            break;
        case GLUT_KEY_UP: // Slide camera in the positive Y direction - up arrow
            cameraY += 1.0f;
            originY += 1.0f;
            break;
        case GLUT_KEY_DOWN: // Slide camera in the positive Y direction - down arrow
            cameraY -= 1.0f;
            originY -= 1.0f;
            break;
    
        default:
            break;
    }
    glutPostRedisplay(); // Request display update
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}


/* Handler for window-repaint event. Called back when the window first appears and whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix

   // Set the camera to look at the origin (0,0,0) from the calculated position
   glRotatef(cameraRoll, 0.0, 0.0, 1.0); // Apply camera roll
   glRotatef(cameraAngleY, 1.0, 0.0, 0.0); // Apply camera pitch
   glRotatef(cameraAngleX, 0.0, 1.0, 0.0); // Apply camera yaw
   gluLookAt(cameraX, cameraY, cameraZ, originX, originY, originZ, 0.0, 1.0, 0.0);

   // Draw Checkerboard Plane
   int squaresPerSide = 16;
   float squareSize = 20.0f / squaresPerSide; // Increase size to create a plane that goes into the screen
   for (int i = 0; i < squaresPerSide; ++i) {
       for (int j = 0; j < squaresPerSide; ++j) {
           if ((i + j) % 2 == 0) {
               glColor3f(1.0f, 1.0f, 1.0f); // White color
           } else {
               glColor3f(0.0f, 0.0f, 0.0f); // Black color
           }
           glBegin(GL_QUADS);
           glVertex3f(-10.0f + i * squareSize, 0.0f, -10.0f + j * squareSize);
           glVertex3f(-10.0f + (i + 1) * squareSize, 0.0f, -10.0f + j * squareSize);
           glVertex3f(-10.0f + (i + 1) * squareSize, 0.0f, -10.0f + (j + 1) * squareSize);
           glVertex3f(-10.0f + i * squareSize, 0.0f, -10.0f + (j + 1) * squareSize);
           glEnd();
       }
   }

   // Draw a Cube
   glPushMatrix();
   glTranslatef(-5.0f, 1.0f, -5.0f); // Position the cube on the plane
   glColor3f(0.0f, 1.0f, 0.0f); // Green color
   glutSolidCube(2.0f);
   glColor3f(0.0f, 0.0f, 0.0f); // Black color for edges
   glutWireCube(2.0f);
   glPopMatrix();

   // Draw a Sphere
   glPushMatrix();
   glTranslatef(0.0f, 1.0f, -5.0f); // Position the sphere on the plane
   glColor3f(0.0f, 0.0f, 1.0f); // Blue color
   glutSolidSphere(1.0f, 50, 50);
   glColor3f(0.0f, 0.0f, 0.0f); // Black color for edges
   glutWireSphere(1.0f, 50, 50);
   glPopMatrix();

   // Draw a Cylinder
   glPushMatrix();
   glTranslatef(5.0f, 0.0f, -5.0f); // Position the cylinder on the plane
   glColor3f(1.0f, 0.0f, 0.0f); // Red color
   glRotatef(-90, 1.0f, 0.0f, 0.0f); // Rotate cylinder to stand upright
   GLUquadric *quadric = gluNewQuadric();
   gluCylinder(quadric, 1.0f, 1.0f, 2.0f, 50, 50);
   glColor3f(0.0f, 0.0f, 0.0f); // Black color for edges
   gluQuadricDrawStyle(quadric, GLU_LINE);
   gluCylinder(quadric, 1.0f, 1.0f, 2.0f, 50, 50);
   gluDeleteQuadric(quadric);
   glPopMatrix();

   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(2000, 1500);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutKeyboardFunc(handleKeypress); // Set keyboard input handler
   glutSpecialFunc(handleSpecialKeypress); // Set special key input handler
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
