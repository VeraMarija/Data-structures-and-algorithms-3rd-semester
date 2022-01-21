#include<stdio.h>
#include<stdlib.h>

#define N 10000

typedef struct _Element {
	void* d;  //data
	int p;   //priority
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

void fix_from_bottom_to_top(PriorityQueue* pq,int child ) {
	if (child == 0)
		return;
	int parent = (child - 1) / 2;
	if (pq->array[parent].p < pq->array[child].p ) {
		Element temp = pq->array[parent];
		pq->array[parent] = pq->array[child];
		pq->array[child] = temp;
		fix_from_bottom_to_top(pq, parent);
	}
	
}

PriorityQueue* add_element(PriorityQueue* pq, Element el) {
	pq->array[pq->i] = el;
	fix_from_bottom_to_top(pq, pq->i);
	pq->i++;
	return pq;
}


void fix_from_top_to_bottom(PriorityQueue* pq, int parent) {
	int higher;
	int left = 2 * parent + 1;
	int right = 2 * parent + 2;
	if (pq->i - 1 < left  &&  pq->i - 1 < right)
		return;
	if (pq->i - 1 < right)
		higher = left;
	higher = (pq->array[left].p > pq->array[right].p) ? left : right;
	if (pq->array[parent].p < pq->array[higher].p) {
		Element temp = pq->array[parent];
		pq->array[parent] = pq->array[higher];
		pq->array[higher] = temp;
		fix_from_top_to_bottom(pq, higher);
	}
}

Element extract_parent_from_top(PriorityQueue* pq ) {
	Element temp = pq->array[0];
	pq->array[0] = pq->array[pq->i - 1];
	pq->array[pq->i - 1].d = 0;
	pq->array[pq->i - 1].p = 0;
	pq->i--;
	fix_from_top_to_bottom(pq, 0);
	return temp;
}

void print_pq(PriorityQueue* pq) {
	for (int i = 0;i < pq->i;++i) {
		printf("%d ", pq->array[i].p);
	}

}

int main() {
	PriorityQueue p;
	PriorityQueue* pq =&p;
	pq = create(pq);
	Element el;
	
	el.p = 2;
	pq = add_element(pq, el);
	el.p = 6;
	pq = add_element(pq, el);
	el.p = 2;
	pq = add_element(pq, el);
	el.p = 1;
	pq = add_element(pq, el);
	el.p = 8;
	pq = add_element(pq, el);
	el.p = 5;
	pq = add_element(pq, el);
	el.p = 4;
	pq = add_element(pq, el);
	el.p = 6;
	pq = add_element(pq, el);
	el.p = 7;
	pq = add_element(pq, el);
	el.p = 3;
	pq = add_element(pq, el);
	
	print_pq(pq);
	Element extracted = extract_parent_from_top(pq);
	printf("\n\nizvadeni roditelj s vrha:  %d\n\n", extracted.p);
	print_pq(pq);

	extracted = extract_parent_from_top(pq);
	printf("\n\nizvadeni roditelj s vrha:  %d\n\n", extracted.p);
	print_pq(pq);

	free(pq->array);
	return 0;
}