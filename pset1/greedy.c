/**
 * greedy.c
 *
 * gives the minimum number of common US coins
 * required to give change for an amount given
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

 int main(void)
 {
    int cents = -1;
    int coins = 0;
    while(cents < 0)
    {
        printf("How much change is owed?: ");
        cents = (int) round(GetFloat() * 100.0);
    }
    
    int coinValues[4] = {25, 10, 5, 1};

    for (int i = 0; i < 4; i++)
    {
        int x = cents / coinValues[i];
        coins += x;
        cents -= x * coinValues[i];
        
    }
    
    printf("%i\n", coins);

    return 0;           
 }
