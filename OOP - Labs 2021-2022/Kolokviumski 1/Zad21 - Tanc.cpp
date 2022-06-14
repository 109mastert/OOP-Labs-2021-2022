#include<iostream>
#include <cstring>
using namespace std;

typedef struct Tanc{
    char ime[16];
    char zemja[16];
}Tanc;
typedef struct Tancer{
    char ime[21];
    char prezime[21];
    Tanc niza[5];
}Tancer;
void tancuvanje(Tancer *t, int n, char *zemja){
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            if(strcmp(t[i].niza[j].zemja,zemja)==0){
                cout<<t[i].ime<<" "<<t[i].prezime<<", "<<t[i].niza[j].ime<<endl;
                break;
            }
        }

    }
}
int main()
{
    int i, j, n;
    char zemja[15];
	Tancer tanceri[5];
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tanceri[i].ime;
        cin >> tanceri[i].prezime;
        for(j = 0; j < 3; j++){
        	cin >> tanceri[i].niza[j].ime;
            cin >> tanceri[i].niza[j].zemja;
        }
    }
    cin >> zemja;
    tancuvanje(tanceri, n, zemja);
	return 0;
}
