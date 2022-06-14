#include<iostream>
#include <cstring>

using namespace std;

class Delo{
protected:
    char name[50];
    int year;
    char country[50];
    void copy(const Delo &d){
        strcpy(this->name,d.name);
        this->year=d.year;
        strcpy(this->country,d.country);
    }
public:
    Delo(char *name="",int year=2000,char *country=""){
        strcpy(this->name,name);
        this->year=year;
        strcpy(this->country,country);
    }
    Delo(const Delo &d){
        copy(d);
    }
    Delo &operator=(const Delo &d){
        if(this!=&d){
            copy(d);
        }
        return *this;
    }
    bool operator==(const Delo &d1){
        return (strcmp(this->name,d1.name)==0);
    }
    char *getIme(){
        return name;
    }
    int getYear(){
        return year;
    }
    char *getCountry(){
        return country;
    }
};

class Pretstava{
private:
    Delo delo;
    int NoTickets;
    char data[15];
public:
    Pretstava(Delo delo,int NoTickets,char *data){
        this->delo=delo;
        this->NoTickets=NoTickets;
        strcpy(this->data,data);
    }
    Delo getDelo(){
        return delo;
    }
    int getNoTickets(){
        return NoTickets;
    }
    virtual double cena(){
        /// 20-21 vek 50den, 19vek 75vek, <19vek 100den
        double sum=0.0;
        if(delo.getYear()-1900>0)
            sum+=50;
        else if(delo.getYear()-1800>0)
            sum+=75;
        else
            sum+=100;
        if(strcmp(delo.getCountry(),"Italija")==0)
            sum+=100;
        else if(strcmp(delo.getCountry(),"Rusija")==0)
            sum+=150;
        else
            sum+=80;
        return sum;
    }
};

class Balet:public Pretstava{
private:
    static int ticketPrice;
public:
    Balet(Delo delo,int NoTickets,char *data):Pretstava(delo,NoTickets,data){}
    double cena(){
        return Pretstava::cena()+ticketPrice;
    }
    static void setCenaBalet(int tp){
        ticketPrice=tp;
    }
};
int Balet::ticketPrice = 150;

class Opera:public Pretstava{
public:
    Opera(Delo delo,int NoTickets,char *data):Pretstava(delo,NoTickets,data){}
};

double prihod(Pretstava **pretstavi, int n){
    double sum=0.0;
    for(int i=0;i<n;i++)
        sum+=pretstavi[i]->getNoTickets()*pretstavi[i]->cena();
    return sum;
}
int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo &d1){
    int sum=0;
    for(int i=0;i<n;i++){
        if(strcmp(pretstavi[i]->getDelo().getIme(),d1.getIme())==0)
            sum++;
    }
    return sum;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };
    return 0;
}
