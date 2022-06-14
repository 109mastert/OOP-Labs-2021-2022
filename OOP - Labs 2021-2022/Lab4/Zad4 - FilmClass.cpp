#include <iostream>
#include <cstring>

using namespace std;

enum zanr{action=0,comedy,drama};

class Film{
private:
    char *name;
    int size;
    zanr genre;

    void copy(const Film &other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->size=other.size;
        this->genre=other.genre;
    }
public:
    Film(char *name="",int size=0,zanr genre=action){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->size=size;
        this->genre=genre;
    }
    Film(const Film &other){
        copy(other);
    }
    Film &operator=(const Film &other){
        if(this!=&other)
        {
            delete []name;
            this->name=new char[strlen(other.name)+1];
            strcpy(this->name,other.name);
            this->size=other.size;
            this->genre=other.genre;
        }
        return *this;
    }
//    ~Film(){
//        delete []name;
//    }
    int getSize(){
        return size;
    }
    zanr getGenre(){
        return genre;
    }
    void pecati(){
        cout<<size<<"MB-\"" <<name<< "\" \n"; // so \" se pisuva navodnik
    }
};
class DVD{
private:
    Film movies[5];
    int NoMovies;
    int size;
public:
    DVD(int size){
        this->size=size;
        NoMovies=0;
    }
    DVD(Film *movies,int NoMovies=0,int size=0){
        this->size=size;
        this->NoMovies=NoMovies;
        for(int i=0;i<NoMovies;i++){
            this->movies[i]=movies[i];
        }
    }
    Film getFilm(int i){
        return movies[i]; //kako da pratu adresa za dole da naprae pecatenje na film
    }
    void dodadiFilm(Film f){
        if(f.getSize()<=size && NoMovies<5){
            movies[NoMovies++]=f;
            this->size-=f.getSize();
        }
    }
    void print(){
        for(int i=0;i<NoMovies;i++)
            movies[i].pecati();
    }
    int getBroj(){
        return NoMovies;
    }
    void pecatiFilmoviDrugZanr(zanr genre){
        for(int i=0;i<NoMovies;i++){
            if(movies[i].getGenre()!=genre)
                movies[i].pecati();
        }
    }
    float procentNaMemorijaOdZanr(zanr genre){
        int gmemory=0,total=0;
        for(int i=0;i<NoMovies;i++)
        {
            if(movies[i].getGenre()==genre)
                gmemory+=movies[i].getSize();
            total+=movies[i].getSize();
        }
        return (float)gmemory/total*100;
    }
};
int main() {

    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

	}
    return 0;
}
