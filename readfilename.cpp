#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <string>

using namespace std;

string toUpperStr(string x);

string getFilePath(const string& path);
 
string getFileName(const string& path);
 
string getFileExtension(const string& path);

void moveFile(const string& oldPath, const string& newPath);
 
void splitType();

void clone();

int main(){

    do{
        string command;
        getline(cin,command);

        if(command == "exit") break;
        else if(command == "clone") clone();
        else if(command == "sorttype") splitType();
        else if(command == "sortdate"); //splitdate();
        else if(command == "search"); //search();
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);

    return 0;
}

    /**
    * FUNCTION: getFilePath 
    * USE: Returns the path from a given file path
    * @param path: The path of the file
    * @return: The path from the given file path
    */
string getFilePath(const std::string& path) {
        auto pathEnd = path.find_last_of("/\\");
        auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);
        return pathName;
}
 
    /**
    * FUNCTION: getFileName 
    * USE: Returns the file name from a given file path
    * @param path: The path of the file
    * @return: The file name from the given file path
    */
string getFileName(const std::string& path) {
        auto fileNameStart = path.find_last_of("/\\");
        auto fileName = fileNameStart == std::string::npos ? path : path.substr(fileNameStart + 1);
        return fileName;
}
 
    /**
    * FUNCTION: getFileExtension 
    * USE: Returns the file extension from a given file path
    * @param path: The path of the file
    * @return: The file extension from the given file path
    */
string getFileExtension(const std::string& path) {
        auto fileName = getFileName(path);
        auto extStart = fileName.find_last_of('.');
        auto ext = extStart == std::string::npos ? "" : fileName.substr(extStart + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { 
            return static_cast<unsigned char>(std::tolower(c)); 
        });
        return ext;
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void moveFile(const string& oldPath, const string& newPath){
    rename(oldPath.c_str(), newPath.c_str());
}

void splitType(){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);

    cout << "Choose your files type : ";
    string filesType;
    cin >> filesType;
    for (auto & c: filesType) c = tolower(c);

     cout << "----------------------------------------------------------------------------------------------------" << endl;

    string newPath;
    newPath = directoryPath + "\\" + filesType;
    
  
    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();

        if(getFileExtension(currPath) == filesType){
            rmdir(newPath.c_str());
            mkdir(newPath.c_str());
        }
    }

    bool typeFound = false;

    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();

        if(getFileExtension(currPath) == filesType){
            cout << getFileName(currPath) << " --> has been moved to new directory : " << filesType << endl;
            moveFile(currPath,newPath + "\\" + getFileName(currPath));
            typeFound = true;
        }
    }
    if(!typeFound) cout << "not found any file with type : " + filesType << endl;
    else cout << "all files have been moved successfully." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
}

void clone(){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    //set path
    string fullpath;
    getline(cin,fullpath);
    auto filePath = getFilePath(fullpath);
    string s_filename(getFileName(fullpath));

    //file extension
    auto extension = getFileExtension(fullpath);

    //obtain file size
    streampos begin,end;
    ifstream myfile (fullpath, ios::binary);
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    auto size = end-begin;
    myfile.close();
    
    //time
    struct stat fileInfo;
    if (stat(s_filename.c_str(), &fileInfo) != 0) {  // Use stat( ) to get the info
      std::cerr << "Error: " << strerror(errno) << '\n';
   }
    auto timecreate = ctime(&fileInfo.st_ctime);         // Creation time
    auto timemod = ctime(&fileInfo.st_mtime);         // Last mod time

    //console 
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Path: " << filePath <<endl; 
    cout << "Name: " << s_filename << endl;
    cout << "Size: " << size << " bytes"<<endl;
    cout << "Extension:."<<extension<<endl;
    cout << "Created: " <<timecreate;
    cout << "Last Modified: " << timemod;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    //output file
    ofstream o{s_filename+"(Cloned).txt"};
    o << "Path: " << filePath<<endl;
    o << "Name: " << s_filename << endl;
    o << "Size: " << size << " bytes"<<endl;
    o << "Extension:."<<extension<<endl; 
    o << "Created: " <<timecreate;
    o << "Last Modified: " << timemod;
    o.close();
    
}
