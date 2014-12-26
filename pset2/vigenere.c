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
    int cipherNum[strlen(cipher)];
    // check string to see if each item is a character
    for(i = 0, n = strlen(cipher); i < n; i++)
    {
        if(!isalpha(cipher[i]))
        {
            printf("Fool!\n");
            return 1;
        }
        //creat a numerical version of the cipher
        cipherNum[i] = (int) tolower(cipher[i]) -  (int) 'a';
    }
    
    // get the phrase
    string text = GetString();
    
    // TEST enter phrase for testing
    text = "Meet me at the park at eleven am";
    string solution = "Negh zf av huf pcfx bt gzrwep oz";
    
    for(int i=0, n = strlen(text); i < n; i++)
    {
        char ch = text[i];
        int cipherPos = 0;

        if(isalpha(ch))
        {   
            int mod = (int) 'a';

            if isupper(ch)
            {
                mod = (int) 'A';    
            }
            ch = (char) (cipherNum[cipherPos % strlen(cipherNum)] + (int) ch - mod) % 26 + mod);
            cipherPos ++;
        }
        
        printf("%c", ch);
    }
    printf("\n");
    printf(solution):
    printf("\n");

    return 0;
}
