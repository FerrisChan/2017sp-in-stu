#include <stdio.h>
#include "prime.h"

int main( int argc, char** argv ) {

    int n=0;
    int i =0;
    // You may want to check the validity of "n" as well
    printf("Enter the number of n: ");
    scanf("%d", &n);
    // perro and exit if input is not an intergate 
    if (argc <2 ||argc >2 ||  n<=1 || (int)n != n ){
        printf("please input an intergate. \n");
        return -1 ;
    }
    printf("Printing primes less than or equal to %d \n",n);
    // Test function is_prime(); Replace it with your own code
    for (i=2;i<=n;i++){
    if( is_prime(i) ) {
        // printf the primes
        printf("%d  ", i);
    }
    }
    return 0;
}
