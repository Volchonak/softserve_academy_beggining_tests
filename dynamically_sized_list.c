#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "dynamically_sized_list.h"

void readStringFromConsole(char** str_)
{
	/*	
		this function allocate dynamic memory for sentence in stdin buffer (until '\n' is reached)
		and assign this string to str_
	*/
	if (!str_) return;
	int reallocSize = REALLOC_SIZE, // value of memory to be added every reallocation
		offset = 0; //current position
	char* str = NULL;
	do {
		str = (char*)malloc(reallocSize * sizeof(char));
	} while (!str);
	str[0] = '\0';
	char* ptr2 = str;
	printf("Enter your string. Press '\\n' to end your string\n");
	char ch;
	while (1)
	{
		if (offset != 0 && (offset % reallocSize) == 0) //check for available allocated memory
		{
			reallocSize += reallocSize;
			do {
				ptr2 = (char*)realloc(ptr2, reallocSize);
			} while (!ptr2);
			str = ptr2;
		}
		ch = getchar(); // getting a character from stdin buffer
		if (ch == '\n')
		{
			*(str + offset) = '\0';
			break;
		}
		*(str + offset) = ch;
		++offset;
	}
	*str_ = str;
}

void addNewString(char*** list, int* numOfStrings, int* numOfAllocatedElements)
{
	if (!list || !numOfStrings || !numOfAllocatedElements) 
		return;
	char** tmp = NULL;
	++(*numOfStrings);
	if (*numOfStrings > * numOfAllocatedElements)
	{
		*numOfAllocatedElements += NUMOFELEMENTSTOADD;
		tmp = (char**)malloc(*numOfAllocatedElements * sizeof(char*));
		if (!tmp)//check for allocated memory
		{
			--(*numOfStrings);
			--(*numOfAllocatedElements);
			printf("\nError. String was not added.\n");
			return;
		}
		if (*numOfStrings > 1)//copy pointers on previous strings on new buffer
		{
			memcpy(tmp, *list, ((*numOfStrings - 1) * sizeof(char*)));
		}
		if (list)//delete previous buffer
		{
			free(*list);
		}
		*list = tmp;
		tmp = NULL;
	}
	readStringFromConsole(*list + *numOfStrings - 1);//read string from stdin
}

void printAllStrings(const char** list,const int numOfStrings)
{
	//prints all strings from list
	if (!list) return;
	for (int i = 0; i < numOfStrings; ++i)
	{
		if (!list[i])
			return;
		printf("%d. %s\n", i+1, *(list+i));
	}
}

void removeDuplicates(char*** list, int* numOfStrings, int* numOfAllocatedElements)
{
	//checks for identical strings and deletes the second
	if (!list||!(*list)||!numOfStrings||!numOfAllocatedElements) 
		return;
	for (int i = 0; i < *numOfStrings; ++i)
	{
		for (int j = i + 1; j < *numOfStrings; ++j)
		{
			if(!strcmp(*(*list+i),*(*list+j)))//check for identical strings
			{
				deleteElem(list, j, numOfStrings, numOfAllocatedElements);
				--j;
			}
		}
	}
}

void deleteElem(char*** list, int numOfElemToDelete, int* numOfElements, int* numOfAllocatedElements)
{
	//deletes element on position 'numOfElemToDelete' from array and free
	if (!list|| !(*list)|| numOfElemToDelete<0) return;
	if (!*(*list + numOfElemToDelete)) return;
	free(*(*list + numOfElemToDelete));
	memmove(*list + numOfElemToDelete, *list + numOfElemToDelete + 1, sizeof(char*) * (*numOfElements - numOfElemToDelete - 1));
	--(*numOfElements);
	if ((*numOfAllocatedElements - *numOfElements) > NUMOFELEMENTSTOADD)//if array with list pointers has more than 'NUMOFELEMENTSTOADD'
	{																	//empty pointers, array will be resized
		*numOfAllocatedElements -= NUMOFELEMENTSTOADD;
		char** tmp = (char**)malloc(*numOfAllocatedElements * sizeof(char*));
		if (!tmp) return;
		memcpy(tmp, *list, *numOfElements * sizeof(char*));
		free(*list);
		*list = tmp;
	}
}

