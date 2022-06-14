#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

enum typeC{
    standard,loyal,vip
};

class UserExistsException{
public:
    void message(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer{
protected:
    char name[51];
    char email[51];
    typeC type;
    float baseDiscount;
    float AddedDiscount;
    int NoProducts;
    static float BD;
    static float AD;

    void copy(const Customer &c){
        strcpy(this->name,c.name);
        strcpy(this->email,c.email);
        this->type=c.type;
        this->NoProducts=c.NoProducts;
        this->baseDiscount=c.baseDiscount;
        this->AddedDiscount=c.AddedDiscount;
    }
public:
    Customer(){
        strcpy(this->name,"");
        strcpy(this->email,"");
        this->type=standard;
        this->baseDiscount=0;
        this->AddedDiscount=0;
        this->NoProducts=0;
    }
    Customer(char *name,char *email,typeC type,int NoProducts){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->type=type;
        this->NoProducts=NoProducts;
        if(type==loyal){
            this->baseDiscount=10;
            this->AddedDiscount=0;
        }
        else if(type=vip){
            this->baseDiscount=10;
            this->AddedDiscount=AD;
        }
        else{
            this->baseDiscount=0;
            this->AddedDiscount=0;
        }
    }
    Customer(const Customer &c){
        copy(c);
    }
    Customer &operator=(const Customer &c){
        if(this!=&c){
            copy(c);
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,const Customer &c){
        out<<c.name<<endl<<c.email<<endl<<c.NoProducts<<endl;
        if(c.type==standard)
            out<<"standard 0"<<endl;
        else if(c.type==loyal)
            out<<"loyal "<<c.baseDiscount+c.AddedDiscount<<endl;
        else
            out<<"vip "<<c.baseDiscount+c.AddedDiscount<<endl;
        return out;
    }
    void setDiscount1(int discount){
        BD=discount;
        this->baseDiscount=discount;
    }
    char *getEmail(){
        return email;
    }
    void setType(typeC type){
        this->type=type;
        if(type==loyal){
            this->baseDiscount=BD;
            this->AddedDiscount=0;
        }
        else{
            this->baseDiscount=BD;
            this->AddedDiscount=AD;
        }
    }
    int getNoProducts(){
        return NoProducts;
    }
    typeC getType(){
        return type;
    }
};
float Customer::BD=10;
float Customer::AD=20;

class FINKI_bookstore{
private:
    Customer *customer;
    int NoCustomers;
public:
    FINKI_bookstore(){
        this->NoCustomers=0;
        this->customer=new Customer[0];
    }
    FINKI_bookstore(Customer *customer,int NoCustomers){
        this->NoCustomers=NoCustomers;
        this->customer = new Customer[NoCustomers];
        for(int i=0;i<NoCustomers;i++)
            this->customer[i]=customer[i];
    }
    void setCustomers(Customer *c, int n){
        this->NoCustomers=n;
        this->customer= new Customer[n];
        for(int i=0;i<NoCustomers;i++)
            this->customer[i]=c[i];
    }
    FINKI_bookstore &operator+=(Customer &c){
        for(int i=0;i<NoCustomers;i++){
            if(strcmp(customer[i].getEmail(),c.getEmail())==0)
                throw UserExistsException();
        }
        Customer *tmp = new Customer [NoCustomers+1];
        for(int i=0;i<NoCustomers;i++)
            tmp[i]=customer[i];
        tmp[NoCustomers++]=c;
        delete []customer;
        customer=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const FINKI_bookstore &fb){
        for(int i=0;i<fb.NoCustomers;i++){
            out<<fb.customer[i];
        }
        return out;
    }
    void update(){
        for(int i=0;i<NoCustomers;i++){
            if(customer[i].getNoProducts()>5 && customer[i].getType()==standard)
                customer[i].setType(loyal);
            else if(customer[i].getNoProducts()>10 && customer[i].getType()==loyal)
                customer[i].setType(vip);
        }
    }
};


//23 51  -- 00 41
int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;

    Customer c(name,email,(typeC)tC,numProducts);
    try{
        fc+=c;
    }
    catch(UserExistsException &uee){
        uee.message();
    }


    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
