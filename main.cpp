#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Task{
    int id;
    string name;
    bool completed;
};

class TodoList {
private:
    vector<Task> tasks;

public:

    int getSize(){ //to get size of private vector Task
        return (int)tasks.size(); 
    }

    void addTask(string name, bool status=false){ //Adding Items to vector Task
        tasks.push_back({(int)tasks.size()+1,name,status});
    }

    void viewTask(){ //Seeing the To Do List
        for(Task t: tasks){
            cout << t.id << ". " << (t.completed ? "[x] " : "[ ] ") << t.name << "\n";
        }
    }

    bool deleteTask(string name){ //Deleting from the List
        for(int i=0;i<tasks.size();i++){
            if(tasks[i].name==name){
                tasks.erase(tasks.begin()+i);
                for(int i=0;i<tasks.size();i++) tasks[i].id=i+1;
                return true;
            }
        }
        return false;
    }

    bool completeTask(string name){ //Mark Task as Finish/Unfinished
        for(int i=0;i<tasks.size();i++){
            if(tasks[i].name==name){
                tasks[i].completed=!tasks[i].completed;
                return true;
            }
        }
        return false;
    }

    void saveToFile(){ //Saving Data into the File
        ofstream file("tasks.txt");
        for(Task t: tasks){
            file << t.id << "," << t.name << "," << t.completed << "\n";
        }
        file.close();
    }

    void loadFromFile(){ //Loading data from the file
        ifstream file("tasks.txt");
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string id, name, completed;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, completed, ',');
            tasks.push_back({stoi(id), name, completed == "1"});
        }
        file.close();
    }
    
};

void showMenu(){
    cout<<"add --> Add Items\nview --> View List\ndelete --> Delete Item\nmark --> Mark as complete/incomplete\nmenu --> Show Menu\nquit --> Quit"<<endl;
}

int main(){
    TodoList t1;
    string command, argument;

    t1.loadFromFile();
    showMenu();

    do{
        cout<<endl<<">";
        cin>>command;
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        getline(cin,argument);
        if(!argument.empty()) argument = argument.substr(1);
        if(command == "add"){
            if(argument.empty()){
                cout << "Please enter a task name!" << endl;
            }
            else{
                t1.addTask(argument);
                cout << "Task Added Successfully" << endl;
                t1.saveToFile();
            }
        }
        else if(command=="view"){
            if(t1.getSize()==0){
                cout<<"No Item in list!";
            }
            else{
                t1.viewTask();
            }
        }
        else if(command=="delete"){
            if(!t1.deleteTask(argument)){
                cout << "Task not found!";
            }
            else{
                cout<<"Task deleted";
                t1.saveToFile();
            }
        }
        else if(command=="mark"){
            if(!t1.completeTask(argument)){
                cout<<"Task not found!";
            }
            else{
                t1.saveToFile();
                t1.viewTask();
            }
            
        }
        else if(command=="menu"){
            showMenu();
        }
        else{
            cout<<"Invalid command.";
        }
    }while (command!="quit");

    return 0;

}