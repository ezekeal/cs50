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
 * recursive search algorithm
 */
bool binary(int start, int end, int values[], int target)
{
    
    int midIndex = (start + end) / 2;
    int midValue = values[midIndex];

    if (midValue == target)
    {
        return true;
    }
    else if (start == end || start + 1 == end) 
    {
        return false;
    }
    else if (midValue > target)
    {
        return binary(start, midIndex, values, target);
    }
    else if (midValue < target)
    {
        return binary(midIndex, end, values, target);
    }
    else
    {
        printf("something's wrong");
        return false;
    }
}



/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }
    
    if (values[0] == value || values[n-1] == value)
    {
        return true;
    }

    return binary(0, n-1, values, value);
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
