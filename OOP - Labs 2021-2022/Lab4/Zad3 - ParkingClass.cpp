#include <iostream>
#include <cstring>

using namespace std;

class Avtomobil{
private:
    char color[21];
    char brand[21];
    char model[21];
public:
    Avtomobil(char *color="",char *brand="",char *model=""){
        strcpy(this->color,color);
        strcpy(this->brand,brand);
        strcpy(this->model,model);
    }
    Avtomobil &operator=(const Avtomobil &car){
        if(this!=&car){
            strcpy(this->color,car.color);
            strcpy(this->brand,car.brand);
            strcpy(this->model,car.model);
        }
        return *this;
    }
    void print(){
        cout<<color<<" "<<brand<<" "<<model<<endl;
    }
};

class ParkingPlac{
private:
    char adress[21];
    char *id;
    int price;
    int profit;
    Avtomobil *cars;
    int NoCars;

    void copy(const ParkingPlac &pc){

    }
public:
    ParkingPlac(){
        strcpy(this->adress,"");
        this->id = new char[0];
        strcpy(this->id,"");
        price=0;
        profit=0;
        NoCars=0;
        cars = new Avtomobil[50];
    }
    ParkingPlac(char *adress, char *id, int price){
        strcpy(this->adress,adress);
        this->id= new char[strlen(id)+1];
        strcpy(this->id,id);
        this->price=price;
        profit=0;
        NoCars=0;
        this->cars = new Avtomobil[0];
    }
//    ~ParkingPlac(){
//        delete []id;
//        delete []cars;
//    }
//    ParkingPlac(const ParkingPlac &pc){
//        copy(pc);
//    }
    ParkingPlac &operator=(const ParkingPlac &pc){
        if(this!=&pc){
            delete []id;
            strcpy(this->adress,pc.adress);
            this->id= new char[strlen(pc.id)+1];
            strcpy(this->id,pc.id);
            this->price=pc.price;;
        }
        return *this;
    }
    char *getId(){
        return id;
    }
    void pecati(){
        if(profit!=0)
            cout<<this->id<<" "<<this->adress<<" - "<<profit<<" denari"<<endl;
        else
            cout<<this->id<<" "<<this->adress<<endl;
    }
    int platiCasovi(int hours){
        profit+=(hours*price);
    }
    bool daliIstaAdresa(ParkingPlac p){
        if(strcmp(this->adress,p.adress)==0)
            return true;
        return false;
    }
    void parkirajVozilo(Avtomobil novovozilo){
        if(NoCars!=0){
            Avtomobil *tmp = new Avtomobil[++NoCars];
            for(int i=0;i<NoCars-1;i++){
                tmp[i]=cars[i];
            }
            tmp[NoCars-1]=novovozilo;
            delete []cars;
            cars=tmp;
        }
        else{
            delete [] cars;
            cars = new Avtomobil[++NoCars];
            cars[NoCars-1]=novovozilo;
        }
    }
    void pecatiParkiraniVozila(){
        cout <<"Vo parkingot se parkirani slednite vozila:" << endl;
        for(int i=0;i<NoCars;i++){
            cout<<i+1<<".";
            cars[i].print();
        }
    }
    void setProfit(int profit){
        this->profit=profit;
    }

};

int main()
{
    ParkingPlac p[100];
    int n, m;
    char adresa[50], id[50];
    int brojcasovi, cenacas;
    cin >> n;
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(adresa, 50);
            cin >> id >> cenacas;

            ParkingPlac edna(adresa, id, cenacas);

            p[i] = edna;
        }

        //plakjanje
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> id >> brojcasovi;

            int findId = false;
            for (int j = 0; j < m; j++)
            {
                if (strcmp(p[j].getId(), id) == 0)
                {
                    p[j].platiCasovi(brojcasovi);
                    findId = true;
                }
            }
            if (!findId)
                cout << "Ne e platen parking. Greshen ID." << endl;
        }

        cout << "=========" << endl;
        ParkingPlac pCentar("Cvetan Dimov", "C10", 80);
        for (int i = 0; i < n; i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    }
    else
    {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for (int i = 0; i < brVozila; ++i)
        {
            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if (brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}
