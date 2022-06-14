#include <iostream>
#include <cstring>
using namespace std;

class Film{
private:
    char name[100];
    char reziser[50];
    char genre[50];
    int year;
public:
    Film(){};
    Film(char *nm, char * rz, char *gn, int yr){
        strcpy(name,nm);
        strcpy(reziser,rz);
        strcpy(genre,gn);
        year=yr;
    };
    ~Film(){};
    void *setName(char *_name){
        strcpy(name,_name);
    }
    void *setReziser(char *_rz){
        strcpy(reziser,_rz);
    }
    void *setGenre(char *_gn){
        strcpy(genre,_gn);
    }
    void *setYear(int yr){
        year=yr;
    }
    void print(){
        cout<<"Ime: "<<name<<"\nReziser: "<<reziser<<"\nZanr: "<<genre<<"\nGodina: "<<year<<endl;
    }
    int getYear(){
        return year;
    }
};

int main() {
 	int n;
 	cin >> n;
 	Film movies[n];
 	//da se inicijalizira niza od objekti od klasata Film
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		movies[i].setName(ime);
 		movies[i].setReziser(reziser);
 		movies[i].setGenre(zanr);
 		movies[i].setYear(godina);
 		//da se kreira soodveten objekt
 		//movies[i].print();
 	}
 	int godina;
 	cin >> godina;
 	for(int i=0;i<n;i++)
    {
        if(movies[i].getYear()==godina)
            movies[i].print();
    }
 	//da se povika funkcijata pecati_po_godina
 	return 0;
 }
