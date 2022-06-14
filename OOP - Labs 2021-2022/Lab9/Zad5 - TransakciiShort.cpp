#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException{
private:
    int day,month,year;
public:
    InvalidDateException(int day,int month,int year){
        this->day=day;
        this->month=month;
        this->year=year;
    }
    void message(){
        cout<<"Invalid Date "<<day<<"/"<<month<<"/"<<year<<endl;
    }
};
class NotSupportedCurrencyException{
private:
    char *currency;
public:
    NotSupportedCurrencyException(char *currency){
        this->currency= new char[strlen(currency)+1];
        strcpy(this->currency,currency);
    }
    ~NotSupportedCurrencyException(){
        delete []currency;
    }
    void message(){
        cout<<currency<<" is not a supported currency"<<endl;
    }
};


class Transakcija{
protected:
    int day,month,year;
    double amount;
    static double EUR;
    static double USD;
public:
    Transakcija(int day=1,int month=1,int year=1111,double amount=0){
        if(day<1 || day>31 || month<1 || month >12)
            throw InvalidDateException(day,month,year);
        this->day=day;
        this->month=month;
        this->year=year;
        this->amount=amount;
    }
    virtual double voDenari()=0;
    virtual void pecati()=0;
    static void setEUR(double newEUR){
        EUR=newEUR;
    }
    static void setUSD(double newUSD){
        USD=newUSD;
    }
};
double Transakcija::EUR=61;
double Transakcija::USD=50;

class DenarskaTransakcija:public Transakcija{
public:
    DenarskaTransakcija(int day=1,int month=1,int year=1111,double amount=0):Transakcija(day,month,year,amount){}
    double voDenari(){
        return amount;
    }
    void pecati(){
        cout<<day<<"/"<<month<<"/"<<year<<" "<<amount<<" MKD"<<endl;
    }
};

class DeviznaTransakcija:public Transakcija{
private:
    char currency[4];
public:
    DeviznaTransakcija(int day=1,int month=1,int year=1111,double amount=0,char *currency=""):Transakcija(day,month,year,amount){
        if(strcmp(currency,"EUR")!=0 && strcmp(currency,"USD")!=0)
            throw NotSupportedCurrencyException(currency);
        strcpy(this->currency,currency);
    }
    double voDenari(){
        if(strcmp(currency,"EUR")==0)
            return amount*EUR;
        else if(strcmp(currency,"USD")==0)
            return amount*USD;
    }
    void pecati(){
        if(strcmp(currency,"EUR")==0)
            cout<<day<<"/"<<month<<"/"<<year<<" "<<amount<<" EUR"<<endl;
        else if(strcmp(currency,"USD")==0)
            cout<<day<<"/"<<month<<"/"<<year<<" "<<amount<<" USD"<<endl;
    }
};

class Smetka{
private:
    Transakcija **transactions;
    int NoTransactions;
    char account[16];
    double saldo;
public:
    Smetka(char *account="",double saldo=0.0){
        NoTransactions=0;
        strcpy(this->account,account);
        this->saldo=saldo;
        transactions = new Transakcija *[0];
    }
    ~Smetka(){
        delete []transactions;
    }
    Smetka &operator+=(Transakcija *t){
        Transakcija **tmp = new Transakcija *[NoTransactions+1];
        for(int i=0;i<NoTransactions;i++)
            tmp[i]=transactions[i];
        tmp[NoTransactions++]=t;
        delete []transactions;
        transactions=tmp;
        return *this;
    }
    void izvestajVoDenari(){
        double sum=saldo;
        for(int i=0;i<NoTransactions;i++)
            sum+=transactions[i]->voDenari();
        cout<<"Korisnikot so smetka: "<<account<<" ima momentalno saldo od "<<sum<<" MKD"<<endl;
    }
    void pecatiTransakcii(){
        for(int i=0;i<NoTransactions;i++)
            transactions[i]->pecati();
    }
};
int main () {

	Smetka s ("300047024112789",1500);

	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];

	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
		if (tip==2){
			cin>>valuta;
			try{
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
			}
			catch(InvalidDateException &ide){
                ide.message();
			}
			catch(NotSupportedCurrencyException &nsce){
                nsce.message();
			}

            //delete t;
		}
		else {
            try{
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
            }
            catch(InvalidDateException &ide){
                ide.message();
            }

            //delete t;
		}

	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();


    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();




	return 0;
}
