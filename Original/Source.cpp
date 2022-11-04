#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include<stdio.h>
#include<math.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<errno.h>
#include<GL\GL.h>
#include<GL\GLU.h>
#include<GL\glut.h>

int flag = 0;
float y = 8, x = -100, z = 70; //initial camera position
float deltaMove = 0.0; // initially camera doesn't move
// Camera direction0
float lx = 1.0, lz = 0.0; // camera points initially along y-axis
float angle = 90.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts
int move = 0;
int vertmove = 0;

void restrict()			//restrict movement within boundaries
{
    if (x > 60)    x = 60;
    else if (x < -100)    x = -100;
    if (y > 100)    y = 100;
    else if (y < 0.5)    y = 0.5;
    if (z > 100)    z = 100;
    else if (z < -30)    z = -30;
}

void disp_interior()		//mba block interiors
{
    int k;
    glPushMatrix();
    glTranslatef(-10, 0.1, 50);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(40, 0, 0);
    glVertex3f(40, 0, -50);
    glVertex3f(0, 0, -50);
    glEnd();
    glColor3f(0, 0, 0);
    for (k = 2; k < 38; k += 4)
    {
        glBegin(GL_QUADS);
        glVertex3f(k, 0, -0.1);
        glVertex3f(k, 4, -0.1);
        glVertex3f(k + 2, 4, -0.1);
        glVertex3f(k + 2, 0, -0.1);
        glEnd();
    }
    for (k = -2; k > -48; k -= 6)
    {
        glBegin(GL_QUADS);
        glVertex3f(0.1, 0, k);
        glVertex3f(0.1, 4, k);
        glVertex3f(0.1, 4, k - 2);
        glVertex3f(0.1, 0, k - 2);
        glEnd();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.1, 50);
    for (k = -2; k > -48; k -= 6)
    {
        glBegin(GL_QUADS);
        glVertex3f(-0.1, 0, k);
        glVertex3f(-0.1, 4, k);
        glVertex3f(-0.1, 4, k - 2);
        glVertex3f(-0.1, 0, k - 2);
        glEnd();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.1, 0);
    for (k = -2; k > -38; k -= 4)
    {
        glBegin(GL_QUADS);
        glVertex3f(k, 0, 0.1);
        glVertex3f(k, 4, 0.1);
        glVertex3f(k - 2, 4, 0.1);
        glVertex3f(k - 2, 0, 0.1);
        glEnd();
    }
    glPopMatrix();
    for (int i = 0; i < 35; i += 5)
    {
        glPushMatrix();
        glTranslatef(-10, 10 + i, 50);
        glColor3f(1, 0.894, 0.709);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(40, 0, 0);
        glVertex3f(40, 0, -4);
        glVertex3f(0, 0, -4);
        glEnd();
        glColor3f(1, 0.972, 0.862);
        glBegin(GL_QUADS);
        glVertex3f(4, 0, -4);
        glVertex3f(36, 0, -4);
        glVertex3f(36, 2, -4);
        glVertex3f(4, 2, -4);
        glEnd();
        glColor3f(0, 0, 0);
        for (k = 2; k < 38; k += 4)
        {
            glBegin(GL_QUADS);
            glVertex3f(k, 0, -0.1);
            glVertex3f(k, 4, -0.1);
            glVertex3f(k + 2, 4, -0.1);
            glVertex3f(k + 2, 0, -0.1);
            glEnd();
        }
        glPushMatrix();
        glTranslatef(40, 0, 0);
        glColor3f(1, 0.894, 0.709);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -50);
        glVertex3f(-4, 0, -50);
        glVertex3f(-4, 0, 0);
        glEnd();
        glColor3f(1, 0.972, 0.862);
        glBegin(GL_QUADS);
        glVertex3f(-4, 0, -4);
        glVertex3f(-4, 0, -46);
        glVertex3f(-4, 2, -46);
        glVertex3f(-4, 2, -4);
        glEnd();
        glColor3f(0, 0, 0);
        for (k = -2; k > -48; k -= 6)
        {
            glBegin(GL_QUADS);
            glVertex3f(-0.1, 0, k);
            glVertex3f(-0.1, 4, k);
            glVertex3f(-0.1, 4, k - 2);
            glVertex3f(-0.1, 0, k - 2);
            glEnd();
        }
        glTranslatef(0, 0, -50);
        glColor3f(1, 0.894, 0.709);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(-40, 0, 0);
        glVertex3f(-40, 0, 4);
        glVertex3f(0, 0, 4);
        glEnd();
        glColor3f(1, 0.972, 0.862);
        glBegin(GL_QUADS);
        glVertex3f(-4, 0, 4);
        glVertex3f(-36, 0, 4);
        glVertex3f(-36, 2, 4);
        glVertex3f(-4, 2, 4);
        glEnd();
        glColor3f(0, 0, 0);
        for (k = -2; k > -38; k -= 4)
        {
            glBegin(GL_QUADS);
            glVertex3f(k, 0, 0.1);
            glVertex3f(k, 4, 0.1);
            glVertex3f(k - 2, 4, 0.1);
            glVertex3f(k - 2, 0, 0.1);
            glEnd();
        }
        glPopMatrix();
        glColor3f(1, 0.894, 0.709);
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -50);
        glVertex3f(4, 0, -50);
        glVertex3f(4, 0, 0);
        glEnd();
        glColor3f(1, 0.972, 0.862);
        glBegin(GL_QUADS);
        glVertex3f(4, 0, -4);
        glVertex3f(4, 0, -46);
        glVertex3f(4, 2, -46);
        glVertex3f(4, 2, -4);
        glEnd();
        glColor3f(0, 0, 0);
        for (k = -2; k > -48; k -= 6)
        {
            glBegin(GL_QUADS);
            glVertex3f(0.1, 0, k);
            glVertex3f(0.1, 4, k);
            glVertex3f(0.1, 4, k - 2);
            glVertex3f(0.1, 0, k - 2);
            glEnd();
        }
        glPopMatrix();
    }

}

