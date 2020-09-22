#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dynamically_sized_list.h"

int main(void)
{
	char** list = NULL;//pointer on array with pointers on char*
	int continueProgram = 1; // if this value = 0, program ends 
	int numOfStrings = 0,
		numOfAllocatedElements = 0;
	printf(COMMANDS);
	do {
		printf("Enter command to choose action\n>>");
		char ch;
		ch = getchar();
		clearSTDIN(""); ////clear stdin after readed character
		switch (ch)
		{
		case 'a': addNewString(&list, &numOfStrings, &numOfAllocatedElements); break;
		case 'd': removeDuplicates(&list, &numOfStrings, &numOfAllocatedElements); break;
		case 'r':
		{
			if (!numOfStrings) //number of strings == 0
			{
				printf("There is no string\n");
				break;
			}
			char* find, * replace;
			int num;
			printf("Enter number of string to operate (from 1 to %d)\n", numOfStrings);
			readInt(&num);
			while (num<1 || num>numOfStrings)
			{
				printf("Wrong number. Try again");
				readInt(&num);
			}
			printf("Enter string to find\n>>");
			readStringFromConsole(&find);
			printf("Enter string to replace\n>>");
			readStringFromConsole(&replace);
			replaceText(&list[num - 1], find, replace);
		} break;
		case 's': sort(&list, numOfStrings); break;
		case 'p': printAllStrings(list, numOfStrings); break;
		case 'D':	
		{
			if (!numOfStrings) //number of strings == 0
			{
				printf("There is no string\n");
				break;
			}
			int num;
			printf("Enter number of string to delete (from 1 to %d)\n", numOfStrings);
			readInt(&num);
			while (num<1 || num>numOfStrings)
			{
				printf("Wrong number. Try again");
				readInt(&num);
			}
			deleteElem(&list, num-1, &numOfStrings, &numOfAllocatedElements);
		} break;
		case 'n': printf("Number of items in the list = %d\n", numOfStrings); break;
		case 'f': 
		{
			char* find;
			printf("Enter string to find\n");
			readStringFromConsole(&find);
			int index = findExactMatch(list, find, numOfStrings);
			if (index<0)
			{
				printf("No match was found\n");
			}
			else
			{
				printf("Your string number is %d\n", index + 1);
			}
		} break;
		case 'c': printf(COMMANDS); break;
		default: continueProgram = 0;
		}
	} while (continueProgram);
	destroy(&list, numOfStrings);
	return 0;
}