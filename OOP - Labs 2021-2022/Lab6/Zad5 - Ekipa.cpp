#include <iostream>
#include <cstring>

using namespace std;

class Ekipa{
protected:
    char name[15];
    int wins;
    int loses;
public:
    Ekipa(char *name="",int wins=0,int loses=0){
        strcpy(this->name,name);
        this->wins=wins;
        this->loses=loses;
    }
    Ekipa(const Ekipa &e){
        strcpy(this->name,e.name);
        this->wins=e.wins;
        this->loses=e.loses;
    }
    void pecati(){
        cout<<"Ime: "<<name<<" Pobedi: "<<wins<<" Porazi: "<<loses;
    }
};
class FudbalskaEkipa:public Ekipa{
private:
    int NoRedcards;
    int NoYellowcards;
    int draws;
public:
    FudbalskaEkipa(char *name="",int wins=0,int loses=0,int NoRedcards=0,int NoYellowcards=0,int draws=0):Ekipa(name,wins,loses){
        this->NoRedcards=NoRedcards;
        this->NoYellowcards=NoYellowcards;
        this->draws=draws;
    }
    FudbalskaEkipa(const Ekipa &e,int NoRedcards=0,int NoYellowcards=0,int draws=0):Ekipa(e){
        this->NoRedcards=NoRedcards;
        this->NoYellowcards=NoYellowcards;
        this->draws=draws;
    }
    FudbalskaEkipa(const FudbalskaEkipa &f):Ekipa(f){
        this->NoRedcards=f.NoRedcards;
        this->NoYellowcards=f.NoYellowcards;
        this->draws=f.draws;
    }
    void pecati(){
        Ekipa::pecati();
        cout<<" Nereseni: "<<draws<<" Poeni: "<<points()<<endl;
    }
    int points(){
        return wins*3+draws;
    }
};


int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