class building			//construction of the block buildings
{
    float structure[8][3];
public:
    building(float a, float b, float c)
    {
        structure[0][0] = 0; structure[0][1] = 0; structure[0][2] = 0;
        structure[1][0] = a; structure[1][1] = 0; structure[1][2] = 0;
        structure[2][0] = a; structure[2][1] = b; structure[2][2] = 0;
        structure[3][0] = 0; structure[3][1] = b; structure[3][2] = 0;
        structure[4][0] = 0; structure[4][1] = 0; structure[4][2] = c;
        structure[5][0] = a; structure[5][1] = 0; structure[5][2] = c;
        structure[6][0] = a; structure[6][1] = b; structure[6][2] = c;
        structure[7][0] = 0; structure[7][1] = b; structure[7][2] = c;
    }
    void disp_build(char text[15], char side = '/0')
    {
        float door[3];
        glColor3f(1, 0.980, 0.980);
        glBegin(GL_QUADS);
        glVertex3fv(structure[0]);
        glVertex3fv(structure[1]);
        glVertex3fv(structure[2]);
        glVertex3fv(structure[3]);
        glEnd();
        glBegin(GL_QUADS);
        glVertex3fv(structure[0]);
        glVertex3fv(structure[4]);
        glVertex3fv(structure[7]);
        glVertex3fv(structure[3]);
        glEnd();
        glBegin(GL_QUADS);
        glVertex3fv(structure[4]);
        glVertex3fv(structure[5]);
        glVertex3fv(structure[6]);
        glVertex3fv(structure[7]);
        glEnd();
        glBegin(GL_QUADS);
        glVertex3fv(structure[1]);
        glVertex3fv(structure[2]);
        glVertex3fv(structure[6]);
        glVertex3fv(structure[5]);
        glEnd();

        if (structure[1][0] > (-1 * structure[4][2]))
        {
            for (float i = 10; i < structure[2][1]; i += 10)
            {
                glPushMatrix();
                glTranslatef(0, i, 0);
                for (float j = 5; j < structure[1][0]; j += 15)
                {
                    glColor3f(0, 0, 0);
                    glBegin(GL_POLYGON);
                    glVertex3f(j, 0, 0.1);
                    glVertex3f(j + 5, 0, 0.1);
                    glVertex3f(j + 5, 5, 0.1);
                    glVertex3f(j, 5, 0.1);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glVertex3f(j, 0, structure[4][2] - 0.1);
                    glVertex3f(j + 5, 0, structure[4][2] - 0.1);
                    glVertex3f(j + 5, 5, structure[4][2] - 0.1);
                    glVertex3f(j, 5, structure[4][2] - 0.1);
                    glEnd();
                }
                for (float j = 0; j < structure[1][0]; j += 15)
                {
                    glColor3f(1, 0, 0);
                    glBegin(GL_POLYGON);
                    glVertex3f(j, -10, 0.1);
                    glVertex3f(j + 2, -10, 0.1);
                    glVertex3f(j + 2, 10, 0.1);
                    glVertex3f(j, 10, 0.1);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glVertex3f(j, -10, structure[4][2] - 0.1);
                    glVertex3f(j + 2, -10, structure[4][2] - 0.1);
                    glVertex3f(j + 2, 10, structure[4][2] - 0.1);
                    glVertex3f(j, 10, structure[4][2] - 0.1);
                    glEnd();
                }
                glPopMatrix();
            }
            glColor3f(0, 0, 0);
            door[0] = (structure[1][0] / 2);
            glBegin(GL_POLYGON);
            glVertex3f(door[0] - 4, 0, 0.2);
            glVertex3f(door[0] + 4, 0, 0.2);
            glVertex3f(door[0] + 4, 7, 0.2);
            glVertex3f(door[0] - 4, 7, 0.2);
            glEnd();
            glPushMatrix();
            glTranslatef(10, 0, 3);
            //draw_board();
            glPushMatrix();
            glTranslatef(1, 2, 0.1);
            glScalef(.01, .01, .01);
            glLineWidth(2);
            glColor3f(0, 0, 0);
            char t[] = "RVITM";
            for (int c = 0; t[c] != 0; ++c)
                glutStrokeCharacter(GLUT_STROKE_ROMAN, t[c]);
            glPopMatrix();
            glPopMatrix();
        }
        else
        {
            for (float i = 10; i < structure[2][1]; i += 10)
            {
                glPushMatrix();
                glTranslatef(0, i, 0);
                for (float j = -5; j > structure[4][2]; j -= 15)
                {
                    glColor3f(0, 0, 0);
                    glBegin(GL_POLYGON);
                    glVertex3f(-0.1, 0, j);
                    glVertex3f(-0.1, 0, j - 5);
                    glVertex3f(-0.1, 5, j - 5);
                    glVertex3f(-0.1, 5, j);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glVertex3f(structure[1][0] + 0.1, 0, j);
                    glVertex3f(structure[1][0] + 0.1, 0, j - 5);
                    glVertex3f(structure[1][0] + 0.1, 5, j - 5);
                    glVertex3f(structure[1][0] + 0.1, 5, j);
                    glEnd();
                }
                for (float j = 0; j > structure[4][2]; j -= 15)
                {
                    glColor3f(1, 0, 0);
                    glBegin(GL_POLYGON);
                    glVertex3f(-0.1, -10, j);
                    glVertex3f(-0.1, -10, j - 2);
                    glVertex3f(-0.1, 10, j - 2);
                    glVertex3f(-0.1, 10, j);
                    glEnd();
                    glBegin(GL_POLYGON);
                    glVertex3f(structure[1][0] + 0.1, -10, j);
                    glVertex3f(structure[1][0] + 0.1, -10, j - 2);
                    glVertex3f(structure[1][0] + 0.1, 10, j - 2);
                    glVertex3f(structure[1][0] + 0.1, 10, j);
                    glEnd();
                }
                glPopMatrix();
            }
            door[2] = (structure[4][2] / 2);
            door[0] = structure[1][0];
            glColor3f(0, 0, 0);
            if (side == 'r')
            {
                glBegin(GL_POLYGON);
                glVertex3f(door[0] + 0.2, 0, door[2] - 4);
                glVertex3f(door[0] + 0.2, 0, door[2] + 4);
                glVertex3f(door[0] + 0.2, 7, door[2] + 4);
                glVertex3f(door[0] + 0.2, 7, door[2] - 4);
                glEnd();
                glPushMatrix();
                glTranslatef(door[0] + 3, 0, -2);
                glRotatef(90, 0, 1, 0);
                //draw_board();
                glPushMatrix();
                glTranslatef(1, 2, 0.1);
                glScalef(.01, .01, .01);
                glLineWidth(2);
                glColor3f(0, 0, 0);
                for (int c = 0; text[c] != 0; ++c)
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[c]);
                glPopMatrix();
                glPopMatrix();
            }
            else if (side == 'l')
            {
                glBegin(GL_POLYGON);
                glVertex3f(-0.2, 0, door[2] - 4);
                glVertex3f(-0.2, 0, door[2] + 4);
                glVertex3f(-0.2, 7, door[2] + 4);
                glVertex3f(-0.2, 7, door[2] - 4);
                glEnd();
                glPushMatrix();
                glTranslatef(-3, 0, -10);
                glRotatef(-90, 0, 1, 0);
                //draw_board();
                glPushMatrix();
                glTranslatef(1, 2, 0.1);
                glScalef(.01, .01, .01);
                glLineWidth(2);
                glColor3f(0, 0, 0);
                for (int c = 0; text[c] != 0; ++c)
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[c]);
                glPopMatrix();
                glPopMatrix();
            }
        }
        glPushMatrix();
        glTranslatef(0, 10, 0);
        glColor3f(0, 0, 1);
        for (int i = 0; i < structure[2][1] - 5; i += 5)
        {
            glBegin(GL_LINES);
            glVertex3f(structure[0][0], i, structure[0][2] + 0.1);
            glVertex3f(structure[1][0], i, structure[0][2] + 0.1);
            glVertex3f(structure[0][0] - 0.1, i, structure[0][2]);
            glVertex3f(structure[0][0] - 0.1, i, structure[4][2]);
            glVertex3f(structure[4][0], i, structure[4][2] - 0.1);
            glVertex3f(structure[5][0], i, structure[4][2] - 0.1);
            glVertex3f(structure[5][0] + 0.1, i, structure[5][2]);
            glVertex3f(structure[1][0] + 0.1, i, structure[1][2]);

            glEnd();
        }
        glPopMatrix();
    }
};

