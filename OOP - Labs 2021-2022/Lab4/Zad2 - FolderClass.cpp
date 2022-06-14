#include <iostream>
#include <cstring>
using namespace std;
enum extension{pdf=0, txt, exe};
class File{
private:
    char *filename;
    extension ext;
    char *owner;
    int size;

    void copy(const File &other){
        this->filename=new char[strlen(other.filename)+1];
        strcpy(this->filename,other.filename);
        this->ext=other.ext;
        this->owner=new char[strlen(other.owner)+1];
        strcpy(this->owner,other.owner);
        this->size=other.size;
    }
public:
    File(){
        this->filename=new char[1];
        strcpy(this->filename,"");
        this->ext=txt;
        this->owner=new char[1];
        strcpy(this->owner,"");
        this->size=0;
    }
    File(char *filename, char *owner, int size,extension ext){
        this->filename=new char[strlen(filename)+1];
        strcpy(this->filename,filename);
        this->ext=ext;
        this->owner=new char[strlen(owner)+1];
        strcpy(this->owner,owner);
        this->size=size;
    }
    File(const File &CopyFile){
        copy(CopyFile);
    }
    File &operator=(const File &OperatorFile){
        if(this!=&OperatorFile){
            delete []filename;
            delete []owner;
            copy(OperatorFile);
        }
        return *this;
    }
    ~File(){
        delete []filename;
        delete []owner;
    }
    void print(){
        cout<<"File name: "<<this->filename;
        if(ext==0)
            cout<<".pdf"<<endl;
        if(ext==1)
            cout<<".txt"<<endl;
        if(ext==2)
            cout<<".exe"<<endl;
        cout<<"File owner: "<<owner<<endl;
        cout<<"File size: "<<size<<endl;
    }
    bool equals(const File & that){
        if(strcmp(this->filename,that.filename)==0){
            if(this->ext==that.ext){
                if(strcmp(this->owner,that.owner)==0)
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
    char *foldername;
    int NoFiles;
    File *files;
public:
    Folder(){
        this->foldername=new char[1];
        strcpy(this->foldername,"");
        this->NoFiles=0;
        this->files = new File[NoFiles];
    }
    Folder(const char* foldername){
        this->foldername=new char[strlen(foldername)+1];
        strcpy(this->foldername,foldername);
        this->NoFiles=0;
        this->files = new File[NoFiles];
    }
    ~Folder(){
        delete []foldername;
        delete []files;
    }
    void print(){
        cout<<"Folder name: "<<foldername<<endl;
        for(int i=0;i<NoFiles;i++)
            files[i].print();
    }
    void add(const File & file){
        if(NoFiles!=0){
            int i=0;
            File *tmp = new File[++NoFiles];
            for(i=0;i<NoFiles-1;i++)
                tmp[i]=files[i];
            tmp[NoFiles-1]=file;
            delete []files;
            files = tmp;
        }
        else{
            delete []files;
            files = new File[++NoFiles];
            files[0]=file;
        }
    }
    void remove(const File & file){
        int i=0,j=0;
        File *tmp = new File[--NoFiles];
        for(i=0;i<NoFiles+1;i++)
        {
            if(files[i].equals(file)==false)
                tmp[j++]=files[i];
        }
        delete []files;
        files = tmp;
    }

};

int main()
{
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
		cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
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
