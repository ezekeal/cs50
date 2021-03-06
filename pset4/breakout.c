//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// colors
char*  COLORS[7] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN", "BLUE", "MAGENTA"};

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if something happens
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                
                // get paddle y and width
                double rY = getY(paddle);
                double rW = getWidth(paddle);

                // set paddle x to mouse x
                double rX = getX(event) - rW / 2;
                
                // normalize to window
                if (rX < 0)
                {
                    rX = 0;
                }
                else if (rX > WIDTH - rW)
                {
                    rX = WIDTH - rW;
                }

                setLocation(paddle, rX, rY);
            }
        }

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // set brick dimensions based on enclosing window
    double bW = (0.8 * WIDTH)/ COLS;
    double bH = (0.6 * (HEIGHT / 4)) / ROWS;
    double bWp = (0.2 * WIDTH) / (COLS +1); 
    double bHp = (0.4 * (HEIGHT / 4)) / (ROWS + 1);
    // starting x and y location
    double x = 0, y = 0;

    // instantiate bricks based on ROWS and COLS constants
    for(int i=0; i<ROWS; i++)
    {
        y += bHp;
        x = 0;
        for(int j=0; j<COLS; j++)
        {
            x += bWp;
            GRect brick = newGRect(x,y, bW, bH);
            setFilled(brick, true);
            string bC = COLORS[(int)(i+j) % 7];
            setColor(brick, bC);
            add(window, brick);
            x += bW;
        }
        y += bH;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // get coordinates for the center
    double x = WIDTH / 2;
    double y = HEIGHT / 2;

    GOval b = newGOval(x,y,RADIUS, RADIUS);
    setFilled(b, true);
    setColor(b, "BLACK");
    add(window, b);
    return b;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int paddleWidth = WIDTH / 5;
    int paddleHeight = HEIGHT / 100;
    int x = WIDTH / 2 - paddleWidth / 2;
    int y = HEIGHT - HEIGHT / 8 - paddleHeight / 2;
    GRect p = newGRect(x, y,paddleWidth,paddleHeight);
    setFilled(p, true);
    setColor(p, "BLACK");
    add(window, p);
    return p;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
