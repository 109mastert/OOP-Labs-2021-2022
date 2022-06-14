#include<stdio.h>
#include<string.h>

typedef struct SkiLift{
    char name[21];
    int users;
    int state;
}skilift;

typedef struct SkiCenter{
    char name[21];
    char country[21];
    skilift skilifts[20];
    int NoSkilifts;
}skicenter;

void najgolemKapacitet(skicenter *sc, int n){
    int maxusers=0,newmaxusers=0,flag=1,rsc;
    for(int i=0;i<n;i++,newmaxusers=0)
    {
        for(int j=0;j<sc[i].NoSkilifts;j++){
            if(sc[i].skilifts[j].state==1)
                newmaxusers+=sc[i].skilifts[j].users;
        }
        if(flag){
            maxusers=newmaxusers;
            rsc=i;
            flag--;
        }
        else{
            if(newmaxusers>maxusers)
            {
                maxusers=newmaxusers;
                rsc=i;
            }
            else if(newmaxusers==maxusers){
                if(sc[i].NoSkilifts>sc[rsc].NoSkilifts)
                    rsc=i;
            }
        }
    }
    printf("%s\n%s\n%d",sc[rsc].name,sc[rsc].country,maxusers);
}

int main()
{
    int n;
	scanf("%d", &n);
	skicenter sc[n];
	for (int i = 0; i < n; i++){
        scanf("%s%s%d",sc[i].name,sc[i].country,&sc[i].NoSkilifts);
        for(int j=0;j<sc[i].NoSkilifts;j++)
        {
            scanf("%s%d%d",sc[i].skilifts[j].name,&sc[i].skilifts[j].users,&sc[i].skilifts[j].state);
        }
	}
    najgolemKapacitet(sc,n);
	return 0;
}
