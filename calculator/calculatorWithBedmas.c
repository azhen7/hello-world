/***************************************************************************************************************
 * - 5/25/2021: Version 1.02
 *      - Added PI functionality.
 *
 * - 5/26/2021: Version 1.03
 *      - Bug 1 (incorrect value of PI) - PATCHED
 *      - Bug 2 (nCr and nPr doesn't work properly) - PATCHED
 *      - Bug 3 (incorrect value of a + b * c) - PATCHED - BEDMAS is handled differently now
 *          - This lead to Bug (a - b where a < b) - PATCHED
 *      - Bug 4 (incorrect value of a % b + c) - PATCHED
 *      - Bug 5 (incorrect value of a + b % c) - PATCHED
 *      - Bug 6 (fraction addition doesn't work) - PATCHED
 *      - Bug 7 (where adding 5 numbers returns -nan) - PATCHED - Zeroing all elements is now handled manually instead of using memset()
 *      - Bug 8 (cPI has incorrect value, where c is a number (e.g. 2PI)) - PATCHED
 *      - Added the constants: Golden Ratio, Root 2, Root 3, Euler's number.
 *
 * - 5/27/2021: Version 1.04
 *      - Added Silver Ratio, Apery's Constant.
 *      - Bug 9 (Seg fault when input string has no spaces) - PATCHED
 *      - Added sqrt and cbrt
 *          - Bug 10 (sqrt(a) where a < 0 = 0) - PATCHED
 *          - Bug 11 (a + sqrt(b) returns value of sqrt(a) + b) - PATCHED
 *      - Automatic text formatting function was removed.
 *
 * - 5/28/2021: Version 1.05
 *      - sqrt and cbrt has been removed
 *      - Added root() function (root(a, b) returns bth root of a)
 *          - Bug 12 (a root( + b, c returns value of a + root(b, c)) - PATCHED
 *          - Bug 13 (a + root(b, c) = NAN) - PATCHED
 *      - Bug 14 (4 nCr 2 = 2 * the correct value) - PATCHED
 *      - Added log_base function (log_base(a, b) returns log base b of a)
 *      - Added GCD and LCM functions
 *      - Bug 15 (a + root(b, c) = NAN) - PATCHED
 *      - Bug 16 (root(b, c) + a has incorrect value) - PATCHED
 *      - Bug 17 (root(b, c) * a has incorrect value) - PATCHED
 *
 * - 5/29/2021: Version 1.06
 *      - Bug 18 (a * root(b, c) has incorrect value) - PATCHED
 *      - Bug 19 (root(b, c) * a = NULL) - PATCHED
 *      - Bug 20 (Seg fault after entering root(b, c)) - PATCHED
 *      - Bug 21 (sin(9) = NAN) - PATCHED
 *      - New feature: If result returned is an integer, 0 decimal places are printed.
 *
 * - 5/30/2021: Version 1.07
 *      - Added base converter - you can convert numbers in different bases. Type "convert bases" to
 *        use the number base converter
 *      - Bug 22 (tan( + 4 + 4 returns value of tan(4) + 4) - PATCHED - Now, nums[location] is checked for whether
 *        it is before next operation
 *      - Bug 23 (second input when first input starts with "cos(" or "tan(" displays error) - PATCHED
 *      - Bug 24 (-a * b returns value of -a - b) - PATCHED
 *      - Added E function (4E3)
 *      - Update to nCr and nPr: you now cannot do "a nCr b" where b is a decimal
 *
 *  - 5/31/2021: Version 1.08
 *      - Bug 25 (a + sin(b) returns value of sin(b)) - PATCHED
 *      - Update to trig functions - If character right after "(" is not a number, NAN is returned
 *      - Added arcsin, arccos, arctan, arcsinh, arccosh, arctanh
 *      - Added iterative log function
 *      - Re-added sqrt and cbrt for convenience
 *      - Added square and cube functions (which square and cube a number, respectively)
 *      - Added code that checks for double decimal points
 *
 *  - 6/1/2021: Version 1.09
 *      - Bug 26 (square(b) = NAN) - PATCHED
 *      - Bug 27 (log(9 + 2 returns a value, not NAN) - PATCHED
 *      - Added ln and log for convenience
 *      - Changed iterative log from "iterate_log(" to "log*("
 *      - Bug 30 (a / b % c returns infinity) - PATCHED
 *      - Added binary log (log2) for convenience
 *      - Added tetration function (for a given number n, a is multiplied to itself n - 1 times)
 *
 *  - 6/2/2021: Version 1.10
 *      - Bug 31 (tetration returns incorrect value) - PATCHED
 *      - Bug 32 (cbrt(-27) = NAN) - PATCHED
 *      - Bug 33 (a * b nCr c returns incorrect value) - PATCHED - nCr and nPr now take higher precedence than
 *        multiplication and division
 *
 *  - 6/3/2021: Version 1.11
 *      - Bug 34 (a -b returns incorrect value) - PATCHED
 *      - Bug 35 (root(a, b), where a < 0 and b is an odd number, returns -nan) - PATCHED
 *      - Bug 36 (3 + PI returns incorrect value) - PATCHED
 *
 *  - 6/4/2021: Version 1.12
 *      - Added prime factoring
 *          - Bug 37 (infinite loop when entering specific input) - PATCHED
 *
 *  - 6/5/2021: Version 1.13
 *      - Bug 38 (incorrect ouput when entering specific input) - PATCHED
 *      - Bug 39 (Floating point exception) - PATCHED
 *
 *  - 6/7/2021: Version 1.14
 *      - Bug 40 (sin(a * b = NAN) - PATCHED
 *
 *  - 6/8/2021: Version 1.15
 *      - Bug 41 (sin(Pi = NAN) - PATCHED
****************************************************************************************************************/

