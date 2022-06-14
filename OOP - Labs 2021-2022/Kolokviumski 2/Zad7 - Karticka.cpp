#include<iostream>
#include<cstring>

using namespace std;

class OutOfBoundException{
public:
    void message(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class Karticka{
protected:
   char smetka[16];
   int pin;
   bool povekjePin;
   const static int p;
public:
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
    }
    virtual double tezinaProbivanje(){
        int c=0,pom=pin;
        while(pom){
            c++;
            pom/=10;
        }
        return c;
    }
    char *getSmetka(){
        return smetka;
    }
    bool getDopolnitelenPin(){
        return povekjePin;
    }
    friend ostream &operator<<(ostream &out, Karticka &k){
        out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
    }
};
const int Karticka::p=4;

class SpecijalnaKarticka:public Karticka{
private:
    int *pins;
    int NoPins;
public:
    SpecijalnaKarticka(char *smetka,int pin):Karticka(smetka,pin){
        this->NoPins=0;
        this->pins= new int[0];
        povekjePin=true;
    }
    ~SpecijalnaKarticka(){
        delete []pins;
    }
    double tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+NoPins;
    }
    friend ostream &operator<<(ostream &out, SpecijalnaKarticka &sk){
        out<<sk.smetka<<": "<<sk.tezinaProbivanje()<<endl;
    }
    SpecijalnaKarticka &operator+=(int newPin){
        if(NoPins==p)
            throw OutOfBoundException();

        int *tmp = new int[NoPins+1];
        for(int i=0;i<NoPins;i++)
            tmp[i]=pins[i];
        tmp[NoPins++]=newPin;
        delete []pins;
        pins=tmp;
        return *this;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else
                this->karticki[i]=new Karticka(*karticki[i]);
            }
      this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int limit){
        LIMIT=limit;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite: "<<endl;
        for(int i=0;i<broj;i++){
            SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
            if(sk!=nullptr && sk->tezinaProbivanje()<=LIMIT)
                cout<<*sk;
            else if(karticki[i]->tezinaProbivanje()<=LIMIT){
                    cout<<*karticki[i];
            }

        }
    }
    void dodadiDopolnitelenPin(char * smetka, int novPin){
        for(int i=0;i<broj;i++){
            SpecijalnaKarticka *sk=dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
            if(sk!=nullptr && strcmp(smetka,karticki[i]->getSmetka())==0){
                try{
                    *sk+=novPin;
                }
                catch(OutOfBoundException &obe){
                    obe.message();
                }
                break;
            }
        }
    }
};
int Banka::LIMIT=7;

int main(){
    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin){
            niza[i]=new Karticka(smetka,pin);
           // cout<<*niza[i];
       }
        else{
            niza[i]=new SpecijalnaKarticka(smetka,pin);
           /* SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka*>(niza[i]);
            cout<<*sk;*/
        }

    }
    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        komercijalna.dodadiDopolnitelenPin(smetka,pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();
}
