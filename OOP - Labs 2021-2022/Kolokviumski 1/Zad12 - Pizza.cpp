#include <iostream>
#include <cstring>

using namespace std;

class Pica{
    char name[16];
    int price;
    char *ingredients;
    int discount;

    void copy(const Pica &p){
        strcpy(this->name,p.name);
        this->price=p.price;
        this->discount=p.discount;
        this->ingredients=new char[strlen(p.ingredients)+1];
        strcpy(this->ingredients,p.ingredients);
    }
public:
    Pica(char *name="",int price=0,char *ingredients="",int discount=0){
        strcpy(this->name,name);
        this->price=price;
        this->discount=discount;
        this->ingredients=new char[strlen(ingredients)+1];
        strcpy(this->ingredients,ingredients);
    }
    Pica(const Pica &p){
        copy(p);
    }
    Pica &operator=(const Pica &p){
        if(this!=&p)
        {
            delete []ingredients;
            copy(p);
        }
        return *this;
    }
    ~Pica(){
        delete []ingredients;
    }
    int getDiscount(){
        return discount;
    }
    void pecati(){
        cout<<name<<" - "<<ingredients<<", "<<price<<" "<<price-((float)price/100*discount)<<endl;
    }
    bool istiSe(Pica p){
        if(strcmp(this->ingredients,p.ingredients)==0)
            return true;
        return false;
    }
};
class Picerija{
private:
    char name[16];
    Pica *pizza;
    int NoPizzas;

    void copy(const Picerija &p){
        strcpy(this->name,p.name);
        this->pizza=new Pica[p.NoPizzas];
        for(int i=0;i<p.NoPizzas;i++){
            this->pizza[i]=p.pizza[i];
        }
        this->NoPizzas=p.NoPizzas;
    }
public:
    Picerija(char *name=""){
        strcpy(this->name,name);
        NoPizzas=0;
    }
    Picerija(char *name, Pica *pizza,int NoPizzas){
        strcpy(this->name,name);
        this->pizza=new Pica[NoPizzas];
        for(int i=0;i<NoPizzas;i++){
            this->pizza[i]=pizza[i];
        }
        this->NoPizzas=NoPizzas;
    }
    Picerija (const Picerija &p){
        copy(p);
    }
    Picerija &operator=(const Picerija &p){
        if(this!=&p){
            delete []pizza;
            copy(p);
        }
        return *this;
    }
    ~Picerija(){
        delete []pizza;
    }
    Picerija& operator+=(Pica &p){
        bool go=true;
		for(int i=0;i<NoPizzas;i++){
            if(pizza[i].istiSe(p)){
                go=false;
                break;
            }
		}
		if(go){
            Pica *tmp = new Pica[NoPizzas+1];
            for(int i=0;i<NoPizzas;i++)
                tmp[i]=pizza[i];
            tmp[NoPizzas++]=p;
            delete []pizza;
            pizza=tmp;
		}
		return *this;
	}
	void setIme(char *name){
        strcpy(this->name,name);
	}
	char *getIme(){
        return name;
	}
    void dodadi(Pica p){
        for(int i=0;i<NoPizzas;i++){
            if(pizza[i].istiSe(p))
                return;
        }
        Pica *tmp = new Pica[NoPizzas+1];
        for(int i=0;i<NoPizzas;i++)
            tmp[i]=pizza[i];
        tmp[NoPizzas++]=p;
        delete []pizza;
        pizza=tmp;
    }
    void piciNaPromocija(){
        for(int i=0;i<NoPizzas;i++){
            if(pizza[i].getDiscount()>0)
                pizza[i].pecati();
        }
    }
};


int main() {

	int n;
	char ime[15];
	cin >> ime;
	cin >> n;

	Picerija p1(ime);
	for (int i = 0; i < n; i++){
		char imp[100];
		cin.get();
		cin.getline(imp, 100);
		int cena;
		cin >> cena;
		char sostojki[100];
		cin.get();
		cin.getline(sostojki, 100);
		int popust;
		cin >> popust;
		Pica p(imp, cena, sostojki, popust);
		p1+=p;
	}

	Picerija p2 = p1;
	cin >> ime;
	p2.setIme(ime);
	char imp[100];
	cin.get();
	cin.getline(imp, 100);
	int cena;
	cin >> cena;
	char sostojki[100];
	cin.get();
	cin.getline(sostojki, 100);
	int popust;
	cin >> popust;
	Pica p(imp, cena, sostojki, popust);
	p2+=p;

	cout << p1.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p1.piciNaPromocija();

	cout << p2.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p2.piciNaPromocija();

	return 0;
}
