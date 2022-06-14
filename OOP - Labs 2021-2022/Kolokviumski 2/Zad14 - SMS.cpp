#include <iostream>
#include <cstring>

using namespace std;

class SMS{
protected:
    float price;
    char number[15];
    void copy(const SMS &sms){
        this->price=sms.price;
        strcpy(this->number,sms.number);
    }
public:
    SMS(char *number="", float price=0.0){
        this->price=price;
        strcpy(this->number,number);
    }
    SMS(const SMS &sms){
        copy(sms);
    }
    SMS &operator=(const SMS &sms){
        if(this!=&sms){
            copy(sms);
        }
        return *this;
    }
    virtual float SMS_cena()=0;
    friend ostream &operator<<(ostream &out, SMS &s){
        return out<<"Tel: "<<s.number<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
    }
};

class RegularSMS:public SMS{
private:
    char *content;
    bool roaming;
    static float ROAM;
public:
    RegularSMS(char *number="",float price=0.0,char *content="",bool roaming=false):SMS(number,price){
        this->content = new char[strlen(content)+1];
        strcpy(this->content,content);
        this->roaming=roaming;
    }
    ~RegularSMS(){
        delete []content;
    }
    float SMS_cena(){
        float price=this->price;
        if(this->roaming)
            price+=(price*(ROAM/100));
        else
            price*=1.18;
        if(strlen(this->content)>=160)
            price*=(strlen(this->content)/160+1);
        return price;
    }
    static void set_rProcent(int r){
        ROAM=r;
    }
    friend ostream &operator<<(ostream &out, RegularSMS &r){
        return out<<"Tel: "<<r.number<<" - cena: "<<r.SMS_cena()<<"den."<<endl;
    }
};
float RegularSMS::ROAM=300;


class SpecialSMS:public SMS{
private:
    bool humanitarian;
    static float PROCENT;
public:
    SpecialSMS(char *number="",float price=0.0,bool humanitarian=false):SMS(number,price){
        this->humanitarian=humanitarian;
    }
    float SMS_cena(){
        float price=this->price;
        if(!this->humanitarian)
            price+=(price*(PROCENT/100));
        return price;
    }
    static void set_sProcent(int p){
        PROCENT=p;
    }
    friend ostream &operator<<(ostream &out, SpecialSMS &s){
        return out<<"Tel: "<<s.number<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
    }
};
float SpecialSMS::PROCENT=150;

void vkupno_SMS(SMS **poraka, int n){
    float totalR=0.0,totalS=0.0;
    int r=0,s=0;
    for(int i=0;i<n;i++){
        RegularSMS *reg = dynamic_cast<RegularSMS*>(poraka[i]);
        SpecialSMS *spec = dynamic_cast<SpecialSMS*>(poraka[i]);
        if(reg!=nullptr){
            r++;
            totalR+=reg->SMS_cena();
        }
        else if(spec!=nullptr){
            s++;
            totalS+=spec->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<r<<" regularni SMS poraki i nivnata cena e: "<<totalR<<endl;
    cout<<"Vkupno ima "<<s<<" specijalni SMS poraki i nivnata cena e: "<<totalS<<endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
            RegularSMS *r=dynamic_cast<RegularSMS*>(sms[i]);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}
	return 0;
}
