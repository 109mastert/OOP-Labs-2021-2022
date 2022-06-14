#include<iostream>
#include <cstring>
using namespace std;

typedef struct Voz{
    char relacija[51];
    float distance;
    int passangers;
}Train;
typedef struct ZeleznickaStanica{
    char city[21];
    Train trains[30];
    int NoTrains;
}ZeleznickaStanica;
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
   int start;
   for(int i=0;i<n;i++){
        if(strcmp(zs[i].city,grad)==0){
            start=i;
            break;
        }
   }
   int r,minkm;
    if(zs[start].trains[0].distance>zs[start].trains[1].distance)
        minkm=zs[start].trains[0].distance;
    else
        minkm=zs[start].trains[1].distance;
    for(int i=1;i<zs[start].NoTrains;i++){
        if(minkm>=zs[start].trains[i].distance){
            minkm=zs[start].trains[i].distance;
            r=i;
        }
    }
    cout<<"Najkratka relacija: "<<zs[start].trains[r].relacija<<" ("<<zs[start].trains[r].distance<<" km)"<<endl;
}
int main(){

    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici
    ZeleznickaStanica zStanica[n];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>>zStanica[i].city>>zStanica[i].NoTrains;
        for(int j=0;j<zStanica[i].NoTrains;j++){
            cin>>zStanica[i].trains[j].relacija;
            cin>>zStanica[i].trains[j].distance;
            cin>>zStanica[i].trains[j].passangers;
        }
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
