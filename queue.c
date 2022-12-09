#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"



char Queue_Pop (Queue *q) {
	for (size_t i = 0; i < q->initialized; i ++) {
		if (q->items [i].i == q->pop) {
			q->items [i].i = 0;
			q->pop ++;
			return q->items [i].c;
		}
	}
	
	return '\0';
}

/*void Queue_Cleanup (Queue *q) {
	Queue new = Queue_New (q->initialized);
	
	for (size_t i = 0; i <= q->initialized; i ++) {
		Queue_Push (&new, Queue_Pop (q));
	}
	
	Queue old = q;
	Queue_Destroy (q);
	*q = new;
}*/


void Queue_Push (Queue *q, const char c) {
	for (size_t i = 0; i < q->initialized; i ++) {
		//putchar (q->items [i].i);
		if (q->items [i].i == 0) {
			q->items [i].i = q->push ++;
			q->items [i].c = c;
			return;
		}
	}
	while (q->initialized >= q->alloc)	// is at end of alloced
		q->items = realloc (q->items, (q->alloc *= 2) * sizeof (Queue_Item));
	
	
	q->items [q->initialized].i = q->push ++;
	q->items [q->initialized].c = c;
	
	q->initialized ++;
}

void Queue_Push_Bulk (Queue *q, const char *str) {
	for (const char *i = str; *i != '\0'; i ++)
		Queue_Push (q, *i);
}

Queue Queue_New (size_t initial_sz) {
	Queue out;
	out.items = malloc (sizeof (Queue_Item) * initial_sz);
	out.pop = out.push = 1;
	out.initialized = 0;
	out.alloc = initial_sz;
	
	return out;
}

void Queue_Destroy (Queue *q) {
	free (q->items);
}
