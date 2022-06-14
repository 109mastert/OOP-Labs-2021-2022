#include <iostream>
#include <cstring>

using namespace std;
enum Tip{LINUX=1,UNIX,WINDOWS };
class OS{
private:
    char *name;
    float version;
    Tip type;
    float size;
    void copy(const OS &os){
        this->name=new char[strlen(os.name)+1];
        strcpy(this->name,os.name);
        this->version=os.version;
        this->type=os.type;
        this->size=os.size;
    }
public:
    OS(char *name="",float version=0.0,Tip type=LINUX,float size=0.0){
       this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->version=version;
        this->type=type;
        this->size=size;
    }
    OS(const OS &os){
        copy(os);
    }
    OS &operator=(const OS &os){
        if(this!=&os){
            delete []name;
            copy(os);
        }
        return *this;
    }
    ~OS(){
        delete []name;
    }
    float getVersion()const{
        return version;
    }
    void pecati(){
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<type<<" Golemina:"<<size<<"GB"<<endl;
    }
    bool ednakviSe(const OS &os){
        if(strcmp(this->name,os.name)==0){
            if(this->version==os.version){
                if(this->type==os.type){
                    if(this->size==os.size)
                        return true;
                }
            }
        }
        return false;
    }
    int sporediVerzija(const OS &os){
        if(this->version==os.version)
            return 0;
        else if(this->version>os.version)
            return 1;
        else
            return -1;
    }
    bool istaFamilija(const OS &sporedba){
        if(strcmp(this->name,sporedba.name)==0 && this->type==sporedba.type)
            return true;
        return false;
    }
};
class Repozitorium{
private:
    char name[21];
    OS *osystem;
    int NoOS;

    void copy(const Repozitorium &r){
        strcpy(this->name,r.name);
        this->NoOS=r.NoOS;
        this->osystem=new OS[NoOS];
        for(int i=0;i<NoOS;i++){
            this->osystem[i]=r.osystem[i];
        }
    }
public:
    Repozitorium(char *name="",int NoOS=0){
        strcpy(this->name,name);
        this->NoOS=NoOS;
    }
    Repozitorium(char *name,OS *osystem,int NoOS){
        strcpy(this->name,name);
        this->NoOS=NoOS;
        this->osystem=new OS[NoOS];
        for(int i=0;i<NoOS;i++){
            this->osystem[i]=osystem[i];
        }
    }
    Repozitorium(const Repozitorium &r){
        copy(r);
    }
    Repozitorium &operator=(const Repozitorium &r){
        if(this!=&r){
            delete []osystem;
            copy(r);
        }
        return *this;
    }
    ~Repozitorium(){
        delete []osystem;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<name<<endl;
        for(int i=0;i<NoOS;i++)
            osystem[i].pecati();
    }
    void dodadi(const OS &nov){
        for(int i=0;i<NoOS;i++){
            if(this->osystem[i].istaFamilija(nov)){
                if(this->osystem[i].getVersion()<nov.getVersion()){
                    osystem[i]=nov;
                    return;
                }
            }
        }
        OS *tmp = new OS[NoOS+1];
        for(int i=0;i<NoOS;i++)
            tmp[i]=osystem[i];
        tmp[NoOS]=nov;
        if(NoOS++!=0)
            delete []osystem;
        osystem=tmp;
    }
    void izbrishi(const OS &operativenSistem){

        for(int i=0;i<NoOS;i++){
            if(this->osystem[i].ednakviSe(operativenSistem)){
                    OS *tmp = new OS[--NoOS];
                    for(int j=0;j<NoOS;j++){
                        tmp[j]=osystem[j];
                    delete []osystem;
                    osystem=tmp;
                    return;
                }
            }
        }
    }
};

//13 35 -14 19
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
        OS os = OS(ime, verzija, (Tip)tip, golemina);
      //  os.pecati();
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OS os = OS(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
