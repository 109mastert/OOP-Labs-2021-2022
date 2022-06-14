#include <iostream>
#include <cstring>
using namespace std;

class Masa{
private:
    int height;
    int width;
public:
    Masa(int height=0, int width=0){
        this->height=height;
        this->width=width;
    }
    ~Masa(){}
    void pecati(){
        cout<<"Masa: "<<height<<" "<<width<<endl;
    }
};

class Soba{
private:
    Masa masa;
    int height;
    int width;
public:
    Soba(){
        height=0;
        width=0;
    }
    Soba(int height, int width, Masa masa){
        this->masa=masa;
        this->height=height;
        this->width=width;
    }
    ~Soba(){}
    void pecati(){
        cout<<"Soba: "<<height<<" "<<width<<" ";
        masa.pecati();
    }
};
class Kukja{
private:
    Soba soba;
    char adress[51];
public:
    Kukja(){
        strcpy(this->adress,"");
    }
    Kukja(Soba soba, char *adress){
        this->soba=soba;
        strcpy(this->adress,adress);
    }
    ~Kukja(){}
    void pecati(){
        cout<<"Adresa: "<<adress<<" ";
        soba.pecati();
    }
};

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}
    return 0;
}
