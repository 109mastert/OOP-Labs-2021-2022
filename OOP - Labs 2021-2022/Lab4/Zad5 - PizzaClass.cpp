#include <iostream>
#include <cstring>

using namespace std;

class Pica{
private:
    char name[15];
    int price;
    char *ingredients;
    int discount;
    void copy(const Pica &p){
        strcpy(this->name,p.name);
        this->price=p.price;
        this->ingredients=new char[strlen(p.ingredients)+1];
        strcpy(this->ingredients,p.ingredients);
        this->discount=p.discount;
    }
public:
    Pica(){
    strcpy(this->name,"");
    price=0;
    this->ingredients= new char[0];
    discount=0;
    }
    Pica(char *name, int price, char *ingredients, int discount){
        strcpy(this->name,name);
        this->price=price;
        this->ingredients=new char[strlen(ingredients)+1];
        strcpy(this->ingredients,ingredients);
        this->discount=discount;
    }
    Pica (const Pica &p){
        copy(p);
    }
    Pica &operator=(const Pica &p){
        if(this!=&p){
            delete []ingredients;
            copy(p);
        }
        return *this;
    }
    ~Pica(){
        delete []ingredients;
    }
    int getPrice(){
        return price;
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
    Pica *pizzas;
    int NoPizzas;
public:
    Picerija(){
        strcpy(this->name,"");
        NoPizzas=0;
    }
    Picerija(char *name=""){
        strcpy(this->name,name);
        NoPizzas=0;
    }
    Picerija(char *name, Pica *pizzas,int NoPizzas){
        strcpy(this->name,name);
        this->pizzas=new Pica[NoPizzas];
        for(int i=0;i<NoPizzas;i++){
            this->pizzas[i]=pizzas[i];
        }
        this->NoPizzas=NoPizzas;
    }
    Picerija(const Picerija &p){
        strcpy(this->name,p.name);
        this->pizzas=new Pica[p.NoPizzas];
        for(int i=0;i<p.NoPizzas;i++){
            this->pizzas[i]=p.pizzas[i];
        }
        this->NoPizzas=p.NoPizzas;
    }
    void setIme(char *name){
        strcpy(this->name,name);
    }
    char *getIme(){
        return name;
    }
    void dodadi(Pica p){
        for(int i=0;i<NoPizzas;i++){
            if(this->pizzas[i].istiSe(p))
                return;
        }
        if(NoPizzas>0){
            Pica *tmp = new Pica[++NoPizzas];
            for(int i=0;i<NoPizzas-1;i++)
                tmp[i]=pizzas[i];
            tmp[NoPizzas-1]=p;
            delete []pizzas;
            pizzas=tmp;
        }
        else{
            pizzas=new Pica[++NoPizzas];
            pizzas[0]=p;
        }
    }
    void piciNaPromocija(){
        for(int i=0;i<NoPizzas;i++){
            if(pizzas[i].getDiscount()>0){
                pizzas[i].pecati();
            }
        }
    }
};

int main () {
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
