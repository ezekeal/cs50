#include <stdio.h>
#include <cs50.h>

int main (void)
{
    /* mario.c
     * 
     * create a mario style half pyramid of hashes based on user input
     */
    
    int height = 24;
    int width;
    //prompt user for the height (a non-negative integer no greater than 23)
    while (!(height >= 0 && height < 24)) // loop will repeat until the prompt is obeyed
    {
        printf("Enter a half-pyramid height [0-23]: ");
        height = GetInt();
        width = height + 1;
    }
    
    for (int i = 1; i <= height; i++)  // each iteration prints a line i represents the line number
    {
        for (int j = 1; j <= width; j++) // each iteration prints a character j is the character position
        {
            if ( j < width - i )
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
    
    return 0;
}
