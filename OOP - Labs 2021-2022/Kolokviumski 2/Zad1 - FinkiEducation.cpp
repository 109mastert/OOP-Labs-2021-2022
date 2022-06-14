#include <iostream>
#include <cstring>

using namespace std;

class Book{
protected:
    char ISBN[21];
    char title[51];
    char author[31];
    float price;
public:
    Book(char *ISBN="",char *title="",char *author="",float price=0.0){
        strcpy(this->ISBN,ISBN);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }
    virtual double bookPrice()=0;
    friend ostream &operator<<(ostream &out,Book &b){
        return out<<b.ISBN<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice()<<endl;
    }
};
bool operator>(Book &b1,Book &b2){
    return (b1.bookPrice()>b2.bookPrice());
}
class OnlineBook:public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(char *ISBN="",char *title="",char *author="",float price=0.0,char *url="",int size=0):Book(ISBN,title,author,price){
        this->url= new char[strlen(url)+1];
        strcpy(this->url,url);
        this->size=size;
    }
    OnlineBook(const OnlineBook &ob):Book(ob){
        this->url=new char[strlen(ob.url)+1];
        strcpy(this->url,url);
        this->size=ob.size;
    }
    OnlineBook &operator=(const OnlineBook &ob){
        if(this!=&ob){
            strcpy(this->ISBN,ob.ISBN);
            strcpy(this->title,ob.title);
            strcpy(this->author,ob.author);
            this->price=ob.price;
            delete []url;
            this->url=new char[strlen(ob.url)+1];
            strcpy(this->url,url);
            this->size=ob.size;
        }
        return *this;
    }
    ~OnlineBook(){
        delete []url;
    }
    double bookPrice(){
        if(size>20)
            return price*1.2;
        else
            return price;
    }
     void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    }
};
class PrintBook:public Book{
private:
    float weight;
    bool stock;
public:
    PrintBook(char *ISBN="",char *title="",char *author="",float price=0.0,float weight=0.0,bool stock=false):Book(ISBN,title,author,price){
        this->weight=weight;
        this->stock=stock;
    }
    PrintBook(const PrintBook &pb):Book(pb){
        this->weight=weight;
        this->stock=stock;
    }
    PrintBook &operator=(const PrintBook &pb){
        if(this!=&pb){
            strcpy(this->ISBN,pb.ISBN);
            strcpy(this->title,pb.title);
            strcpy(this->author,pb.author);
            this->price=pb.price;
            this->weight=pb.weight;
            this->stock=pb.stock;
        }
        return *this;
    }
    double bookPrice(){
        if(weight>0.7)
            return price*1.15;
        else
            return price;
    }
    void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    }
};
void mostExpensiveBook (Book** books, int n){
    int ob=0,pb=0,r=0;
    Book *max = books[0];
    for(int i=0;i<n;i++){
        if(max->bookPrice()<books[i]->bookPrice())
            max=books[i];
        if(dynamic_cast<OnlineBook *>(books[i]))
            ob++;
        else if(dynamic_cast<PrintBook *>(books[i]))
            pb++;
    }
    cout<<"Total number of online books: "<<ob<<endl;
    cout<<"Total number of print books: "<<pb<<endl;
    cout<<"The most expensive book is: "<<endl<<*max<<endl;
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}
        cout<<"FINKI-Education"<<endl;
		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
