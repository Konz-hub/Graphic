#include <windows.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include <ctime>

#define WIN32_LEAN_AND_MEAN
#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 900

// Function to draw a rectangle
void DrawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a circle
void DrawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Function to draw a sun
void DrawSun(float x, float y, float radius) {
    glColor3ub(255, 223, 0); // Yellow
    DrawCircle(x, y, radius, 100); // Added the missing 'segments' argument
}

// Function to draw the scene with a gloomy theme
void DrawScene() {
    // Background gradient
    glBegin(GL_QUADS);
    glColor3ub(47, 79, 79); // Dark slate gray
    glVertex2f(0, SCREEN_HEIGHT);
    glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
    glColor3ub(25, 25, 25); // Almost black
    glVertex2f(SCREEN_WIDTH, 0);
    glVertex2f(0, 0);
    glEnd();

    // Wall
    glColor3ub(169, 169, 169); // Gray wall
    DrawRectangle(0, SCREEN_HEIGHT / 4, SCREEN_WIDTH, SCREEN_HEIGHT * 3 / 4);

    // Circular window with black base and white cross grill
    glColor3ub(0, 0, 0); // Black base
    glBegin(GL_POLYGON); // Filled circle for the base
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * PI * i / 100;
        glVertex2f(SCREEN_WIDTH / 2 + 150 * cos(angle), SCREEN_HEIGHT / 2 + 150 * sin(angle));
    }
    glEnd();

    // White cross grill
    glColor3ub(255, 255, 255); // White color
    DrawRectangle(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2 - 150, 10, 300); // Vertical bar
    DrawRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 5, 300, 10); // Horizontal bar

    // Flower pot on the right center
    glColor3ub(139, 69, 19); // Brown for the pot
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - 25, 0, 50, 30); // Pot base aligned with the floor
    glColor3ub(34, 139, 34); // Green for the plant stem
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - 5, 30, 10, 40); // Plant stem starting above the pot
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the scene
    DrawScene();

    glFlush();
}

// Initialize OpenGL settings
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT); // Set 2D orthographic projection
}

// Idle function to refresh the display
void idle() {
    glutPostRedisplay(); // Trigger the display function
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Specify display mode
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Scene 3: Montage - Passage of Time");
    glutDisplayFunc(display);
    glutIdleFunc(idle); // Set the idle function to refresh the display

    initGL();
    glutMainLoop();
    return 0;
}
