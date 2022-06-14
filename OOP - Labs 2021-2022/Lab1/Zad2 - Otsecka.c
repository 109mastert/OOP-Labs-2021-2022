#include <stdio.h>
#include <stdlib.h>

typedef struct tocka{
    float x;
    float y;
} tocka;
typedef struct otsecka{
    tocka a;
    tocka b;
} otsecka;
int se_secat(otsecka o1,otsecka o2){
   // printf("Na otseckata2 tocka a ,x e %.2f, na tockata b-x e %.2f",o2.a.x,o2.b.x);
    if(o2.a.x <= o1.a.x && o2.b.x <= o1.b.x){
        return 1;
    }
    else return 0;
}
int main()
{
    double x1, y1, x2, y2;
    scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
   // printf("x1 e %.2lf, y1 e %.2lf, x2 e %.2lf, y2 e %.2lf",x1, y1, x2, y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
    return 0;
}
