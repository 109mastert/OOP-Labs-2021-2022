#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

class Automobile{
private:
    char *brand;
    int *plate;
    int maxSpeed;
    void copy(const Automobile &a){
        this->brand= new char[strlen(a.brand)+1];
        strcpy(this->brand,a.brand);
        this->plate=new int[5];
        for(int i=0;i<5;i++)
            this->plate[i]=a.plate[i];
        this->maxSpeed=a.maxSpeed;
    }

public:
    Automobile(){
        this->brand=new char[1];
        strcpy(this->brand,"");
        this->plate=new int[5];
        for(int i=0;i<5;i++)
            this->plate[i]=0;
        this->maxSpeed=0;
    }
    Automobile(char *brand,int *plate,int maxSpeed){
        this->brand= new char[strlen(brand)+1];
        strcpy(this->brand,brand);
        this->plate=new int[5];
        for(int i=0;i<5;i++)
            this->plate[i]=plate[i];
        this->maxSpeed=maxSpeed;
    }
    Automobile(const Automobile &a){
        copy(a);
    }
    Automobile &operator=(const Automobile &a){
        if(this!=&a){
            delete []brand;
            delete []plate;
            copy(a);
        }
        return *this;
    }
    bool operator==(const Automobile &other){
        if(strcmp(this->brand,other.brand)==0 && (this->maxSpeed==other.maxSpeed)){
            for(int i=0;i<5;i++){
                if(this->plate[i]!=other.plate[i])
                    return false;
            }
            return true;
        }
        return false;
    }
    friend ostream &operator<<(ostream &out,const Automobile &a){
        out<<"Marka\t"<<a.brand<<"\tRegistracija[ ";
        for(int i=0;i<5;i++)
            out<<a.plate[i]<<" ";
        out<<"]"<<endl;
        return out;
    }
    ~Automobile(){
        delete []brand;
        delete []plate;
    }
    int getPlateNo()const{
        int p=0;
        for(int i=0,j=4;i<5;i++,j--){
            p+=plate[j]*pow(10,i);
        }
        return p;
    }
    int getSpeed(){
        return maxSpeed;
    }
};
class RentACar{
private:
    char name[100];
    Automobile *car;
    int NoCars;

    void copy(const RentACar &rac){
        strcpy(this->name,rac.name);
        this->car=new Automobile[rac.NoCars];
        this->NoCars=rac.NoCars;
    }
public:
    RentACar(char *name=""){
        strcpy(this->name,name);
        this->NoCars=0;
        this->car=new Automobile[this->NoCars];
        for(int i=0;i<NoCars;i++)
            this->car[i]=car[i];
    }
    ~RentACar(){
        delete []car;
    }
    RentACar &operator+=(const Automobile &a){
        Automobile *tmp= new Automobile[NoCars+1];
        for(int i=0;i<NoCars;i++)
            tmp[i]=this->car[i];
        tmp[NoCars++]=a;
        delete []car;
        car=tmp;
        return *this;
    }
    RentACar &operator-=(const Automobile &a){
        for(int i=0;i<NoCars;i++){
            if(this->car[i].getPlateNo()==a.getPlateNo()){
                Automobile *tmp= new Automobile[--NoCars];
                for(int i=0,j=0;j<NoCars+1;j++){
                    if(this->car[j].getPlateNo()!=a.getPlateNo())
                        tmp[i++]=this->car[j];
                }
                delete []car;
                car=tmp;
                return *this;
            }
        }
    }

    void pecatiNadBrzina(int max){
        cout<<name<<endl;
        for(int i=0;i<NoCars;i++){
            if(this->car[i].getSpeed()>=max)
                cout<<car[i];
        }
    }

};


int main()
{
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;

       	Automobile nov=Automobile(marka,regisracija,maximumBrzina);

    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}

