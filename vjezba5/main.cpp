#include<stdio.h>
#include<stdlib.h>

#define N 10000

typedef struct _Element {
	void* d;  //data
	int p=0;    //priority
}Element;


typedef struct _PriorityQueue{
	Element* array;
	int i;
}PriorityQueue;

PriorityQueue* create(PriorityQueue *pq) {
	pq->array = (Element*)malloc(N*sizeof(Element));
	pq->i = 0;
	return pq;
}

void fix_from_bottom_to_top(PriorityQueue* pq, int child, int c) {
	int r = (c - 1) / 2;
	if (child >= pq->array[r].p) {
		int temp = pq->array[r].p;
		pq->array[r].p = child;
		pq->array[c].p = temp;
		
		if (r) {
			fix_from_bottom_to_top(pq, pq->array[r].p, r);
		}
	}
	else 
		pq->array[c].p = child;
}

PriorityQueue* add_element(PriorityQueue* pq, Element *el) {
	if (pq->i == 0) {
		pq->array[0].p = el->p;
		pq->i = 1;
		return pq;
	}
	fix_from_bottom_to_top(pq, el->p, pq->i);
	pq->i++;
	return pq;
}


void fix_from_top_to_bottom(PriorityQueue* pq, int parent, int r) {
	int l = 2 * r + 1;
	int d = 2 * r + 2;
	int c;   // higher priority child indeks
	pq->array[l].p >= pq->array[d].p ? c = l : c = d;
	if (parent < pq->array[c].p) {
		int temp = pq->array[r].p;
		pq->array[r].p = pq->array[c].p;
		pq->array[c].p = temp;
		if ( (2*c+1) < pq->i)
			fix_from_top_to_bottom(pq, pq->array[c].p, c);
	}
}

int extract_parent_from_top(PriorityQueue* pq ) {
	int extracted;
	if (pq->i == 1) {
		extracted = pq->array[0].p;
		pq->i = 0;
		pq->array[0].p = 0;
		return extracted;
	}
	if (pq->i == 2) {
		extracted = pq->array[0].p;
		pq->i = 1;
		pq->array[0].p = pq->array[1].p;
		pq->array[1].p = 0;
		return extracted;
	}
	extracted = pq->array[0].p;
	pq->array[0].p = pq->array[pq->i-1].p;
	pq->array[pq->i-1].p = 0;
	fix_from_top_to_bottom(pq, pq->array[0].p, 0);
	pq->i--;
	return extracted;
}

int main() {
	PriorityQueue p;
	PriorityQueue* pq =&p;
	pq = create(pq);
	//pq->array = (Element*)malloc(N * sizeof(Element));
	//pq->i = 0;
	Element e;
	Element* el = &e;
	el->p = 85;
	pq = add_element(pq, el);
	el->p = 60;
	pq = add_element(pq, el);
	el->p = 80;
	pq = add_element(pq, el);
	el->p = 25;
	pq = add_element(pq, el);
	el->p = 30;
	pq = add_element(pq, el);
	el->p = 70;
	pq = add_element(pq, el);
	el->p = 50;
	pq = add_element(pq, el);
	el->p = 23;
	pq = add_element(pq, el);
	el->p = 10;
	pq = add_element(pq, el);
	el->p = 20;
	pq = add_element(pq, el);
	el->p = 70;
	pq = add_element(pq, el);

	for (int j = 0;j < pq->i;++j) {
		printf("%d ", pq->array[j].p);
	}

	int extracted = extract_parent_from_top(pq);
	printf("\n\nizvadeni roditelj s vrha:  %d\n\n", extracted);

	for (int j = 0;j < pq->i;++j) {
		printf("%d ", pq->array[j].p);
	}
	return 0;
}