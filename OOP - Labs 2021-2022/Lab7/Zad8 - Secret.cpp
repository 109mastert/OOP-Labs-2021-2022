#include<cstring>
#include<iostream>

using namespace std;

class Secret{
public:
    virtual double simpleEntropy()=0;
    virtual int total()=0;
};

bool operator==(Secret &s1,Secret &s2){
    return (s1.simpleEntropy()==s2.simpleEntropy() && s1.total()==s2.total());
}
bool operator!=(Secret &s1,Secret &s2){
    return (s1.simpleEntropy()!=s2.simpleEntropy() && s1.total()!=s2.total());
}
class DigitSecret:public Secret{
private:
    int arr[100];
    int size;
public:
    DigitSecret(int arr[]={0},int size=0){
        this->size=size;
        for(int i=0;i<size;i++)
            this->arr[i]=arr[i];
    }

    double simpleEntropy(){
        int c=0,j;
        for(int i=0;i<size;i++){
            for(j=0;j<size;j++){
                if(i!=j && arr[i]==arr[j])
                    break;
            }
            if(j==size)
                c++;
        }
        return (double)c/size;
    }
    int total(){
        return size;
    }
    friend ostream &operator<<(ostream &out,DigitSecret &ds){
        for(int i=0;i<ds.size;i++)
            out<<ds.arr[i];
        out<<" Simple entropy: "<<ds.simpleEntropy()<<" Total: "<<ds.total();
        return out;
    }
};

class CharSecret:public Secret{
private:
    char arr[101];
    int size;
public:
    CharSecret(char *arr=""){
        this->size=strlen(arr);
        for(int i=0;i<this->size;i++){
            this->arr[i]=arr[i];
        }
        this->arr[size]='\0';
    }
    double simpleEntropy(){
        int c=0,j;
        for(int i=0;i<size;i++){
            for(j=0;j<size;j++){
                if(i!=j && arr[i]==arr[j])
                    break;
            }
            if(j==size)
                c++;
        }
        return (double)c/size;
    }
    int total(){
        return size;
    }
    friend ostream &operator<<(ostream &out,CharSecret &c){
        for(int i=0;i<c.size;i++)
            out<<c.arr[i];
        out<<" Simple entropy: "<<c.simpleEntropy()<<" Total: "<<c.total();
        return out;
    }
};

void process(Secret ** secrets, int n){
    Secret *max=secrets[0];
    for(int i=1;i<n;i++){
        if(max->simpleEntropy()<secrets[i]->simpleEntropy())
            max=secrets[i];
    }
    if(dynamic_cast<CharSecret*>(max)){
            CharSecret *cs=dynamic_cast<CharSecret*>(max);
            cout<<*cs<<endl;
        }
    else if(dynamic_cast<DigitSecret*>(max)){
        DigitSecret *ds=dynamic_cast<DigitSecret*>(max);
        cout<<*ds<<endl;
    }
}

void printAll (Secret ** secrets, int n){
    for(int i=0;i<n;i++){
        if(dynamic_cast<CharSecret*>(secrets[i])){
            CharSecret *cs=dynamic_cast<CharSecret*>(secrets[i]);
            cout<<*cs<<endl;
        }
        if(dynamic_cast<DigitSecret*>(secrets[i])){
            DigitSecret *ds=dynamic_cast<DigitSecret*>(secrets[i]);
            cout<<*ds<<endl;
        }
    }
}


int main() {
    int n;
    cin >> n;
    if(n == 0) {
		cout << "Constructors" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
  		cout << "operator <<" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
  		cout << "== and !=" << endl;
		int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
  		cout << "Secret processor" << endl;
		int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
		int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
		int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
		int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }

    return 0;
}
