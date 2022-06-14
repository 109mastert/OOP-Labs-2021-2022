#include<iostream>
using namespace std;

class Number {
    public:
    virtual double doubleValue()=0;
    virtual int intValue()=0;
    virtual void print()=0;
};

bool operator==(Number &n1,Number &n2){
    return (n1.intValue()==n2.intValue()&&n1.doubleValue()==n2.doubleValue());
}

class Integer:public Number{
private:
    int x;
public:
    Integer(int x=0){
        this->x=x;
    }
    int intValue(){
        return x;
    }
    double doubleValue(){
        return (double)x;
    }
    void print(){
        cout<<"Integer: "<<x<<endl;
    }
};

class Double:public Number{
private:
    double x;
public:
    Double(double x=0.0){
        this->x=x;
    }
    int intValue(){
        return (int)x;
    }
    double doubleValue(){
        return x;
    }
    void print(){
        cout<<"Double: "<<x<< endl;
    }
};

class Numbers{
private:
    int NoNums;
    Number **num;
public:
    Numbers(){
        this->NoNums=0;
        num = new Number *[0];
    }
    Numbers(const Numbers &n){
        this->NoNums=n.NoNums;
        for(int i=0;i<NoNums;i++){
            this->num[i]=n.num[i];
        }
    }
    Numbers &operator=(const Numbers n){
        if(this!=&n){
            this->NoNums=n.NoNums;
            for(int i=0;i<NoNums;i++){
                this->num[i]=n.num[i];
        }
        }
        return *this;
    }
    ~Numbers(){
        for(int i=0;i<NoNums;i++)
            delete [] num[i];
        delete []num;
    }
    Numbers &operator+=(Number *n){
        bool ima=false;
        for(int i=0;i<NoNums;i++){
            if(num[i]==n){
                ima=true;
                break;
            }
        }
        if(!ima){
            Number **tmp = new Number *[NoNums+1];
            for(int i=0;i<NoNums;i++)
                tmp[i]=num[i];
            tmp[NoNums++]=n;
            delete []num;
            num=tmp;
        }
        return *this;
    }
    int intNums(){
        int sum=0;
        for(int i=0;i<NoNums;i++){
            if(dynamic_cast<Integer*>(num[i]))
                sum++;
        }
        return sum;
    }
    int intSum(){
        int sum=0;
        for(int i=0;i<NoNums;i++){
            if(dynamic_cast<Integer*>(num[i]))
                sum+=num[i]->intValue();
        }
        return sum;
    }
    double doubleSum(){
        double sum=0.0;
        for(int i=0;i<NoNums;i++){
            if(dynamic_cast<Double*>(num[i]))
                sum+=num[i]->doubleValue();
        }
        return sum;
    }
    void statistics(){
        cout<<"Count of numbers: "<<NoNums<<endl;
        cout<<"Sum of all numbers: "<<intSum()+doubleSum()<<endl;
        cout<<"Count of integer numbers: "<<intNums()<<endl;
        cout<<"Sum of integer numbers: "<<intSum()<<endl;
        cout<<"Count of double numbers: "<<NoNums-intNums()<<endl;
        cout<<"Sum of double numbers: "<<doubleSum()<<endl;
    }

    void integersLessThan(Integer n){
       bool nema=true;
        for(int i=0;i<NoNums;i++){
            if(dynamic_cast<Integer*>(num[i])){
                if((num[i]->intValue()) < n.intValue()){
                    num[i]->print();
                    nema=false;
                }
            }
        }
        if(nema)
            cout<<"None"<<endl;
    }
    void doublesBiggerThan (Double n){
        bool nema=true;
        for(int i=0;i<NoNums;i++){
            if(dynamic_cast<Double*>(num[i])){
                if((num[i]->doubleValue()) > n.doubleValue()){
                    num[i]->print();
                    nema=false;
                }
            }
        }
        if(nema)
            cout<<"None"<<endl;
    }

};

int main() {

	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}

	int lessThan;
	double biggerThan;

	cin>>lessThan;
	cin>>biggerThan;

	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));

	return 0;
}
