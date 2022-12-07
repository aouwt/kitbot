struct _Queue_Item {
	size_t i;
	void *v;
};

struct _Queue {
	size_t alloc;	// size of allocated buffer
	size_t initialized;	// what has already been allocated
	size_t pop;
	size_t push;
	struct _Queue_Item *items;
};


void *Queue_Pop (Queue *q) {
	for (size_t i = 0; i <= q->initialized; i ++) {
		if (q->items [i].i == q->pop) {
			q->pop ++;
			return q->items [i].v;
		}
	}
	
	return NULL;
}

void Queue_Cleanup (Queue *q) {
	Queue new = Queue_New (q->initialized);
	
	for (size_t i = 0; i <= q->initialized; i ++) {
		
	}
	
}
void Queue_Push (Queue *q, void *val) {
	for (size_t i = 0; i <= q->initialized; i ++) {
		if (q->items [i].i == 0) {
			q->items [i].i = q->push ++;
			q->items [i].v = val;
			return;
		}
	}
	if (q->initialized == q->alloc)	// is at end of alloced
		q->items = realloc (q->items, (q->alloc *= 2));
	
	q->items [q->initialized ++] = q->push ++;
}

Queue Queue_New (size_t initial_sz) {
	malloc
}
