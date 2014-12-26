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
    // check the number of arguments
    if(argc != 2)
    {
        printf("Fool!\n");
        return 1;
    }
    
    string cipher = argv[1];

    // check string to see if each item is a character
    for(int i = 0, n = strlen(cipher); i < n; i++)
    {
        if(!isalpha(cipher[i]))
        {
            printf("Fool!\n");
            return 1;
        }
        cipher[i] = tolower(cipher[i]);
    }
    
    // get the phrase
    string text = GetString();
    
    int cipherPos = 0;
    
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
            ch = (char) ( ( (int) cipher[cipherPos % strlen(cipher)] - (int) 'a' + (int) ch - mod ) % 26 + mod );
            cipherPos ++;
        }
        
        printf("%c", ch);
    }
    printf("\n");

    return 0;
}
