/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// index of x/y coordinates by tile value
int tileLoc[MAX * MAX][2];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
void swap(int tileA, int tileB);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen [int](the length/width of the square board)\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int tile = d * d - 1;
    // iterate rows
    for(int j=0; j<d; j++)
    {
        // iterate columns
        for(int i=0; i<d; i++)
        {
            board[i][j] = tile;
            tileLoc[tile][0] = i;
            tileLoc[tile][1] = j;
            tile--;
        }
    }
    //swap 1 and 2 if the board has even dimensions
    if(d%2 == 0)
    {
        swap(1,2);
    }

    return;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int j=0; j<d; j++)
    {
        for (int i=0; i<d; i++)
        {
            int num = board[i][j];
            if (num == 0)
            {
                printf("_  ");
            }
            else if (num > 9)
            {
                printf("%d ", num);
            }
            else
            {
                printf("%d  ", num);
            }
        }
        printf("\n");
    }

    printf("\n");
    return;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{    
    // test to see if tile is in bounds
    if(tile < 1 || tile > d*d-1)
    {
        return false;
    }
    
    // get tile coordinates
    int tileX = tileLoc[tile][0]; 
    int tileY = tileLoc[tile][1];

    // test each direction
    // up
    if (tileY-1 >= 0)
    {
        if(board[tileX][tileY-1] == 0)
        {
            swap(tile, 0);
            return true;
        }
    }
    // down
    if (tileY+1 < d)
    {
        if(board[tileX][tileY+1] == 0)
        {
            swap(tile, 0);
            return true;
        }
    }
    // left
    if (tileX-1 >= 0)
    {
        if(board[tileX-1][tileY] == 0)
        {
            swap(tile, 0);
            return true;
        }
    }
    // right
    if (tileX+1 < d)
    {
        if(board[tileX+1][tileY] == 0)
        {
            swap(tile, 0);
            return true;
        }
    }
   
    //if not adjacent return false
    return false;
}

/**
 * Swaps two tiles
 */
void swap(int tileA, int tileB)
{
    int xA = tileLoc[tileA][0];
    int yA = tileLoc[tileA][1];
    int xB = tileLoc[tileB][0];
    int yB = tileLoc[tileB][1];
    //update index
    tileLoc[tileA][0] = xB;
    tileLoc[tileA][1] = yB;
    tileLoc[tileB][0] = xA;
    tileLoc[tileB][1] = yA;
    //update board
    board[xA][yA] = tileB;
    board[xB][yB] = tileA;
    return;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int tile = 1;
    for(int i=0; i<d; i++)
    {
        for (int j=0; j<d; j++)
        {   if(i == d-1 && j == d-1)
            {
                return true;
            }
            if(board[j][i] != tile)
            {
                return false;
            }
            tile++;
        }
    }
    printf("something's wrong");
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

