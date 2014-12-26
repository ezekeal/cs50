/**
 * caesar.c
 *
 * encrypts text with a cipher
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
    if(argc != 2 || !isalpha(argv[1]))
    {
        printf("Fool!\n");
        return 1;
    }
    
    int k = atoi(argv[1]) % 26;

    string text = GetString();
    
    for(int i=0, n = strlen(text); i < n; i++)
    {
        char ch = text[i];

        if(isalpha(ch))
        {   
            int mod = (int) 'a';

            if isupper(ch)
            {
                mod = (int) 'A';    
            }
            ch = (char) ( (k + (int) ch - mod) % 26 + mod); 
        }
        
        printf("%c", ch);
    }

    printf("\n");

    return 0;
}
