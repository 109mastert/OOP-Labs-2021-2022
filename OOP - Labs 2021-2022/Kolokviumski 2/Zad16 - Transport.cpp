#include <iostream>
#include <cstring>

using namespace std;

class Transport{
protected:
    char destination[50];
    int price;
    int distance;
public:
    Transport(char *destination="",int price=0,int distance=0){
        strcpy(this->destination,destination);
        this->price=price;
        this->distance=distance;
    }
    virtual int cenaTransport()=0;
    int getDistance(){
        return distance;
    }
    bool operator<(Transport *t){
        return (this->cenaTransport()<t->cenaTransport());
    }
    friend ostream &operator<<(ostream &out,Transport &t){
        return out<<t.destination<<" "<<t.distance<<" "<<t.cenaTransport()<<endl;
    }
};
class AvtomobilTransport:public Transport{
private:
    bool driver;
public:
    AvtomobilTransport(char *destination="",int price=0,int distance=0,bool driver=false):Transport(destination,price,distance){
        this->driver=driver;
    }
    int cenaTransport(){
        if(driver)
            return price*1.2;
        else
            return price;
    }
};
class KombeTransport:public Transport{
private:
    int NoPassangers;
public:
    KombeTransport(char *destination="",int price=0,int distance=0,int NoPassangers=0):Transport(destination,price,distance){
        this->NoPassangers=NoPassangers;
    }
    int cenaTransport(){
        return price-(200*NoPassangers);
    }
};

void pecatiPoloshiPonudi(Transport **t, int n, Transport &newT){
    Transport *tmp = nullptr;
    for(int i=0;i<n-1;i++){
        if(t[i]->getDistance()>t[i+1]->getDistance()){
            tmp=t[i];
            t[i]=t[i+1];
            t[i+1]=tmp;
            i=-1;
        }
    }
    for(int i=0;i<n;i++){
        if(newT<t[i])
            cout<<*t[i];
    }
}

int main(){
    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }

    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
        delete [] ponudi;
    return 0;
    }

