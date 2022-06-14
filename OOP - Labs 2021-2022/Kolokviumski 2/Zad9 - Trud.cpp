#include <iostream>
#include <cstring>

using namespace std;

class Exception{
public:
    void message(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};
class StudentException{
private:
    int indx;
public:
    StudentException(int indx){
        this->indx=indx;
    }
    void message(){
        cout<<"Ne postoi PhD student so indeks "<<indx<<endl;
    }
};
class Trud{
protected:
    char type; ///C konferenciski, J za trud vo spisanie
    int publishYear;
    void copy(const Trud &t){
        this->type=t.type;
        this->publishYear=t.publishYear;
    }
public:
    Trud(char type='C',int publishYear=2000){
        this->type=type;
        this->publishYear=publishYear;
       // cout<<"Kreiran trud od tip "<<type<<" i godina "<<publishYear<<endl;
    }
    Trud(const Trud &t){
        copy(t);
    }
    Trud &operator=(const Trud &t){
        if(this!=&t){
            copy(t);
        }
        return *this;
    }
    bool operator==(const Trud &t){
        return (this->type == t.type && this->publishYear==t.publishYear);
    }
    char getType(){
        return type;
    }
    int getPublishYear(){
        return publishYear;
    }
    friend istream &operator>>(istream &in, Trud &t){
        return in>>t.type>>t.publishYear;
    }
};

class Student{
protected:
    char name[30];
    int index;
    int year;
    int *subjects;
    int NoSubjects;
public:
    Student(char *name,int index,int year,int subjects[], int NoSubjects){
        strcpy(this->name,name);
        this->index=index;
        this->year=year;
        this->NoSubjects=NoSubjects;
        this->subjects = new int[NoSubjects];
        for(int i=0;i<NoSubjects;i++)
            this->subjects[i]=subjects[i];
            //this->subjects[i]=subjects[i];
    }
    virtual double rang(){
        double sum=0.0;
        for(int i=0;i<NoSubjects;i++)
            sum+=subjects[i];
        return (float)sum/NoSubjects;
    }
    friend ostream &operator<<(ostream &out, Student &s){
        return out<<s.index<<" "<<s.name<<" "<<s.year<<" "<<s.rang()<<endl;
    }
    int getIndex(){
        return index;
    }
};
class PhDStudent:public Student{
private:
    Trud *trud;
    int NoTrudovi;
    static int kTrud;
    static int sTrud;
public:
    PhDStudent(char *name,int index,int year,int subjects[],int NoSubjects,Trud trud[],int NoTrudovi):Student(name,index,year,subjects,NoSubjects){
        this->NoTrudovi=NoTrudovi;
        this->trud = new Trud[NoTrudovi];
        for(int i=0,j=0;i<NoTrudovi;i++){
            try{
                if(trud[i].getPublishYear()<year){
                    this->NoTrudovi--;
                    throw Exception();
                }
                this->trud[j++]=trud[i];
            }
            catch(Exception &e){
                e.message();
            }
        }
    }
    static void setkTrud(int koef){
            kTrud=koef;
        }
    static void setsTrud(int journal){
        sTrud=journal;
    }
    double rang(){
        double sum=0.0;
        for(int i=0;i<NoTrudovi;i++){
            if(trud[i].getType()=='J' || trud[i].getType()=='j')
                sum+=sTrud;
            else if(trud[i].getType()=='C' || trud[i].getType()=='c')
                sum+=kTrud;
        }
        return Student::rang()+sum;
    }
    PhDStudent &operator+=(Trud &t){
        //cout<<"Publish year is "<<t.getPublishYear()<<" and the year is "<<year<<endl;
        for(int i=0;i<NoTrudovi;i++){
            if(t.getPublishYear()<year)
                throw Exception();
        }
        Trud *tmp= new Trud[NoTrudovi+1];
        for(int i=0;i<NoTrudovi;i++)
            tmp[i]=trud[i];
        tmp[NoTrudovi++]=t;
        delete []trud;
        trud=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, PhDStudent &ps){
        return out<<ps.index<<" "<<ps.name<<" "<<ps.year<<" "<<ps.rang()<<endl;
    }
};
int PhDStudent::kTrud=1;
int PhDStudent::sTrud=3;

int proveriStudent(Student **studenti, int n,int indx){
    int c=0;
    for(int i=0;i<n;i++){
        if(studenti[i]->getIndex()==indx && dynamic_cast<PhDStudent*>(studenti[i]))
            return i;
    }
    throw StudentException(indx);
}

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++){
            PhDStudent *ps= dynamic_cast<PhDStudent*>(niza[i]);
            if(ps!=nullptr)
                cout<<*ps;
            else
                cout << *niza[i];
		}


		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
		try{
            int r=proveriStudent(niza,m,indeks);
            PhDStudent *ps= dynamic_cast<PhDStudent*>(niza[r]);
            try{
                *ps+=t;
            }
            catch(Exception &e){
                e.message();
            }
		}
		catch(StudentException &se){
            se.message();
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				try{
                    niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
				}
				catch(Exception &e){
                    e.message();
				}

			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try{
            int r=proveriStudent(niza,m,indeks);
            PhDStudent *ps= dynamic_cast<PhDStudent*>(niza[r]);
            try{
                *ps+=t;
            }
            catch(Exception &e){
                e.message();
            }
		}
		catch(StudentException &se){
            se.message();
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr); ///tuka treba za trud exception nekako da ga opravu
            cout<<phd;

	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		try{
            int r=proveriStudent(niza,m,indeks);
            PhDStudent *ps= dynamic_cast<PhDStudent*>(niza[r]);
            try{
                *ps+=t;
            }
            catch(Exception &e){
                e.message();
            }
		}
		catch(StudentException &se){
            se.message();
		}

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setkTrud(conf);
        PhDStudent::setsTrud(journal);

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