building admin(40, 80, -50);

void loop(float x, float y, float z)		//the basket loop of the basketball post
{
    float xx, zz, d;
    glColor3f(1, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 360; i++)
    {
        d = i * (180 / 3.14);
        xx = cos(d) + x;
        zz = sin(d) + z;
        glVertex3f(xx, y, zz);
    }
    glEnd();
}

class bball				//construction of basketball court
{
    float bordr[4][3];
    float bskt[8][3];
public:
    bball()
    {
        bordr[0][0] = 0; bordr[0][1] = 0; bordr[0][2] = 0;
        bordr[1][0] = 20; bordr[1][1] = 0; bordr[1][2] = 0;
        bordr[2][0] = 20; bordr[2][1] = 0; bordr[2][2] = -20;
        bordr[3][0] = 0; bordr[3][1] = 0; bordr[3][2] = -20;
        bskt[0][0] = 14; bskt[0][1] = 4.5; bskt[0][2] = -0.1;
        bskt[1][0] = 16; bskt[1][1] = 4.5; bskt[1][2] = -0.1;
        bskt[2][0] = 16; bskt[2][1] = 6.5; bskt[2][2] = -0.1;
        bskt[3][0] = 14; bskt[3][1] = 6.5; bskt[3][2] = -0.1;
        bskt[4][0] = 14, bskt[4][1] = 4.5; bskt[4][2] = -19.9;
        bskt[5][0] = 16; bskt[5][1] = 4.5; bskt[5][2] = -19.9;
        bskt[6][0] = 16; bskt[6][1] = 6.5; bskt[6][2] = -19.9;
        bskt[7][0] = 14; bskt[7][1] = 6.5; bskt[7][2] = -19.9;
    }
    void disp_court()
    {
        glPushMatrix();
        glTranslatef(0, 0.1, 0);
        glColor3f(0.745, 0.745, 0.745);
        glBegin(GL_QUADS);
        glVertex3fv(bordr[0]);
        glVertex3fv(bordr[1]);
        glVertex3fv(bordr[2]);
        glVertex3fv(bordr[3]);
        glEnd();
        glColor3f(1, 0.270, 0);
        GLUquadricObj* quadratic;
        quadratic = gluNewQuadric();
        GLUquadricObj* quadratic1;
        quadratic1 = gluNewQuadric();
        glPushMatrix();
        glTranslatef(15, 0, 0);
        loop(0, 5, -1);
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.698, 0.133, 0.133);
        gluCylinder(quadratic, 0.1, 0.1, 5.0f, 32, 32);
        glPopMatrix();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(15, 0, -20);
        loop(0, 5, 1);
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.698, 0.133, 0.133);
        gluCylinder(quadratic1, 0.1, 0.1, 5.0f, 32, 32);
        glPopMatrix();
        glPopMatrix();
        glColor3f(0.745, 0.745, 0.745);
        glBegin(GL_QUADS);
        for (int i = 0; i < 8; i++)
            glVertex3fv(bskt[i]);
        glEnd();
        glPopMatrix();
    }
};
bball crt1;

