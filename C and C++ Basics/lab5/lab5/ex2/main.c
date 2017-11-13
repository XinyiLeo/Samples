#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean(int x[]){
    double sum = 0;
    int i;

    for ( i = 0; i < 10; i++ )
        sum += x[i];
    return sum/10;
}

double median(int x[]){
    int i,j,k,tmp;

    for ( i = 0 ; i < 10 ; i++ )
    {
        k = i;
        for ( j = i+1 ; j < 10 ; j++ )
            if ( x[j] < x[k] )
                k = j;
        if ( k == i )   continue;
        tmp = x[i];
        x[i] = x[k];
        x[k] = tmp;
    }
    return ((double)(x[10>>1]+x[(10>>1)-1]))/2;;
    }


double variance(int x[]){

    double k = mean(x),var = 0;
    int i = 0;

    for ( i = 0 ; i < 10 ; i++ )
        var += (x[i]-k)*(x[i]-k);
    return var/10;

}

double stdd(int x[]){
    return sqrt(variance(x));
}

int main()
{
    int x[10],i;

    for ( i = 0 ; i < 10 ; i++ )
        scanf("%d",&x[i]);

    printf("MEAN              : %.2f\n",mean(x));
    printf("MEDIAN            : %.2f\n",median(x));
    printf("VARIANCE          : %.2f\n",variance(x));
    printf("STANDARD DEVIATION: %.2f\n",stdd(x));

    return 0;
}
