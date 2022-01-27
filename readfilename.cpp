#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

const int N = 27;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    string textline;
    ifstream source;
    source.open(filename);
    char readname[N];
    int s1,s2,s3;
    while(getline(source,textline)){
      const char *data = textline.c_str();
      sscanf(data,"%[^:]: %d %d %d", readname, &s1, &s2, &s3);
      names.push_back(readname);
      scores.push_back(s1+s2+s3);
      grades.push_back(score2grade(s1+s2+s3));
    }
    source.close();
}

void getCommand(string &command, string &key){
  cout << "Please input your command: ";
  string input;
  char a[N],b[N];
  getline(cin,input);
  sscanf(input.c_str(),"%s %[^\n]",a,b);
  command = a;key = b;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
  int pos = 0; 
  bool found;
  cout << "---------------------------------"<<endl;
  for(unsigned int i = 0; i < names.size() ;i++){
    if(toUpperStr(names[i]) == key){
      pos = i;
      found = true;
    }
    else if(i == names.size()-1 && found == false){
      cout << "Cannot found." <<endl;
    }
  }
  if (found == true){
    cout << names[pos] << "'s score = " << scores[pos] << endl;
    cout << names[pos] << "'s grade = " << grades[pos] << endl;
  }
  cout << "---------------------------------"<<endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
  cout << "---------------------------------"<<endl;
  const char *grade = key.c_str();
  bool found;
  for( unsigned int i = 0; i < names.size() ;i++){
    if(grades[i] == *grade){
      cout << names[i] << " (" << scores[i] << ")" << endl;
      found = true;
    }
    else if(i == names.size()-1 && found == false){
      cout << "Cannot found." << endl;
    }
  }
  cout << "---------------------------------"<<endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}