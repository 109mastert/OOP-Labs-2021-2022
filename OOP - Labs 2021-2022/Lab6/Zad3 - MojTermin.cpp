#include <iostream>
#include <cstring>
using namespace std;

class Lekar{
protected:
    int fax;
    char name[10];
    char surname[11];
    float salary;
public:
    Lekar(int fax=0,char *name="",char *surname="",float salary=0.0){
        this->fax=fax;
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary=salary;
    }
    Lekar(const Lekar &l){
        this->fax=l.fax;
        strcpy(this->name,l.name);
        strcpy(this->surname,l.surname);
        this->salary=l.salary;
    }
    void pecati(){
        cout<<fax<<": "<<name<<" "<<surname<<endl;
    }
    double plata(){
        return salary;
    }
};
class MaticenLekar:public Lekar{
private:
    int patients;
    double *pay;
public:
    MaticenLekar(int fax=0,char *name="",char *surname="",float salary=0.0,int patients=0,double *pay={0}):Lekar(fax,name,surname,salary){
        this->patients=patients;
        this->pay=new double[patients];
        for(int i=0;i<patients;i++){
            this->pay[i]=pay[i];
        }
    }
    MaticenLekar(const Lekar &l,int patients,double *pay):Lekar(l){
        this->patients=patients;
        this->pay=new double[patients];
        for(int i=0;i<patients;i++){
            this->pay[i]=pay[i];
        }
    }
    MaticenLekar(const MaticenLekar &ml):Lekar(ml){
        this->patients=ml.patients;
        this->pay=new double[ml.patients];
        for(int i=0;i<patients;i++){
            this->pay[i]=ml.pay[i];
        }
    }
    double prosek(){
        double sum=0;
        for(int i=0;i<patients;i++)
            sum+=pay[i];
        return sum/patients;
    }
    void pecati(){
        Lekar::pecati();
        cout<<"Prosek na kotizacii: "<<prosek()<<endl;
    }
    double plata(){
        return Lekar::plata()+0.3*prosek();
    }
};

int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;

	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];

	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
	}

	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}

	int testCase;
	cin>>testCase;
	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}

	delete [] lekari;
	delete [] maticni;

	return 0;
}
