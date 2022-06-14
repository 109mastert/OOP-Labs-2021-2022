#include <stdio.h>
#include <string.h>

typedef struct Vozenje{
    char name[101];
    int time;
    float price;
    int SD; //student discount
}ride;
typedef struct ZabavenPark{
    char name[101];
    char location[101];
    ride rides[100];
    int n;
}amusmentpark;
void print(amusmentpark *a,int n){
    for(int j=0;j<n;j++)
    {
        printf("%s %s\n",a[j].name,a[j].location);
        for(int i=0;i<a[j].n;i++){
            printf("%s %d %.2f\n",a[j].rides[i].name,a[j].rides[i].time,a[j].rides[i].price);
        }
    }

}
void najdobar_park(amusmentpark *a,int n){
    int oldmaxSD=0,newmaxSD=0,r=0,oldtime=0,newtime=0;
    for(int i=0;i<a[0].n;i++){
        if(a[0].rides[i].SD==1)
            oldmaxSD++;
        oldtime+=a[0].rides[i].time;

    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<a[i].n;j++)
        {
            if(a[i].rides[j].SD==1)
                newmaxSD++;
            newtime+=a[i].rides[j].time;

        }
        if(newmaxSD>oldmaxSD)
        {
            oldmaxSD=newmaxSD;
            r=i;
        }
        else if(newmaxSD==oldmaxSD)
        {
            if(newtime>oldtime)
            {
                oldmaxSD=newmaxSD;
                r=i;
            }
        }
        newmaxSD=0;
    } // do tuka rabote
    printf("Najdobar park: %s %s\n",a[r].name,a[r].location);
}
//if sd==1
  //  maxSD+=n;

int main()
{
	int i, j, n, broj;
	//kreiraj niza od maksimum 100 zabavni parkovi
	amusmentpark ff[100];
	scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
		//ime na festivalot
		scanf("%s", ff[i].name);
        //mesto
		scanf("%s", ff[i].location);
		//broj na filmovi, dobro
		scanf("%d", &ff[i].n);

		for (j = 0; j < ff[i].n; j++){
			scanf("%s", ff[i].rides[j].name);  			/* Ime na filmot */
			scanf("%d", &ff[i].rides[j].time); 		/* Vremetraenje   */
			scanf("%f", &ff[i].rides[j].price); 	/* Cena */
            scanf("%d", &ff[i].rides[j].SD);	/* Popust */

		}


			}
    print(ff,n);
    najdobar_park(ff,n);

	return 0;
}
