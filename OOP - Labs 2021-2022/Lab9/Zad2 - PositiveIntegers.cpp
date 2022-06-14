#include <iostream>

using namespace std;

class ArithmeticException{
public:
    void message(){
        cout<<"Division by zero is not allowed"<<endl;
    }
};

class NumbersNotDivisibleException{
private:
    int x;
public:
    NumbersNotDivisibleException(int x){
        this->x=x;
    }
    void message(){
        cout<<"Division by "<<x<<" is not supported"<<endl;
    }
};

class ArrayFullException{
public:
    void message(){
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};

class IndexOutOfBoundsException{
private:
    int indx;
public:
    IndexOutOfBoundsException(int indx){
        this->indx=indx;
    }
    void message(){
        cout<<"Index "<<indx<<" is out of bounds"<<endl;
    }
};

class NumberIsNotPositiveException{
private:
    int x;
public:
    NumberIsNotPositiveException(int x){
        this->x=x;
    }
    void message(){
        cout<<"Number "<<x<<" is not positive integer"<<endl;
    }
};

class PositiveIntegers{
protected:
    int *nums;
    int NoElements;
    int MaxCapacity;
public:
    PositiveIntegers(int MaxCapacity=0){
        this->NoElements=0;
        this->MaxCapacity=MaxCapacity;
        this->nums= new int[NoElements];
        for(int i=0;i<NoElements;i++)
            this->nums[i]=nums[i];
    }
    PositiveIntegers(const PositiveIntegers &pi){
        this->NoElements=pi.NoElements;
        this->MaxCapacity=pi.MaxCapacity;
        this->nums=new int[NoElements];
        for(int i=0;i<NoElements;i++)
            this->nums[i]=pi.nums[i];
    }
    PositiveIntegers &operator+=(int &i){
        if(NoElements==MaxCapacity)
            throw ArrayFullException();
        if(i<=0)
            throw NumberIsNotPositiveException(i);
        int *tmp = new int[NoElements+1];
        for(int j=0;j<NoElements;j++)
            tmp[j]=nums[j];
        tmp[NoElements++]=i;
        delete []nums;
        nums=tmp;
        return *this;
    }
    PositiveIntegers operator*(int i){
        PositiveIntegers p(*this);
        for(int j=0;j<p.NoElements;j++)
            p.nums[j]*=i;
        return p;
    }
    PositiveIntegers operator/(int i){
        if(i==0)
            throw ArithmeticException();
        for(int j=0;j<NoElements;j++){
            if(nums[j]%i!=0)
                throw NumbersNotDivisibleException(i);
        }
        PositiveIntegers pi (*this);
		for (int j=0;j<pi.NoElements;j++)
			pi.nums[j]/=i;
		return pi;
    }
    int operator[](int i){
        if(i<0 || i>NoElements)
            throw IndexOutOfBoundsException(i);
        return nums[i];
    }
    void increaseCapacity(int c){
        this->MaxCapacity+=c;
    }
    void print(){
        cout<<"Size: "<<NoElements<<" Capacity: "<<MaxCapacity<<" Numbers: ";
        for(int i=0;i<NoElements;i++)
            cout<<nums[i]<<" ";
        cout<<endl;
    }
};

int main() {

	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
		try{
            pi+=number;
        }catch(ArrayFullException &a){
            a.message();
        }catch(NumberIsNotPositiveException &n){
            n.message();
        }
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();

	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{
            pi+=number;
		}catch(ArrayFullException &a){
            a.message();
		}catch(NumberIsNotPositiveException &n){
            n.message();
        }
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
	PositiveIntegers pi1;
	cout<<"===TESTING DIVISION==="<<endl;

	try{
        pi1 = pi/0;
        pi1.print(); //tuka treba da bide smeneto, but at the same time i ne
	}catch(ArithmeticException &a){
        a.message();
    }
    try{
        pi1 = pi/1;
        pi1.print(); //tuka treba da bide smeneto, but at the same time i ne
    }catch(NumbersNotDivisibleException &n){
        n.message();
    }
    try{
        pi1 = pi/2;
        pi1.print(); //tuka treba da bide smeneto, but at the same time i ne
    }catch(NumbersNotDivisibleException &n){
        n.message();
    }

	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print(); //tuka treba da bide smeneto, but at the same time i ne
	cout<<"===TESTING [] ==="<<endl;
	try{
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
	}catch(IndexOutOfBoundsException &indx){
        indx.message();
	}
	try{
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
	}catch(IndexOutOfBoundsException &indx){
        indx.message();
	}
	try{
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
	}catch(IndexOutOfBoundsException &indx){
        indx.message();
	}
	try{
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
	}catch(IndexOutOfBoundsException &indx){
        indx.message();
	}
	return 0;
}
