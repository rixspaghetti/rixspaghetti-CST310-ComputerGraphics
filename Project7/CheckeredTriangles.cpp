
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}

GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// Variables for rotation, movement, and zoom
float angle = 0.0f;
bool spinning = true;
float zoom = 1.0f;
float moveX = 0.0f, moveY = 0.0f;

// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, GLfloat(width)/height, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                    // level 0
               3,                    // use only R, G, and B components
               2, 2,                 // texture has 2x2 texels
               0,                    // no border
               GL_RGB,               // texels are in RGB format
               GL_UNSIGNED_BYTE,     // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws textured triangles with applied transformations (rotation, movement, and zoom).
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  
  // Apply transformations
  glTranslatef(moveX, moveY, -5.0f); // Move triangles
  glScalef(zoom, zoom, zoom);        // Zoom in/out
  glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate the triangles
  
  glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);    glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0);    glVertex2f(0, 0);

    glTexCoord2f(4, 8);        glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(0, 0);
    glTexCoord2f(8, 0.0);      glVertex2f(3, 0);

    glTexCoord2f(5, 5);        glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
  glEnd();

  glFlush();
}

void update(int value) {
  if (spinning) {
    angle -= 2.0f;  // Increase the angle for rotation
    if (angle > 360) {
      angle -= 360;
    }
  }
  glutPostRedisplay();  // Redisplay the scene with the new rotation
  glutTimerFunc(16, update, 0);  // 60 frames per second
}

// Handles keyboard input for controls
void handleKeys(unsigned char key, int x, int y) {
  switch (key) {
    case 'p':  // Pause spinning
      spinning = false;
      break;
    case 'c':  // Continue spinning
      spinning = true;
      break;
    case 'u':  // Move up
      moveY += 0.1f;
      break;
    case 'd':  // Move down
      moveY -= 0.1f;
      break;
    case 'l':  // Move left
      moveX -= 0.1f;
      break;
    case 'r':  // Move right
      moveX += 0.1f;
      break;
    case '+':  // Zoom in
      zoom += 0.1f;
      break;
    case '-':  // Zoom out
      zoom -= 0.1f;
      break;
  }
  glutPostRedisplay();
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(520, 390);
  glutCreateWindow("Textured Triangles");
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(handleKeys);  // Register keyboard handler
  glutTimerFunc(16, update, 0);  // Start the update loop
  
  glutMainLoop();
  return 0;
}
