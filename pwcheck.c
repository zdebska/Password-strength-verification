/*
---       Project 1       ---
---   Zdebska Kateryna    ---
---       31.01.10        --- 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//constants
#define MAX_LENGTH 100 
#define ADD_PARAM "--stats" 

//globals
int LEVEL, PARAM;


//           ADDITIONAL FUNCTIONS


int LenStr(char *password) // сounting the length of an array
{
    int counter = 0;
    while (password[counter])
        counter++;
    return counter;
}

bool Compare(char *str1, char *str2) // comparison of two strings
{
    //length comparison
    if (LenStr(str1) != LenStr(str2))
        return false;

    //conparison by symbols
    for (int i = 0; i < LenStr(str1); i++)
        if (str1[i] != str2[i])
            return false;
    return true;
}

bool isNumber(char *str) //checking if string is number
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}


//           LEVELS CHECK FUNCTIONS


bool FirstCondition(char *password) 
{
    bool fl_capital_letter = false, fl_small_letter = false, rezult = false; // flags that indicate the presence of 
    for (int i = 0; password[i] != '\0'; i++)                                // a capital/small letter
    {
        if (password[i] >= 'a' && password[i] <= 'z')
            fl_small_letter = true;
        else if (password[i] >= 'A' && password[i] <= 'Z')
            fl_capital_letter = true;
    }
    if (fl_small_letter && fl_capital_letter)
        rezult = true;
    return rezult;
}

bool SecondCondition(char *password)
{
    bool fl_number = false, fl_symbol = false; // flags that indicate the presence of number/symbol
    if (FirstCondition(password))
    {
        if (PARAM <= 2)  // the second level can be passed only if the first level is completed
            return true; // thus, at least 2 conditions from second level will be completed
        else
        {
            for (int i = 0; password[i] != '\0'; i++)
            {
                if (password[i] >= '0' && password[i] <= '9')
                {
                    fl_number = true;
                }
                if ((password[i] >= 32 && password[i] < '0') || (password[i] > '9' && password[i] < 'A') ||
                    (password[i] > 'Z' && password[i] < 'a') || (password[i] > 'z' && password[i] <= 126))
                    fl_symbol = true;
            }
            if (PARAM>=4 ? fl_number && fl_symbol : fl_number || fl_symbol) // if PARAM==3 at least one flag must be true
                return true;
        }
    }
    return false;
}

bool ThirdCondition(char *password)
{
    int counter_symbols = 0; // counter_symbols - number of repeating pairs which contain the same symbols
    if (SecondCondition(password))
    {
        for (int i = 1; password[i] != '\0'; i++)
        {
            if (password[i] == password[i - 1])
                counter_symbols++;
            else
                counter_symbols = 0;
            if (counter_symbols == PARAM - 1) // the number of pairs is 1 less than the PARAM
                return false;
        }
        return true;
    }
    return false;
}

bool FourthCondition(char *password)
{
    char temp[MAX_LENGTH][MAX_LENGTH] = {0}; // array of substrings of length PARAM
    int num_substr = 0; // number of substrings
    if (ThirdCondition(password))
    {
        for (; num_substr <= LenStr(password) - PARAM; num_substr++)
        {
            for (int j = num_substr; j < PARAM + num_substr; j++)
                temp[num_substr][j - num_substr] = password[j];
        }
        //comparing all substrings in array 
        for (int j = 0; j < num_substr; j++)
        {
            for (int k = j + 1; k < num_substr; k++)
            {
                if (Compare(temp[j], temp[k]))
                    return false;
            }
        }
        return true;
    }
    return false;
}


//           START


int main(int argc, char *argv[])
{
    //variables of stats (COUNT and SUM are for AVG)
    int MIN = MAX_LENGTH, COUNT = 0, NCHARS = 0; 
    float AVG = 0, SUM = 0;

    int size = 0; // size of array
    char password[MAX_LENGTH] = {0}; // array for each password
    char c; // for reading from file
    bool fl_stats = false; // existence of third argument 
    bool levels[5] = {0}; //array of checked levels
    int symbols[127] = {0}; // array of unique symbols in passwords

    //VALIDATION

    if (argc < 3 || argc > 4)
    {
        fprintf(stderr, "Error: Invalid number of arguments");
        return EXIT_FAILURE;
    }

     //VALIDATION 

    if (argc == 4)
    {
        fl_stats = true;
        if (!Compare(argv[3], ADD_PARAM))
        {
            fprintf(stderr, "Error: Incorect third parametr");
            return EXIT_FAILURE;
        }

    }
    // since the second argument has no limitations in objective, the variable has the greatest data type for it
    unsigned long long temp_param = strtoull(argv[2], NULL, 10);
    // if the parameter is greater than MAX_LENGTH, it can be treated as MAX_LENGTH 
    if (temp_param > MAX_LENGTH)
        temp_param = MAX_LENGTH;
    PARAM = temp_param;
    LEVEL = atoi(argv[1]);

    //VALIDATION

    if (PARAM < 1 || (LEVEL < 1 || LEVEL > 4))
    {
        fprintf(stderr, "Error: Invalid parametrs");
        return EXIT_FAILURE;
    }

    if (!isNumber(argv[1]) || !isNumber(argv[2]))
    {
        fprintf(stderr, "Error: Incorrect parametrs (not number)");
        return EXIT_FAILURE;
    }

    //reading and checking passwords
    while ((c = getchar()) != EOF)
    {
        if (c != '\n')
        {
            password[size] = c;
            /*If a symbol is present, the value of the array with the indexes of the ASCII table becomes 1,
            * in order to calculate the sum of the values of the array, and get NCHAR
            */
            symbols[(int)(c)] = 1;
            size++;

            //VALIDATION

            if (size > 100)
            {
                fprintf(stderr, "Error: Invalid length of password");
                return EXIT_FAILURE;
            }
        }
        else
        {
            password[size] = '\0'; // making string
            //checking on levels
            levels[1] = FirstCondition(password);
            levels[2] = SecondCondition(password);
            levels[3] = ThirdCondition(password);
            levels[4] = FourthCondition(password);
            if (levels[LEVEL])
                printf("%s\n", password);

            // calculation statistics
            if (MIN >= LenStr(password))
                MIN = LenStr(password);
            SUM += LenStr(password);
            COUNT++;

            size = 0; // reset password size for another one
        }
    }

    // calculation statistics
    AVG = SUM / COUNT;
    for (int i = 0; i < 127; i++)
        NCHARS += symbols[i];

    // statistics output
    if (fl_stats)
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", NCHARS, MIN, AVG);

    return 0;
}
