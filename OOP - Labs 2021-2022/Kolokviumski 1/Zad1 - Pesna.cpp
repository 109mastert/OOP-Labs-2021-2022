#include <iostream>
#include <cstring>

using namespace std;

enum tip{POP=0,RAP,ROCK};

class Pesna{
private:
    char *name;
    int duration;
    tip type;

    void copy(const Pesna &p){
        this->name= new char[strlen(p.name)+1];
        strcpy(this->name,p.name);
        this->duration=p.duration;
        this->type=p.type;
    }
public:
    Pesna(char *name="",int duration=0,tip type=POP){
        this->name= new char[strlen(name)+1];
        strcpy(this->name,name);
        this->duration=duration;
        this->type=type;
    }
    Pesna(const Pesna &p){
        copy(p);
    }
    Pesna &operator=(const Pesna &p){
        if(this!=&p){
            delete []name;
            copy(p);
        }
        return *this;
    }
    ~Pesna(){
        delete []name;
    }
    int getDuration(){
        return duration;
    }
    tip getType(){
        return type;
    }
    void pecati(){
        cout<<"\""<<name<<"\"-"<<duration<<"min"<<endl;
    }
};
class CD{
private:
    Pesna song[10];
    int NoSongs;
    int maxduration;
    void copy(const CD &cd){
        this->NoSongs=cd.NoSongs;
        this->maxduration=cd.maxduration;
        for(int i=0;i<NoSongs;i++)
            this->song[i]=cd.song[i];
    }
public:
    CD(int maxduration=0){
        NoSongs=0;
        this->maxduration=maxduration;
    }
    CD(Pesna *song,int NoSongs,int maxduration){
        this->NoSongs=NoSongs;
        this->maxduration=maxduration;
        for(int i=0;i<NoSongs;i++)
            this->song[i]=song[i];
    }
    CD(const CD &cd){
        copy(cd);
    }
    CD &operator=(const CD &cd){
        if(this!=&cd){
            copy(cd);
        }
        return *this;
    }
    Pesna getPesna(int i){
        return song[i];
    }
    int getBroj(){
        return NoSongs;
    }
    void dodadiPesna(Pesna p){
        if(p.getDuration()<=this->maxduration && NoSongs<10){
            song[NoSongs++]=p;
            maxduration-=p.getDuration();
        }
    }
    void pecatiPesniPoTip(tip t){
        for(int i=0;i<NoSongs;i++){
            if(song[i].getType()==t)
                song[i].pecati();
        }
    }
};


int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
