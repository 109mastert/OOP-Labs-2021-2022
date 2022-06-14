#include <stdio.h>
#include <stdlib.h>

struct product{
    char name[50];
    float price;
    float qnty;
};

int main()
{
    int i,n;
    float total=0.0;
    scanf("%d",&n);
    struct product products[n];
    for(i=0;i<n;i++)
    {
        scanf("%s%f%f",products[i].name,&products[i].price,&products[i].qnty);
        total+=(products[i].price*products[i].qnty);
    }
    for(i=0;i<n;i++)
        printf("%d. %s %.2f x %.1f = %.2f\n",i+1,products[i].name,products[i].price,products[i].qnty,products[i].price*products[i].qnty);
    printf("Total : %.2f",total);
    return 0;
}
