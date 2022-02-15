#include "header.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc,char *argv[]){

    do{
        cout<< "Please input command: ";
        string command;
        getline(cin,command);

        if(command == "exit") break;
        else if(command == "clone") clone();
        else if(command == "sorttype") splitType();
        else if(command == "sortdate"); //splitdate();
        else if(command == "search") search();
        else if(command == "show") showFile();
        else if (command == "dclone") deClone();
        else if (command == "dfi") banish(1);
        else if (command == "dfol") banish(2);
        else if (command == "help" or command == "h" or command == "H" ) help();
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);

    return 0;
}