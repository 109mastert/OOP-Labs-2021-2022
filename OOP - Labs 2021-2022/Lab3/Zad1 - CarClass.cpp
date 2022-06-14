#include <iostream>
#include <cstring>
using namespace std;

class person{
private:
    char name[20];
    char surname[20];
public:
    person(char *_name="",char *_surname=""){
        strcpy(name,_name);
        strcpy(surname,_surname);
    }
    ~person(){}
    void print(){
        cout<<name<<" "<<surname<<endl;
    }
};

class date{
private:
    int year,month,day;
public:
    date(int _year=2000, int _month=1, int _day=1){
        year=_year;
        month=_month;
        day=_day;
    }
    void print(){
        cout<<year<<"."<<month<<"."<<day<<endl;
    }
    date(const date &d){
      //  cout<<"Copy constructor called";
        year=d.year;
        month=d.month;
        day=d.day;
    }
};

class Car{
private:
    person owner;
    date bdate;
    float price;
public:
    Car(){}
    Car(person _owner, date _bdate, float _price=0.0){
        owner = _owner;
        bdate=_bdate;
        price=_price;

    }
    void print(){
        owner.print();
        bdate.print();
        cout<<"Price: "<<price<<endl;

    };
    float getPrice(){
        return price;
    }
};
void cheaperThan(Car cars[],int n,int pricelimit){
    for(int i=0;i<n;i++)
    {
        if(cars[i].getPrice()<=pricelimit)
            cars[i].print();
    }
}
int main()
{
    char name[20];
	char lastName[20];
	int year;
	int month;
	int day;
	float price;

	int testCase;
	cin >> testCase;

	if (testCase == 1) {
		cin >> name;
		cin >> lastName;
		person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		date Date(year, month, day);

		cin >> price;
		Car car(lik, Date,  price);

		car.print();
	}
	else if (testCase == 2) {
		cin >> name;
		cin >> lastName;
		person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		date Date(date(year, month, day));

		cin >> price;
		Car car(lik, Date,  price);
		car.print();
	}
	else {
		int numCars;
		cin >> numCars;

		Car cars[10];
		for (int i = 0; i < numCars; i++) {
			cin >> name;
			cin >> lastName;
			person lik(name, lastName);

			cin >> year;
			cin >> month;
			cin >> day;
			date Date(year, month, day);

			cin >> price;
			cars[i] = Car(lik, Date,  price);
		}
        float priceLimit;
        cin >> priceLimit;
		cheaperThan(cars, numCars, priceLimit);
	}
    return 0;
}
