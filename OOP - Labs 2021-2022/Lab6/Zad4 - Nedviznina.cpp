#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina{
protected:
    char *adress;
    int squares;
    int pps; //price per square
public:
    Nedviznina(char *adress="",int squares=0,int pps=0){
        this->adress=new char[strlen(adress)+1];
        strcpy(this->adress,adress);
        this->squares=squares;
        this->pps=pps;
    }
    Nedviznina(const Nedviznina &n){
        this->adress=new char[strlen(n.adress)+1];
        strcpy(this->adress,n.adress);
        this->squares=n.squares;
        this->pps=n.pps;
    }
    ~Nedviznina(){
        delete []adress;
    }
    int cena(){
        return squares*pps;
    }
    void pecati(){
        //Kukja_vo_Centar, Kvadratura: 60, Cena po Kvadrat: 850
        cout<<adress<<", Kvadratura: "<<squares<<", Cena po Kvadrat: "<<pps<<endl;
    }
    double danokNaImot(){
        return 0.05*cena();
    }
    friend istream &operator>>(istream &in, Nedviznina &n){
        in>>n.adress>>n.squares>>n.pps;
        return in;
    }
    char *getAdresa(){
        return adress;
    }
};
class Vila:public Nedviznina{
private:
    int luxTax;
public:
    Vila(char *adress="",int squares=0,int pps=0,int luxTax=0):Nedviznina(adress,squares,pps){
        this->luxTax=luxTax;
    }
    Vila(const Nedviznina &n, int luxTax):Nedviznina(n){
        this->luxTax=luxTax;
    }
    Vila(const Vila &v):Nedviznina(v){
        this->luxTax=v.luxTax;
    }
    void pecati(){
        cout<<adress<<", Kvadratura: "<<squares<<", Cena po Kvadrat: "<<pps<<", Danok na luksuz: "<<luxTax<<endl;
       // cout<<"Danok za: "<<adress<<", e: "<<danokNaImot()<<endl;
    }
    double danokNaImot(){
        return cena()*((float)luxTax/100)+Nedviznina::danokNaImot();
    }
    friend istream &operator>>(istream &in, Vila &v){
        in>>v.adress>>v.squares>>v.pps>>v.luxTax;
        return in;
    }
    char *getAdresa(){
        return adress;
    }
};
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
