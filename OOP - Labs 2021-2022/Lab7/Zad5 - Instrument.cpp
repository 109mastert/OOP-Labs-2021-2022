#include <iostream>
#include <cstring>

using namespace std;

class ZicanInstrument{
protected:
    char name[20];
    int NoStrings;
    float price;
public:
    ZicanInstrument(char *name="",int NoStrings=0,float price=0.0){
        strcpy(this->name,name);
        this->NoStrings=NoStrings;
        this->price=price;
    }
    virtual float cena()=0;
    int getNoStrings(){
        return NoStrings;
    }
    friend ostream &operator<<(ostream &out,ZicanInstrument &i){
        out<<i.name<<" "<<i.NoStrings<<" "<<i.cena()<<endl;
    }
  /*  bool operator==(ZicanInstrument &i){
        return (this->NoStrings==i.getNoStrings());
    }*/
};

bool operator==(ZicanInstrument &i1,ZicanInstrument &i2){
    return (i1.getNoStrings()==i2.getNoStrings());
}

class Mandolina:public ZicanInstrument{
private:
    char form[20];
public:
    Mandolina(char *name="",int NoStrings=0,float price=0.0,char *form=""):ZicanInstrument(name,NoStrings,price){
        strcpy(this->form,form);
    }
    float cena(){
        if(strcmp(form,"Neapolitan")==0)
            price*=1.15;
        return price;
    }
};

class Violina:public ZicanInstrument{
private:
    float size;
public:
    Violina(char *name="",int NoStrings=0,float price=0.0,float size=0.0):ZicanInstrument(name,NoStrings,price){
        this->size=size;
    }
    float cena(){
        if(size==0.25)
            price*=1.10;
        else if(size==1.0)
            price*=1.2;
        return price;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n){
    for(int j=0;j<n;j++){
        if(*i[j]==zi)
            cout<<i[j]->cena()<<endl;
    }
    cout<<zi.cena()<<endl;
}

int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}
