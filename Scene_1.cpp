#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>

#define Screen_Width 1280
#define Screen_Height 900
#define PI 3.14159265358979323846 // Define Pi

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black with full opacity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Screen_Width, 0.0, Screen_Height); // Set 2D orthographic projection
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	// Draw the back wall (dark gray)
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_QUADS);
	glVertex2f(300.0f, 400.0f); // Bottom-left corner
	glVertex2f(1000.0f, 400.0f); // Bottom-right corner
	glVertex2f(1000.0f, 900.0f); // Top-right corner
	glVertex2f(300.0f, 900.0f); // Top-left corner
	glEnd();

	// Draw the floor (medium gray)
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f); // Bottom-left corner
	glVertex2f(Screen_Width, 0.0f); // Bottom-right corner
	glVertex2f(1000.0f, 400.0f); // Top-right corner
	glVertex2f(300.0f, 400.0f); // Top-left corner
	glEnd();

	// Draw the left wall (dark gray)
	glColor3f(0.15f, 0.15f, 0.15f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f); // Bottom-left corner
	glVertex2f(300.0f, 400.0f); // Top-right corner
	glVertex2f(300.0f, 900.0f); // Top-left corner
	glVertex2f(0.0f, 900.0f); // Bottom-right corner
	glEnd();

	// Draw the right wall (dark gray)
	glColor3f(0.15f, 0.15f, 0.15f);
	glBegin(GL_QUADS);
	glVertex2f(Screen_Width, 0.0f); // Bottom-right corner
	glVertex2f(1000.0f, 400.0f); // Top-left corner
	glVertex2f(1000.0f, 900.0f); // Top-right corner
	glVertex2f(Screen_Width, 900.0f); // Bottom-left corner
	glEnd();

	// Draw the light source (white rectangle)
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(600.0f, 850.0f); // Bottom-left corner
	glVertex2f(680.0f, 850.0f); // Bottom-right corner
	glVertex2f(680.0f, 870.0f); // Top-right corner
	glVertex2f(600.0f, 870.0f); // Top-left corner
	glEnd();

	// Draw the circle in the center (light gray) using Pi
	glColor3f(0.5f, 0.5f, 0.5f);
	float centerX = Screen_Width / 2.0f;
	float centerY = Screen_Height / 2.0f + 50.0f; // Slightly higher
	float radius = 30.0f; // Slightly larger
	int numSegments = 100;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * PI * float(i) / float(numSegments);
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		glVertex2f(centerX + x, centerY + y);
	}
	glEnd();

	// Draw the cross inside the circle (light gray)
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	// Horizontal line
	glVertex2f(centerX - radius, centerY);
	glVertex2f(centerX + radius, centerY);
	// Vertical line
	glVertex2f(centerX, centerY - radius);
	glVertex2f(centerX, centerY + radius);
	glEnd();

	glutSwapBuffers(); // Swap the front and back buffers
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Screen_Width, Screen_Height);
	glutCreateWindow("Scene 1: Wall and Floor");
	initGL();
	glutDisplayFunc(drawScene);
	glutMainLoop();
	return 0;
}

