#include <stdio.h>
#include <cs50.h>

int main (void)
{
    /* mario.c
     * 
     * create a mario style half pyramid of hashes based on user input
     */
    
    int = height = 24;
    //prompt user for the height (a non-negative integer no greater than 23)
    while !(x >= 0 && x <= 23) // loop will repeat until the prompt is obeyed
    {
        printf("Enter a half-pyramid height [0-23]: ");
        height = getint();
    }
    
    for (int i = 1; i <= height; i++)  // each iteration prints a line i represents the line number
    {
        for (int j = 1; j <= i + 2; j++) // each iteration prints a character j is the character position
        {
            if ( j < height )
            {
                printf(" ");
            }
            else
            {
                printf("#")
            }
            printf("\n");
        }
    }
    //re-prompt if the user enters something outside the bounds
    
    //generate the pyramid using printf and one or more loops
    //be aware of alignment
}
