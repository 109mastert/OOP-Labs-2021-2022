#include <iostream>
#include <cstring>
/// 12 32
using namespace std;

class ExistingGame{
public:
    void message(){
        cout<<"The game is already in the collection"<<endl;
    }
};

class Game{
protected:
    char name[100];
    float price;
    bool sale;

    void copy(const Game &g){
        strcpy(this->name,g.name);
        this->price=g.price;
        this->sale=g.sale;
    }
public:
    Game(char *name="",float price=0.0,bool sale=false){
        strcpy(this->name,name);
        this->price=price;
        this->sale=sale;
    }
    Game(const Game &g){
        copy(g);
    }
    Game &operator=(const Game &g){
        if(this!=&g){
            copy(g);
        }
        return *this;
    }
    bool getSale(){
        return sale;
    }
    float getPrice(){
        return price;
    }
    virtual ~Game(){}
    friend ostream &operator<<(ostream &out,const Game &g){
        out<<"Game: "<<g.name<<", regular price: $"<<g.price;
        if(g.sale)
            out<<", bought on sale";
        return out;
    }
    friend istream &operator>>(istream &in, Game &g){
        in.get();
        in.getline(g.name,100);
        in>>g.price;
        in>>g.sale;
        return in;
    }
    bool operator==(Game &g1){
        return (strcmp(this->name,g1.name)==0);
    }
    char *getName(){
        return name;
    }
};

class SubscriptionGame:public Game{
private:
    float sub;
    int month,year;
public:
    SubscriptionGame(char *name="",float price=0.0,bool sale=false,float sub=0.0,int month=1,int year=1111):Game(name,price,sale){
        this->sub=sub;
        this->month=month;
        this->year=year;
    }
    int getYear(){
        return year;
    }
    int getMonth(){
        return month;
    }
    float getSub(){
        return sub;
    }
    friend ostream &operator<<(ostream &out,const SubscriptionGame &sg){
        Game g(sg);
        out<<g;
        out<<", monthly fee: $"<<sg.sub<<", purchased: "<<sg.month<<"-"<<sg.year<<endl;
        return out;
    }
    friend istream &operator>>(istream &in, SubscriptionGame &sg){
        in.get();
        in.getline(sg.name,100);
        in>>sg.price>>sg.sale;
        in>>sg.sub>>sg.month>>sg.year;
        return in;
    }
};
class User{
private:
    char username[100];
    Game **games;
    int NoGames;
public:
    User(char *username=""){
        strcpy(this->username,username);
        games= new Game*[0];
        this->NoGames=0;
    }
    User &operator+=(Game &g){
        for(int i=0;i<NoGames;i++){
            if(*games[i]==g){
                throw ExistingGame();
            }

        }
        Game **tmp = new Game *[NoGames+1];
        for(int i=0;i<NoGames;i++)
            tmp[i]=games[i];
        tmp[NoGames++]=&g;
        delete []games;
        games=tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out,const User &u){
        SubscriptionGame *sg=nullptr;
        out<<endl<<"User: "<<u.username<<endl;
        for(int i=0;i<u.NoGames;i++){
            sg=dynamic_cast<SubscriptionGame *>(u.games[i]);
            if(sg!=nullptr){
                out<<"- "<<*sg<<endl;
            }
            else
                out<<"- "<<*u.games[i]<<endl;
        }
        return out;
    }
    double total_spent(){
        double sum=0.0;
        int monthsby;
        SubscriptionGame *sg=nullptr;
        for(int i=0;i<NoGames;i++){
            if(games[i]->getSale())
                sum+=0.3*games[i]->getPrice();
            else
                sum+=games[i]->getPrice();
            sg=dynamic_cast<SubscriptionGame*>(games[i]);
            if(sg!=nullptr){ //maj 2018
                monthsby=((2018-sg->getYear())*12)+5-sg->getMonth();
                sum+=monthsby*sg->getSub();
            }
        }
        return sum;
    }
};


int main() {
    int test_case_num;
    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
    }
    else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
    }
    else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
    }
    else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
    }
    else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }
        //cout<<(*g);

        u+=(*g); /// tuka crashnuva sigurno
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

    /*cout<<"\nUser: "<<u.get_username()<<"\n";

        for (int i=0; i < u.get_games_number(); ++i){
            Game * g;
            SubscriptionGame * sg;
            g = &(u.get_game(i));

            sg = dynamic_cast<SubscriptionGame *> (g);

            if (sg){
              cout<<"- "<<(*sg);
            }
            else {
              cout<<"- "<<(*g);
            }
            cout<<"\n";
        }*/

    }
   else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

    //      for (int i=0; i < u.get_games_number(); ++i){
    //          Game * g;
    //          SubscriptionGame * sg;
    //          g = &(u.get_game(i));

    //          sg = dynamic_cast<SubscriptionGame *> (g);

    //          if (sg){
    //            cout<<"- "<<(*sg);
    //          }
    //          else {
    //            cout<<"- "<<(*g);
    //          }
    //          cout<<"\n";
    //      }
    }
    else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
