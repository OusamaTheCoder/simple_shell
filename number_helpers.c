#include "shell.h"

/**
 * convertLongToString - Converts a number to a string.
 * @number: Number to be converted to a string.
 * @string: Buffer to save the number as a string.
 * @base: Base to convert the number.
 * Return: Nothing.
 */
void convertLongToString(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long quotient  = number;
	char nameLetters[] = {"0123456789abcdef"};

	if (quotient  == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (quotient )
	{
		if (quotient  < 0)
			string[index++] = nameLetters[-(quotient  % base)];
		else
			string[index++] = nameLetters[quotient  % base];
		quotient  /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	reverseString(string);
}


/**
 * parseInt - Convert a string to an integer.
 * @s: Pointer to the source string.
 * 
 * Return: Integer representation of the string or 0.
 */
int parseInt(char *s)
{
	int valueSign  = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			valueSign  *= -1;
		if (*s == '+')
			valueSign  *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * valueSign );
}

/**
 * countCharacters - Count the coincidences of characters in a string.
 * @string: Pointer to the source string.
 * @character: String with characters to be counted.
 * 
 * Return: Integer count of characters or 0.
 */
int countCharacters(char *string, char *character)
{
	int i = 0, dirCounter  = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			dirCounter ++;
	}
	return (dirCounter );
}

