#include <iostream>
#include <cstring>

using namespace std;

class List{
private:
    int *listnums;
    int NoNumbers;

    void copy(const List &other){
        this->NoNumbers=other.NoNumbers;
        this->listnums= new int[NoNumbers];
        for(int i=0;i<NoNumbers;i++){
            listnums[i]=other.listnums[i];
        }
    }
public:
    List(){
        this->listnums=new int[0];
        NoNumbers=0;
    }
    List(int *li,int NoNumbers){
        this->NoNumbers=NoNumbers;
        this->listnums= new int[NoNumbers];
        for(int i=0;i<NoNumbers;i++){
            listnums[i]=li[i];
        }
    }
    List(const List & other){
        copy(other);
    }
    ~List(){
        delete [] listnums;
    }
    List & operator=(const List & other){
        if(this!=&other){
            delete [] listnums;
            copy(other);
        }
        return *this;
    }
    void print(){
        int sum=0; float avg;
        cout<<NoNumbers<<": ";
        for(int i=0;i<NoNumbers;i++){
            cout    <<listnums[i]<<" ";
            sum+=listnums[i];
        }
        cout<<"sum: "<<this->sum()<<" average: "<<this->average()<<endl;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<NoNumbers;i++)
            sum+=listnums[i];
        return sum;
    }
    double average(){
        return (double)this->sum()/NoNumbers;
    }
    int getNoNumbers(){
        return NoNumbers;
    }
};
class ListContainer{
private:
    List *lists;
    int NoLists;
    int tries;
    void copy(const ListContainer & other){
        this->NoLists=other.NoLists;
        this->lists= new List[NoLists];
        for(int i=0;i<NoLists;i++){
            this->lists[i]=other.lists[i];
        }
        this->tries=other.tries;
    }
public:
    ListContainer(){
        NoLists=0;
        this->lists = new List[0];
        tries=0;
    }
    ListContainer(List *lists,int NoLists, int tries=0){
        this->NoLists=NoLists;
        this->lists= new List[NoLists];
        for(int i=0;i<NoLists;i++){
            this->lists[i]=lists[i];
        }
    }
    ListContainer(const ListContainer & other){
        copy(other);
    }
    ListContainer & operator=(const ListContainer & other){
        if(this!=&other){
            delete [] lists;
            copy(other);
        }
        return *this;
    }
    ~ListContainer(){
        delete [] lists;
    }
    void print(){
        if(NoLists>0)
        {
            for(int i=0;i<NoLists;i++)
            {
                if(lists[i].getNoNumbers()!=0)
                {
                    cout<<"List number: "<<i+1<<" List info: ";
                    lists[i].print();
                }
                else
                    cout<<"The list is empty"<<endl;
            }
            cout<<"Sum: "<<this->sum()<<" Average: "<<this->average()<<endl;
            cout<<"Successful attempts: "<<NoLists<<" Failed attempts: "<<tries-NoLists<<endl;
        }
        else
            cout<<"The list is empty"<<endl;

    }
    void addNewList(List l){
        tries++;
        if(NoLists!=0){
            for(int i=0;i<NoLists;i++){
                if(l.sum()==lists[i].sum())
                    return;
            }
            List *tmp = new List[++NoLists];
            for(int i=0;i<NoLists-1;i++)
                tmp[i]=lists[i];
            tmp[NoLists-1]=l;
            delete []lists;
            lists=tmp;
            }
            else{
                delete []lists;
                lists = new List[++NoLists];
                lists[0]=l;
            }
    }
    int sum(){
        int sum=0;
        for(int i=0;i<NoLists;i++){
            sum+=lists[i].sum();
        }
        return sum;
    }
    double average(){
        int elements;
        for(int i=0;i<NoLists;i++)
            elements+=lists[i].getNoNumbers();
        return (double)this->sum()/(double)elements;
    }
};

int main() {
	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		cin>>n;
		for (int j=0;j<n;j++){
			cin>>niza[j];
		}
		List l=List(niza,n);
		lc.addNewList(l);
	}
    int testCase;
    cin>>testCase;
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
    }
    else {
        lc.print();
    }
    return 0;
}
