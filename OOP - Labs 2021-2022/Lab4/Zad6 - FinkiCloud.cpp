#include <iostream>
#include <cstring>

using namespace std;
enum Tip{LINUX=0,UNIX,WINDOWS};
class OperativenSistem {
private:
    char *name;
    float version;
    Tip type;
    float size;

    void copy(const OperativenSistem &os){
        this->name=new char[strlen(os.name)+1];
        strcpy(this->name,os.name);
        this->version=os.version;
        this->type=os.type;
        this->size=os.size;
    }
public:
    OperativenSistem(char *name="",float version=0.0,Tip type=LINUX,float size=0.0){
    this->name=new char[strlen(name)+1];
    strcpy(this->name,name);
    this->version=version;
    this->type=type;
    this->size=size;

    }
    OperativenSistem(const OperativenSistem &os){
        copy(os);
    }
    OperativenSistem &operator=(const OperativenSistem &os){
        if(this!=&os){
            delete []name;
            copy(os);
        }
        return *this;
    }
    ~OperativenSistem(){
        delete []name;
    }
    float getVersion()const{
        return version;
    }
    void pecati(){
        //Ime: Ubuntu Verzija: 17.04 Tip: 1 Golemina:2.25GB
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<type<<" Golemina:"<<size<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os){
        if(strcmp(this->name,os.name)==0){
            if(this->type==os.type){
                if(this->version==os.version){
                    if(this->size==os.size)
                        return true;
                }
            }
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(this->version==os.version)
            return 0;
        else if(this->version>os.version)
            return 1;
        else
            return -1;
    }
    bool istaFamilija(const OperativenSistem &sporedba){
    //isto ime i tip
        if(strcmp(this->name,sporedba.name)==0){
            if(this->type==sporedba.type)
                return true;
        }
        return false;
    }
};
class Repozitorium{
private:
    char name[21];
    OperativenSistem *os;
    int NoOS;

    void copy(const Repozitorium &r){
        strcpy(this->name,r.name);
        this->NoOS=NoOS;
        this->os=new OperativenSistem[NoOS];
        for(int i=0;i<NoOS;i++){
            this->os[i]=r.os[i];
        }
    }
public:
    Repozitorium(const char *name=""){
        strcpy(this->name,name);
        NoOS=0;
    }
    Repozitorium(const Repozitorium & r){
        copy(r);
    }
    ~Repozitorium(){
        delete []os;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<name<<endl;
        for(int i=0;i<NoOS;i++){
            os[i].pecati();
        }
    }
    void dodadi(const OperativenSistem &nov){
        if(NoOS!=0){
            for(int i=0;i<NoOS;i++){
                if(os[i].istaFamilija(nov)){
                    nov.getVersion();
                    if(os[i].getVersion()<nov.getVersion()){
                        os[i]=nov;
                        return;
                    }
                }
            }
            OperativenSistem *tmp = new OperativenSistem[++NoOS];
            for(int i=0;i<NoOS-1;i++)
                tmp[i]=os[i];
            tmp[NoOS-1]=nov;
            delete [] os;
            os=tmp;
        }
        else{
            os = new OperativenSistem[++NoOS];
            os[0]=nov;
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        for(int i=0;i<NoOS;i++){
            if(os[i].ednakviSe(operativenSistem)){
                OperativenSistem *tmp = new OperativenSistem[--NoOS];
                for(int j=0;j<NoOS;j++){
                    tmp[j]=os[j];
                }
                delete [] os;
                os = tmp;
                return;
            }
        }
    }
};


int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
