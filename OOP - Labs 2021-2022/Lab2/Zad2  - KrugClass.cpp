#include <iostream>
using namespace std;

class Krug {
private:
    float r;
    const float pi=3.14;
public:
    Krug(){};
    Krug(float _r = 0){
        r=_r;
    };
    ~Krug(){};
    float plostina(){
        return r*r*pi;
    }
    float perimetar(){
        return 2*r*pi;
    }
    bool ednakvi(){
        if(plostina()==perimetar())
            return true;
        else
            return false;
    }
};

int main() {
	float r;
	cin >> r;
	Krug k(r);
	//instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
	Krug k1();
    //instanciraj objekt od klasata Krug cij radius ne e definiran
	return 0;
}
