#include <iostream>
#include <cstring>

using namespace std;

typedef struct Player{
    char username[16];
    int level;
    int points;
}Igrac;

typedef struct Game{
    char name[21];
    Igrac player[30];
    int NoPlayers;
}KompjuterskaIgra;

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int max=lista[0].NoPlayers,r=0,rp;
    for(int i=1;i<n;i++){
        if(max<lista[i].NoPlayers){
            max=lista[i].NoPlayers;
            r=i;
        }
    }
    int maxp=lista[r].player[0].points;
    rp=0;
    for(int i=1;i<lista[r].NoPlayers;i++){
        if(maxp<lista[r].player[i].points){
            maxp=lista[r].player[i].points;
            rp=i;
        }
        else if(maxp==lista[r].player[i].points){
            if(lista[r].player[rp].level<lista[r].player[i].level){
                maxp=lista[r].player[i].points;
                rp=i;
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<lista[r].player[rp].username<<" koj ja igra igrata "<<lista[r].name<<endl;
}
int main()
{
    int n,m;
    char name[20];
    cin>>n;
    KompjuterskaIgra games[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.name>>nova.NoPlayers;
        Igrac player[30];
        for (int j=0; j<nova.NoPlayers; j++) {
            Igrac newp;
            cin>>newp.username>>newp.level>>newp.points;
            nova.player[j]=newp;
        }
        games[i]=nova;
    }

    najdobarIgrac(games,n);
    return 0;
}
