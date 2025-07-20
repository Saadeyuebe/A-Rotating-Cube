#include <iostream>
#include <cmath>
#include <cstring>
#include <windows.h> // For Sleep()

// Screen config
const int SCREEN_WIDTH = 75;
const int SCREEN_HEIGHT = 30;
const int SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

// Cube render config
const float CUBE_SIZE = 7.0f;
const float STEP = 0.5f;
const float ROT_SPEED = 0.10f;
const float CAMERA_DIST = 50.0f;
const float SCALE = 40.0f;
const char FILL_CHAR = ' ';
const int FRAME_DELAY = 4;

// Rotation angles
float angleX = 0.0f, angleY = 0.0f;

// Buffers
char charBuffer[SCREEN_SIZE];
float depthBuffer[SCREEN_SIZE];

// Utility vars
float projX, projY, projZ, invZ;
int screenX, screenY, screenIdx;

float rotateX(int i, int j, int k) {
    return j * sin(angleX) * sin(angleY) * cos(0) - k * cos(angleX) * sin(angleY) * cos(0)
         + j * cos(angleX) * sin(0) + k * sin(angleX) * sin(0)
         + i * cos(angleY) * cos(0);
}

float rotateY(int i, int j, int k) {
    return j * cos(angleX) * cos(0) + k * sin(angleX) * cos(0)
         - j * sin(angleX) * sin(angleY) * sin(0) + k * cos(angleX) * sin(angleY) * sin(0)
         - i * cos(angleY) * sin(0);
}

float rotateZ(int i, int j, int k) {
    return k * cos(angleX) * cos(angleY) - j * sin(angleX) * cos(angleY) + i * sin(angleY);
}

void projectSurface(float cx, float cy, float cz, char symbol) {
    projX = rotateX(cx, cy, cz);
    projY = rotateY(cx, cy, cz);
    projZ = rotateZ(cx, cy, cz) + CAMERA_DIST;

    invZ = 1 / projZ;
    screenX = (int)(SCREEN_WIDTH / 2 + SCALE * invZ * projX * 2);
    screenY = (int)(SCREEN_HEIGHT / 2 + SCALE * invZ * projY);
    screenIdx = screenX + screenY * SCREEN_WIDTH;

    if (screenIdx >= 0 && screenIdx < SCREEN_SIZE) {
        if (invZ > depthBuffer[screenIdx]) {
            depthBuffer[screenIdx] = invZ;
            charBuffer[screenIdx] = symbol;
        }
    }
}

int main() {
    std::cout << "\x1b[2J";     // Clear screen
    std::cout << "\x1b[90m";    // Gray text color

    while (true) {
        std::fill(charBuffer, charBuffer + SCREEN_SIZE, FILL_CHAR);
        std::fill(depthBuffer, depthBuffer + SCREEN_SIZE, 0.0f);

        for (float x = -CUBE_SIZE; x < CUBE_SIZE; x += STEP) {
            for (float y = -CUBE_SIZE; y < CUBE_SIZE; y += STEP) {
                projectSurface(x, y, -CUBE_SIZE, '@');    // Front
                projectSurface(CUBE_SIZE, y, x, '$');     // Right
                projectSurface(-CUBE_SIZE, y, -x, '~');   // Left
                projectSurface(-x, y, CUBE_SIZE, '#');    // Back
                projectSurface(x, -CUBE_SIZE, -y, ';');   // Bottom
                projectSurface(x, CUBE_SIZE, y, '+');     // Top
            }
        }

        std::cout << "\x1b[H"; // Move cursor to top
        for (int i = 0; i < SCREEN_SIZE; ++i)
            std::cout << (i % SCREEN_WIDTH ? charBuffer[i] : '\n');

        angleX += ROT_SPEED;
        angleY += ROT_SPEED;

        Sleep(FRAME_DELAY);
    }

    return 0;
}
