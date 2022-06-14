#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
protected:
    char *name;
    char owner[50];
    int width,height;
    void copy(const Image &img){
        this->name = new char[strlen(img.name)+1];
        strcpy(this->name,img.name);
        strcpy(this->owner,img.owner);
        this->width=img.width;
        this->height=img.height;
    }
public:
    Image(char *name="untitled",char *owner="unknown",int width=800,int height=800){
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->owner,owner);
        this->width=width;
        this->height=height;
    }
    Image(const Image &img){
        copy(img);
    }
    Image &operator=(const Image &img){
        if(this!=&img){
            delete []name;
            copy(img);
        }
        return *this;
    }
    virtual int getSize(){
        return this->width*this->height*3;
    }
    ~Image(){
        delete []name;
    }
    friend ostream &operator<<(ostream &out, Image &i){
        return out<<i.name<<" "<<i.owner<<" "<<i.getSize()<<endl;
    }
    bool operator>(Image &i){
        ///Tuka moze da se podobre situacija
        return (this->width*this->height>i.getSize());
    }
};

class TransparentImage:public Image{
private:
    bool transparency;
public:
    TransparentImage(char *name="untitled",char *owner="unknown",int width=800,int height=800,bool transparency=true):Image(name,owner,width,height){
        this->transparency=transparency;
    }
    int getSize(){
        if(transparency)
            return width*height*4;
        else
            return (width*height)+(width*height)/8;
    }
    friend ostream &operator<<(ostream &out, const TransparentImage &ti){
        if(ti.transparency)
            out<<ti.name<<" "<<ti.owner<<" "<<ti.width*ti.height*4<<endl;
        else
            out<<ti.name<<" "<<ti.owner<<" "<<(ti.width*ti.height)+(ti.width*ti.height)/8<<endl;
        return out;
    }
};

class Folder{
private:
    char name[255];
    char owner[50];
    Image **imgs;
    int NoImages;
    void copy(const Folder &f){
        strcpy(this->name,f.name);
        strcpy(this->owner,f.owner);
        this->NoImages=f.NoImages;
        this->imgs=new Image*[f.NoImages];
        for(int i=0;i<NoImages;i++){
            this->imgs[i]=f.imgs[i];
        }
    }
public:
    Folder(char *name="",char *owner="unknown"){
        strcpy(this->name,name);
        strcpy(this->owner,owner);
        this->NoImages=0;
        this->imgs=new Image*[NoImages];
    }
    ~Folder(){
        delete []imgs;
    }
    Folder(const Folder &f){
        copy(f);
    }
    Folder &operator=(const Folder &f){
        if(this!=&f){
            copy(f);
        }
        return *this;
    }
    Folder &operator+=(Image &img){
        Image **tmp = new Image *[NoImages+1];
        for(int i=0;i<NoImages;i++)
            tmp[i]=imgs[i];
        tmp[NoImages++]=&img;
        delete []imgs;
        imgs=tmp;
        return *this;
    }
    Image *operator[](int i){
        if(i>NoImages)
            return nullptr;
        else
            return imgs[i];
    }
    friend ostream &operator<<(ostream &out, Folder &f){
        TransparentImage *ti = nullptr;
        out<<f.name<<" "<<f.owner<<endl;
        out<<"--"<<endl;
        for(int i=0;i<f.NoImages;i++)
            out<<*f.imgs[i];
        out<<"--"<<endl<<"Folder size: "<<f.totalSize()<<endl;
        return out;
    }
    Image *getMaxFile(){
        Image *max = imgs[0];
        for(int i=0;i<NoImages;i++){
            if(imgs[i]->getSize()>max->getSize())
                max=imgs[i];
        }
            return max;
    }
    int totalSize(){
        int sum=0;
        for(int i=0;i<NoImages;i++)
            sum+=imgs[i]->getSize();
        return sum;
    }
};

Folder max_folder_size(Folder *f,int n){
    Folder max=f[0];
    for(int i=1;i<n;i++){
        if(max.totalSize()<f[i].totalSize())
            max=f[i];
    }
    return max;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;

      Image f1;
      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }
        Folder tmp=max_folder_size(dir_list, folders_num);
      cout<<tmp;
    }
    return 0;
};
