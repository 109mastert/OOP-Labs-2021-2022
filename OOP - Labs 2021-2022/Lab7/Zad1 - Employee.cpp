#include <iostream>
#include <cstring>

using namespace std;

class Employee{
protected:
    char name[50];
    int years;
    int xp;
public:
    Employee(char *name="",int years=0,int xp=0){
        strcpy(this->name,name);
        this->years=years;
        this->xp=xp;
    }
    virtual double plata()=0;
    virtual double bonus(){
        return 0;
    }
    int getYears(){
        return years;
    }
    virtual ~Employee(){}
};
bool operator == (Employee &emp1, Employee &emp2) {
  return emp1.getYears() == emp2.getYears()&&emp1.bonus() == emp2.bonus();
}
class SalaryEmployee:public Employee{
private:
    double baseSalary;
    static int No;
public:
    SalaryEmployee(char *name="",int years=0,int xp=0,double baseSalary=0):Employee(name,years,xp){
        this->baseSalary=baseSalary;
        No++;
    }
    static int getStatic(){
        return No;
    }
    double bonus(){
        return (baseSalary*xp)/100.0;
    }
    double plata(){
        return baseSalary+bonus();
    }
};
int SalaryEmployee::No=0;

class HourlyEmployee:public Employee{
private:
    int hours;
    int pph; //pay per hour
    static int No;
public:
    HourlyEmployee(char *name="",int years=0,int xp=0,int hours=0,int pph=0):Employee(name,years,xp){
        this->hours=hours;
        this->pph=pph;
        No++;
    }
    static int getStatic(){
        return No;
    }
    double plata(){
        return hours*pph+bonus();
    }
    double bonus(){
        if(hours>320){
            return (hours-320)*(pph*0.5);
        }
        else
            return 0;
    }
};
int HourlyEmployee::No=0;
class Freelancer:public Employee{
private:
    int NoProjects;
    double sums[];
    static int No;
public:
    Freelancer(char *name,int years,int xp,int NoProjects,double sums[]):Employee(name,years,xp){
        this->NoProjects=NoProjects;
        for(int i=0;i<NoProjects;++i)
            this->sums[i]=sums[i];
        No++;
    }
    static int getStatic(){
        return No;
    }
    double plata(){
        double sum=0.0;
        for(int i=0;i<NoProjects;++i){
            sum+=sums[i];
        }
        return sum+bonus();
    }
    double bonus(){
        if(NoProjects>5){
            return (NoProjects-5)*1000.0;
        }
        else
            return 0;
    }
};
int Freelancer::No=0;
class Company{
private:
    char name[50];
    int NoEmployees;
    Employee **e;
public:
    Company(char *name=""){
        strcpy(this->name,name);
        NoEmployees=0;
        e= new Employee *[0];
    }
    Company & operator += (Employee *emp) {
    Employee ** tmp = new Employee*[NoEmployees + 1];
    for (int i=0; i < NoEmployees; ++i) {
      tmp[i] = e[i];
    }
    tmp[NoEmployees++] = emp;
    delete [] e;
    e = tmp;
    return * this;
  }
    double vkupnaPlata(){
        double sum=0;
        for(int i=0;i<NoEmployees;++i){
            sum+=e[i]->plata();
        }
        return sum;
    }
    double filtriranaPlata(Employee * emp){
        double sum=0.0;
        for(int i=0;i<NoEmployees;++i){
            if(*emp==*e[i])
                sum+=e[i]->plata();
        }
        return sum;
    }
    void pecatiRabotnici(){
        cout << "Vo kompanijata " << name << " rabotat:" <<endl;
        cout << "Salary employees: " << SalaryEmployee::getStatic() << endl;
        cout << "Hourly employees: " << HourlyEmployee::getStatic() << endl;
        cout << "Freelancers: " << Freelancer::getStatic() << endl;
    }
    ~Company() {
    for (int i=0; i < NoEmployees; ++i) {
            delete e[i];
        }
        delete []e;
    }
};
int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
      cin >> type;
      cin >> employeeName >> age >> experience;

      if (type == 1) {
        int basicSalary;
        cin >> basicSalary;
        c += new SalaryEmployee(employeeName, age, experience, basicSalary);
      }

      else if (type == 2) {
        int hoursWorked;
        int hourlyPay;
        cin >> hoursWorked >> hourlyPay;
        c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
      }

      else {
        int numProjects;
        cin >> numProjects;
        double projects[10];
        for (int i=0; i < numProjects; ++i) {
          cin >> projects[i];
        }
        c += new Freelancer(employeeName, age, experience, numProjects, projects);
      }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}
