#include <iostream>
#include <cstring>
using namespace std;

class NBAPlayer{
protected:
    char *name;
    char team[40];
    double avgp; //average points
    double avga; //average assists
    double avgh; //average hoops
    void copy(const NBAPlayer &n){
        this->name=new char[strlen(n.name)+1];
        strcpy(this->name,n.name);
        strcpy(this->team,n.team);
        this->avgp=n.avgp;
        this->avga=n.avga;
        this->avgh=n.avgh;
    }
public:
    NBAPlayer(char *name="",char *team="",double avgp=0.0,double avga=0.0,double avgh=0.0){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->team,team);
        this->avgp=avgp;
        this->avga=avga;
        this->avgh=avgh;
    }
    NBAPlayer(const NBAPlayer &n){
        copy(n);
    }
    NBAPlayer &operator=(const NBAPlayer &n){
        if(this!=&n){
            delete []name;
            copy(n);
        }
        return *this;
    }
    ~NBAPlayer(){
        delete []name;
    }
    float rating(){
        return (avgp*0.45+avga*0.3+avgh*0.25);
    }
    void print(){
        cout<<name<<" - "<<team<<endl;
        cout<<"Points: "<<avgp<<endl;
        cout<<"Assists: "<<avga<<endl;
        cout<<"Rebounds: "<<avgh<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};
class AllStarPlayer:public NBAPlayer{
private:
    double asavgp,asavga,asavgh;
public:
    AllStarPlayer(char *name="",char *team="",double avgp=0.0,double avga=0.0,double avgh=0.0, double asavgp=0.0, double asavga=0.0,double asavgh=0.0):NBAPlayer(name,team,avgp,avga,avgh){
        this->asavgp=asavgp;
        this->asavga=asavga;
        this->asavgh=asavgh;
    }
    AllStarPlayer(NBAPlayer &p,double asavgp, double asavga,double asavgh):NBAPlayer(p){
        this->asavgp=asavgp;
        this->asavga=asavga;
        this->asavgh=asavgh;
    }
    AllStarPlayer(const AllStarPlayer &asp):NBAPlayer(asp){
        this->asavgp=asp.asavgp;
        this->asavga=asp.asavga;
        this->asavgh=asp.asavgh;
    }
    AllStarPlayer &operator=(const AllStarPlayer &asp){
        if(this!=&asp){
            this->name=new char[strlen(asp.name)+1];
            strcpy(this->name,asp.name);
            strcpy(this->team,asp.team);
            this->avgp=asp.avgp;
            this->avga=asp.avga;
            this->avgh=asp.avgh;
            this->asavgp=asp.asavgp;
            this->asavga=asp.asavga;
            this->asavgh=asp.asavgh;
        }
        return *this;
    }
    ~AllStarPlayer(){}
    float allStarRating(){
        return (asavgp*0.3+asavga*0.4+asavgh*0.3);
    }
    float rating(){
        return (float)((NBAPlayer::rating()+allStarRating())/2.0);
    }
    void print(){
        NBAPlayer tmp(*this);
        tmp.print();
        cout<<"All Star Rating: "<<allStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
