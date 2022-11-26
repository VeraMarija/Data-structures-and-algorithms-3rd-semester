#ifndef HEADER_FILE
#define HEADER_FILE

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	float x, y, z;
}Vrh;

typedef struct {
	Vrh normala;
	Vrh vrhovi[3];
	unsigned short boja;
}Trokut;

typedef struct {
	Trokut* niz_trokuta;
	unsigned int broj_trokuta;
}Objekt3D;

Objekt3D* read_and_return(FILE* fp);

void write_object_to_bin(FILE* fp, Objekt3D* objekt);

void write_object_to_text(FILE* fp, Objekt3D* objekt);

void delete_object(Objekt3D* objekt);

#endif
