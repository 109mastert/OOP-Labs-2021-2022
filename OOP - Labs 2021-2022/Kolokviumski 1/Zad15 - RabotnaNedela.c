#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela
struct RabotnaNedela{
    int hours[5];
    int weeknum;
};
typedef struct RabotnaNedela RN;

struct Rabotnik{
    char name[51];
    RN week[4];
};
// ovde strukturata Rabotnik

typedef struct Rabotnik R;

int maxNedela(R *r){
    int weekly=0,oldweekly,flag=1,rweek;
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            weekly+=r[0].week[i].hours[j];
        }
      //  printf("The hours for week %d are %d\n",i,weekly);
        if(flag){
            oldweekly=weekly;
            rweek=i;
            flag--;
        }
        else{
            if(weekly>oldweekly)
            {
                oldweekly=weekly;
                rweek=i;
            }

        }
        weekly=0;
    }
    return rweek+1;
}

int weeklyhours(R r,int week){
    int weekly=0;
    for(int i=0;i<5;i++)
        weekly+=r.week[week].hours[i];
    return weekly;
}

void table(R *r, int n){
    int total=0;
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0;i<n;i++){
        printf("%s\t",r[i].name);
        for(int j=0;j<NEDELI+1;j++)
        {
            if(j<NEDELI)
            {
                printf("%d\t",weeklyhours(r[i],j));
                total+=weeklyhours(r[i],j);
            }
        }
        printf("%d\n",total);
        total=0;
    }
}

// ovde funkciite


int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].name);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].week[j].hours[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].name);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
