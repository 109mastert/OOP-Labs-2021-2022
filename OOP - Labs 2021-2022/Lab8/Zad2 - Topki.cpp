#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual void print()=0;
    virtual float getPlostina()=0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    Forma(char *boja="",int gustina=0){
        strcpy(this->boja,boja);
        this->gustina=gustina;
    }
};
class Topka:public Forma,public Igrachka{
private:
    int r;
public:
    Topka(char *boja, int gustina,int r):Forma(boja,gustina){
        this->r=r;
    }
    float getMasa(){
        return getVolumen()*gustina;
    }
    float getVolumen(){
        return (float)4/3*3.14*r*r*r;
    }
    float getPlostina(){
        return (float)4*3.14*r*r;
    }
    void print(){
        cout<<"Ball with radius: "<<r<<" with density: "<<gustina<<" and color "<<boja<<", volumen: "<<getVolumen()<<" and mass: "<<getMasa()<<endl;
    }
};
class Kocka:public Forma,public Igrachka{
private:
    int y,x,z;
public:
    Kocka(char *boja="",int gustina=0,int y=0,int x=0,int z=0):Forma(boja,gustina){
        this->y=y;
        this->x=x;
        this->z=z;
    }
    float getMasa(){
        return getVolumen()*gustina;
    }
    float getVolumen(){
        return y*x*z;
    }
    float getPlostina(){
        return (float)2*(x*y+x*z+y*z);
    }
    void print(){
        cout<<"height: "<<y<<" width: "<<x<<" depth: "<<z<<" with density: "<<gustina<<" and color "<<boja<<", volumen: "<<getVolumen()<<" and mass: "<<getMasa()<<endl;
    }
};
int main(){
    int n,type,density,r,x,y,z;
    float totalmass,maxVolume,minArea;
    char clr[50];
    cin>>n;
    Igrachka **kupche= new Igrachka *[n];
    for(int i=0;i<n;i++){
        cin>>type;
        if(type==1){
            cin>>clr>>density>>r;
            kupche[i]=new Topka(clr,density,r);
        }
        else{
            cin>>clr>>density>>y>>x>>z;
            kupche[i]= new Kocka(clr,density,y,x,z);
        }
        if(i==0){
            maxVolume=kupche[i]->getVolumen();
            minArea=kupche[i]->getPlostina();
        }
        else{
            if(maxVolume<kupche[i]->getVolumen())
                maxVolume=kupche[i]->getVolumen();
            if(minArea>kupche[i]->getPlostina())
                minArea=kupche[i]->getPlostina();
        }
        totalmass+=kupche[i]->getMasa();
    }
    cin>>clr>>density>>y>>x>>z;
    Kocka petra(clr,density,y,x,z);
    if(totalmass>petra.getMasa())
        cout<<"DA"<<endl;
    else
        cout<<"NE"<<endl;
    cout<<"Razlikata e: "<<abs(maxVolume-petra.getVolumen())<<endl;
    cout<<"Razlikata e: "<<abs(minArea-petra.getPlostina())<<endl;
	return 0;
}
