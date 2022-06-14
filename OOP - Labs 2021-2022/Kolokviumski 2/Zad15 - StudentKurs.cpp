#include<iostream>
#include<string.h>
using namespace std;

class BadInputException{
public:
    void message(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

class StudentKurs{
protected:
   char ime[30];
   int ocena;
   bool daliUsno; ///1 do max
   static int MAX;
   const static int MINOCENKA=6;
public:
    StudentKurs(char* ime="",int finalenIspit=0){
        strcpy(this->ime,ime);
        this->ocena=finalenIspit;
        this->daliUsno=false;
     }
     bool getDaliUsno(){
        return daliUsno;
     }
     char *getName(){
        return ime;
     }
     virtual int ocenka(){
        return ocena;
     }
     static void setMAX(int max){
        MAX=max;
     }
     static int getMIN(){
        return MINOCENKA;
     }
     friend ostream &operator<<(ostream &out, const StudentKurs &sk){
        return out<<sk.ime<<" --- "<<sk.ocena<<endl;
     }
};
int StudentKurs::MAX=10;

class StudentKursUsno:public StudentKurs{
private:
    char *grade; ///odlicen=+2 dobro=+1 loshno=-1  else ista ocenka
public:
    StudentKursUsno(char *ime="", int ocena=0):StudentKurs(ime,ocena){
        this->grade = new char[1];
        strcpy(this->grade,"");
        this->daliUsno=true;
    }
    StudentKursUsno operator+=(char *g){
        for(int i=0;i<strlen(g);i++){
            if(!isalpha(g[i]))
                throw BadInputException();
        }
        this->grade = new char[strlen(g)+1];
        strcpy(this->grade,g);
        return *this;
    }
    char *getGrade(){
        return grade;
    }
    int ocenka(){
        if(strcmp(this->grade,"odlicen")==0)
            this->ocena+=2;
        else if(strcmp(this->grade,"dobro")==0)
            this->ocena+=1;
        else if(strcmp(this->grade,"losho")==0)
            this->ocena-=1;
        if(ocena>MAX)
            ocena=MAX;
        return ocena;
    }
    friend ostream &operator<<(ostream &out, const StudentKursUsno &sku){
         return out<<sku.ime<<" --- "<<sku.ocena<<endl;
    }
};


class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
    strcpy(this->naziv,naziv);
    for (int i=0;i<broj;i++){
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else
            this->studenti[i]=new StudentKurs(*studenti[i]);
    }
    this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++){
            if(studenti[i]->ocenka()>=StudentKurs::getMIN())
                cout<<*studenti[i];
        }
    }
    void postaviOpisnaOcenka(char *ime, char *g){
        char newStr[10];
        int k=0;
        for(int i=0;i<broj;i++){
            StudentKursUsno *s= dynamic_cast<StudentKursUsno*>(studenti[i]);
            if(strcmp(studenti[i]->getName(),ime)==0 && s!=nullptr){
                try{
                    (*s)+=g; ///Na dodavanjeto prae greska
                }
                catch(BadInputException &bie){
                    bie.message();
                    for(int j=0;j<strlen(g);j++){
                        if(isalpha(g[j]))
                            newStr[k++]=g[j];
                    }
                    newStr[k]='\0';
                    *s+=newStr;
                }
            }
        }
    }
};
int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
       cin>>ime>>opisna;
       programiranje.postaviOpisnaOcenka(ime,opisna);
    }
    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
