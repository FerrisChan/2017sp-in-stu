#include "prime.h"
#include <math.h>
#include <stdio.h>
int is_prime( int num ) {

    int result = 0;
    /* write your own implementation here */
    int i=0; // the times of recyele
    int k; 
    // k as the sqrt of num
    k = (int) sqrt((double)num);
    for(i=2;i<=k;i++)
    // find a number i can product num, and i <= k 
        if(num%i==0)
            break;

    if(i>k){
        // can not find a number i < k to product num,
        // because i = k+1, after last cycle 
        result = 1;
    }
    else
       result = 0;
    return result;
}