void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

void update(void)
{
    if (deltaMove) { // update camera position
        x += deltaMove * lx * 0.38;
        z += deltaMove * lz * 0.38;
    }
    if (vertmove == 1)    y += 0.1;
    if (vertmove == -1) y -= 0.1;
    restrict();
    glutPostRedisplay(); // redisplay everything
}

void disp_roads()			//display the roads in the campus
{
    glColor3f(0.411, 0.411, 0.411);
    glBegin(GL_QUADS);
    glVertex3f(-40, 0.1, 83);
    glVertex3f(-40, 0.1, -27);
    glVertex3f(-20, 0.1, -27);
    glVertex3f(-20, 0.1, 83);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-80, 0.1, 57);
    glVertex3f(-80, 0.1, 67);
    glVertex3f(-20, 0.1, 67);
    glVertex3f(-20, 0.1, 57);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-80, 0.1, 73);
    glVertex3f(-80, 0.1, 83);
    glVertex3f(-20, 0.1, 83);
    glVertex3f(-20, 0.1, 73);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-20, 0.1, 60);
    glVertex3f(-20, 0.1, 83);
    glVertex3f(40, 0.1, 83);
    glVertex3f(40, 0.1, 60);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(40, 0.1, 83);
    glVertex3f(40, 0.1, -27);
    glVertex3f(60, 0.1, -27);
    glVertex3f(60, 0.1, 83);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-20, 0.1, -7);
    glVertex3f(-20, 0.1, -27);
    glVertex3f(40, 0.1, -27);
    glVertex3f(40, 0.1, -7);
    glEnd();
    
    
}

