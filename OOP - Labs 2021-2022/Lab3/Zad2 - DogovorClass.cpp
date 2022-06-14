#include <iostream>
#include <cstring>

using namespace std;

int i=0;
class Potpisuvac
{
private:
    char name[20],surname[20],embg[14];
public:
    Potpisuvac(char *_name="",char *_surname="", char *_embg=""){
        strcpy(name,_name);
        strcpy(surname,_surname);
        strcpy(embg,_embg);
    };
    Potpisuvac(const Potpisuvac &p){
        strcpy(name,p.name);
        strcpy(surname,p.surname);
        strcpy(embg,p.embg);
    }
    char *getEMBG(){
        return embg;
    }
};
class Dogovor
{
private:
    int contractnum;
    char category[50];
    Potpisuvac potpisuvaci[3];
public:
    Dogovor(int _connum,char *_category,Potpisuvac _potpisuvac[]){
        contractnum=_connum;
        strcpy(category,_category);
        potpisuvaci[0]=_potpisuvac[0];
        potpisuvaci[1]=_potpisuvac[1];
        potpisuvaci[2]=_potpisuvac[2];
    }
    bool proverka(){
    if((strcmp(potpisuvaci[0].getEMBG(),potpisuvaci[1].getEMBG()))!=0)
        {
            if((strcmp(potpisuvaci[0].getEMBG(),potpisuvaci[2].getEMBG()))!=0)
            {
                if((strcmp(potpisuvaci[1].getEMBG(),potpisuvaci[2].getEMBG()))!=0)
                    return false;
                else
                    return true;
            }
            else
                return true;
        }
        else
            return true;
    }
};
//ne smee da se menuva main funkcijata
int main()
{
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] = p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        d.proverka();
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
