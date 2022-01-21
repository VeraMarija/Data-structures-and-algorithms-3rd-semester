#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree() {
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree* bst, char* word) {
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokaziva�.
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
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
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
	// Ispisuje rije�i u stablu na ekran po abecednom redu.
	// In-order �etnja po stablu (lijevo dijete, �vor, desno dijete)
	if (bst == NULL)
		return;
	PrintBSTree(bst->left);
	printf("%s\n", bst->word);
	PrintBSTree(bst->right);
	
}

void SaveBSTree(BSTree bst, FILE* fd) {
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (ttenutni �vor pa djeca)
	if (bst == NULL)
		return;
	fprintf(fd, bst->word);
	fprintf(fd, "\n");
	SaveBSTree(bst->left,fd);
	SaveBSTree(bst->right,fd);
}

void DeleteBSTree(BSTree bst) {
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)
	if (bst == NULL)
		return;
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE* fd) {
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().
	BSTree bst;
	bst = NewBSTree();
	char buffer[1024];
	while ( fscanf( fd, "%s", buffer) != EOF) {
		AddNode(&bst, _strdup(buffer));
	}
	return bst;
}
