#include <iostream>
#include <cstring>

using namespace std;

class FudbalskaEkipa{
protected:
    char coach[100];
    int goals[10];
public:
    FudbalskaEkipa(char *coach="",int goals[]={0}){
        strcpy(this->coach,coach);
        for(int i=0;i<10;i++)
            this->goals[i]=goals[i];
    }
    FudbalskaEkipa &operator+=(int goal){
        for(int i=9;i>0;i--){
            goals[i]=goals[i-1];
        }
        goals[0]=goal;
        return *this;
    }
    virtual int uspeh()=0;
    virtual char *getCountryName()=0;
    friend ostream &operator<<(ostream &out, FudbalskaEkipa &fe){
        return out<<fe.getCountryName()<<endl<<fe.coach<<endl<<fe.uspeh()<<endl;
    }
    bool operator>(FudbalskaEkipa *fe){
        return (this->uspeh()>fe->uspeh());
    }
};

class Klub:public FudbalskaEkipa{
private:
    char name[50];
    int NoTitles;
public:
    Klub(char *coach,int goals[],char *name,int NoTitles):FudbalskaEkipa(coach,goals){
        strcpy(this->name,name);
        this->NoTitles=NoTitles;
    }
    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++)
            sum+=goals[i];
        return sum*3+NoTitles*1000;
    }
    char *getCountryName(){
        return name;
    }
};

class Reprezentacija:public FudbalskaEkipa{
private:
    char country[50];
    int NoGames;
public:
    Reprezentacija(char *coach,int goals[],char *country,int NoGames):FudbalskaEkipa(coach,goals){
        strcpy(this->country,country);
        this->NoGames=NoGames;
    }
    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++)
            sum+=goals[i];
        return sum*3+NoGames*50;
    }
    char *getCountryName(){
        return country;
    }
};
void najdobarTrener(FudbalskaEkipa **ekipa, int n){
    FudbalskaEkipa *max = ekipa[0];
    for(int i=1;i<n;i++){
        if(max->uspeh()<ekipa[i]->uspeh())
            max=ekipa[i];
    }
    cout<<*max;
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
