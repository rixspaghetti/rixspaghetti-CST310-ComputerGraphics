#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Global variables to control functionalities:
bool isMoving = true;
float verticalShift = 0.0;
float zoomFactor = 1.0;
float rotationAngle = 0.0;
float centerCubeRotationAngle = 0.0;
GLfloat verticalOffset = 1.0;
GLfloat cameraAngle = 0.0;
// Camera control
// Camera control
// Camera control
// Camera control
float cameraZ = -20.0f; // Start 20 units back on the z-axis
float cameraSpeed = 0.1f; // Speed at which the camera moves

// ... (rest of your global variables and namespace declarations)

// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.

namespace Cube {

  const int NUM_VERTICES = 8;
  const int NUM_FACES = 6;

  GLfloat angle = 0.0f; // The rotation angle of the cube.
  GLfloat position = 0.0f; // The translation of the cube on some axis.

  GLint vertices[NUM_VERTICES][3] = {
    {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
    {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  GLint faces[NUM_FACES][4] = {
    {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
    {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

  GLfloat vertexColors[NUM_VERTICES][3] = {
    {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
    {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

  void update() {
    angle += 0.2f; // Update the rotation angle for the next frame.
    position = sinf(angle * 0.1f); // This will move the cube up and down on the y-axis.
  }

  void draw(GLfloat* color = nullptr) {
    glPushMatrix(); // Push the current matrix to the stack

    glTranslatef(0.0f, position, 0.0f); // Apply translation
    glRotatef(angle, 0.5f, 1.0f, 0.0f); // Apply rotation around a vector (0.5, 1, 0)

    glBegin(GL_QUADS);
    for (int i = 0; i < NUM_FACES; i++) {
      for (int j = 0; j < 4; j++) {
        if (color) {
          glColor3fv(color); // Use the provided color for all vertices
        } else {
          glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
        }
        glVertex3iv((GLint*)&vertices[faces[i][j]]);
      }
    }
    glEnd();

    glPopMatrix(); // Pop the matrix to revert to the previous state
  }
}

class LeftPlane {
public:
    static void draw() {
        glPushMatrix();

        glTranslatef(-5.0f, 0.0f, 0.0f);   // Move to the left
        glScalef(0.3f, 10.0f, 10.0f);      // Scale to look like a thick plane, now 4 times bigger in y and z
        glColor3f(0.0f, 0.0f, 1.0f);       // Color of the left plane
        glutSolidCube(1.0f);

        glPopMatrix();
    }
};

class RightPlane {
public:
    static void draw() {
        glPushMatrix();

        glTranslatef(5.0f, 0.0f, 0.0f);    // Move to the right
        glScalef(0.3f, 10.0f, 10.0f);      // Scale to look like a thick plane, now 4 times bigger in y and z
        glColor3f(0.0f, 0.0f, 1.0f);       // Color of the right plane
        glutSolidCube(1.0f);

        glPopMatrix();
    }
};


namespace BouncingCubes {
    const int NUM_CUBES = 2;
    GLfloat cubeSpeeds[NUM_CUBES] = {0.05f, -0.05f};
    GLfloat cubePositions[NUM_CUBES][3] = {{-4.5f, 2.0f, 2.0f}, {4.5f, -2.0f, -2.0f}}; // Start close to the planes
    void updatePositions() {
        if (isMoving) {  // Only update positions if isMoving is true
            for (int i = 0; i < NUM_CUBES; i++) {
                cubePositions[i][0] += cubeSpeeds[i];

                // Check for collisions with the planes and reverse direction if needed
                if (cubePositions[i][0] <= -5.0f + 0.5f) {
                    cubePositions[i][0] = -5.0f + 0.5f;
                    cubeSpeeds[i] = -cubeSpeeds[i];
                } else if (cubePositions[i][0] >= 5.0f - 0.5f) {
                    cubePositions[i][0] = 5.0f - 0.5f;
                    cubeSpeeds[i] = -cubeSpeeds[i];
                }
            }
        }
    }

    void draw() {
        for (int i = 0; i < NUM_CUBES; i++) {
            glPushMatrix();
            // Translate the cube to its current position
            glTranslatef(cubePositions[i][0], cubePositions[i][1], cubePositions[i][2]);

            // Set a different color for each cube
            GLfloat color[3];
            if (i == 0) {
                color[0] = 1.0f; color[1] = 0.0f; color[2] = 1.0f; // First cube pink
            } else {
                color[0] = 0.0f; color[1] = 1.0f; color[2] = 1.0f; // Second cube turqoise
            }

            // Draw the cube with the color set above
            Cube::draw(color);
            glPopMatrix();
        }
    }
}



// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // The center cube is at the origin, so we look at (0, 0, 0)
    // The camera's up-vector is assumed to be (0, 1, 0), which means 'up' is in the positive y-direction
    gluLookAt(0.0, -5.0 + verticalShift, cameraZ,  // Camera position with vertical shift
              0.0, 0.0 + verticalShift, 0.0,       // Look at the origin with vertical shift
              0.0, 1.0, 0.0);                      // Up vector 

    /*gluLookAt(8 * cos(cameraAngle) * zoomFactor, 
            7 * cos(cameraAngle) - 1 + verticalOffset, 
            4 * cos(cameraAngle / 3) + 2, 0.5, 0.5, 0.5, 0, 1, 0); */

    glScalef(zoomFactor, zoomFactor, zoomFactor);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f); // Rotate around the y-axis
    // Move the camera back and forth along the z-axis
    cameraZ += cameraSpeed;

    
    if (cameraZ <= -20.0f || cameraZ >= 20.0f) {
        cameraSpeed = -cameraSpeed; // Reverse direction when limits are reached
    }


    // Draw the left and right planes
    LeftPlane::draw();
    RightPlane::draw();

    // Update and draw the bouncing cubes
    BouncingCubes::updatePositions();
    BouncingCubes::draw();

    // Draw the primary cube at the center
    // No need to translate or rotate as we want it to be at the origin
    Cube::draw();

    // Swap buffers to display the frame
    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        rotationAngle += 20;  // Increment rotation angle for rotating the whole scene
        if (rotationAngle >= 360.0f) {
            rotationAngle -= 360.0f; // Keep the angle in the range [0, 360]
        }
        break;
    case 's':
        isMoving = false;  // Stop the movement
        break;
    case 'c':
        isMoving = true;   // Continue the movement
        break;
    case 'u':
        verticalShift += 0.5;
        break;
    case 'd':
        verticalShift -= 0.5;
        break;
    case '=':  // Zoom in
        zoomFactor -= 0.3;
        if (zoomFactor < 0.3) zoomFactor = 0.3; // Set minimum zoom limit
        break;
    case '-':  // Zoom out
        zoomFactor += 0.3;
        if (zoomFactor > 3.0) zoomFactor = 3.0; // Set maximum zoom limit
        break;
    }
    glutPostRedisplay();
}


// Modify the timer function to incorporate the new functionalities:
void timer(int v) {
    if (isMoving) {
        rotationAngle += 0.5;  // Increment rotation angle for rotating the whole scene
        BouncingCubes::updatePositions(); // Update positions of the bouncing cubes
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}


// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}



void update(int value) {
    // Update the rotation angle
    centerCubeRotationAngle += 2.0f;  
    if (centerCubeRotationAngle > 360.0f) {
        centerCubeRotationAngle -= 360.0f;
    }

    // Invalidate the current display and call to re-draw
    glutPostRedisplay();

    // Register the timer function again for continuous updates
    glutTimerFunc(16, update, 0);
}


// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, update, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);  // Register keyboard callback.
  init();
  glutMainLoop();
}