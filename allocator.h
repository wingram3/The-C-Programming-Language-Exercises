#include <stdio.h>

#define NALLOC 1024

typedef long Align;           // For alignment to long boundary.

union header {
    struct {
        union header *ptr;    // Next block if on free list.
        unsigned size;        // Size of this block.
    } s;
    Align x;                  // Never used, just forces alignment of blocks.
};

typedef union header Header;

void my_free(void *ap);
static Header *morecore(unsigned nu);
void *my_malloc(unsigned nbytes);
