#include<iostream>
#include<cstring>
using namespace std;

class Category{
private:
    char name[21];
public:
    Category(char *name="unnamed"){
        strcpy(this->name,name);
    }
  /*  Category(const Category &c){
        strcpy(this->name,c.name);
       // cout<<"Copy constructor for category called"<<endl; za proba samo
    }*/
    ~Category(){}
    void print(){
        cout<<"Category: "<<name<<endl;
    }
};

class NewsArticle{
private:
    Category category;
    char title[31];
public:
    NewsArticle(){ //default konstruktor bez argumenti, za da moze da se kreira newsarticle bez argumenti pr NewsArticle a
        strcpy(this->title,"untitled");
    }
    NewsArticle(Category c, char *title="untitled"){
        this->category=c;
        strcpy(this->title,title);
    }
    void print(){
        cout<<"Article title: "<<title<<endl;
        category.print();
    }
};

class FrontPage{
private:
    NewsArticle article;
    float price;
    int editionNumber;
public:
    FrontPage(){ //za da moze da se povika kreiranje na objekt bez elementi
        this->price=0.0;
        this->editionNumber=0;
    }
    FrontPage(NewsArticle article,float price=0.0, int editionNumber=0){
        this->article=article;
        this->price=price;
        this->editionNumber=editionNumber;
    }
    ~FrontPage(){}
    void print(){
        cout<<"Price: "<<this->price<<", Edition number: "<<this->editionNumber<<endl;
        article.print();
    }
};

int main() {
	char categoryName[20];
	char articleTitle[30];
	float price;
	int editionNumber;

	int testCase;
	cin >> testCase;


	if (testCase == 1) {
		int iter;
		cin >> iter;
		while (iter > 0) {
			cin >> categoryName;
			cin >> articleTitle;
			cin >> price;
			cin >> editionNumber;
			Category category(categoryName);
			NewsArticle article(category, articleTitle);
			FrontPage frontPage(article, price, editionNumber);
			frontPage.print();
			iter--;
		}
	}
	else if (testCase == 2) {
		cin >> categoryName;
		cin >> price;
		cin >> editionNumber;
		Category category(categoryName);
		NewsArticle article(category);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}// test case 3
	else if (testCase == 3) {
		cin >> categoryName;
		cin >> articleTitle;
		cin >> price;
		Category category(categoryName);
		NewsArticle article(category, articleTitle);
		FrontPage frontPage(article, price);
		frontPage.print();
	}
    else {
    	FrontPage frontPage = FrontPage();
        frontPage.print();
    }
	return 0;
}
