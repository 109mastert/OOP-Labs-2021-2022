#include <iostream>
#include <cstring>

using namespace std;
enum extension{pdf=0,txt,exe};

class File{
private:
    char *name;
    extension ext;
    char *owner;
    int size;
    void copy(const File &f){
        this->name=new char[strlen(f.name)+1];
        strcpy(this->name,f.name);
        this->owner= new char[strlen(f.owner)+1];
        strcpy(this->owner,f.owner);
        this->ext=f.ext;
        this->size=f.size;
    }
public:
    File(char *name="",char *owner="",int size=0,extension ext=pdf){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->owner= new char[strlen(owner)+1];
        strcpy(this->owner,owner);
        this->ext=ext;
        this->size=size;
    }
    File(const File &f){
        copy(f);
    }
    File &operator=(const File &f){
        if(this!=&f){
            delete []name;
            delete []owner;
            copy(f);
        }
        return *this;
    }
    ~File(){
        delete []name;
        delete []owner;
    }
    void print(){
        cout<<"File name: "<<name<<".";
        if(ext==0)
            cout<<"pdf";
        else if(ext==1)
            cout<<"txt";
        else if(ext==2)
            cout<<"exe";
        cout<<"\nFile owner: "<<owner<<"\nFile size: "<<size<<endl;
    }
    bool equals(const File & that){
        if(strcmp(this->name,that.name)==0){
            if(strcmp(this->owner,that.owner)==0){
                if(this->ext==that.ext)
                    return true;
            }
        }
        return false;
    }
    bool equalsType(const File & that){
        if(this->ext==that.ext)
            return true;
        return false;
    }
};
class Folder{
private:
    char *name;
    int NoFiles;
    File *file;

    void copy(const Folder &f){
        this->name=new char[strlen(f.name)+1];
        strcpy(this->name,f.name);
        this->NoFiles=f.NoFiles;
        this->file=new File[NoFiles];
        for(int i=0;i<NoFiles;i++)
            file[i]=f.file[i];
    }
public:
    Folder(const char *name=""){
        this->name= new char[strlen(name)+1];
        strcpy(this->name,name);
        NoFiles=0;
        this->file=new File[NoFiles];
    }
    Folder(const Folder &f){
        copy(f);
    }
    Folder &operator=(const Folder &f){
        if(this!=&f){
            delete []file;
            delete []name;
            copy(f);
        }
        return *this;
    }
    ~Folder(){
        delete []file;
        delete []name;
    }
    void print(){
        cout<<"Folder name: "<<name<<endl;
        for(int i=0;i<NoFiles;i++)
            file[i].print();
    }
    void add(const File & f){
        File *tmp = new File[NoFiles+1];
        for(int i=0;i<NoFiles;i++)
            tmp[i]=file[i];
        tmp[NoFiles++]=f;
        delete []file;
        file=tmp;
    }
    void remove(const File & f){
        int i=0,j=0;
        File *tmp = new File[--NoFiles];
        for(i=0;i<NoFiles+1;i++)
        {
            if(!file[i].equals(f))
                tmp[j++]=file[i];
        }
        delete []file;
        file = tmp;
    }
};

int main(){
    char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}