void replaceText(char** str, const char* find, const char* replace)
{
	//looks in 'str' for substring 'find' and replaces 'find' on 'replace'
	if (!str || !(*str)|| !find || !replace) return;
	char* ptr = NULL;
	int strLen = strlen(*str),
		findLen = strlen(find),
		replaceLen = strlen(replace),
		ptrLen = 0;
	
	if (strLen == 0 || findLen == 0 || replaceLen == 0) return;//if length of any arguments < 0 ->
	do														   // there is nothing to replace
	{
		strLen = strlen(*str);
		ptr=strstr(*str, find);
		if (!ptr) break; // if ptr==NULL -> there is nothing left to replace (could replace nothing at all)
		ptrLen = strlen(ptr);
		char* tmp = (char*)malloc(strLen - findLen + replaceLen + 1);//allocate memory fo new length
		if (!tmp) return;
		strncpy(tmp, *str, strLen - ptrLen);//copy str before 'find'
		strncpy(tmp + strLen - ptrLen, replace, replaceLen); //insert 'replace' at new string
		strcpy(tmp + strLen - ptrLen + replaceLen, ptr + findLen);//copy str after 'find'
		free(*str);
		*str = tmp;
	} while (1);
	printf("New string:\t%s\n", *str);
}


void readInt(int* val)
{
	// read MAXCHARACTERS from stdin buffer (deletes everything else) and look for int value
	if (!val) return;
	char* buffer = (char*)malloc(MAXCHARACTERS+1);
	if (!buffer) return;
	fgets(buffer, MAXCHARACTERS, stdin);//read from stdin 
	clearSTDIN(buffer);		//clear stdin after readed characters
	char* end = NULL; 
	*val = 0;
	*val = strtol(buffer, &end, 10);	//converts numbers in buffer from char to int or return 0 if there is no digital number
	while (*val == 0)
	{
		printf("Incorrect input. Try again\n"); // asks for new input if there was no number
		fgets(buffer, MAXCHARACTERS, stdin);
		clearSTDIN(buffer);
		*val = strtol(buffer, &end, 10);
	}
	free(buffer);
}

void clearSTDIN(const char* buffer)
{
	//clear stdin 
	if (!buffer) return;
	int clearBuffer = 1;
	for (int i = 0; i < MAXCHARACTERS; ++i)
	{
		if (buffer[i] == '\n')
		{
			clearBuffer = 0;
			break;
		}
	}
	if (clearBuffer)
	{
		while (getchar() != '\n');
	}
		
}

void sort(char*** list, int numOfStrings)
{
	//sorts array of char* strings in order from a to z
	if (!list||!(*list)) return;
	for (int i = 0; i < numOfStrings; ++i)
	{
		for (int j = i+1; j < numOfStrings; ++j)
		{
			if (strcmp((*list)[i], (*list)[j]) > 0)
			{
				swap(list, i, j);
			}
		}
	}
}

void swap(char*** list, int first, int second)
{
	if (!list||!(*list)) return;
	char** tmp = (*list)[first];
	(*list)[first] = (*list)[second];
	(*list)[second] = tmp;
}

void destroy(char*** array, int numOfObjects)
{
	// deletes 'numOfObjects' elements from array
	if (!array||!(*array)) return;
	for (int i = 0; i < numOfObjects; ++i)
	{
		if (!(*array)[i]) continue;
		free((*array)[i]);
		(*array)[i] = NULL;
	}
	free(*array);
}

int findExactMatch(const char** list, const char* find, int numOfStrings)
{
	if (!list || !find) return -1;
	for (int i = 0; i < numOfStrings; ++i)
	{
		if (!strcmp(list[i], find))
		{
			return i;
		}
	}
	return -1;
}