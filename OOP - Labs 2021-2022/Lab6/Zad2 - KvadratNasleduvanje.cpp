#include <iostream>
#include <cstring>

using namespace std;

class Kvadrat {
protected:
    double a; //side
public:
    Kvadrat(double a=0.0){
        this->a=a;
    }
    Kvadrat(const Kvadrat &k){
        this->a=k.a;
    }
    double perimetar(){
        return a*4;
    }
    double plostina(){
        return a*a;
    }
    void pecati(){
        cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
};

class Pravoagolnik:public Kvadrat {
    private:
    double x;
    double y;

    public:
    Pravoagolnik(double a=0.0,double x=0.0,double y=0.0):Kvadrat(a){
        this->x=x+a;
        this->y=y+a;
    }
    Pravoagolnik (const Kvadrat &k, double x, double y):Kvadrat(k){
        //treba da se sobere so a od kvadrat
        this->x=x+a;
        this->y=y+a;
    }

    Pravoagolnik(const Pravoagolnik &p):Kvadrat(p){
        this->x=p.x+a;
        this->y=p.y+a;
    }
    double perimetar(){
        //treba da se povikat od kvadrat klasata nekako
        return 2*x+2*y;
    }
    double plostina(){
        //treba da se povikat od kvadrat klasata nekako
        return x*y;
    }
    void pecati(){
        if(x==y){
            Kvadrat tmp(x);
            tmp.pecati();
        }
        else
            cout<<"Pravoagolnik so strani: "<<x<<" i "<<y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }

    //TODO prepokrivanje na metodite perimetar, plostina i pecati od klasata Kvadrat
};

int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;

	cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

	for (int i=0;i<n;i++){
		cin>>a;

		kvadrati[i] = Kvadrat(a);
	}

	for (int i=0;i<n;i++){
		cin>>x>>y;

		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}
