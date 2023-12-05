//Author: Conner Estes
// Created: 09/27/2023
// Description: My individual source file for my CMPS 3350 project.
// (c) Copyright by Conner Estes

//#include "burger_dash.cpp"
#include "cestes.h"
#include <GL/glx.h>
#include "fonts.h"
#include <ctime>
#include <cstring>
#include <unistd.h>
/*

void display_border(int xres, int yres)
{
    //draw border around window
    int b = 50;
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(1.0f,1.0f,0.0f,0.5f);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2i(0,0);
        glVertex2i(0+b,0+b);
        glVertex2i(0,0+yres);
        glVertex2i(0+b,0+yres-b);
        glVertex2i(xres,0+yres);
        glVertex2i(xres-b,0+yres-b);
        glVertex2i(xres, 0);
        glVertex2i(xres-b,b);
        glVertex2i(0,0);
        glVertex2i(0+b,0+b);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}
*/


Square burger;
int physics_count;


void display_name (int x , int y)
{
    Rect r;
    r.bot = y;
    r.left = x;
    r.center = 0;
    ggprint8b(&r, 0, 0x00000000, "Conner");
}




Enemy enemy;  // Definition of the enemy variable

bool Check3(Square burger, Oil oil) {
    int leftBurger = burger.pos[0] - burger.width;
    int rightBurger = burger.pos[0] + burger.width;
    int topBurger = burger.pos[1] - burger.height;
    int bottomBurger = burger.pos[1] + burger.height;

    int leftOil = oil.pos[0] - oil.width;
    int rightOil = oil.pos[0] + oil.width;
    int topOil = oil.pos[1] - oil.height;
    int bottomOil = oil.pos[1] + oil.height;

    if (rightBurger < leftOil || rightOil < leftBurger)
        return false;

    if (bottomBurger < topOil || bottomOil < topBurger)
        return false;


    // If there is a collision, set burger's velocity to 0

    return true;




}


// Definition of the collision detection function
bool Check2(Square burger, Enemy enemy) {
    bool enemyCollisionOccurred = false;
    int leftBurger = burger.pos[0] - burger.width;
    int rightBurger = burger.pos[0] + burger.width;
    int topBurger = burger.pos[1] - burger.height;
    int bottomBurger = burger.pos[1] + burger.height;

    int leftEnemy = enemy.pos[0] - enemy.width;
    int rightEnemy = enemy.pos[0] + enemy.width;
    int topEnemy = enemy.pos[1] - enemy.height;
    int bottomEnemy = enemy.pos[1] + enemy.height;

    if (rightBurger <= leftEnemy || rightEnemy <= leftBurger)
        return false;

    if (bottomBurger < topEnemy || bottomEnemy < topBurger)
        return false;

    // If there is a collision, set burger's velocity to 0
    return true;
}

// Implement the Enemy class as needed
// For example, rendering the enemy
void renderEnemy() {
    glPushMatrix();
    glColor3ub(0, 0, 255);  // Blue color
    glTranslatef(enemy.pos[0], enemy.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-enemy.width, -enemy.height);
    glVertex2f(-enemy.width, enemy.height);
    glVertex2f(enemy.width, enemy.height);
    glVertex2f(enemy.width, -enemy.height);
    glEnd();
    glPopMatrix();
}

int total_physics_function_calls(){
    static int firsttime = 1;
    static int physics_count;
    if (firsttime){

        physics_count =0;
        firsttime = 0;
    }

    else{
        physics_count++;
    }





   return physics_count;

}


const double physicsRate = 1.0 / 10.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end)
{
    //return the difference in two times.
    return (double)(end->tv_sec - start->tv_sec ) +
        (double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source)
{
    //copy one time structure to another.
    memcpy(dest, source, sizeof(struct timespec));
}

Health healthbar;
void renderHealth() {
    int green;
    int red;
    //Health healthbar;
    if (healthbar.health > 170) {
        green = 255;
        red = 0;
    }

    else if (healthbar.health < 170 && healthbar.health > 85 ) {
            red = 255;
            green = 255;
    }
    if (healthbar.health < 85) {
        red = 255;
        green = 0;

    }

    glPushMatrix();
    glColor3ub(red, green, 0);  // Green color
    glTranslatef(healthbar.pos[0], healthbar.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-healthbar.width, -healthbar.height);
    glVertex2f(-healthbar.width, healthbar.height);
    glVertex2f(healthbar.width, healthbar.height);
    glVertex2f(healthbar.width, -healthbar.height);
    glEnd();
    glPopMatrix();



}


Oil oil;

void renderOil(){

    glPushMatrix();
    glColor3ub(0,255, 0);  // Green color
    glTranslatef(oil.pos[0], oil.pos[1], 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-oil.width, -oil.height);
    glVertex2f(-oil.width, oil.height);
    glVertex2f(oil.width, oil.height);
    glVertex2f(oil.width, -oil.height);
    glEnd();
    glPopMatrix();

}

void renderGameOver( int xres, int yres, X11_wrapper& x11, Global& gl) {
    glClear(GL_COLOR_BUFFER_BIT);
    unsigned int c = 0x00ffff44;
    // Render game over message and any other elements of the game over screen.
    // You can use glColor3ub, glPushMatrix, glBegin, glEnd, and other OpenGL functions
    // to draw text and graphics for the game over screen.
    // For example:
    glColor3ub(255, 0, 0); // Red color
    // Position and draw your game over message.
    // Example:
    Rect gameOverText;
    gameOverText.bot = yres / 2;
    gameOverText.left = xres / 2;
    gameOverText.center = 1;
    ggprint8b(&gameOverText, 16, c, "Game Over");

    // Render any other game over elements as needed.

    x11.swapBuffers();
}



// burger_dash.cpp



// ... other definitions ...

