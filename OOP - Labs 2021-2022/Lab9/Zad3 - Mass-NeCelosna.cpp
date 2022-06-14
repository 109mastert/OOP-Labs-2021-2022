#include<iostream>
#include<cstring>
#include <ctype.h>

using namespace std;

class WrongRegistration{
public:
    void message(){
        cout<<"Pogresno vnesena registracija"<<endl;
    }
};

class ImaMasa{
public:
    virtual double vratiMasa()=0;
    virtual void pecati()=0;
};
class PaketPijalok{
protected:
    double volume;
    int qnty;
    static double DRINK_DENSITY;
    static double AMBALAZA_WEIGHT;
public:
    PaketPijalok(double volume=0.0,int qnty=0){
        this->volume=volume;
        this->qnty=qnty;
    }
    double vratiMasa(){}
    void pecati(){}
    int getKolicina(){}
};
double PaketPijalok::AMBALAZA_WEIGHT=0.2;
double PaketPijalok::DRINK_DENSITY=0.8;
class PaketSok:public PaketPijalok,public ImaMasa{
private:
    bool daliGaziran;
public:
    PaketSok(double volume=0.0,int qnty=0,bool daliGaziran=false):PaketPijalok(volume,qnty){
        this->daliGaziran=daliGaziran;
    }
    double vratiMasa(){
        if(!daliGaziran)
            return ((volume*DRINK_DENSITY+AMBALAZA_WEIGHT)+0.1)*qnty;
        else
            return (volume*DRINK_DENSITY+AMBALAZA_WEIGHT)*qnty;
    }
    void pecati(){
        cout<<"Paket sok"<<endl;
        cout<<"kolicina "<<qnty<<", so po "<<DRINK_DENSITY*volume<<" l(dm3)"<<endl;
    }
};
class PaketVino:public PaketPijalok,public ImaMasa{
private:
    double procentAlkohol ;
public:
    PaketVino(double volume=0.0,int qnty=0,double procentAlkohol =0.0):PaketPijalok(volume,qnty){
        this->procentAlkohol=procentAlkohol;
    }
    double vratiMasa(){ //voa e sus
        return (volume*DRINK_DENSITY+AMBALAZA_WEIGHT)*(0.9*procentAlkohol)*qnty;
    }
    void pecati(){
        cout<<"Paket vino"<<endl;
        cout<<"kolicina "<<qnty<<", "<<procentAlkohol*100<<"% alkohol od po "<<volume*DRINK_DENSITY<<" l(dm3)"<<endl;
    }
};
class Kamion{
private:
    char reg[50];
    char driver[50];
    ImaMasa **im;
    int NoStuff;
public:
    Kamion(char *driver){
        strcpy(this->driver,driver);
        strcpy(this->reg,"");
        im = new ImaMasa *[0];
        NoStuff=0;
    }
    Kamion(char *reg,char *driver){
        strcpy(this->reg,reg);
        strcpy(this->driver,driver);
        im = new ImaMasa *[0];
        NoStuff=0;
    }
    void registriraj(char *reg){
        strcpy(this->reg,reg);
    }
    void dodadiElement(ImaMasa *ima){
        ImaMasa **tmp = new ImaMasa *[NoStuff+1];
        for(int i=0;i<NoStuff;i++)
            tmp[i]=im[i];
        tmp[NoStuff++]=ima;
        delete []im;
        im=tmp;
    }
    double vratiVkupnaMasa(){
        double sum=0.0;
        for(int i=0;i<NoStuff;i++)
            sum+=im[i]->vratiMasa();
        return sum;
    }
    void pecati(){
        if(strlen(reg)!=8 || !isalpha(reg[0]) || !isalpha(reg[1]) || !isalpha(reg[6]) || !isalpha(reg[7]))
            throw WrongRegistration();
        cout<<"Kamion so registracija "<<reg<<" i vozac "<<driver<<" prenesuva:"<<endl;
        for(int i=0;i<NoStuff;i++){
            im[i]->pecati();
        }
    }
    Kamion pretovar(char *registration,char *name){
        int max=im[0]->vratiMasa(),r=0;
        Kamion k(name);
        k.registriraj(registration);
        for(int i=0;i<NoStuff;i++){
            if(max<im[i]->vratiMasa()){
                max=im[i]->vratiMasa();
                r=i;
            }
        }
        for(int i=0;i<NoStuff;i++){
            if(i!=r){
                k.dodadiElement(im[i]);
            }
        }
        return k;
    }
};
int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g,valid=false;
    double proc;

    cin>>reg;
    cin>>ime;

    Kamion  A(reg, ime);
    ImaMasa **d = new ImaMasa*[5];
    cin>>vol>>kol;
    cin>>g;
    d[0] = new PaketSok(vol, kol, g);
    cin>>vol>>kol;
    cin>>proc;
    d[1] = new PaketVino(vol, kol, proc);
    cin>>vol>>kol;
    cin>>proc;
    d[2] = new PaketVino(vol, kol, proc);
    cin>>vol>>kol;
    cin>>g;
    d[3] = new PaketSok(vol, kol, g);
    cin>>vol>>kol;
    cin>>proc;
    d[4] = new PaketVino(vol, kol, proc);

    A.dodadiElement(d[0]);
    A.dodadiElement(d[1]);
    A.dodadiElement(d[2]);
    A.dodadiElement(d[3]);
    A.dodadiElement(d[4]);
    try{
        A.pecati();
        cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
        valid=true;
    }
    catch(WrongRegistration &wr){
        wr.message();
    }
    cin>>reg;
    cin>>ime;
    if(valid){
        try{
            Kamion B = A.pretovar(reg, ime);
            B.pecati();
            cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
        }
        catch (WrongRegistration &wr){
            wr.message();
        }
    }
}
