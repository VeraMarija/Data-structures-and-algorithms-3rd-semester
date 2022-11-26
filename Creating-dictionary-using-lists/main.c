#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "dictionary.h"

int readWord(FILE* fd, char* buffer){
	int c;
	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

void main()
{
	FILE* fd;
	char buffer[1024];
	Dictionary dict;

	fd = fopen("liar.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	
	dict = create();
	while (readWord(fd, buffer)) {		
		add(dict, buffer);
	}
	fclose(fd);

	print(dict);

	int (*fun_ptr)(Word*) = &filter;
	dict = filterDictionary(dict, fun_ptr);

	printf("dict after change:\n\n\n");
	print(dict);

	destroy(dict);

	return 0;
	
}