// This program now includes bouncing cubes and vertical planes along with the flyby animation and controls.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Cube data and drawing
namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

void draw() {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
}
}

// Global variables for camera and cube control
GLfloat cameraAngle = 0.0;
GLfloat zoomFactor = 1.0;
GLfloat verticalOffset = 0.0;
bool isRotating = false;
bool isAnimating = true;
GLfloat cubePosition = 0.0;
GLfloat cubeSpeed = 0.05;
bool cubeMovingRight = true;

// Timer function for animation and bouncing
void timer(int v) {
  if (isAnimating) {
    cameraAngle += (isRotating ? 0.02 : 0.0);  // Adjust rotation speed
    
    // Move the cube left and right, and bounce off the planes
    if (cubeMovingRight) {
      cubePosition += cubeSpeed;
      if (cubePosition > 3.0) {  // Right plane boundary
        cubeMovingRight = false;
      }
    } else {
      cubePosition -= cubeSpeed;
      if (cubePosition < -3.0) {  // Left plane boundary
        cubeMovingRight = true;
      }
    }
  }
  glLoadIdentity();
  gluLookAt(8 * cos(cameraAngle) * zoomFactor, 
            7 * cos(cameraAngle) - 1 + verticalOffset, 
            4 * cos(cameraAngle / 3) + 2, 0.5, 0.5, 0.5, 0, 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

// Display function to draw the cubes and the planes
void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw original cube
  Cube::draw();

  // Additional cubes with different colors, positions, and bouncing
  glPushMatrix();
  glTranslatef(cubePosition, 0.0, 0.0);  // Cube bouncing horizontally
  glColor3f(1.0, 0.5, 0.2);  // Orange cube
  Cube::draw();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-cubePosition, 0.0, 0.0);  // Another cube bouncing in the opposite direction
  glColor3f(0.5, 1.0, 0.2);  // Greenish cube
  Cube::draw();
  glPopMatrix();

  // Draw vertical planes
  glColor3f(0.7, 0.7, 0.7);  // Gray color for planes
  glBegin(GL_QUADS);
  // Left plane
  glVertex3f(-3.2, -2.0, -1.0);
  glVertex3f(-3.2,  2.0, -1.0);
  glVertex3f(-3.2,  2.0,  2.0);
  glVertex3f(-3.2, -2.0,  2.0);
  // Right plane
  glVertex3f( 3.2, -2.0, -1.0);
  glVertex3f( 3.2,  2.0, -1.0);
  glVertex3f( 3.2,  2.0,  2.0);
  glVertex3f( 3.2, -2.0,  2.0);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'r':  // Start/stop rotation
      isRotating = !isRotating;
      break;
    case 's':  // Stop animation
      isAnimating = false;
      break;
    case 'c':  // Continue animation
      isAnimating = true;
      break;
    case 'u':  // Move camera up
      verticalOffset += 0.1;
      break;
    case 'd':  // Move camera down
      verticalOffset -= 0.1;
      break;
    case '+':  // Zoom in
      zoomFactor *= 0.9;
      break;
    case '-':  // Zoom out
      zoomFactor *= 1.1;
      break;
    default:
      break;
  }
}

// Reshape function to adjust viewport
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Initialization function
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

// Main function
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Bouncing Cubes with Planes");

  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  init();
  glutMainLoop();
}
