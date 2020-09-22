#ifndef DYNAMICALLY_SIZED_LIST
#define DYNAMICALLY_SIZED_LIST


#define REALLOC_SIZE 10
#define COMMANDS "Commands: \n'c'-commands\n'a'-add new string,\n"\
			"'d'-delete(remove) diplicates,\n'r'-replace text,\n"\
			"'s'-sort list,\n'p'-print all strings,\n'D'-delete string,\n"\
			"'n' -number of items in the list,\n'f' -find exect match'\neverything else-exit program\n"
#define MAXCHARACTERS 4
#define NUMOFELEMENTSTOADD 10

void readStringFromConsole(char** _str);
void addNewString(char*** list, int* numOfStrings, int* numOfAllocatedElements);
void printAllStrings(const char** list, const int numOfStrings);
void removeDuplicates(char*** list, int* numOfStrings, int* numOfAllocatedElements);
void deleteElem(char*** list, int numOfElemToDelete, int* numOfElements, int* numOfAllocatedElements);
void replaceText(char** str, const char* find, const char* replace);
void readInt(int* val);
void swap(char*** list, int first, int second);
void sort(char*** list, int numOfStrings);
void destroy(char*** array, int numOfObjects);
void clearSTDIN(const char* buffer);
int findExactMatch(const char** list, const char* find, int numOfStrings);


#endif