void trees()			//draw a tree
{
    GLUquadricObj* quadratic;
    GLUquadricObj* quadratic1;
    quadratic1 = gluNewQuadric();
    quadratic = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.721, 0.525, 0.043);
    gluCylinder(quadratic, 1, 1, 10.0f, 32, 32);
    glPopMatrix();
    glTranslatef(0, 2, 0);
    glPushMatrix();
    float k = 0;
    for (int i = 0, j = 0; i < 3; i++, j += 0.5, k += 0.15)
    {
        glTranslatef(0, 1.8, 0);
        glColor3f(0.133 + k, 0.545 + k, 0.133 - k);
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic1, 4 - j, 0, 4.0f, 32, 32);
        glPopMatrix();
    }
    glPopMatrix();
}

void draw_arch(char text[5])		//draw the arch
{
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(-40,3.5, -36);
    glScalef(2, 7, 4);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40, 3.5, -20);
    glScalef(2, 7, 4);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40, 3.5, -4);
    glScalef(2, 7, 4);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40, 9, -20);
    glScalef(2, 4, 36);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-42, 8.3, -34.7);
    glRotatef(-90,0.0,1.0,0.0);
    glScalef(.009, .009, .009);
    glLineWidth(4.5);
    glColor3f(1, 1, 1);
    for (int c = 0; text[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[c]);
    glPopMatrix();
}

