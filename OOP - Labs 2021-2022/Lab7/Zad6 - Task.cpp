#include<iostream>
#include<cstring>
using namespace std;

class Task{
protected:
    char id[6];
public:
    Task(char *id=""){
        strcpy(this->id,id);
    }
    virtual int getOrder()=0;
    virtual void print()=0;
    char *getID(){
        return id;
    }
};

//Preoptovaruvanje na operatorot za sporedba == (prima 2 argumenti bidejki se definira nadvor od klasata Task)
bool operator==(Task *t1,Task &t2){
    return (strcmp(t1->getID(),t2.getID())==0 && t1->getOrder()==t2.getOrder());
}

class TimedTask:public Task{
private:
    int time;
public:
    TimedTask(char *id="",int time=0):Task(id){
        this->time=time;
    }
    int getOrder(){
        return time;
    }
    void print(){
        cout<<"TT->"<<id<<":"<<time<<endl;
    }
};

class PriorityTask:public Task{
private:
    int priority;
public:
    PriorityTask(char *id="",int priority=0):Task(id){
        this->priority=priority;
    }
    int getOrder(){
        return priority;
    }
    void print(){
        cout<<"PT->"<<id<<":"<<priority<<endl;
    }

};
void scheduleTimedTasks(Task ** tasks, int n, int t) {
    Task **temp=new Task*[1];
    for(int i=0;i<n-1;i++){
        if(tasks[i]->getOrder()>tasks[i+1]->getOrder()){
            temp[0]=tasks[i+1];
            tasks[i+1]=tasks[i];
            tasks[i]=temp[0];
            i=-1;
        }
    }
    for(int i=0;i<n;i++){
        if(dynamic_cast<TimedTask *>(tasks[i])){
            if(tasks[i]->getOrder()<t){
                tasks[i]->print();
            }
        }
    }
}

void schedulePriorityTasks(Task ** tasks, int n, int p) {
    Task **temp=new Task*[1];
    for(int i=0;i<n-1;i++){
        if(tasks[i]->getOrder()>tasks[i+1]->getOrder()){
            temp[0]=tasks[i+1];
            tasks[i+1]=tasks[i];
            tasks[i]=temp[0];
            i=-1;
        }
    }
    for(int i=0;i<n;i++){
        if(dynamic_cast<PriorityTask *>(tasks[i])){
            if(tasks[i]->getOrder()<p){
                tasks[i]->print();
            }
        }
    }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;
    if (testCase==0){
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
       // tasks[i]->print();
    	}

    	cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
    	schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

	return 0;
}
