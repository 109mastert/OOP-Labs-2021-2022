#include <iostream>
#include <cstring>

using namespace std;

enum Size{small,family,medium};

class Pizza{
protected:
    char name[20];
    char ingredients[50];
    float basePrice;
public:
    Pizza(char *name,char *ingredients,float basePrice){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->basePrice=basePrice;
    }
    virtual double price()=0;
};

bool operator<(Pizza &p1,Pizza &p2){
    return (p1.price()<p2.price());
}

class FlatPizza:public Pizza{
private:
    Size size;
public:
    FlatPizza(char *name,char *ingredients,float basePrice):Pizza(name,ingredients,basePrice){
        this->size=small;
    }
    FlatPizza(char *name,char *ingredients,float basePrice,Size size):Pizza(name,ingredients,basePrice){
        this->size=size;
    }
    double price(){
        if(size==family)
            return basePrice*1.5;
        else if(size==medium)
            return basePrice*1.3;
        else
            return basePrice*1.1;
    }
    friend ostream &operator<<(ostream &out,FlatPizza &fp){
        out<<fp.name<<": "<<fp.ingredients<<", ";
        if(fp.size==small)
            out<<"small"<<" - "<<fp.price()<<endl;
       /* else if(fp.size==medium)
            out<<"large"<<" - "<<fp.price()<<endl;*/
        else
            out<<"family"<<" - "<<fp.price()<<endl;
        return out;
    }
};

class FoldedPizza:public Pizza{
private:
    bool whiteFlour;
public:
    FoldedPizza(char *name,char *ingredients,float basePrice):Pizza(name,ingredients,basePrice){
        this->whiteFlour=true;
    }
    FoldedPizza(char *name,char *ingredients,float basePrice,bool whiteFlour):Pizza(name,ingredients,basePrice){
        this->whiteFlour=whiteFlour;
    }
    double price(){
        if(whiteFlour)
            return basePrice*1.1;
        else
            return basePrice*1.3;
    }
    void setWhiteFlour(bool wf){
        this->whiteFlour=wf;
    }
    friend ostream &operator<<(ostream &out,FoldedPizza &fp){
        out<<fp.name<<": "<<fp.ingredients<<", ";
        if(fp.whiteFlour)
            out<<"wf - ";
        else
            out<<"nwf - ";
        out<<fp.price()<<endl;
        return out;
    }
};

void expensivePizza(Pizza **p,int n){
    Pizza *max=p[0];
    for(int i=1;i<n;i++){
        if(max->price()<p[i]->price())
            max=p[i];
    }
    FlatPizza *fp = dynamic_cast<FlatPizza*>(max);
    if(fp!=nullptr)
        cout<<*fp<<endl;
    else{
        FoldedPizza *fp1 = dynamic_cast<FoldedPizza *>(max);
        cout<<*fp1<<endl;
    }
}


int main() {
  int test_case;
  char name[20];
  char ingredients[100];
  float inPrice;
  Size size;
  bool whiteFlour;

  cin >> test_case;
  if (test_case == 1) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FlatPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 2) {
    // Test Case FlatPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    int s;
    cin>>s;
    FlatPizza fp(name, ingredients, inPrice, (Size)s);
    cout << fp;

  } else if (test_case == 3) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    cout << fp;
  } else if (test_case == 4) {
    // Test Case FoldedPizza - Constructor, operator <<, price
    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza fp(name, ingredients, inPrice);
    fp.setWhiteFlour(false);
    cout << fp;

  } else if (test_case == 5) {
	// Test Cast - operator <, price
    int s;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp1;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    cin>>s;
    FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
    cout << *fp2;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
    cout << *fp3;

    cin.get();
    cin.getline(name,20);
    cin.getline(ingredients,100);
    cin >> inPrice;
    FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
    fp4->setWhiteFlour(false);
    cout << *fp4;

    cout<<"Lower price: "<<endl;
    if(*fp1<*fp2)
        cout<<fp1->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp1<*fp3)
        cout<<fp1->price()<<endl;
    else cout<<fp3->price()<<endl;

    if(*fp4<*fp2)
        cout<<fp4->price()<<endl;
    else cout<<fp2->price()<<endl;

    if(*fp3<*fp4)
        cout<<fp3->price()<<endl;
    else cout<<fp4->price()<<endl;

  } else if (test_case == 6) {
	// Test Cast - expensivePizza
    int num_p;
    int pizza_type;

    cin >> num_p;
    Pizza **pi = new Pizza *[num_p];
    for (int j = 0; j < num_p; ++j) {

      cin >> pizza_type;
      if (pizza_type == 1) {
        cin.get();
        cin.getline(name,20);

        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << (*fp);
        pi[j] = fp;
      }
      if (pizza_type == 2) {

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp =
            new FoldedPizza (name, ingredients, inPrice);
        if(j%2)
          (*fp).setWhiteFlour(false);
        cout << (*fp);
        pi[j] = fp;

      }
    }

    cout << endl;
    cout << "The most expensive pizza:\n";
    expensivePizza(pi,num_p);


  }
  return 0;
}
