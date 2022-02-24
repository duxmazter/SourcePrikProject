#include "spk.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc,char *argv[]){

    do{
        SetConsoleTextAttribute(h,248) ;
        cout<< "Please input command: ";
        string command;
        getline(cin,command);
        string uCom = toUpperStr(command);

        if(uCom == "EXIT") break;
        else if(uCom == "CLONE") clone();
        else if(uCom == "STYPE") splitType();
        else if(uCom == "SDATE") splitDate();
        else if(uCom == "FIND") search();
        else if(uCom == "SHOW") showFile();
        else if (uCom == "DCLONE") deClone();
        else if (uCom == "DFI") banish(1);
        else if (uCom == "DFOL") banish(2);
        else if (uCom == "DSPEC") dspec();
        else if (uCom == "PNAME") pushname();
        else if (uCom == "HELP" or command == "h" or command == "H" ) help();
        else{
        SetConsoleTextAttribute(h,4) ;   
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        SetConsoleTextAttribute(h,7) ;   
        }
    }while(true);

    return 0;
}
