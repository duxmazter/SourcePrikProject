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
namespace Utils {
    /**
    * FUNCTION: getFilePath 
    * USE: Returns the path from a given file path
    * @param path: The path of the file
    * @return: The path from the given file path
    */
    std::string getFilePath(const std::string& path) {
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
    std::string getFileName(const std::string& path) {
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
    std::string getFileExtension(const std::string& path) {
        auto fileName = getFileName(path);
        auto extStart = fileName.find_last_of('.');
        auto ext = extStart == std::string::npos ? "" : fileName.substr(extStart + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { 
            return static_cast<unsigned char>(std::tolower(c)); 
        });
        return ext;
    }
}

//path string fullpath  
// cin << fullpath;
string fullpath = "C:\\Users\\eak_k\\Downloads\\C\\Git Beginner\\SourcePrikProject\\gif.gif";
auto filePath = Utils::getFilePath(fullpath);
string s_filename(Utils::getFileName(fullpath));


void bookmark();

int main(){

    //file extension
    auto extension = Utils::getFileExtension(fullpath);

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
      return(EXIT_FAILURE);
   }
    auto timecreate = ctime(&fileInfo.st_ctime);         // Creation time
    auto timemod = ctime(&fileInfo.st_mtime);         // Last mod time

    //console 
    bookmark();
    cout << "Path: " << filePath <<endl; 
    cout << "Name: " << s_filename << endl;
    cout << "Size: " << size << " bytes"<<endl;
    cout << "Extension:."<<extension<<endl;
    cout << "Created: " <<timecreate;
    cout << "Last Modified: " << timemod;
    bookmark();

    //output file
    ofstream o{s_filename+"(Cloned).txt"};
    o << "Path: " << filePath<<endl;
    o << "Name: " << s_filename << endl;
    o << "Size: " << size << " bytes"<<endl;
    o << "Extension:."<<extension<<endl; 
    o << "Created: " <<timecreate;
    o << "Last Modified: " << timemod;
    o.close();

    
    return 0;
}

void bookmark(){
    for(int i = 0; i < 100; i++){
        cout << "-";
    }cout<<endl;
}

