#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Word {
	char* word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word* next;
} Word;

typedef Word* Dictionary;

Dictionary create();

void add(Dictionary dict,char* str);

void print(Dictionary dict);

void destroy(Dictionary dict);

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w));

int filter(Word* w);

void print(Dictionary dict);

void destroy(Dictionary dict);

#endif