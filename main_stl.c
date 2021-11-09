#include<stdio.h>
#include<stdlib.h>
#include "stl.h"

int main() {
	FILE* fp = fopen("primjerbin.stl", "rb");
	if (!fp) {
		perror("error: ");
		return 1;
	}
	Objekt3D* objekt = read_and_return(fp);
	fclose(fp);
	FILE* fp_bin = fopen("my_bin_stl.stl", "wb");
	if (!fp_bin) {
		perror("error: ");
		return 1;
	}
	write_object_to_bin(fp_bin, objekt);
	fclose(fp_bin);
	FILE* fp_txt = fopen("my_txt_stl.stl", "wt");
	if (!fp_txt) {
		perror("error: ");
		return 1;
	}
	write_object_to_text(fp_txt, objekt);
	fclose(fp_txt);
	delete_object(objekt);
	return 0;
}