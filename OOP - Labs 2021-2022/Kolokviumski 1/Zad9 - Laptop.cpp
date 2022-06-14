#include <iostream>
#include <cstring>

using namespace std;

typedef struct Laptop{
    char brand[101];
    float display;
    bool touch;
    int price;
}Laptop;
typedef struct ITStore{
    char name[101];
    char location[101];
    Laptop laptops[100];
    int NoLaptops;
}ITStore;
void print(ITStore *store, int n){
    for(int i=0;i<n;i++){
        cout<<store[i].name<<" "<<store[i].location<<endl;
        for(int j=0;j<store[i].NoLaptops;j++){
            cout<<store[i].laptops[j].brand<<" "<<store[i].laptops[j].display<<" "<<store[i].laptops[j].price<<endl;
        }
    }

}
void najeftina_ponuda(ITStore *store,int n){
    int flag=0,r,min;
    for(int i=0;i<n;i++){
        for(int j=0;j<store[i].NoLaptops;j++){
            if(store[i].laptops[j].touch){
                if(!flag++){
                    min=store[i].laptops[j].price;
                    r=i;

                }
                else{
                    if(min>store[i].laptops[j].price){
                        min=store[i].laptops[j].price;
                        r=i;
                    }
                }
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata:\n"<<store[r].name<<" "<<store[r].location<<endl;
    cout<<"Najniskata cena iznesuva: "<<min<<endl;
}

int main(){
    int n;
    cin >> n; //broj na IT prodavnici
    ITStore s[n];
    for(int i=0;i<n;i++){
        cin>>s[i].name>>s[i].location>>s[i].NoLaptops;
        for(int j=0;j<s[i].NoLaptops;j++){
            cin>>s[i].laptops[j].brand>>s[i].laptops[j].display>>s[i].laptops[j].touch>>s[i].laptops[j].price;
        }
    }
    print(s,n);
    //pecatenje na site prodavnici
    najeftina_ponuda(s,n);



    //povik na glavnata metoda

    return 0;
}
