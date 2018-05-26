/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Elias Röbl
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/

#include <stdio.h>
#include "lottery.h"

static char* file_static;
static char separator_static;
static int* lotto_numbers;
static bool drew = false;

 bool init_lottery(char* csv_file, char csv_separator)
 {
    FILE* file = fopen(csv_file, "r");
    separator_static = csv_separator;
    drew = false;
    file_static = csv_file;
    if(file == 0){return false;}
    fclose(file);
    return true;
}

bool get_tip(int tip, int* array)
{
    FILE* file = fopen(file_static, "r");
    int count1 = 0;
    char input[MAX_LINE_LEN] = 0;
    if(tip < 0 || file == 0)
    {
        fclose(file);
        return false;
    }
    char* result = fgets(input, MAX_LINE_LEN, file);
    while(result != NULL && count1 < tip)
    {
        result = fgets(input, MAX_LINE_LEN, file);
        count1++;
        if(input != result)
        {
            fclose(file);
            return false;
        }
    }
    if(ftell(file) == EOF)
    {
        fclose(file);
        return false;
    }
    int position = 0;
    while(input[position] != csv_separator && position < UUID_LEN)
    {
        position++;
    }

    int position_for_insertion = 0;
    int insertion = 0;
    while(position_for_insertion < AMOUNT_OF_LOTTO_NUMBERS)
    {
        position++;
        if(input[position] <= '9' && input[position] >= '0')
        {
            insertion = insertion * 10 + (input[position] - '0');
        }
        else
        {
            array[position_for_insertion] = insertion;
            insertion = 0;
            position_for_insertion++;
        }
    }
    fclose(file);
    return true;
}

bool set_drawing(int* array)
{
    lotto_numbers = array;
    drew = true;
    return false;
}

int get_tip_result(int tip)
{
    if(drew == FALSE ){return -1;}
    int array[AMOUNT_OF_LOTTO_NUMBERS] = 0;
    if(get_tip(tip, array) == FALSE)return -2;
    int count = 0;
    int a,b=0;
    while(a < AMOUNT_OF_LOTTO_NUMBERS)
    {
      while(b < AMOUNT_OF_LOTTO_NUMBERS)
      {
        if(array[a] == lotto_numbers[b]){count++;}
        b++;
      }
      a++;
    }

    return count;
}

int get_right_tips_count(int tip)
{
    if(tip < 0 || tip > TIP_SIZE || !drew){return -1;}
    int count1,count2,count3 = 0;
    while(count3 != -2&& count3 != -1)
    {
        count3 = get_tip_result(count1);
        if(count3 == tip){count2++;}
        count1++;
    }
    return count2;
}
