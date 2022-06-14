#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

class ComplexNumber{
private:
    float real;
    float imaginary;

    void copy(const ComplexNumber &cn){
        this->real=cn.real;
        this->imaginary=cn.imaginary;
    }
public:
    ComplexNumber(float real=0.0,float imaginary=0.0){
        this->real=real;
        this->imaginary=imaginary;
    }
    ComplexNumber(const ComplexNumber &cn){
        copy(cn);
    }
    ComplexNumber &operator=(const ComplexNumber &cn){
        if(this!=&cn){
            copy(cn);
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, const ComplexNumber &cn){
        if(cn.real==0){
            out<<cn.imaginary<<"i"<<endl;
        }
        else if(cn.imaginary==0){
            out<<cn.real<<endl;
        }
        else
            out<<cn.real<<"+"<<cn.imaginary<<"i"<<endl;
        return out;
    }
    ComplexNumber operator+(const ComplexNumber &other){
        ComplexNumber n(this->real+other.real,this->imaginary+other.imaginary);
        return n;
    }
    ComplexNumber operator-(const ComplexNumber &other){
        ComplexNumber n(this->real-other.real,this->imaginary-other.imaginary);
        return n;
        //might need abs possibly
    }
    ComplexNumber operator*(const ComplexNumber &other){
        ComplexNumber n(this->real*other.real,this->imaginary*other.imaginary);
        return n;
    }
    ComplexNumber operator/(const ComplexNumber &other){
        ComplexNumber n(this->real/other.real,this->imaginary/other.imaginary);
        return n;
    }
    bool operator==(const ComplexNumber &other){
        if(this->real==other.real && this->imaginary==other.imaginary)
            return true;
        return false;
    }
    bool operator>(ComplexNumber &other){
        if(this->real>other.real)
            return true;
        else if(this->real==other.real)
        {
            if(this->imaginary>=other.imaginary)
                return true;
            else
                return false;
        }
        return false;
    }
     bool operator<(ComplexNumber &other){
        if(this->real<other.real)
            return true;
        else if(this->real==other.real)
        {
            if(this->imaginary<=other.imaginary)
                return true;
            else
                return false;
        }
        return false;
    }
    void setReal(float r){
        this->real=r;
    }
    void setImaginary(float i){
        this->imaginary=i;
    }
    double module(){
        return sqrt(pow(real, 2) + pow(imaginary, 2));
    }

};
class Equation{
private:
    ComplexNumber *xn;
    char *operators;
public:
    Equation(){
       // cout<<"constructor called";
    }
    friend istream& operator>>(istream &in,Equation &eq){
        char c='.';         //ultra suspicious
        float r,im;
        int n=1;
        eq.xn= new ComplexNumber[n];
        eq.operators = new char[n+1];
        ComplexNumber pom,final;
        for(int i=0;c!='=';i++){
            in>>r>>im;
            in>>c;
            eq.xn[i].setReal(r);eq.xn[i].setImaginary(im);
            eq.operators[i]=c;
            if(eq.operators[i]=='='){
                return in;
            }
            else{
                ComplexNumber *temp = new ComplexNumber[++n];
                char *tmp = new char[n+1];
                for(int j=0;j<n-1;j++){
                    temp[j]=eq.xn[j];
                    tmp[j]=eq.operators[j];
                }
                delete []eq.xn;
                delete []eq.operators;
                eq.xn=temp;
                eq.operators=tmp;
            }
        }
        return in;
    }
    ComplexNumber result(){
        ComplexNumber res=xn[0];
        for(int i=0;i<strlen(operators);i++){
            switch(operators[i]){
                case '+':
                    res=(res+xn[i+1]);
                    break;
                case '-':
                    res=(res-xn[i+1]);
                    break;
                case '*':
                    res=(res*xn[i+1]);
                    break;
                case '/':
                    res=(res/xn[i+1]);
                    break;
                default:
                    return res;
            }
        }
    }
    double sumModules(){
        float sum=0.0;
        for(int i=0;i<strlen(operators)-1;i++){
            sum+=xn[i].module();
        }
        return sum;
    }
};



int main() {
	int testCase;
	double real, imaginary;
	ComplexNumber first, second, result;
   // cout<<first;*/
	cin >> testCase;

	if (testCase <= 8) {
		cin >> real;
		cin >> imaginary;
		first = ComplexNumber(real, imaginary);
		cin >> real;
		cin >> imaginary;
		second = ComplexNumber(real, imaginary);
	}

	if (testCase == 1) {
		cout << "===== OPERATOR + =====" << endl;
		result = first + second;
		cout << result;
	}
	else if (testCase == 2) {
		cout << "===== OPERATOR - =====" << endl;
		result = first - second;
		cout << result;
	}
	else if (testCase == 3) {
		cout << "===== OPERATOR * =====" << endl;
		result = first * second;
		cout << result;
	}
	else if (testCase == 4) {
		cout << "===== OPERATOR / =====" << endl;
		result = first / second;
		cout << result;
	}
	else if (testCase == 5) {
		cout << "===== OPERATOR == =====" << endl;
		cout << first;
		cout << second;
		if (first == second)
			cout << "EQUAL" << endl;
		else
			cout << "NOT EQUAL" << endl;
	}
	else if (testCase == 6) {
		cout << "===== OPERATOR > =====" << endl;
		cout << first;
		cout << second;
		if (first > second)
			cout << "FIRST GREATER THAN SECOND" << endl;
		else
			cout << "FIRST LESSER THAN SECOND" << endl;
	}
	else if (testCase == 7) {
		cout << "===== OPERATOR < =====" << endl;
		cout << first;
		cout << second;
		if (first < second)
			cout << "FIRST LESSER THAN SECOND" << endl;
		else
			cout << "FIRST GREATER THAN SECOND" << endl;
	}
	else if (testCase == 8) {
		cout << "===== MODULE =====" << endl;
		double module = first.module();
		cout << first;
		cout << "Module: " << module << endl;
		cout << second;
		module = second.module();
		cout << "Module: " << module << endl;
	}
	else if (testCase == 9) {
		cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
		Equation equation;
		cin >> equation;
		cout << equation.sumModules();
	}
	else if (testCase == 10) {
		cout << "===== EQUATION RESULT =====" << endl;
		Equation equation;
		cin >> equation;
		result = equation.result();
		cout << result;
	}
	return 0;
}
