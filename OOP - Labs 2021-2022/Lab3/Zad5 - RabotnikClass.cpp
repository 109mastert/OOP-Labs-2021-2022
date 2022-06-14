#include <iostream>
#include <cstring>
using namespace std;

class Rabotnik{
private:
    char name[31];
    char surname[31];
    int salary;
public:
    Rabotnik(char *name="",char *surname="",int salary=0){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary=salary;
    }
    ~Rabotnik(){}
    void setName(char *name){
        strcpy(this->name,name);
    }
    void setSurname(char *surname){
        strcpy(this->surname,surname);
    }
    void setSalary(int salary){
        this->salary=salary;
    }
    int getSalary(){
        return salary;
    }
    void print(){
        cout<<name<<" "<<surname<<" "<<salary<<endl;
    }
};
class Fabrika{
private:
    Rabotnik r[100];
    int employees;
public:
    Fabrika(Rabotnik r[], int employees){
        this->employees=employees;
        for(int i=0;i<this->employees;i++){
            this->r[i]=r[i];
        }
    }
    ~Fabrika(){}
    void printEmployees(){
        cout<<"Site vraboteni:"<<endl;
        for(int i=0;i<employees;i++)
        {
            r[i].print();
        }
    }
    void printEmployeesbySalary(int salary){
        cout<<"Vraboteni so plata povisoka od "<<salary<<" :"<<endl;
        for(int i=0;i<employees;i++)
        {
            if(r[i].getSalary()>salary)
                r[i].print();
        }
    }
};

int main()
{
    int n,salary,lowsalary;
    char name[31],surname[31];
    cin>>n;
    Rabotnik r[n];
    for(int i=0;i<n;i++){
        cin>>name>>surname>>salary;
        r[i].setName(name);
        r[i].setSurname(surname);
        r[i].setSalary(salary);
    }
    cin>>lowsalary;
    Fabrika f(r,n);
    f.printEmployees();
    f.printEmployeesbySalary(lowsalary);
    return 0;
}
