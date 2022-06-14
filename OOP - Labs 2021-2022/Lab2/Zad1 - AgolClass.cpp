#include <iostream>
using namespace std;

class Agol {
private:
    int s,m,sec;
public:
    Agol(){};
    Agol(int a,int b,int c){
        s=a;
        m=b;
        sec=c;
    };
    ~Agol(){};
    void set_stepeni(int _s){
        s=_s;
    }
    void set_minuti(int _m){
        m=_m;
    }
    void set_sekundi(int _sec){
        sec=_sec;
    }
    int getSekundi(){
        return sec;
    }
    int to_sekundi(){
        return s*3600+m*60+sec;
    }
};
bool proveri(int s,int m,int sec){
    if(sec>=0 && sec<=60)
    {
        if(m>0 && m<=60)
        {
            if(s<=359 && s>=0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool changeOfSeconds(Agol a, int sec){
	return a.getSekundi()!=sec;
}

int main() {

    //da se instancira objekt od klasata Agol
    int deg, min, sec;
    Agol a1;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {
    	a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
			cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;
    }
    else
        cout<<"Nevalidni vrednosti za agol\n";

    return 0;
}