void wall() {
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 10, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 10, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 10, 40);
    glutWireCube(1);
    glPopMatrix();
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 10, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 10, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 10, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 10, 40);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 8, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 8, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 8, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 8, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 8, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 8, 40);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 6, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 6, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 6, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 6, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 6, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 6, 40);
    glutWireCube(1);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 4, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 4, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 4, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 4, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 4, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 4, 40);
    glutWireCube(1);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-66, 0.5, 10);
    glScalef(1, 2, 72);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 46);
    glScalef(23, 2, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, 38);
    glScalef(1, 2, 17);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, 24);
    glScalef(23, 2, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55, 0.5, -25);
    glScalef(23, 2, 1);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44, 0.5, -5);
    glScalef(1, 2, 40);
    glutWireCube(1);
    glPopMatrix();

    //boundry wall
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-7, 5, 98);
    glScalef(147, 12, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 5, -35);
    glScalef(147, 12, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(67, 5, 32);
    glScalef(1, 12, 133);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-80, 5, 9);
    glScalef(1, 12, 87);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-80, 5, 93);
    glScalef(1, 12, 12);
    glutSolidCube(1);
    glPopMatrix();

    //left gate
    if (flag == 0) {
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 11);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 9);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 7);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 5);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 3);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glScalef(1, 5, 1);
        glutWireCube(1);
        glPopMatrix();
    }

    if (flag == 1) {
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glRotatef(90,0.0,1.0,0.0);
        glScalef(1, 5, 7);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(1, 5, 5);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(1, 5, 3);
        glutWireCube(1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(-78, 2.6, 62);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(1, 5, 1);
        glutWireCube(1);
        glPopMatrix();
    }
    

    //right gate

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 11);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 9);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 7);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 5);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 3);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-78, 2.6, 78);
    glScalef(1, 5, 1);
    glutWireCube(1);
    glPopMatrix();


    
}