#include "defs.h"

long double solveEquation(char* input);
long double convertFloat(char* input, int startIndex, int endIndex);
unsigned int numberOfOperations(char* input);
long double getMathConstant(char* input, int index, float mathConstant);
long double returnValueOfMathConstant(char* input, int i);
long double setNum(char* operations, int index);
int isvalidInput(char* input);

int main(void)
{
    char* getEquation = NULL;
    double result = 0.0;
    //Number base conversion
    int base_input;
    int base_convert;
    char* convertedValue;
    //Prime factoring
    int numToPrimeFactor = 0;
    int numberOfPrimeFactors = 0;

    system("clear");
    printf("Enter a bunch of equations below: \n");

    while (1)
    {
        getEquation = get_string("");
        //Number base conversion
        if (strcmp(getEquation, "convert bases") == 0)
        {
            do
            {
                base_input = get_int("Enter base of input: ");
            }
            while (base_input > 36 || base_input < 2);

            do
            {
                base_convert = get_int("Enter base to convert input to: ");
            }
            while (base_convert > 36 || base_input < 2);

            getEquation = get_string("Enter input: ");

            if (validateInput(getEquation, base_input))
                printf("Invalid input.\n");
            else
            {
                convertedValue = convert(getEquation, base_input, base_convert);

                if (convertedValue != NULL)
                    printf("Your input in base %i is: %s\n", base_convert, convertedValue);
                else
                    printf("malloc(): memory allocation failed.\n Operation discontinued.\n");
            }
        }
        //Prime factoring
        else if (strcmp(getEquation, "prime factor") == 0)
        {
            numToPrimeFactor = get_int("Enter number to be prime factored: ");
            if (numToPrimeFactor > UINT_MAX)
            {
                printf("Number too large to prime factor.\n\n");
                continue;
            }
            if (numToPrimeFactor <= 1)
            {
                printf("Number cannot be prime factored.\n\n");
                continue;
            }
            if (isPrime(numToPrimeFactor) == 0)
            {
                printf("(%i)\n\n", numToPrimeFactor);
                continue;
            }
            numberOfPrimeFactors = getNumberOfPrimeFactors(numToPrimeFactor);
            int* primeFactors = (int*) malloc(numberOfPrimeFactors);
            primeFactors = getPrimeFactors(numToPrimeFactor);
            int* primeFactorExponents = (int*) malloc(numberOfPrimeFactors);
            primeFactorExponents = getPrimeFactorExponents(numToPrimeFactor);
            //printf("%i\n", numberOfPrimeFactors);
            for (int i = 0; i < numberOfPrimeFactors; i++)
            {
                printf("%i", primeFactors[i]);
                if (primeFactorExponents[i] > 1)
                    printf("^%i", primeFactorExponents[i]);
                if (i != numberOfPrimeFactors - 1)
                    printf(" x ");
            }
            puts("");
        }
        //Solve equation
        else
        {
            result = solveEquation(getEquation);

            //Erase equation typed by user
            fputs("\033[A\033[2K", stdout);
            rewind(stdout);

            if (fabs(round(result) - result) < 0.000000001)
                printf("%s = %.0f\n", getEquation, result);
            else
                printf("%s = %f\n", getEquation, result);
        }
        putchar('\n');
    }
}

