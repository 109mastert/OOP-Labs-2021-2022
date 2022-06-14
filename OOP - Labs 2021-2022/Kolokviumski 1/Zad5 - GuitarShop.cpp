#include <iostream>
#include <cstring>

using namespace std;

class Gitara{
private:
    char code[26];
    float price;
    int year;
    char type[41];
    void copy(const Gitara &g){
        strcpy(this->code,g.code);
        this->price=g.price;
        this->year=g.year;
        strcpy(this->type,g.type);
    }
public:
    Gitara(char *type="",char *code="",int year=0,float price=0.0){
        strcpy(this->code,code);
        this->price=price;
        this->year=year;
        strcpy(this->type,type);
    }
    Gitara(const Gitara &g){
        copy(g);
    }
    Gitara &operator=(const Gitara &g){
        if(this!=&g){
            copy(g);
        }
        return *this;
    }
    bool daliIsti(Gitara g){
        if(strcmp(this->code,g.code)==0)
            return true;
        return false;
    }
    char *getTip(){
        return type;
    }
    char *getSeriski(){
        return code;
    }
    float getNabavna(){
        return price;
    }
    int getGodina(){
        return year;
    }
    void pecati(){
        cout<<code<<" "<<type<<" "<<price<<endl;
    }
};
class Magacin{
private:
    char name[31];
    char location[61];
    Gitara *guitar;
    int NoGuitars;
    int year;

    void copy(const Magacin &m){
        strcpy(this->name,m.name);
        strcpy(this->location,m.location);
        this->NoGuitars=m.NoGuitars;
        this->year=m.year;
        this->guitar=new Gitara[m.NoGuitars];
        for(int i=0;i<NoGuitars;i++)
            this->guitar[i]=m.guitar[i];
    }
public:
    Magacin(char *name="", char *location="", int year=0){
        strcpy(this->name,name);
        strcpy(this->location,location);
        NoGuitars=0;
        this->year=year;
        this->guitar=new Gitara[NoGuitars];
    }
    Magacin(Magacin &m){
        copy(m);
    }
    Magacin &operator=(const Magacin &m){
        if(this!=&m){
            delete []guitar;
            copy(m);
        }
        return *this;
    }
    ~Magacin(){
        delete []guitar;
    }
    double vrednost(){
        double value=0;
        for(int i=0;i<NoGuitars;i++){
            value+=(double)guitar[i].getNabavna();
        }
        return value;
    }
    void dodadi(Gitara g){
        Gitara *tmp = new Gitara[++NoGuitars];
        for(int i=0;i<NoGuitars-1;i++)
            tmp[i]=guitar[i];
        tmp[NoGuitars-1]=g;
        delete []guitar;
        guitar=tmp;
    }
    int countOcurances(Gitara p){
        int o=0;
        for(int i=0;i<NoGuitars;i++)
            if(this->guitar[i].daliIsti(p))
                o++;
        return o;
    }
    void prodadi(Gitara p){
        Gitara *tmp = new Gitara[NoGuitars-countOcurances(p)];
        for(int i=0,j=0;i<NoGuitars;i++){
            if(!guitar[i].daliIsti(p))
                tmp[j++]=guitar[i];
        }
        NoGuitars-=countOcurances(p);
        delete []guitar;
        guitar=tmp;
    }
    void pecati(bool daliNovi){
        cout<<name<<" "<<location<<endl;
        for(int i=0;i<NoGuitars;i++)
        {
            if(daliNovi){
                if(guitar[i].getGodina()>=year)
                    guitar[i].pecati();
            }
            else
                guitar[i].pecati();
        }
    }
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}
