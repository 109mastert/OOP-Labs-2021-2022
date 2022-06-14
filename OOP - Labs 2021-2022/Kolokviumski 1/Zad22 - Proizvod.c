#include <stdio.h>
#include <string.h>

typedef struct Proizvod{
    char code[21];
    int price;
    int qnty;
}product;
typedef struct Narachka{
    char name[16];
    product products[10];
    int NoAvaliableOrders[10];
    int NoProducts;
}order;

void pecatiFaktura(order n){
    int total=0;
    printf("Faktura za %s\n",n.name);
    for(int i=0;i<n.NoProducts;i++){
        if(n.products[i].qnty<=n.NoAvaliableOrders[i]);
        else
        {
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
    }
    for(int i=0;i<n.NoProducts;i++)
    {
        printf("%s %d %d %d\n",n.products[i].code,n.products[i].price,n.products[i].qnty,n.products[i].price*n.products[i].qnty);
        total+=n.products[i].price*n.products[i].qnty;
        n.NoAvaliableOrders[i]-=n.products[i].qnty;
    }
    printf("Vkupnata suma na fakturata e %d",total);
    //da se pecatat treba sga
}

int main() {

    order narachka;
    int i;
    scanf("%s%d",narachka.name,&narachka.NoProducts);
    for (i = 0; i < narachka.NoProducts; ++i) {
        scanf("%s%d%d",narachka.products[i].code,&narachka.products[i].price,&narachka.NoAvaliableOrders[i]);
    }

    int j;
    for (j = 0; j < narachka.NoProducts; ++j) {
        scanf("%d",&narachka.products[j].qnty);
    }
    pecatiFaktura(narachka);
    return 0;
}
