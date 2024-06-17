#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <SOIL/SOIL.h>

using namespace std;


GLuint queenTextureID; // Texture ID for the queen image
GLuint queenTextureID2; // Texture ID for the queen image

void loadTextures() {
    queenTextureID = SOIL_load_OGL_texture("./queen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    queenTextureID2 = SOIL_load_OGL_texture("./black_queen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (queenTextureID == 0) {
        std::cerr << "Error loading texture: " << SOIL_last_result() << std::endl;
    }
}

void initRendering() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

const int N = 5;
vector<int> queens(N); 
int currentRow = 0;     

bool isValid(int row, int col) {
    for (int i = 0; i < col; ++i) {
        if (queens[i] == row || abs(queens[i] - row) == abs(i - col)) {
            return false; 
        }
    }
    return true;
}



bool moveQueens(int row) {
    if (row >= N) {
        return true; 
    }
    for (int i = 0; i < N; ++i) {
        if (isValid(i, row)) {
            queens[row] = i; 
            
            if (row == currentRow) {
                glutPostRedisplay();
                break;
            }
            
            if (moveQueens(row + 1)) {
                return true;
            }
        }
    }
    return true; 
}

void drawQueen(int row, int col) {
for (int i = 0; i < N; ++i) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, queenTextureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(queens[i] * 100, i * 100);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f((queens[i] + 1) * 100, i * 100);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f((queens[i] + 1) * 100, (i + 1) * 100);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(queens[i] * 100, (i + 1) * 100);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
}

void drawBoard() {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if ((col + row) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f); // White squares
            } else {
                glColor3f(0.0f, 0.0f, 0.0f); // Black squares
            }
            glBegin(GL_QUADS);
            glVertex2f(col * 100, row * 100);
            glVertex2f((col + 1) * 100, row * 100);
            glVertex2f((col + 1) * 100, (row + 1) * 100);
            glVertex2f(col * 100, (row + 1) * 100);
            glEnd();

                drawQueen(col, row);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoard();
    // drawQueens();
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (currentRow < N) {
            // moveQueens(currentCol);
            // currentCol++;
            //
            if (moveQueens(currentRow)) {
                currentRow ++ ;
            }
        }
    }
}

int main(int argc, char** argv) {

    queens = {4, 0, 4, 0, 4};
    // queens = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    // queens = {};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(N * 100, N * 100);
    glutCreateWindow("xd");
    glOrtho(0, N * 100, N * 100, 0, -1, 1);

    initRendering();
    loadTextures();
    glutDisplayFunc(display);

    glutMouseFunc(mouseClick);

    glutMainLoop();
    return 0;
}
