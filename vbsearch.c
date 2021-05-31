/* This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2 of the License

    Author: Andrey Vitsenko: <avits@mail.ru>
*/

#include <stdlib.h>

int comp (const void *, const void *); 
/*  The comp routine is  expected  to have two arguments which point to the key object and to an array member, 
    and should return an integer less than, equal to, or greater than zero if the key object is found, 
    respectively, to be less than, to match, or be greater than the array member.
*/
int comp_eq (const void *, const void *);
/*  The comp_eq function is expected to have two arguments which point to the key object and to an array member, 
    and which returns zero if the key object matches the array member, and nonzero otherwise.
*/

void *vsearch(const void *key, const void *fnd, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *),int (*compar_eq)(const void *, const void *))
{
char *ptr;
ptr=(char *)fnd;    /* starting point as returned by bsearch */
    do{
        if ( compar_eq(key,ptr) == 0 ) return (void *)ptr;  /* do we found the key? If so, return pointer on array element */
        ptr=ptr+size;   /* going up */
        if ( ptr >= (char *)base + nmemb*size )  break;
    } while ( !compar(key,ptr)); /* coninue till scalar function of the array element is equal of the scalar function of the key */
ptr=(char *)fnd-size; /* OK, no success. Going down */
    do{
        if ( compar_eq(key,ptr) == 0 ) return (void *)ptr; /* do we found the key? If so, return pointer on array element */
        ptr=ptr-size;
        if ( ptr < (char *)base )  break; /* coninue till scalar function of the array element is equal of the scalar function of the key */
    } while ( !compar(key,ptr));
return NULL; /* no success. Key no found */
}
