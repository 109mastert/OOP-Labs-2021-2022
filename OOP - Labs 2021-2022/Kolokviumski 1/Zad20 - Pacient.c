#include<stdio.h>

typedef struct Pacient{
    char name[101];
    int insurance;
    int NoPregledi;
}patient;

typedef struct MaticenDoktor{
    char name[101];
    int NoPatients;
    patient patients[200];
    float price;
}dr;

void najuspesen_doktor(dr *md,int n){
    int maxp=0,flag=1,newmaxp=0,rdr;
    for(int i=0;i<n;i++){
        for(int j=0;j<md[i].NoPatients;j++)
        {
            if(md[i].patients[j].insurance==0)
                newmaxp++;
        }
        // printf("%d Doktor ima %d pacienti bez insurance\n",i+1,newmaxp);
        if(flag){
            maxp=newmaxp;
            rdr=i;
            flag--;
        }
        else{
            if(newmaxp>maxp)
            {
                maxp=newmaxp;
                rdr=i;
            }
            else if(newmaxp==maxp){
                if(exams(md[i])>exams(md[rdr]))
                {
                    maxp=newmaxp;
                    rdr=i;
                }
            }
        }
        newmaxp=0;
    }
    printf("%s %.2f %d",md[rdr].name,WIexams(md[rdr])*md[rdr].price,exams(md[rdr]));
}
int exams(dr md){
    int noexams=0;
    for(int i=0;i<md.NoPatients;i++){
        noexams+=md.patients[i].NoPregledi;
    }
    return noexams;
}
int WIexams(dr md){
    int noexams=0;
    for(int i=0;i<md.NoPatients;i++){
        if(md.patients[i].insurance==0)
            noexams+=md.patients[i].NoPregledi;
    }
    return noexams;
}

int main()
{
	int i, j, n, broj;
	scanf("%d",&n);
	dr md[n];
	for (i = 0; i < n; i++){
		//ime na doktor
		scanf("%s",md[i].name);
		//broj na pacienti
		scanf("%d",&md[i].NoPatients);
		//cena na pregled
		scanf("%f",&md[i].price);

		for (j = 0; j < md[i].NoPatients; j++){
			scanf("%s",&md[i].patients[j].name);
			scanf("%d",&md[i].patients[j].insurance);
			scanf("%d",&md[i].patients[j].NoPregledi);
		}
	}
	najuspesen_doktor(md, n);

	return 0;
}
