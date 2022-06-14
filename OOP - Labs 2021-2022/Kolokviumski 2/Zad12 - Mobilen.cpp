#include <iostream>
#include <cstring>

using namespace std;

enum tip{
    smartphone,pc
};

class InvalidProductionDate{
public:
    void message(){
        cout<<"Невалидна година на производство"<<endl;
       // cout<<"Nevalidna godina na proizvodstvo"<<endl;
    }
};

class Device{
protected:
    char model[100];
    tip type;
    static float TIME;
    int year;
    void copy(const Device &d){
        strcpy(this->model,d.model);
        this->type=d.type;
        this->year=d.year;
    }
public:
    Device(char *model="",tip type=smartphone,int year=2000){
        strcpy(this->model,model);
        this->type=type;
        this->year=year;
    }
    Device(const Device &d){
        copy(d);
    }
    Device &operator=(const Device &d){
        if(this!=&d){
            copy(d);
        }
        return *this;
    }
    static void setPocetniCasovi(float t){
        TIME=t;
    }
    int getYear(){
        return year;
    }
    friend ostream &operator<<(ostream &out, const Device &d){
        float t=0;
        if(d.year>2015)
            t+=2;
        if(d.type==pc)
            t+=2;
        out<<d.model<<endl;
        if(d.type==smartphone)
            out<<"Mobilen "<<TIME+t<<endl;
        else
            out<<"Laptop "<<TIME+t<<endl;
        return out;
    }
};
float Device::TIME=1;

class MobileServis{
private:
    char adress[100];
    Device *devices;
    int NoDevices;
    void copy(const MobileServis &ms){
        strcpy(this->adress,ms.adress);
        this->NoDevices=ms.NoDevices;
        this->devices = new Device[ms.NoDevices];
        for(int i=0;i<this->NoDevices;i++)
            this->devices[i]=ms.devices[i];
    }
public:
    MobileServis(char *adress=""){
        strcpy(this->adress,adress);
        this->NoDevices=0;
        this->devices= new Device[0];
    }
    MobileServis(const MobileServis &ms){
        copy(ms);
    }
    MobileServis &operator=(const MobileServis &ms){
        if(this!=&ms){
            delete []devices;
            copy(ms);
        }
        return *this;
    }
    MobileServis &operator+=(Device &d){
        if(d.getYear()<2000 || d.getYear()>2019)
            throw InvalidProductionDate();
        Device *tmp = new Device[NoDevices+1];
        for(int i=0;i<NoDevices;i++)
            tmp[i]=devices[i];
        tmp[NoDevices++]=d;
        delete []devices;
        devices=tmp;
        return *this;
    }
    ~MobileServis(){
        delete []devices;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adress<<endl;
        for(int i=0;i<NoDevices;i++){
            cout<<devices[i];
        }
    }
    pecatiUredi(){

    }
};


int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &ipd){
                ipd.message();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}

