#include<iostream>
#include <cstring>

using namespace std;

class Vozilo{
protected:
    float weight;
    int height,width;
public:
    Vozilo(float weight=0.0,int width=0,int height=0){
        this->weight=weight;
        this->width=width;
        this->height=height;
    }
    virtual float getWeight()=0;
    int getWidth(){
        return width;
    }
    virtual float getmaxLoad()=0;
    virtual int vratiDnevnaCena()=0;
};

class Avtomobil:public Vozilo{
private:
    int NoDoors;
public:
    Avtomobil(float weight=0.0,int width=0,int height=0,int NoDoors=0):Vozilo(weight,width,height){
        this->NoDoors=NoDoors;
    }
     float getWeight(){
        return weight;
    }
    float getmaxLoad(){
        return 0;
    }
    int vratiDnevnaCena(){
        if(NoDoors<5)
            return 100;
        else
            return 130;
    }
};

class Avtobus:public Vozilo{
private:
    int NoPassangers;
public:
    Avtobus(float weight=0.0,int width=0,int height=0,int NoPassangers=0):Vozilo(weight,width,height){
        this->NoPassangers=NoPassangers;
    }
     float getWeight(){
        return weight;
    }
    float getmaxLoad(){
        return 0;
    }
    int vratiDnevnaCena(){
        return NoPassangers*5;
    }
};

class Kamion:public Vozilo{
private:
    float maxLoad;
public:
    Kamion(float weight=0.0,int width=0,int height=0,float maxLoad=0.0):Vozilo(weight,width,height){
        this->maxLoad=maxLoad;
    }
    float getWeight(){
        return weight;
    }
    float getmaxLoad(){
        return maxLoad;
    }
    int vratiDnevnaCena(){
        return (weight+maxLoad)*0.02;
    }
};

class ParkingPlac{
private:
    int NoVehicles;
    Vozilo **vehicle;
public:
    ParkingPlac(){
        this->NoVehicles=0;
        vehicle=new Vozilo *[0];
    }
    ~ParkingPlac(){
        for(int i=0;i<NoVehicles;i++)
            delete []vehicle[i];
        delete []vehicle;
    }
    ParkingPlac &operator+=(Vozilo *v){
        Vozilo **tmp =new Vozilo *[NoVehicles+1];
        for(int i=0;i<NoVehicles;i++)
            tmp[i]=vehicle[i];
        tmp[NoVehicles++]=v;
        delete []vehicle;
        vehicle=tmp;
        return *this;
    }
    float presmetajVkupnaMasa(){
        float total=0.0;
        for(int i=0;i<NoVehicles;i++)
            total+=vehicle[i]->getWeight();
        return total;
    }
    int brojVozilaPoshirokiOd(int l){
        int count=0;
        for(int i=0;i<NoVehicles;i++){
            if(vehicle[i]->getWidth()>l)
                count++;
        }
        return count;
    }
    void pecati(){
        int a=0,b=0,t=0;
        for(int i=0;i<NoVehicles;i++){
            if(dynamic_cast<Avtomobil*>(vehicle[i]))
                a++;
            else if(dynamic_cast<Avtobus*>(vehicle[i]))
                b++;
            else if(dynamic_cast<Kamion*>(vehicle[i]))
                t++;
        }
        cout<<"Brojot na avtomobili e "<<a<<", brojot na avtobusi e "<<b<<" i brojot na kamioni e "<<t<<"."<<endl;
    }
    int pogolemaNosivostOd(Vozilo& v){
        int c=0;
        for(int i=0;i<NoVehicles;i++){
            if(dynamic_cast<Kamion *>(vehicle[i])){
                if(vehicle[i]->getmaxLoad()>v.getWeight())
                    c++;
            }
        }
        return c;
    }
    int vratiDnevnaZarabotka(){
        int sum=0;
        for(int i=0;i<NoVehicles;i++)
            sum+=vehicle[i]->vratiDnevnaCena();
        return sum;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;

    return 0;
}
