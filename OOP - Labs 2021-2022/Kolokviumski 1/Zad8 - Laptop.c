#include <stdio.h>
#include <stdlib.h>

typedef struct laptop{
    char manufacturer[101];
    float display;
    int touch;
    int price;
}laptop;

typedef struct itstore{
    char shop_name[101];
    char location[101];
    laptop laptops[100];
    int n;
}ITStore;

void print(ITStore *store, int n){
    for(int i=0;i<n;i++)
    {
        printf("%s %s\n",store[i].shop_name,store[i].location);
        for(int j=0;j<store[i].n;j++)
        {
            printf("%s %g %d\n",store[i].laptops[j].manufacturer,store[i].laptops[j].display,store[i].laptops[j].price);
        }
    }

}
void najeftina_ponuda(ITStore *s,int n){
    int flag=1,bestprice,r;
    for(int i=0;i<n;i++){
        for(int j=0;j<s[i].n;j++)
        {
            if(s[i].laptops[j].touch==1)
            {
                if(flag){
                    bestprice=s[i].laptops[j].price;
                    r=i;
                    flag--;
                }
                else{
                    if(bestprice>s[i].laptops[j].price){
                        bestprice=s[i].laptops[j].price;
                        r=i;
                    }
                }
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n %s %s\nNajniskata cena iznesuva: %d",s[r].shop_name,s[r].location,bestprice);
}

int main()
{
    ITStore s[100];
    int n;
    scanf("%d",&n); //broj na IT prodavnici
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0;i<n;i++)
    {
        scanf("%s%s%d",s[i].shop_name,s[i].location,&s[i].n);
        for(int j=0;j<s[i].n;j++)
        {
            scanf("%s%f%d%d",s[i].laptops[j].manufacturer,&s[i].laptops[j].display,&s[i].laptops[j].touch,&s[i].laptops[j].price);
        }

    }
    //pecatenje na site prodavnici
     print(s,n);
    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}
