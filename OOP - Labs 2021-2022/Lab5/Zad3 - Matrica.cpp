#include <iostream>

using namespace std;
class Matrica{
private:
    float a[10][10];
    int rows,columns;
public:
    Matrica(int rows=0,int columns=0){
        this->rows=rows;
        this->columns=columns;
    }
    Matrica &operator+(int num){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++)
                a[i][j]+=num;
        }
        return *this;
    }
     Matrica &operator-(Matrica &other){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++)
                a[i][j]-=other.a[i][j];
        }
        return *this;
    }
    Matrica &operator*(Matrica &other){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++)
                a[i][j]*=other.a[i][j];
        }
        return *this;
    }
    friend istream &operator>>(istream &in, Matrica &m){
        in>>m.rows>>m.columns;
        for(int i=0;i<m.rows;i++){
            for(int j=0;j<m.columns;j++)
                in>>m.a[i][j];
        }
        return in;
    }
    friend ostream &operator<<(ostream &out, Matrica &m){
        for(int i=0;i<m.rows;i++){
            for(int j=0;j<m.columns;j++)
                out<<m.a[i][j]<<" ";
            out<<endl;
        }
        return out;
    }
};
int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    cout<<((A-(B*C)+2));
  //  cout<<(B+3);
   /* cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;*/
//    cout<<R;
}
