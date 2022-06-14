#include<iostream>
#include<cstring>

using namespace std;

class StockRecord{
private:
    char id[13];
    char name[51];
    float fPrice;
    float mPrice;
    int NoStocks;
    void copy(const StockRecord &sr){
        strcpy(this->id,sr.id);
        strcpy(this->name,sr.name);
        this->fPrice=sr.fPrice;
        this->mPrice=sr.mPrice;
        this->NoStocks=sr.NoStocks;
    }
public:
    StockRecord(char *id="",char *name="",float fPrice=0.0,int NoStocks=0){
        strcpy(this->id,id);
        strcpy(this->name,name);
        this->fPrice=fPrice;
        this->mPrice=0;
        this->NoStocks=NoStocks;
    }
    StockRecord(const StockRecord &sr){
        copy(sr);
    }
    StockRecord &operator= (const StockRecord &sr){
        if(this!=&sr){
            copy(sr);
        }
        return *this;
    }
    void setNewPrice(double c){
        this->mPrice=c;
    }
    double value(){
        return (double)NoStocks*mPrice;
    }
    double profit(){
        return (double)NoStocks*(mPrice-fPrice);
    }
    friend ostream &operator<<(ostream &out,StockRecord &sr){
        return out<<sr.name<<" "<<sr.NoStocks<<" "<<sr.fPrice<<" "<<sr.mPrice<<" "<<sr.profit()<<endl;
    }
};
class Client{
private:
    char name[61];
    int id;
    StockRecord *company;
    int NoCompanies;
    void copy(const Client &c){
        strcpy(this->name,c.name);
        this->id=c.id;
        this->NoCompanies=c.NoCompanies;
        this->company=new StockRecord[c.NoCompanies];
        for(int i=0;i<NoCompanies;i++)
            this->company[i]=c.company[i];
    }
public:
    Client(char *name="",int id=0){
        strcpy(this->name,name);
        this->id=id;
        this->NoCompanies=0;
        this->company=new StockRecord[NoCompanies];
    }
    Client(const Client &c){
        copy(c);
    }
    Client &operator=(const Client &c){
        if(this!=&c){
            delete []company;
            copy(c);
        }
        return *this;
    }
    double totalValue(){
        double sum=0.0;
        for(int i=0;i<NoCompanies;i++)
            sum+=company[i].value();
        return sum;
    }
    Client &operator+=(const StockRecord &sr){
        StockRecord *tmp = new StockRecord[NoCompanies+1];
        for(int i=0;i<NoCompanies;i++)
            tmp[i]=company[i];
        tmp[NoCompanies++]=sr;
        delete []company;
        company=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Client &c){
        out<<c.id<<" "<<c.totalValue()<<endl;
        for(int i=0;i<c.NoCompanies;i++)
            out<<c.company[i];
        return out;
    }
};

int main(){
    int test;
    cin >> test;

    if(test == 1){
    	double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
    	char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
        	cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
    	cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
        	StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
            	cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
