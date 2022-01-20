#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

void bookmark();

int main(){
    //decalare source file name
    string s_filename("text");

    //obtain file size
    streampos begin,end;
    ifstream myfile ("text.txt", ios::binary);
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    myfile.close();


    //console 
    bookmark();
    cout << "Name: " << s_filename << endl;
    cout << "Size: " << end-begin << " bytes"<<endl;
    bookmark();

    //output file
    ofstream o{s_filename+"(Cloned).txt"};
    o << "Name: " << s_filename << endl;
    o << "Size: " << end-begin << " bytes"<<endl;
    o.close();
    
    

    return 0;
}

void bookmark(){
    for(int i = 0; i < 30; i++){
        cout << "-";
    }cout<<endl;
}