long double solveEquation(char* input)
{
    unsigned int times = 0, posIndex = 0;
    double total = 0.0;
    char* equation = (char*) malloc(strlen(input) * sizeof(char));
    char* arr = (char*) malloc(ARRAY_SIZE);
    char* functions = (char*) malloc(strlen(input));
    int functionPositions[strlen(input) - 5];
    unsigned int numberOfFunctions = 0;

    if (!isvalidInput(input))
        return NAN;

    equation = copyStrWithoutSpaces(input);
    char c;

    for (int i = 0; i < strlen(equation); i++)
    {
        if (!isascii(equation[i]))
            return NAN;
        else if (isalpha(equation[i]))
        {
            strncpy(arr, &equation[i], ARRAY_SIZE);
            if (equation[i] == 'P' || equation[i] == 'p')
            {
                if (strncmp(arr, "PI", 2) == 0 || strncmp(arr, "pi", 2) == 0)
                {
                    equation[i] = '!';
                    removeChar(equation, i, 1);
                    i++;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'A')
            {
                if (strncmp(arr, "APERY_CNST", 10) == 0)
                {
                    removeChar(equation, i, 9);
                    i += 9;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'a')
            {
                if (strncmp(arr, "arcsin(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "d");
                }
                else if (strncmp(arr, "arccos(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "e");
                }
                else if (strncmp(arr, "arctan(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "f");
                }
                else if (strncmp(arr, "arcsinh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "g");
                }
                else if (strncmp(arr, "arccosh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "h");
                }
                else if (strncmp(arr, "arctanh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "i");
                }
                else if (strncmp(arr, "abs(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "r");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(equation, i, 8);
                    i += 8;
                }
                else if (strncmp(arr, "GCD(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "2");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'S')
            {
                if (strncmp(arr, "SQRT_2", 6) == 0)
                {
                    equation[i] = 'T';
                    removeChar(equation, i, 5);
                    i += 4;
                }
                else if (strncmp(arr, "SQRT_3", 6) == 0)
                {
                    equation[i] = 'R';
                    removeChar(equation, i, 5);
                    i += 4;
                }
                else if (strncmp(arr, "SILVER_RT", 9) == 0)
                {
                    equation[i] = 'Y';
                    removeChar(equation, i, 8);
                    i += 8;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'r')
            {
                if (strncmp(arr, "root(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "0");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 's')
            {
                if (strncmp(arr, "sin(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "4");
                }
                else if (strncmp(arr, "sec(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "8");
                }
                else if (strncmp(arr, "sinh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "a");
                }
                else if (strncmp(arr, "sinc(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "j");
                }
                else if (strncmp(arr, "sqrt(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "k");
                }
                else if (strncmp(arr, "square(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]) && equation[i + 7] != '-' && !validateConstantFirstChar(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "m");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'l')
            {
                if (strncmp(arr, "log(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "1");
                }
                else if (strncmp(arr, "log*(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "A");
                }
                else if (strncmp(arr, "ln(", 3) == 0)
                {
                    if (!isdigit(equation[i + 3]) && equation[i + 3] != '-' && !validateConstantFirstChar(equation[i + 3]))
                        return NAN;
                    removeChar(equation, i - 1, 3);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 2;
                    strcat(functions, "o");
                }
                else if (strncmp(arr, "log10(", 6) == 0)
                {
                    if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6]))
                        return NAN;
                    removeChar(equation, i - 1, 6);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "p");
                }
                else if (strncmp(arr, "log2(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "q");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'L')
            {
                if (strncmp(arr, "LCM(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "3");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'n')
            {
                if (strncmp(arr, "nPr", 3) == 0)
                {
                    equation[i] = 'P';
                    removeChar(equation, i, 2);
                    i += 2;
                }
                else if (strncmp(arr, "nCr", 3) == 0)
                {
                    equation[i] = 'C';
                    removeChar(equation, i, 2);
                    i += 2;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'c')
            {
                if (strncmp(arr, "cos(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "5");
                }
                else if (strncmp(arr, "cosec(", 6) == 0)
                {
                    if (!isdigit(equation[i + 6]) && equation[i + 6] != '-' && !validateConstantFirstChar(equation[i + 6]))
                        return NAN;
                    removeChar(equation, i - 1,  6);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "7");
                }
                else if (strncmp(arr, "cot(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "9");
                }
                else if (strncmp(arr, "cosh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "b");
                }
                else if (strncmp(arr, "cbrt(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "l");
                }
                else if (strncmp(arr, "cube(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "n");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 't')
            {
                if (strncmp(arr, "tan(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]) && equation[i + 4] != '-' && !validateConstantFirstChar(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = 1;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "6");
                }
                else if (strncmp(arr, "tanh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]) && equation[i + 5] != '-' && !validateConstantFirstChar(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "c");
                }
                else if (strncmp(arr, "tetrate(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]) && equation[i + 8] != '-' && !validateConstantFirstChar(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "B");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'E' || equation[i] == 'e' || equation[i] == 'x');
            else
                return NAN;
        }
    }

    setUp(equation);

    if (strcmp(equation, "NAN") == 0)
        return NAN;

    times = numberOfOperations(equation);

    char* operations = (char*) malloc(times);
    int operationPositions[times];
    int numberOfOperationsLeadingUpToFunction[times];
    unsigned short operationPositionIndex = 0, numberOfSeperators = 0;
    int positions[times + 1];

    for (int i = 0; i < times; i++)
        numberOfOperationsLeadingUpToFunction[i] = 0;

    for (int i = 0; i < strlen(equation); i++)
    {
        if (validateOperation(equation[i]) == 0)
        {
            if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1]))
                continue;
            strncat(operations, &equation[i], 1);
            operationPositions[operationPositionIndex] = i;
            operationPositionIndex++;
            if (equation[i] != ',')
                numberOfOperationsLeadingUpToFunction[strlen(functions)]++;
            else
            {
                numberOfSeperators++;
                if (strlen(functions) < numberOfSeperators)
                    return NAN;
            }
        }
    }

    unsigned int seperatorPositions[numberOfSeperators];
    numberOfSeperators = 0;
    for (int i = 0; i < strlen(equation); i++)
    {
        if (isdigit(equation[i]))
        {
            if (i > 0)
            {
                if (!isdigit(equation[i - 1]) && equation[i - 1] != 'm' && equation[i - 1] != '.')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
            else
            {
                if (equation[i + 1] != '!')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
        }
        else
        {
            if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1]))
            {
                equation[i] = 'm';
                positions[posIndex] = i;
                posIndex++;
            }
            else if (validateConstantChar(equation[i]))
            {
                positions[posIndex] = i;
                posIndex++;
            }
        }
    }
    qsort(positions, posIndex, 4, cmpfunc);
    long double nums[times + 1];
    for (int i = 0; i < times + 1; i++)
        nums[i] = 0;

    //Get all the numbers
    for (int i = 0; i < times + 1; i++)
    {
        nums[i] = convertFloat(equation, positions[i], strlen(equation));
        //Check for maximum / minimum / NAN
        if (nums[i] == NAN)
            return NAN;
        else if (nums[i]> UINT_MAX)
            return INFINITY;
        else if (nums[i] < LLONG_MIN)
            return -INFINITY;

        if (operations[i] == ',')
        {
            seperatorPositions[numberOfSeperators] = i;
            numberOfSeperators++;
        }
    }

    unsigned int location = 0;
    for (int i = 0, negative = 1; i < numberOfFunctions; i++)
    {
        for (int j = 0; j < times + 1; j++)
        {
            if (functionPositions[i] < positions[j])
            {
                if (isFunctionWithTwoArgs(functions[j]))
                {
                    if (functionPositions[i] >= operationPositions[j - 1] && numberOfOperationsLeadingUpToFunction[i] >= 0)
                    {
                        if (operationPositionIndex > 1)
                        {
                            if (positions[j] <= operationPositions[j] && operations[j] == ',')
                            {
                                location = j;
                                break;
                            }
                            else
                                return NAN;
                        }
                        else
                        {
                            location = j;
                            break;
                        }
                    }
                    else if (operations[j] == ',')
                        break;
                    else
                        return NAN;
                }
                else
                {
                    if (functionPositions[i] < positions[j])
                    {
                        location = j;
                        break;
                    }
                }
            }
        }
        //nth root
        if (functions[i] == '0')
        {
            if (nums[location] < 0 && fmodl(nums[location + 1], 2) != 0)
            {
                nums[location] *= -1;
                if (nums[location + 1] == (int) nums[location + 1])
                    negative = -1;
            }
            nums[location + 1] = pow(nums[location], 1 / nums[location + 1]);
            nums[location] = setNum(operations, seperatorPositions[i]);
            nums[location + 1] *= negative;
        }
        //log
        else if (functions[i] == '1')
        {
            nums[location + 1] = log_base(nums[location], nums[location + 1]);
            nums[location] = setNum(operations, seperatorPositions[i]);
        }
        //GCD
        else if (functions[i] == '2')
        {
            if (nums[location] != (int) nums[location] || nums[location + 1] != (int) nums[location + 1])
                return NAN;
            nums[location + 1] = calculateGCD(nums[location], nums[location + 1]);
            nums[location] = setNum(operations, seperatorPositions[i]);
        }
        //LCM
        else if (functions[i] == '3')
        {
            if (nums[location] != (int) nums[location] || nums[location + 1] != (int) nums[location + 1])
                return NAN;
            nums[location + 1] = fabsl(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
            nums[location] = setNum(operations, seperatorPositions[i]);
        }
        //sin
        else if (functions[i] == '4')
            nums[location] = sinl(nums[location]);
        //cos
        else if (functions[i] == '5')
            nums[location] = cosl(nums[location]);
        //tan
        else if (functions[i] == '6')
            nums[location] = tanl(nums[location]);
        //cosecant
        else if (functions[i] == '7')
            nums[location] = cosec(nums[location]);
        //secant
        else if (functions[i] == '8')
            nums[location] = sec(nums[location]);
        //cotangent
        else if (functions[i] == '9')
            nums[location] = cot(nums[location]);
        //sinh
        else if (functions[i] == 'a')
            nums[location] = sinhl(nums[location]);
        //cosh
        else if (functions[i] == 'b')
            nums[location] = coshl(nums[location]);
        //tanh
        else if (functions[i] == 'c')
            nums[location] = tanhl(nums[location]);
        //arcsin
        else if (functions[i] == 'd')
            nums[location] = asinl(nums[location]);
        //arccos
        else if (functions[i] == 'e')
            nums[location] = acosl(nums[location]);
        //arctan
        else if (functions[i] == 'f')
            nums[location] = atanl(nums[location]);
        //arcsinh
        else if (functions[i] == 'g')
            nums[location] = asinhl(nums[location]);
        //arccosh
        else if (functions[i] == 'h')
            nums[location] = acoshl(nums[location]);
        //arctanh
        else if (functions[i] == 'i')
            nums[location] = atanhl(nums[location]);
        //sinc
        else if (functions[i] == 'j')
            nums[location] = sinc(nums[location]);
        //sqrt
        else if (functions[i] == 'k')
            nums[location] = sqrtl(nums[location]);
        //cbrt
        else if (functions[i] == 'l')
            nums[location] = cbrtl(nums[location]);
        //square
        else if (functions[i] == 'm')
            nums[location] *= nums[location];
        //cube
        else if (functions[i] == 'n')
            nums[location] *= nums[location] * nums[location];
        //natural log
        else if (functions[i] == 'o')
            nums[location] = logl(nums[location]);
        //log base 10
        else if (functions[i] == 'p')
            nums[location] = log10l(nums[location]);
        //binary log
        else if (functions[i] == 'q')
            nums[location] = log2l(nums[location]);
        else if (functions[i] == 'r')
            nums[location] = fabsl(nums[location]);
        //iterative log
        else if (functions[i] == 'A')
        {
            nums[location + 1] = iterative_log(nums[location], nums[location + 1]);
            nums[location] = setNum(operations, seperatorPositions[i]);
        }
        //tetration
        else if (functions[i] == 'B')
        {
            if ((int) nums[location + 1] != nums[location + 1])
                return NAN;

            long exponent = nums[location];
            for (int j = 0; j < nums[location + 1] - 1; j++)
                exponent = pow(nums[location], exponent);
            nums[location + 1] = exponent;
            nums[location] = setNum(operations, seperatorPositions[i]);
        }
    }
    //E
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == 'e')
        {
            if ((int) nums[i + 1] != nums[i + 1])
                return NAN;

            nums[i + 1] = (int) (nums[i] * pow(10, nums[i + 1]));
            nums[i] = 0 + 1 * (operations[i + 1] == '*' || operations[i + 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Modulo operation
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == '%')
        {
            nums[i + 1] = fmod(nums[i], nums[i + 1]);
            nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == ',')
        {
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Exponents
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == '^')
        {
            nums[i + 1] = pow(nums[i], nums[i + 1]);
            nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //nCr, nPr
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == 'C')
        {
            if ((int) nums[i] != nums[i] || (int) nums[i + 1] != nums[i + 1])
                return NAN;
            nums[i + 1] = tgamma(nums[i] + 1) / (tgamma(nums[i + 1] + 1) * tgamma(nums[i] - nums[i + 1] + 1));
            total += nums[i + 1];
            nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == 'P')
        {
            if ((int) nums[i] != nums[i] || (int) nums[i + 1] != nums[i + 1])
                return NAN;
            nums[i + 1] = tgamma(nums[i] + 1) / tgamma(nums[i] - nums[i + 1] + 1);
            total += nums[i + 1];
            nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Multiplications, Division
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == '*')
        {
            nums[i + 1] *= nums[i];
            nums[i] = 0;
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == '/')
        {
            nums[i] /= nums[i + 1];
            nums[i + 1] = nums[i];
            nums[i] = 0;
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Assign total the first non-zero number
    for (int i = 0; i < times + 1; i++)
    {
        if (nums[i] != 0)
        {
            total = nums[i];
            break;
        }
    }
    //Addition, Subtraction
    for (int i = 0; i < operationPositionIndex + 1; i++)
    {
        if (operations[i] == '+')
            total += nums[i + 1];
        else if (operations[i] == '-')
            total -= nums[i + 1];
    }
    if (times == 0)
        total = nums[0];
    
    free(operations);
    free(functions);
    free(arr);
    free(equation);

    return total;
}
//Get first number of equation
long double convertFloat(char* input, int startIndex, int endIndex)
{
    char lastNum = '0';
    double total = 0.0;
    short multNeg = 1;
    int numNum = 1;
    short divide = 10;

    //Used to covert equation string to a float
    for (int i = startIndex; i < endIndex; i++)
    {
        //This code is in charge of switching from adding integer parts to adding decimals
        if (!isdigit(input[i]))
        {
            //If input[i] is a decimal point, start adding decimals
            if (input[i] == '.')
            {
                if (!isdigit(input[i + 1]))
                {
                    if (input[i + 1] == '.' || isalpha(input[i + 1]) || isspace(input[i + 1]))
                        return NAN;
                    else
                        break;
                }
                else
                    lastNum = '1';
            }
            //If input[i] is a valid operation, this implies that the first number has terminated
            else if (validateOperation(input[i]) == 0)
                    break;
            else if (validateConstantChar(input[i]))
            {
                total = returnValueOfMathConstant(input, i);
                break;
            }
            else if (input[i] == 'm')
                    multNeg = -1;
            else if (input[i] == ' ')
                break;
            else
                return NAN;
        }
        //This part actually converts the number
        else
        {
            if (lastNum == '0')
            {
                total += input[i] - '0';
                if (isdigit(input[i + 1]))
                    total *= 10;
            }
            else
            {
                total += (input[i] - '0') / (float) pow(divide, numNum);
                numNum++;
            }
        }
    }
    total *= multNeg;
    return total;
}
//Get value of math constant multiplied by coefficient
long double getMathConstant(char* input, int index, float mathConstant)
{
    float value = 0.0, coefForConsts;
    int lookback = 1, startIndexCoefficient = 0;
    if (index > 0 && isdigit(input[index - 1]))
    {
        coefForConsts = 0;
        while ((isdigit(input[index - lookback]) || input[index - lookback] == '.') && index - lookback >= 0)
        {
            startIndexCoefficient++;
            lookback++;
        }

        coefForConsts = convertFloat(input, index - startIndexCoefficient, index);

        value = coefForConsts * mathConstant;
    }
    else
       value = mathConstant;

    return value;
}
//Return value of math constant multiplied by coefficient
long double returnValueOfMathConstant(char* input, int i)
{
    //Pi
    if (input[i] == '!')
        return getMathConstant(input, i, M_PI);
    //Golden Ratio
    else if (input[i] == 'G')
        return getMathConstant(input, i, GOLDEN_RT);
    //Square root of 2
    else if (input[i] == 'T')
        return getMathConstant(input, i, M_SQRT2);
    //Square root of 3
    else if (input[i] == 'R')
        return getMathConstant(input, i, M_SQRT_3);
    //Euler's number
    else if (input[i] == 'E')
        return getMathConstant(input, i, M_E);
    //Silver Ratio
    else if (input[i] == 'Y')
        return getMathConstant(input, i, SILVER_RT);
    //Apery's Constant
    else if (input[i] == 'A')
        return getMathConstant(input, i, APERY_CONST);
    return 0.0;
}
//Get number of operations
unsigned int numberOfOperations(char* input)
{
    unsigned int times = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (isdigit(input[i]))
            continue;
        //Check how many operations we have to do
        if (validateOperation(input[i]) == 0)
        {
            if (validNext(input[i + 1]) == 0)
            {
                if (!(input[i] == '-' && isdigit(input[i + 1]) && !isdigit(input[i - 1])))
                    times++;
            }
        }
    }
    return times;
}
long double setNum(char* operations, int index)
{
    if (index == 0)
        return 0;
    else
    {
        if (operations[index - 1] == '*' || operations[index - 1] == '/')
            return 1;
        else
            return 0;
    }
    return 0;
}
//Validate string
int isvalidInput(char* input)
{
    if (strlen(input) == 0)
        return 1;
    while (*input)
    {
        if (!isspace(*input))
            return 1;
        input++;
    }
    return 0;
}
