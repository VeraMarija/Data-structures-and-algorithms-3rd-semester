#include "dictionary.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print(Dictionary dict) {
	Dictionary tmp = dict;
	tmp = tmp->next;
	while (tmp != NULL) {
		printf("%s - %d\n", tmp->word, tmp->count);
		tmp = tmp->next;
	}
}

void destroy(Dictionary dict) {
	free(dict);
}

Dictionary create() {
	Dictionary dict = (Word*)malloc(sizeof(Word));
	if (!dict)
		return NULL;
	dict->word = "";
	dict->count = 1;
	dict->next = NULL;
	return dict;
}

void add(Dictionary dict, char* str) {
	Dictionary novi = (Word*)malloc(sizeof(Word));
	if (!dict)
		return NULL;
	novi->count = 1;
	novi->word = _strdup(str);
	Dictionary tmp = dict;
	if (tmp->next == 0) {
		novi->next = 0;
		tmp->next = novi;
		return;
	}
	else {
		while (tmp->next != NULL) {
			if (strcmp(novi->word, tmp->next->word) == 0) {
				tmp->next->count++;
				return;
			}
			else if (strcmp(tmp->next->word,novi->word) > 0) {
				novi->next = tmp->next;
				tmp->next = novi;
				return;
			}
			tmp = tmp->next;
		}
		novi->next = NULL;
		tmp->next = novi;
	}	
}

int filter(Word* w) {
	if ((strlen(w->word)> 3) && (w->count>=5 && w->count<=10) )
		return 1;
	return 0;
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w) ){
	Dictionary new_dict = create();
	Dictionary tmp = indict;
	while (tmp->next != NULL) {
		if (filter(tmp->next)) {
			Dictionary novi = (Word*)malloc(sizeof(Word));
			novi->word = tmp->next->word;
			novi->count = tmp->next->count;
			novi->next = NULL;
			Dictionary tmp2 = new_dict;
			while (tmp2->next != NULL) {
				tmp2 = tmp2->next;
			}
			tmp2->next = novi;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return new_dict;
}


