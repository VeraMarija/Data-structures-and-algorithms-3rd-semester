#include <stdio.h>
#include <stdlib.h>
#include "stl.h"

Objekt3D* read_and_return(FILE* fp) {
	Objekt3D* objekt= (Objekt3D*)malloc(sizeof(Objekt3D));
	if (!objekt)
		return NULL;
	unsigned int* p = &objekt->broj_trokuta;
	fseek(fp, 80, SEEK_SET);
	fread(p, sizeof(unsigned int), 1, fp);
	objekt->niz_trokuta = (Trokut*)malloc(objekt->broj_trokuta*sizeof(Trokut) );
	if (!objekt->niz_trokuta)
		return NULL;
	for (int i = 0; i < objekt->broj_trokuta ;++i) {
		fread(&objekt->niz_trokuta[i], 50, 1, fp);
	}

	return objekt;
}

void write_object_to_bin(FILE* fp, Objekt3D* objekt) {
	char header[80] = {0};
	fwrite(header, sizeof(char), 80, fp);
	fwrite(&objekt->broj_trokuta, sizeof(unsigned int), 1, fp);
	for (int i = 0; i < objekt->broj_trokuta;++i) {
		fwrite(&objekt->niz_trokuta[i], 50, 1, fp);
	}
}

void write_object_to_text(FILE* fp, Objekt3D* objekt) {
	char s[] = "solid";
	fputs(s, fp);
	char facetnormal[] = "  facet normal ";
	char outerloop[] = "    outer loop";
	char vertex[] = "      vertex ";
	char endloop[] = "    endloop";
	char endfacet[] = "  endfacet";
	for (int i = 0;i < objekt->broj_trokuta ;++i) {
		fprintf(fp, "\n%s %f %f %f", facetnormal,objekt->niz_trokuta[i].normala.x, objekt->niz_trokuta[i].normala.y, objekt->niz_trokuta[i].normala.z);
		fprintf(fp, "\n%s", outerloop);
		for (int j = 0;j < 3;++j) {
			fprintf(fp, "\n%s %f %f %f", vertex, objekt->niz_trokuta[i].vrhovi[j].x, objekt->niz_trokuta[i].vrhovi[j].y, objekt->niz_trokuta[i].vrhovi[j].z);
		}
		fprintf(fp, "\n%s\n%s", endloop, endfacet);
	}
	char s2[] = "endsolid";
	fputs("\n", fp);
	fputs(s2, fp);
}

void delete_object(Objekt3D* objekt) {
	free(objekt->niz_trokuta);
	free(objekt);
}
