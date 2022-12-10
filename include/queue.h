#ifndef QUEUE_H
	#define QUEUE_H
	
	#include <stddef.h>
	
	typedef struct _Queue_Item {
		size_t i;
		char c;
	} Queue_Item;

	typedef struct _Queue {
		size_t alloc;	// size of allocated buffer
		size_t initialized;	// what has already been allocated
		size_t pop;
		size_t push;
		struct _Queue_Item *items;
	} Queue;
	
	extern char Queue_Pop (Queue *q);
	extern void Queue_Push (Queue *q, const char c);
	extern void Queue_Push_Bulk (Queue *q, const char *str);
	
	extern Queue Queue_New (size_t initial_sz);
	extern void Queue_Destroy (Queue *q);
#endif
