#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h> // For loading image textures

// Texture IDs
GLuint floorTexture, wallTexture, windowTexture, robotTexture, plantTexture;

// Function to load an image texture
void loadImageTexture(GLuint& texture, const char* filePath) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Load the image using SOIL
    unsigned char* image = SOIL_load_image(filePath, nullptr, nullptr, 0, SOIL_LOAD_RGBA);
    if (!image) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return;
    }

    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SOIL_last_width(), SOIL_last_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SOIL_free_image_data(image);
}

// Function to draw a textured rectangle
void drawTexturedQuad(GLuint texture, float x1, float y1, float x2, float y2) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x1, y1);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x2, y1);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x2, y2);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x1, y2);
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable 2D textures
    glEnable(GL_TEXTURE_2D);

    // Draw floor
    drawTexturedQuad(floorTexture, -1.0f, -0.5f, 1.0f, 0.0f);

    // Draw walls
    drawTexturedQuad(wallTexture, -1.0f, 0.0f, -0.8f, 1.0f); // Left wall
    drawTexturedQuad(wallTexture, 0.8f, 0.0f, 1.0f, 1.0f);   // Right wall

    // Draw window
    drawTexturedQuad(windowTexture, -0.5f, 0.5f, 0.5f, 0.9f);

    // Draw robot
    drawTexturedQuad(robotTexture, -0.2f, -0.4f, 0.2f, -0.1f);

    // Draw plant
    drawTexturedQuad(plantTexture, -0.4f, -0.5f, -0.3f, -0.3f);

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

// Reshape callback function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Space Station Hallway");

    // Load textures
    loadImageTexture(floorTexture, "textures/floor.png");  // Floor texture
    loadImageTexture(wallTexture, "textures/wall.png");   // Wall texture
    loadImageTexture(windowTexture, "textures/window.png"); // Window texture
    loadImageTexture(robotTexture, "textures/robot.png"); // Robot texture
    loadImageTexture(plantTexture, "textures/plant.png"); // Plant texture

    // Set callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}

