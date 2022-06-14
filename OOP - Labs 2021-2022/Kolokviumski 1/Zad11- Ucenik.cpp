#include <iostream>
#include <cstring>
using namespace std;
class Ucenik{
    char *name;
    bool gender;
    int age;

    void copy(const Ucenik &u){
        this->name=new char[strlen(u.name)+1];
        strcpy(this->name,u.name);
        this->gender=u.gender;
        this->age=u.age;
    }
public:
    Ucenik(char *name="",bool gender=false,int age=0){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->gender=gender;
        this->age=age;
    }
    Ucenik(const Ucenik &u){
        copy(u);
    }
    Ucenik &operator=(const Ucenik &u){
        if(this!=&u){
            delete []name;
            copy(u);
        }
        return *this;
    }
    ~Ucenik(){
        delete []name;
    }
};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}
