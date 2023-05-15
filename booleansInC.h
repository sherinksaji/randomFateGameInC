#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int divide_by_2_power_n(int val, int n)
{
    return val >> n;
}

int get_boolean_value(char *booleans, int index)
{
    char theCharacter = *booleans;

    int number = (int)theCharacter;
    int boolean_val = 0;
    int i = 7;
    while (i >= 0)
    {

        if (divide_by_2_power_n(number, i) == 1)
        {
            boolean_val = 1;

            number -= (1 << i);
        }
        else
        {
            boolean_val = 0;
        }

        if (i == index)
        {
            break;
        }

        i--;
    }
    return boolean_val;
}

void update_boolean_value(char *booleans, int index, int val)
{

    int boolValuesArr[8];
    int newNumber = 0;
    char theCharacter = *booleans;
    int number = (int)theCharacter;
    int i;

    if (val != 0)
    {
        val = 1;
    }

    for (i = 0; i <= 7; i++)
    {

        boolValuesArr[i] = (i == index) ? val : get_boolean_value(booleans, i);

        newNumber += ((boolValuesArr[i]) << i);
    }

    *booleans += (newNumber - number);
}

void print_boolean(char *booleans, int index)
{
    printf("%d", get_boolean_value(booleans, index));
}

void print_all_boolean(char *booleans)
{
    int i;
    printf("\n");

    for (i = 7; i >= 0; i--)
    {
        print_boolean(booleans, i);
    }
    printf("\n");
    printf("all booleans printed");
    printf("\n");
}

int lottery_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}