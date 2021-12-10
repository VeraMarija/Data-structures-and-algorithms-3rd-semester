#include<stdio.h>
#include<stdlib.h>
#include "longnum.h"


// cita broj iz tekstualne datoteke znamenku po znamenku i gradi listu (dugi broj)
LongNumber read_longnum(char* fname) {
	FILE* fp = fopen(fname, "r");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}
	LongNumber num = (LongNumber)malloc(sizeof(Digit));
	num = NULL;
	char n;
	do {
		n = fgetc(fp);
		if (feof(fp))
			break;
		else {
			LongNumber new_long = (LongNumber)malloc(sizeof(Digit));
			new_long->z = (n % 10 + 2) % 10;
			new_long->next = num;
			num = new_long;			
		}
	} while (1);
	fclose(fp);
	return num; 
}

// pomocna funkcija koja okrece listu znamenaka, trebati ce na vise mjesta
// jer ce se operacije uglavnom oslanjati na dodavanje u glavu liste
// ne gradi novu listu nego preuredjuje dobivenu listu
LongNumber reverse(LongNumber num) {
	LongNumber tmp = num;
	LongNumber prethodni = NULL;
	LongNumber sljedeci = NULL;
	while (tmp!=NULL){
		sljedeci = tmp->next;
		tmp->next = prethodni;
		prethodni = tmp;
		tmp = sljedeci;
	}
	num = prethodni;
	return num;
}

// zapisuje broj u tekstualnu datoteku znamenku po znamenku
void write_longnum(LongNumber num, char* fname) {
	FILE* fp = fopen(fname, "w");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}
	LongNumber tmp = num;
	while (tmp!= NULL) {
		fprintf(fp,"%d", tmp->z);
		tmp = tmp->next;
	}
	fclose(fp);

}

// ispisuje broj na ekran 
void print_longnum(LongNumber num){
	LongNumber tmp = num;
	while (tmp != NULL) {
		printf("%d ", tmp->z);
		tmp = tmp->next;
	}
	putchar('\n');
}

// oslobadja listu znamenaka
void delete_longnum(LongNumber num) {
	while (num != NULL) {
		LongNumber obrisani = num;
		num = num->next;
		free(obrisani);
	}
}

int lenght(LongNumber num) {
	int cnt = 0;
	LongNumber tmp = num;
	while (tmp != NULL) {
		cnt++;
		tmp = tmp->next;
	}
	return cnt;
}

LongNumber add_longnum(LongNumber a, LongNumber b) {
	int len_a = lenght(a);
	int len_b = lenght(b);
	LongNumber tmp;
	tmp = NULL;
	if (len_a > len_b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	//else;
	LongNumber tmp_a = a;
	LongNumber tmp_b = b;
	int zbroj, ostatak = 0;
	LongNumber novi = (LongNumber)malloc(sizeof(Digit));
	novi = NULL;
	while (tmp_a != NULL) {
		LongNumber temporary = (LongNumber)malloc(sizeof(Digit));
		zbroj = tmp_a->z + tmp_b->z +ostatak;
		temporary->z = zbroj % 10;
		temporary->next = novi;
		novi = temporary;
		ostatak = zbroj / 10;
		zbroj = 0;
		tmp_a = tmp_a->next;
		tmp_b = tmp_b->next;
	}
	while (tmp_b != NULL) {
		LongNumber temporary = (LongNumber)malloc(sizeof(Digit));
		zbroj = tmp_b->z + ostatak;
		temporary->z = zbroj % 10;
		temporary->next = novi;
		novi = temporary;
		ostatak = zbroj / 10;
		tmp_b = tmp_b->next;
	}
	if (ostatak) {
		LongNumber temporary = (LongNumber)malloc(sizeof(Digit));
		temporary->z = 1;
		temporary->next = novi;
		novi = temporary;
	}
	novi = reverse(novi);
	return novi;
}

LongNumber mul_by_digit(LongNumber num, int z) {
	LongNumber novi = (LongNumber)malloc(sizeof(Digit));
	novi = NULL;
	LongNumber tmp = num; //pazi stavila si reverse
	int umnozak, ostatak = 0;
	while (tmp != NULL) {
		LongNumber temporary = (LongNumber)malloc(sizeof(Digit));
		umnozak = (tmp->z)*z + ostatak;
		temporary->z = umnozak % 10;
		temporary->next = novi;
		novi=temporary;
		ostatak = umnozak / 10;
		umnozak = 0;
		tmp = tmp->next;
	}
	if (ostatak) {
		LongNumber temporary = (LongNumber)malloc(sizeof(Digit));
		temporary->z = ostatak;
		temporary->next = novi;
		novi = temporary;
	}
	novi = reverse(novi);
	return novi;
}

LongNumber mul_by_pow10(LongNumber num, int pow) {
	LongNumber novi = (LongNumber)malloc(sizeof(Digit));
	novi = NULL;
	while (pow > 0) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		tmp->z = 0;
		tmp->next = novi;
		novi = tmp;
		pow--;
	}
		while (num!= NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		tmp->z = num->z;
		tmp->next = novi;
		novi = tmp;
		num = num->next;
	}
	novi = reverse(novi);
	return novi;
}
// 123 x 235
// ---------
//   123 * 10^0 * 5
//   123 * 10^1 * 3
// + 123 * 10^2 * 2
// --------
//  28905 
LongNumber mul_longnum(LongNumber a, LongNumber b) {
	LongNumber novi= (LongNumber)malloc(sizeof(Digit));
	int potencija = lenght(b)-1;
	novi->z = 0;
	novi->next = NULL;
	b = reverse(b);
	while (b != NULL) {
		LongNumber tmp = mul_by_pow10( a, potencija);
		LongNumber tmp2 = mul_by_digit(tmp, b->z); //pazi
		novi = add_longnum(novi,tmp2);
		b = b->next;
		potencija--;	
	}
	return novi;
}