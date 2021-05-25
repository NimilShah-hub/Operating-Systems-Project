#include<stdio.h>
int main()
{
    int no1, no2, no3;
    printf("Enter the 1st number : ");
    scanf("%d", &no1);
    printf("Enter the 2nd number : ");
    scanf("%d", &no2);
    __asm__ ( "addl %%edx, %%ecx;" : "=no3" (no3) : "no3" (no1) , "d" (no2) );    // cpomputing in assembly as [ add a,b ] --> no1 = no1+no2 
    printf("Sum is %d\n", no3);
    return 0;
}
