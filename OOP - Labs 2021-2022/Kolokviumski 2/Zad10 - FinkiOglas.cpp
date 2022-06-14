#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class NegativnaVrednost{
public:
    void message(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglas{
protected:
    char title[50];
    char category[30];
    char description[100];
    float price;
    void copy(const Oglas &o){
        strcpy(this->title,o.title);
        strcpy(this->category,o.category);
        strcpy(this->description,o.description);
        this->price=o.price;
    }
public:
    Oglas(char *title="",char *category="",char *description="",float price=0.0){
        strcpy(this->title,title);
        strcpy(this->category,category);
        strcpy(this->description,description);
        this->price=price;
    }
    Oglas(const Oglas &o){
        copy(o);
    }
    Oglas &operator=(const Oglas &o){
        if(this!=&o){
            copy(o);
        }
        return *this;
    }
    float getPrice(){
        return price;
    }
    char *getCategory(){
        return category;
    }
    bool operator>(const Oglas &o){
        return (this->price>o.price);
    }
    friend ostream &operator<<(ostream &out,const Oglas &o){
        return out<<o.title<<endl<<o.description<<endl<<o.price<<" evra"<<endl;
    }
};
class Oglasnik{
private:
    char name[20];
    Oglas *ads;
    int NoAds;
public:
    Oglasnik(char *name){
        strcpy(this->name,name);
        this->NoAds=0;
        this->ads = new Oglas[NoAds];
    }
    Oglasnik(char *name,Oglas ads[],int NoAds){
        strcpy(this->name,name);
        this->NoAds,NoAds;
        this->ads = new Oglas[NoAds];
        for(int i=0;i<NoAds;i++)
            this->ads[i]=ads[i];
    }
    ~Oglasnik(){
        delete []ads;
    }
    Oglasnik &operator+=(Oglas &o){
        if(o.getPrice()<0)
            throw NegativnaVrednost();
        Oglas *tmp = new Oglas[NoAds+1];
        for(int i=0;i<NoAds;i++)
            tmp[i]=ads[i];
        tmp[NoAds++]=o;
        delete []ads;
        ads=tmp;
        return *this;
    }
    void oglasiOdKategorija(const char *k){
        for(int i=0;i<NoAds;i++){
            if(strcmp(ads[i].getCategory(),k)==0)
                cout<<ads[i]<<endl;
        }
    }
    void najniskaCena(){
        Oglas min = ads[0];
        for(int i=1;i<NoAds;i++){
            if(min.getPrice()>ads[i].getPrice())
                min=ads[i];
        }
        cout<<min<<endl;
    }
    friend ostream &operator<<(ostream &out, const Oglasnik &o){
        out<<o.name<<endl;
        for(int i=0;i<o.NoAds;i++)
            out<<o.ads[i]<<endl;
        return out;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
                ogl+=o;
        	}
            catch(NegativnaVrednost &nv){
                nv.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
                ogl+=o;
        	}
        	catch(NegativnaVrednost &nv){
                nv.message();
        	}
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
        	}
        	catch(NegativnaVrednost &nv){
                nv.message();
        	}
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
