#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOU 10
int val;
int main()
{
    srand(time(NULL));
    int c = rand()%BOU+1;
    printf("GUESS!\n");
    scanf("%d",&val);
    while (val != c){
        if (val < c)  printf("smaller\n");
        else          printf("larger\n");
        scanf("%d",&val);
    }
    printf("win\n");
    return 0;
}
