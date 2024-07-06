#include "allocator.h"

static Header base;             // Empty list to get started.
static Header *freep = NULL;    // Start of the free list.

int main(int argc, char *argv[])
{
    return 0;
}

/* my_malloc: general-purpose storage allocator. */
void *my_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {          // No free list yet.
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {          // Big enough.
            if (p->s.size == nunits)        // Exactly the right size.
                prevp->s.ptr = p->s.ptr;
            else {                          // Allocate tail end.
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep)                             // Wrapped around the free list.
            if ((p = morecore(nunits)) == NULL)
                return NULL;                        // None left.
    }
}

/* morecore: ask system for more memory. */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1)
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;
    my_free((void *)(up + 1));
    return freep;
}

/* my_free: put block ap in free list. */
void my_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;

    freep = p;
}
