/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (value == values[i])
        {
            return true;
        }
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // O(n^2) sorting algorithm
    for(int i=0; i<n; i++)
    {
        int smallest = values[i];
        int smallIndex = i;
        for (int j=i+1; j<n; j++)
        {
            if(values[j] < smallest)
            {
                smallest = values[j];
                smallIndex = j;
            }
        }
        values[smallIndex] = values[i];
        values[i] = smallest;
    } 
    return;
}
