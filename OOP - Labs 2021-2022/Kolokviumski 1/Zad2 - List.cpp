#include <iostream>
#include <cstring>

using namespace std;

class List{
private:
    int *list;
    int NoNums;

    void copy(const List &l){
        this->NoNums=l.NoNums;
        this->list = new int[NoNums];
        for(int i=0;i<NoNums;i++){
            this->list[i]=l.list[i];
        }
    }
public:
    List(){
        this->list=new int[0];
        NoNums=0;
    }
    List(int *list,int NoNums){
        this->NoNums=NoNums;
        this->list = new int[NoNums];
        for(int i=0;i<NoNums;i++){
            this->list[i]=list[i];
        }
    }
    List(const List & l){
        copy(l);
    }
    List &operator=(const List &l){
        if(this!=&l){
            delete []list;
            copy(l);
        }
        return *this;
    }
    ~List(){
        delete []list;
    }
    int getNoNums(){
        return NoNums;
    }
    void pecati(){
        cout<<NoNums<<": ";
        for(int i=0;i<NoNums;i++){
            cout<<list[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<NoNums;i++){
            sum+=list[i];
        }
        return sum;
    }
    double average(){
        return (double)sum()/NoNums;
    }
};
class ListContainer{
private:
    List *lists;
    int NoLists;
    int tries;
    void copy(const ListContainer &lc){
        this->NoLists=lc.NoLists;
        this->lists=new List[NoLists];
        for(int i=0;i<NoLists;i++){
            this->lists[i]=lc.lists[i];
        }
        this->tries=lc.tries;
    }
public:
    ListContainer(){
        NoLists=0;
        this->lists=new List[NoLists];
        tries=0;
    }
    ListContainer(List *lists, int NoLists){
        this->NoLists=NoLists;
        this->lists=new List[NoLists];
        for(int i=0;i<NoLists;i++){
            this->lists[i]=lists[i];
        }
        this->tries=0;
    }
    ListContainer(const ListContainer &lc){
        copy(lc);
    }
    ListContainer &operator=(const ListContainer &lc){
        if(this!=&lc){
            delete []lists;
            copy(lc);
        }
        return *this;
    }
    ~ListContainer(){
        delete []lists;
    }
    void print(){
        if(NoLists!=0){
            for(int i=0;i<NoLists;i++){
                cout<<"List number: "<<i+1<<" List info: ";
                lists[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<NoLists<<" Failed attempts: "<<tries-NoLists<<endl;
        }
        else
            cout<<"The list is empty"<<endl;

    }
    void addNewList(List l){
        tries++;
        for(int i=0;i<NoLists;i++){
            if(lists[i].sum()==l.sum())
                return;
        }
        List *tmp = new List[++NoLists];
        for(int i=0;i<NoLists-1;i++)
            tmp[i]=lists[i];
        tmp[NoLists-1]=l;
        delete []lists;
        lists=tmp;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<NoLists;i++)
            sum+=lists[i].sum();
        return sum;
    }
    double average(){
        int elements=0;
        for(int i=0;i<NoLists;i++)
            elements+=lists[i].getNoNums();
        return (double)sum()/elements;
    }

};

int main(){
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
