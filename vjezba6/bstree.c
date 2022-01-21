#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree() {
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree* bst, char* word) {
	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè.
	if (*bst == NULL) {
		*bst = (Node*)malloc(sizeof(Node));
		(*bst)->word = word;
		(*bst)->left = NULL;
		(*bst)->right = NULL;
	}
	else if (strcmp((*bst)->word, word) < 0) {
		AddNode(&(*bst)->right, word);
	}
	else if (strcmp((*bst)->word, word) > 0) {
		AddNode(&(*bst)->left, word);
	}

}

int BSTHeight(BSTree bst) {
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).
	if (bst == NULL)
		return 0;
	else {
		int L;
		int R;
		L = BSTHeight(bst->left);
		R = BSTHeight(bst->right);
		if (L > R)
			return L + 1;
		return R + 1;
	}
}

void PrintBSTree(BSTree bst) {
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)
	if (bst == NULL)
		return;
	PrintBSTree(bst->left);
	printf("%s\n", bst->word);
	PrintBSTree(bst->right);
	
}

void SaveBSTree(BSTree bst, FILE* fd) {
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu (ttenutni èvor pa djeca)
	if (bst == NULL)
		return;
	fprintf(fd, bst->word);
	fprintf(fd, "\n");
	SaveBSTree(bst->left,fd);
	SaveBSTree(bst->right,fd);
}

void DeleteBSTree(BSTree bst) {
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu (prvo djeca pa trenutni èvor)
	if (bst == NULL)
		return;
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE* fd) {
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().
	BSTree bst;
	bst = NewBSTree();
	char buffer[1024];
	while ( fscanf( fd, "%s", buffer) != EOF) {
		AddNode(&bst, _strdup(buffer));
	}
	return bst;
}