void welcomeDisplay() {
    char msg1[] = "COMPUTER GRAPHICS LABORATORY MINI PROJECT (18CSL67)";
    char msg2[] = "COLLEGE CAMPUS TOUR";
    char msg3[] = "FUNCTIONS: ";
    char msg4[] = "Key-w : Move Forward";
    char msg5[] = "Key-s : Move Backward";
    char msg6[] = "Key-u : Move Up";
    char msg7[] = "Key-j : Move Down";
    char msg71[] = "Key-g : Ground";
    char msg72[] = "key-p : Parking";
    char msg73[] = "Num-4 : CSE-4th floor";
    char msg74[] = "Key-t : Open Gate";
    char msg8[] = "Mouse-Left_Click & Rotate 360 Degree";
    char msg10[] = "Submitted by : ";
    char msg101[] = "Guide      : ";
    char msg102[] = "Dr. Veena R. S";
    char msg11[] = "Sachin Shenoy (1RF19CS045) CSE 6th Sem";
    char msg12[] = "Nisha E     (1RF19CS036) CSE 6th Sem";
    

    glPushMatrix();
    glTranslatef(-42, 15.4, -24);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.005, .005, .005);
    glLineWidth(2.5);
    glColor3f(0, 0,0);
    for (int c = 0; msg1[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg1[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 14.4, -19);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.005, .005, .005);
    glLineWidth(2.5);
    glColor3f(0, 0, 1);
    for (int c = 0; msg2[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg2[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 11, -24.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.0045, .0045, .0045);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg101[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg101[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 11, -19);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.004, .004, .004);
    glLineWidth(1.5);
    glColor3f(1, 1, 1);
    for (int c = 0; msg102[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg102[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 13, -24.0);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.0045, .0045, .0045);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg10[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg10[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 13, -19);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.004, .004, .004);
    glLineWidth(1.5);
    glColor3f(1, 1, 1);
    for (int c = 0; msg11[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg11[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42, 12, -19);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.004, .004, .004);
    glLineWidth(1.5);
    glColor3f(1, 1, 1);
    for (int c = 0; msg12[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg12[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33, 1, -30);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(1, 1, 1);
    for (int c = 0; msg3[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg3[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24, 6, -33);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg4[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg4[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24, 5, -33);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg5[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg5[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24, 4, -33);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg6[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg6[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24, 3, -33);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg7[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg7[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 4, -39);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg71[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg71[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 5, -39);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg72[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg72[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 3, -39);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg73[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg73[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 2, -39);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg8[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg8[c]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 6, -39);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    glScalef(.006, .006, .006);
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    for (int c = 0; msg74[c] != 0; ++c)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg74[c]);
    glPopMatrix();

    

}

void display()
{
    
    glClearColor(0.7, 0.7, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx, y, z + lz,
        0.0, 1.0, 0.0);
    printf("\nz=%f\tx=%f\n", z, x);
    glColor3f(0,0.5,0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 100);
    glVertex3f(100, 0, 100);
    glVertex3f(100, 0, 20);
    glVertex3f(-100, 0, 20);
    glVertex3f(-100, 0, 20);
    glVertex3f(-15, 0, 20);
    glVertex3f(-15, 0, -100);
    glVertex3f(-100, 0, -100);
    glVertex3f(-15, 0, -100);
    glVertex3f(100, 0, -100);
    glVertex3f(100, 0, -20);
    glVertex3f(-15, 0, -20);
    glVertex3f(25, 0, -20);
    glVertex3f(100, 0, -20);
    glVertex3f(100, 0, 20);
    glVertex3f(25, 0, 20);
    glEnd();
    disp_roads();
    for (int i = -70; i <= -45; i += 10) {
         glPushMatrix();
         glTranslatef(i, 0, 70);
         trees();
         glPopMatrix();
    }
    for (int i = -70; i <= 50; i += 10) {
        glPushMatrix();
        glTranslatef(i, 0, 90);
        trees();
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(-38, 0, 90);
    char tmp[] = "RV INSTITUTE OF TECHNOLOGY AND MANAGEMENT";
    draw_arch(tmp);
    welcomeDisplay();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-65, 0, 45);
    crt1.disp_court();
    glPopMatrix();
    wall();
    disp_interior();
    glPushMatrix();
    glTranslatef(-10, 0, 50);
    admin.disp_build(tmp,'l');
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void pressKey(unsigned char key, int xx, int yy)
{
    switch (key) {
    case 'w': deltaMove = 1.0; glutIdleFunc(update); break;
    case 's': deltaMove = -1.0; glutIdleFunc(update); break;
    case 'u': vertmove = 1; glutIdleFunc(update); break;
    case 'j': vertmove = -1; glutIdleFunc(update); break;
    case 'x': glutDisplayFunc(display); glutPostRedisplay(); break;
    case '4': y = 22; x = -7; z = 45; glutPostRedisplay(); break;
    case 'g': y = 4; x = -58; z = 38; glutPostRedisplay(); break;
    case 'p': y = 4; x = 49; z = 32.2; glutPostRedisplay(); break;
    case 't': flag = 1; glutPostRedisplay(); break;
    }
}

void releaseKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': deltaMove = 0.0; glutIdleFunc(NULL); break;
    case 's': deltaMove = 0.0; glutIdleFunc(NULL); break;
    case 'u': vertmove = 0; glutIdleFunc(NULL); break;
    case 'j': vertmove = 0; glutIdleFunc(NULL); break;
    case 't': flag = 0; glutPostRedisplay(); break;
    }
}

void mouseMove(int x, int y)
{
    if (isDragging) { // only when dragging
        // update the change in angle
        deltaAngle = (x - xDragStart) * -0.005;
        // camera's direction is set to angle + deltaAngle
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
        glutIdleFunc(update);
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = 1;
            xDragStart = x;
        }
        else { /* (state = GLUT_UP) */
            angle += deltaAngle; // update camera turning angle
            isDragging = 0; // no longer dragging
            glutIdleFunc(NULL);

        }
    }
}

int main(int argc,char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(40, 40);
    glutCreateWindow("HOUSE");
    
    
    glutDisplayFunc(display);
    
    glutReshapeFunc(changeSize); // window reshape callback

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);
    glutMouseFunc(mouseButton); // process mouse button push/release
    glutMotionFunc(mouseMove); // process mouse dragging motion
    glutMainLoop();
}
