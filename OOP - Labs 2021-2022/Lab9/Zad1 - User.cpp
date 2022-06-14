#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

class InvalidPassword{
public:
    void showMessage(){
        cout<<"Password is too weak."<<endl;
    }
};
class InvalidEmail{
public:
    void showMessage(){
        cout<<"Mail is not valid."<<endl;
    }
};
class MaximumSizeLimit{
private:
    int maxusers;
public:
    MaximumSizeLimit(int maxusers){
        this->maxusers=maxusers;
    }
    void showMessage(){
        cout<<"You can't add more than "<<maxusers<<" users."<<endl;
    }
};
class User{
protected:
    char username[50];
    char password[50];
    char email[50];
public:
    User(char *username="",char *password="",char *email=""){
        strcpy(this->username,username);
        bool uc=false,lc=false,num=false;
        int atsign=0;
        for(int i=0;i<strlen(email);i++){
            if(email[i]=='@')
                atsign++;
        }
        if(atsign!=1)
            throw InvalidEmail();

        for(int i=0;i<strlen(password);i++){
            if(isupper(password[i]))
                uc=true;
            else if(islower(password[i]))
                lc=true;
            else if(isdigit(password[i]))
                num=true;
            if(uc && lc && num)
                break;
        }
        if(!uc || !lc || !num)
            throw InvalidPassword();

        strcpy(this->password,password);
        strcpy(this->email,email);
    }
    virtual double popularity()=0;
    virtual void print()=0;
};
class FacebookUser:public User{
private:
    int friends;
    int likes;
    int comments;
public:
    FacebookUser(char *username="",char *password="",char *email="",int friends=0,int likes=0,int comments=0):User(username,password,email){
        this->friends=friends;
        this->likes=likes;
        this->comments=comments;
    }
    double popularity(){
        return friends+(likes*0.1)+(comments*0.5);
    }
    void print(){
        cout<<"Username: "<<username<<" password: "<<password<<" email: "<<email<<" friends: "<<friends<<" likes: "<<likes<<" comments: "<<comments<<endl;
    }
};
class TwitterUser:public User{
private:
    int followers;
    int tweets;
public:
    TwitterUser(char *username="",char *password="",char *email="",int followers=0,int tweets=0):User(username,password,email){
        this->followers=followers;
        this->tweets=tweets;
    }
    double popularity(){
        return followers+(tweets*0.5);
    }
    void print(){
        cout<<"Username: "<<username<<" password: "<<password<<" email: "<<email<<" followers: "<<followers<<" tweets: "<<tweets<<endl;
    }
};
class SocialNetwork{
private:
    User **user;
    int NoUsers;
    int MaxNoUsers;
public:
    SocialNetwork(){
        this->NoUsers=0;
        this->MaxNoUsers=5;
        user = new User*[0];
    }
    SocialNetwork &operator+=(User *u){
        if(NoUsers==MaxNoUsers)
            throw MaximumSizeLimit(MaxNoUsers);
        User **tmp = new User *[NoUsers+1];
        for(int i=0;i<NoUsers;i++)
            tmp[i]=user[i];
        tmp[NoUsers++]=u;
        //delete []user; //tuka crashnuva
        user=tmp;
        return *this;
    }
    ~SocialNetwork(){
        delete []user;
    }
    double avgPopularity(){
        double total=0;
        for(int i=0;i<NoUsers;i++){
                total+=user[i]->popularity();
         //   cout<<i+1<<". ";user[i]->print();
        }
        return total/NoUsers;
    }
    void changeMaximumSize(int num){
        this->MaxNoUsers=num;
    }
    void printusers(){
        for(int i=0;i<NoUsers;i++){
            user[i]->print();
        }
    }
};



int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
        try{
            User * u = new FacebookUser(username,password,email,friends,likes,comments);
            network += u;
        }
        catch(InvalidPassword p){
            p.showMessage();
        }catch(InvalidEmail e){
            e.showMessage();
        }catch(MaximumSizeLimit &m){
            m.showMessage();
        }
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;

        try{
            User * u= new TwitterUser(username,password,email,followers,tweets);
            network += u;
        }
        catch(InvalidPassword p){
            p.showMessage();
        }catch(InvalidEmail e){
            e.showMessage();
        }catch(MaximumSizeLimit &m){
            m.showMessage();
        }
      }
    }
   // network.printusers();
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin  >> followers >> tweets;

    try{
            User * u= new TwitterUser(username,password,email,followers,tweets);
            network += u;
        }
        catch(InvalidPassword p){
            p.showMessage();
        }catch(InvalidEmail e){
            e.showMessage();
        }catch(MaximumSizeLimit &m){
            m.showMessage();
    }
   // network.printusers();
    cout << network.avgPopularity();

}
