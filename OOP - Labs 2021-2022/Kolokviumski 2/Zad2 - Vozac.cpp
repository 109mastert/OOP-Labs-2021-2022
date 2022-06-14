#include <iostream>
#include <cstring>

using namespace std;

///Ne rabote so char *name="" u konstruktorite

class Vozac{
protected:
    char name[101];
    int age;
    int NoRaces;
    bool veteran;
public:
    Vozac(char *name="",int age=0,int NoRaces=0,bool veteran=false){
        strcpy(this->name,name);
        this->age=age;
        this->NoRaces=NoRaces;
        this->veteran=veteran;
    }
    virtual double zarabotuvacka()=0;
    virtual double danok()=0;
    friend ostream &operator<<(ostream &out,const Vozac &v){
        out<<v.name<<endl<<v.age<<endl<<v.NoRaces<<endl;
        if(v.veteran)
            out<<"VETERAN"<<endl;
        return out;
    }
};

bool operator==(Vozac &v1,Vozac &v2){
    return (v1.zarabotuvacka()==v2.zarabotuvacka());
}

class Avtomobilist:public Vozac{
private:
    float CarPrice;
public:
    Avtomobilist(char *name="",int age=0,int NoRaces=0,bool veteran=false,float CarPrice=0.0):Vozac(name,age,NoRaces,veteran){
        this->CarPrice=CarPrice;
    }
    double zarabotuvacka(){
        return CarPrice/5;
    }
    double danok(){
        if(NoRaces>10)
            return zarabotuvacka()*0.15;
        else
            return zarabotuvacka()*0.1;
    }
};

class Motociklist:public Vozac{
private:
    int power;
public:
    Motociklist(char *name="",int age=0,int NoRaces=0,bool veteran=false,int power=0):Vozac(name,age,NoRaces,veteran){
        this->power=power;
    }
    double zarabotuvacka(){
        return power*20;
    }
    double danok(){
        if(veteran)
            return zarabotuvacka()*0.25;
        else
            return zarabotuvacka()*0.2;
    }
};
int soIstaZarabotuvachka(Vozac **v,int n, Vozac *v1){
    int sum=0;
    for(int i=0;i<n;i++){
        if(v[i]->zarabotuvacka()==v1->zarabotuvacka())
            sum++;
    }
    return sum;
}

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
