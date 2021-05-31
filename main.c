/* This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2 of the License

    Author: Andrey Vitsenko: <avits@mail.ru>
*/
/*  This is an example that read randomly generated complex array, sort it and 
    search data using binary and lineer searches. All array members must be found 
    because the same array used 
    Usage: vsearch < IN
*/

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <search.h> /* for lfind */
#include <time.h>

unsigned long gettime_n( void){ /* Time in Nano Seconds*/
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);    
    return((long)t.tv_sec * 1000000000 + t.tv_nsec) ;
}

complex *arr;

void *vsearch(const void *key, const void *start, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *), int (*compar_eq)(const void *, const void *));

int comp (const complex *, const complex *);
int comp_eq (const complex *i, const complex *j);

int main( void )
{
long int i=0,N;
double r_num, a_num;
complex cnum;
complex *found,*cfound;
unsigned long ts, te; /* time start, time stop */
complex *s_in; /* array that contain usorted data to search */

 ts=gettime_n();
 if ( scanf("%ld",&N) == EOF ) { fprintf(stderr,"Unexpected EoF\n"); exit (-1) ;}
 arr=malloc(N*sizeof(complex));  if ( arr == NULL ) { fprintf(stderr,"Cannot allocate memory\n"); exit (-1); }
 s_in=malloc(N*sizeof(complex));  if ( s_in == NULL ) { fprintf(stderr,"Cannot allocate memory\n"); exit (-1); }

 do {
    if ( scanf("%lf %lf",&r_num,&a_num) == EOF ) { fprintf(stderr,"Unexpected EoF\n"); exit (-1) ;}
    arr[i]=r_num*cexp(I*a_num);
    i++;
    } while ( i < N ) ; 
  memcpy(s_in,arr,N*sizeof(complex));

  te=gettime_n();
  fprintf(stderr,"Read data: %f\n",(te-ts)/1000000000.);
  ts=gettime_n();
     qsort(arr, N, sizeof (complex), (int(*) (const void *, const void *)) comp); /* sorting array */
  te=gettime_n();
  fprintf(stderr,"Sort: %f\n",(te-ts)/1000000000.);

  ts=gettime_n();
  for(i = 0; i < N; i++ ) {
     found=bsearch(&s_in[i],arr, N, sizeof (complex), (int(*) (const void *, const void *)) comp);
     if (found != NULL) {
         cfound=vsearch(&s_in[i],found, arr, N, sizeof (complex), (int(*) (const void *, const void *)) comp, (int(*) (const void *, const void *)) comp_eq);
     }
  }
  te=gettime_n();
  fprintf(stderr,"B Search: %f\n",(te-ts)/1000000000.);

/* linear search */
  ts=gettime_n();
  for(i = 0; i < N; i++ ) {
     found=lfind(&s_in[i],arr, &N, sizeof (complex), (int(*) (const void *, const void *)) comp_eq);
     if (found != NULL) {
     }
  }
  te=gettime_n();
  fprintf(stderr,"L Search: %f\n",(te-ts)/1000000000.);
 
 free(arr);
 free(s_in);
return 0;
}

/*  The comp routine is  expected  to have two arguments which point to the key object and to an array member, 
    and should return an integer less than, equal to, or greater than zero if the key object is found, 
    respectively, to be less than, to match, or be greater than the array member.
*/
int comp (const complex *i, const complex *j)
{
if ( cabs(*i) > cabs(*j) ) return 1;
if ( cabs(*i) < cabs(*j) ) return -1;
return 0; 
}      

/*  The comp_eq function is expected to have two arguments which point to the key object and to an array member, 
    and which returns zero if the key object matches the array member, and nonzero otherwise.
*/
int comp_eq (const complex *i, const complex *j)
{
if ( *i != *j ) return 1 ;
return 0; 
}      
