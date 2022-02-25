#include "spk.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc,char *argv[]){
    SetConsoleTextAttribute(h,244) ;   
    cout <<  " _____   _____   _   _   _____   _____   _____   _____   _____   _____   _   __      _" << endl ; 
    cout <<  "/  ___| |  _  | | | | | | ___ \\ /  __ \\ |  ___| | ___ \\ | ___ \\ |_   _| | | / /    _|" ; SetConsoleTextAttribute(h,160) ; cout << " " ; SetConsoleTextAttribute(h,244) ; cout << "|_" << endl ;
    cout <<  "\\ `--.  | | | | | | | | | |_/ / | /  \\/ | |__   | |_/ / | |_/ /   | |   | |/ /    |" ; SetConsoleTextAttribute(h,192) ; cout << "     " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout <<  " `--. \\ | | | | | | | | |    /  | |     |  __|  |  __/  |    /    | |   |    \\     |" ; SetConsoleTextAttribute(h,192) ; cout << "    "; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout <<  "/\\__/ / \\ \\_/ / | |_| | | |\\ \\  | \\__/\\ | |___  | |     | |\\ \\   _| |_  | |\\  \\    |" ; SetConsoleTextAttribute(h,192) ; cout << "   " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout <<  "\\____/   \\___/   \\___/  \\_| \\_|  \\____/ \\____/  \\_|     \\_| \\_|  \\___/  \\_| \\_/   |" ; SetConsoleTextAttribute(h,192) ; cout << "   " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout << "---------------------------------------------------------------------------------|" ; SetConsoleTextAttribute(h,192) ; cout << "  " ; SetConsoleTextAttribute(h,244) ; cout << "|-----------------" << endl ; 
    SetConsoleTextAttribute(h,7) ;   


    do{
        SetConsoleTextAttribute(h,248) ;
        cout<< "Please input command :";
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
        SetConsoleTextAttribute(h,252) ;   
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        SetConsoleTextAttribute(h,7) ;   
        }
    }while(true);
SetConsoleTextAttribute(h,248) ;   
    cout << "----------------------------------------------------------------------------------------------------" << endl;  
    cout << "          Program is closing" << "\n" ;
SetConsoleTextAttribute(h,244) ;   
    cout << " _____   _   _    ___    _   _   _   __   __   __  _____   _   _        _" << endl;
    cout << "|_   _| | | | |  / _ \\  | \\ | | | | / /   \\ \\ / / |  _  | | | | |      |" ; SetConsoleTextAttribute(h,160) ; cout << " " ; SetConsoleTextAttribute(h,244) ; cout << "|_" << endl ;
    cout << "  | |   | |_| | / /_\\ \\ |  \\| | | |/ /     \\ V /  | | | | | | | |    |" ; SetConsoleTextAttribute(h,192) ; cout << "     " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout << "  | |   |  _  | |  _  | | . ` | |    \\      \\ /   | | | | | | | |    |" ; SetConsoleTextAttribute(h,192) ; cout << "    "; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout << "  | |   | | | | | | | | | |\\  | | |\\  \\     | |   \\ \\_/ / | |_| |     |" ; SetConsoleTextAttribute(h,192) ; cout << "   " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout << "  \\_/   \\_| |_/ \\_| |_/ \\_| \\_/ \\_| \\_/     \\_/    \\___/   \\___/       |" ; SetConsoleTextAttribute(h,192) ; cout << "   " ; SetConsoleTextAttribute(h,244) ; cout << "|" << endl ;
    cout << "-------------------------------------------------------------------------|" ; SetConsoleTextAttribute(h,192) ; cout << "  " ; SetConsoleTextAttribute(h,244) ; cout << "|-----------------" << endl ;
SetConsoleTextAttribute(h,7) ;   


    return 0;
}
