#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo{
private:
    char *name;
    int NoTours;
    int members;

    void copy(const PlDrustvo &pl){
        this->name= new char[strlen(pl.name)+1];
        strcpy(this->name,pl.name);
        this->NoTours=pl.NoTours;
        this->members=pl.members;
    }
public:
    PlDrustvo(char *name="",int NoTours=0,int members=0){
        this->name= new char[strlen(name)+1];
        strcpy(this->name,name);
        this->NoTours=NoTours;
        this->members=members;
    }
    PlDrustvo(const PlDrustvo &pl){
        copy(pl);
    }
    PlDrustvo &operator=(const PlDrustvo &pl){
        if(this!=&pl){
            delete []name;
            copy(pl);
        }
        return *this;
    }
    PlDrustvo operator+(const PlDrustvo &pl){
        PlDrustvo pom;
        if(this->members>pl.members){
            strcpy(pom.name,this->name);
            pom.NoTours=this->NoTours;
            pom.members=pl.members+this->members;
        }
        else{
           strcpy(pom.name,pl.name);
            pom.NoTours=pl.NoTours;
            pom.members=pl.members+this->members;
        }
        return pom;
    }
    bool operator>(const PlDrustvo &pl){
        if(this->members>pl.members)
            return true;
        return false;
    }
    bool operator<(const PlDrustvo &pl){
        if(this->members<pl.members)
            return true;
        return false;
    }
    friend ostream &operator<<(ostream &out, const PlDrustvo &pl){
        return out<<"Ime: "<<pl.name<<" Turi: "<<pl.NoTours<<" Clenovi: "<<pl.members<<endl;
    }
    int getMembers(){
        return members;
    }
};
void najmnoguClenovi(PlDrustvo pl[], int n){
        int maxMembers=pl[0].getMembers(),r=0;
        for(int i=1;i<n;i++){
            if(pl[i].getMembers()>maxMembers){
                maxMembers=pl[i].getMembers();
                r=i;
            }
        }
        cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<pl[r];
    }
int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

   	}

    pl = drustva[0] + drustva[1];
    cout<<pl;
    najmnoguClenovi(drustva, 3);

    return 0;
}
