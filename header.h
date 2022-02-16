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
#include <dirent.h>
#include <conio.h>

using namespace std;
namespace fs = std::filesystem;

string toUpperStr(string x);

string getFilePath(const string& path);
 
string getFileName(const string& path);
 
string getFileExtension(const string& path);

void moveFile(const string& oldPath, const string& newPath);

bool moveFilesToDirectory(const string& filestype, const string& directoryPath);
 
void splitType();

void clone();

void showFile();

void showCommand();

void deClone();

void banish(int);

void help();

string getFilePath(const std::string& path) {
        auto pathEnd = path.find_last_of("/\\");
        auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);
        return pathName;
}
 
string getFileName(const std::string& path) {
        auto fileNameStart = path.find_last_of("/\\");
        auto fileName = fileNameStart == std::string::npos ? path : path.substr(fileNameStart + 1);
        return fileName;
}
 

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

bool moveFilesToDirectory(const string& filestype, const string& directoryPath){
    
    string newPath;
    newPath = directoryPath + "\\" + filestype;
    
  
    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();

        if(getFileExtension(currPath) == filestype){
            rmdir(newPath.c_str());
            mkdir(newPath.c_str());
        }
    }

    bool typeFound = false;

    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();

        if(getFileExtension(currPath) == filestype){
            cout << getFileName(currPath) << " --> has been moved to new directory : " << filestype << endl;
            moveFile(currPath,newPath + "\\" + getFileName(currPath));
            typeFound = true;
        }
    }

    return typeFound;
}

void splitType(){
    cout << "************************************************************************" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Current command : Split by type" << endl << " - Insert directory and filetype to split files into a new directory." << endl;
    cout << "* OR *" << endl;
    cout << " - Insert * to split all files in the directory.   " << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "************************************************************************" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);

    cout << "Choose your files type : ";
    string filesType;
    cin >> filesType;
    for (auto & c: filesType) c = tolower(c);

    cout << "------------------------------------------------------------------------" << endl;

    if(filesType == "*"){
        bool checkFiles = false;
        for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();

            if(getFileExtension(currPath) != filesType){
                filesType = getFileExtension(currPath);
                if(filesType != ""){
                    moveFilesToDirectory(filesType,directoryPath);
                    checkFiles = true;
                } 
            }
        }
        if(!checkFiles) cout << "This directory is empty." << endl;
        else cout << "All files have been moved successfully." << endl;
    }
    else if(!moveFilesToDirectory(filesType,directoryPath)) cout << "Not found any file with type " + filesType + "." << endl;
    else cout << "All files have been moved successfully." << endl;
    cout << "------------------------------------------------------------------------" << endl;
}

void cloneFile(string fullpath){

    //set path
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
    cout << "Outpath: "<< filePath + "\\" + s_filename + "(Cloned).txt"<<endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    //output file
    ofstream outfile(filePath + "\\" + s_filename + "(Cloned).txt" );
    outfile << "Path: " << filePath<<endl;
    outfile << "Name: " << s_filename << endl;
    outfile << "Size: " << size << " bytes"<<endl;
    outfile << "Extension:."<<extension<<endl; 
    outfile << "Created: " <<timecreate;
    outfile << "Last Modified: " << timemod;
    outfile.close();

    

}

void showFile(){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);

    for (const auto & entry : filesystem::recursive_directory_iterator(directoryPath))
        cout << entry.path() << ::endl;
}

void cloneFol(string directoryPath){
    string dupe ="(Cloned)(Cloned)";
    string sub = "(Cloned)";

    struct stat s;
    //1st loop for cloning flies.
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();
        if ((currPath.find(sub) != string::npos)) rmdir(currPath.c_str());

            if( fs::is_directory(currPath) ){
                string newPath = currPath + "(Cloned)";
                    if ((newPath.find(dupe) != string::npos)) {
                        rmdir(newPath.c_str());
                    }else{
                    rmdir(newPath.c_str());
                    mkdir(newPath.c_str());
                    }
            }
            else if( fs::is_regular_file(currPath)) {
                    cloneFile(currPath);
                }
    }
        

    //2nd loop for moving cloned files.
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();
        if ((currPath.find(sub) != string::npos)) ;
    }    
}

void clone(){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);

    cloneFol(directoryPath);
}

void deClone(){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);

    string dupe ="(Cloned)(Cloned)";
    string sub = "(Cloned)";

    for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();
        if ((currPath.find(sub) != string::npos)) rmdir(currPath.c_str());

            if( fs::is_directory(currPath) ){
                string newPath = currPath + "(Cloned)";
                    if ((newPath.find(dupe) != string::npos)) {
                        rmdir(newPath.c_str());
                    }else{
                    rmdir(newPath.c_str());
                    }
            }
            else if( fs::is_regular_file(currPath)) {
                if ((currPath.find(sub) != string::npos))
                    remove(currPath.c_str());
                }
    }

    cout<< "Succesfully remove all cloned directories from " << directoryPath<<endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

}

void banish(int arg){
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);
    
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();
        if(arg == 1){
            if( fs::is_regular_file(currPath)) remove(currPath.c_str());
        }else if(arg == 2){
            string FileFol = directoryPath + "\\file";
            rmdir(FileFol.c_str());
            mkdir(FileFol.c_str());
            if( fs::is_regular_file(currPath)) moveFile(currPath,FileFol);
        

            // for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)){
            //         if( fs::is_directory(currPath)) remove(currPath.c_str());
            //     }
            // }
            
        }
    }
    string forf; 
    if (arg == 1) forf ="files";
    else if (arg == 2) forf = "folders";
    cout<< "Succesfully remove all " << forf <<" directories from " << directoryPath<<endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
}

void moveFile(const string& oldPath, const string& newPath){
    rename(oldPath.c_str(), newPath.c_str());
}

/* idea splitdate
    * FUNCTION: getFileTimecreate 
    * USE: Returns the file time creation from a given file path
    * @param path: The path of the file
    * @return: The file time creation from the given file path
    
string getFileTimecreate(const std::string& path) {
        //  not complete now. 
         reference 
    struct stat fileInfo;
    if (stat(s_filename.c_str(), &fileInfo) != 0) {  // Use stat( ) to get the info
      std::cerr << "Error: " << strerror(errno) << '\n';
   }
    auto timecreate = ctime(&fileInfo.st_ctime);         // Creation time
    auto timemod = ctime(&fileInfo.st_mtime);         // Last mod time
    
}
*/

/*
void splitDate()
{
    cout << "************************************************************************" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Current command : Split by Date" << endl << " - Insert directory and fileDate to split files into a new directory." << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "************************************************************************" << endl;
    cout << "Choose your files directory : ";
    string directoryPath;
    getline(cin,directoryPath);
    // create <vector> to collect string from timecreate function (not complete)
    
    cout << "------------------------------------------------------------------------" << endl;
}
//  not complete yet.
/*
   if(filesType == "*"){
        bool checkFiles = false;
        for (const auto & entry : std::filesystem::directory_iterator(directoryPath)){
        string currPath;
        currPath = entry.path().string();
            if(getFileExtension(currPath) != filesType){
                filesType = getFileExtension(currPath);
                if(filesType != ""){
                    moveFilesToDirectory(filesType,directoryPath);
                    checkFiles = true;
                } 
            }
        }
        if(!checkFiles) cout << "This directory is empty." << endl;
        else cout << "All files have been moved successfully." << endl;
    }
    else if(!moveFilesToDirectory(filesType,directoryPath)) cout << "Not found any file with type " + filesType + "." << endl;
    else cout << "All files have been moved successfully." << endl;
    cout << "------------------------------------------------------------------------" << endl;
}
*/

void help(){
    cout<< "NAME:"<<endl 
        << "        spk - A fast, simple and clean files manaaging program"<<endl
        << "USAGE:"<<endl
        <<"        [COMMAND]...[DIRECTORY]"<<endl
        << "VERSION:"<<endl
        <<"        v1.0.0"<<endl
        << "COMMAND:"<<endl
        <<"        -help Shows a list of commands or help for one command"<<endl
        << "GLOBAL OPTIONS:"<<endl
        << "  --clone               Clone files or directories"<<endl
        << "  --sorttype            Sort files in all subdirectories by a file's extention to the single folder"<<endl
        << "  --sorttdate           Sort files in all subdirectories by a file's created time to the single folder"<<endl
        << "  --show                Shows all the files and folder in all subdirectories"<<endl
        << "  --dclone              Delete all the files with \"(Cloned)\" in it's name"<<endl
        << "  --dfi                 Delete all files in all subdirectories"<<endl
        << "  --dfol                Delete all folders in all sub directories"<<endl
        << "  --search              Search files from a specific attribute"<<endl
        << "  --help                Shows all commands";

}       

void search(){

string type;
double firstvalue,secondvalue;


cout<< " search by B KB MB GB TB : ";
getline(cin,type) ;

if(type == "B" or type == "KB" or type == "MB" or type == "GB" or type == "TB")	
{	

cout<< "input first value : ";
cin>>firstvalue;
cout<< "input second value : ";
cin>>secondvalue;



	struct dirent *d;
	struct stat folderorfile;
	
	DIR *dr;
	
	string path = ".\\";
	
	dr = opendir(path.c_str());


	if (dr != NULL)
	{
		for (d = readdir(dr); d != NULL; d = readdir(dr))
		{
			string filename = d->d_name;
			
			
			/*/if (stat(type.c_str(), &dst) == 0)
			{
				if (dst.st_mode & S_IFDIR)
				{
					type = "is a FOLDER.";
				}
				else if (dst.st_mode & S_IFREG)
				{
					type = "is a FILE.";
				}
			}
			/*/
			ifstream  myfile(  filename ,ios::binary);
			myfile.seekg(0 , ios:: end);
			float file_size = myfile.tellg();
         
         /*/cout<<filename<<endl;
         if(file_size<1024)
         {
            cout<< file_size<<" bytes"<<endl;
         }
         else if(file_size>=1024 and file_size<(1024*1024))
         {
            cout<< file_size<<" bytes"<<endl;
            cout<< file_size/1024<<" Kbytes"<<endl;
         }
         else if(file_size>=(1024*1024) and file_size<(1024*1024*1024))
         {
            cout<< file_size<<" bytes"<<endl;
            cout<< file_size/1024<<" Kbytes"<<endl;
            cout<< file_size/(1024*1024)<<" Mbytes"<<endl;
         }
         else if(file_size>=(1024*1024*1024) and file_size<(1024.00*1024*1024*1024))
         {
            cout<< file_size<<" bytes"<<endl;
            cout<< file_size/1024<<" Kbytes"<<endl;
            cout<< file_size/(1024*1024)<<" Mbytes"<<endl;
            cout<< file_size/(1024*1024*1024)<<" Gbytes"<<endl;
         }
         else if(file_size>=(1024.00*1024*1024*1024) and file_size<(1024.00*1024*1024*1024*1024))
         {
            cout<< file_size<<" bytes"<<endl;
            cout<< file_size/1024<<" Kbytes"<<endl;
            cout<< file_size/(1024*1024)<<" Mbytes"<<endl;
            cout<< file_size/(1024*1024*1024)<<" Gbytes"<<endl;
            cout<< file_size/(1024.00*1024*1024*1024)<<" Tbytes"<<endl;
         }/*/
              
                  if( type == "B")
                  {
                     if(file_size<1024)
                     {
                        //cout<< file_size<<" bytes";
                     }
                     

                        if(file_size  >=  firstvalue && file_size  <=  secondvalue)
                        {

                           
                           //show file
                           cout<<filename<<endl;
                           


                        }
                     
                  

                  }

                  else if( type == "KB")
                  {
                     if(file_size>=1024 and file_size<(1024*1024))
                     {
                        //cout<< file_size<<" Kbytes";
                        file_size=file_size/1024;
                     }

                    
                     
                        if(file_size  >=  firstvalue && file_size  <=  secondvalue)
                        {

                           
                           //show file
                           cout<<filename<<endl;
                           


                        }
                     

                  }

                  else if( type == "MB")
                  {
                     if(file_size>=(1024*1024) and file_size<(1024*1024*1024))
                     {
                        //cout<< file_size<<" Mbytes";
                        file_size=file_size/(1024*1024);
                     }

                    
                        if(file_size  >=  firstvalue && file_size  <=  secondvalue)
                        {

                           
                           //show file
                           cout<<filename<<endl;
                           


                        }
                   
                  
                     
                  }

                  else if( type == "GB")
                  {
                     if(file_size>=(1024*1024*1024) and file_size<(1024.00*1024*1024*1024))
                     { 
                        //cout<< file_size<<" Gbytes";
                        file_size=file_size/(1024*1024*1024);
                     }
               
                     
                        if(file_size  >=  firstvalue && file_size  <=  secondvalue)
                        {

                           
                           //show file
                           cout<<filename<<endl;


                        }
                     
                  

                  }

                  else if( type == "TB")
                  {
                     if(file_size>=(1024.00*1024*1024*1024) and file_size<(1024.00*1024*1024*1024*1024))
                     {
                        //cout<< file_size<<" Tbytes";
                        file_size=file_size/(1024.00*1024*1024*1024);
                     }
                     

                        if(file_size  >=  firstvalue && file_size  <=  secondvalue)
                        {

                           
                           //show file
                           cout<<filename<<endl;

                        }
                  
                  }
              
            
      }








			

	}
		closedir(dr);
}
else cout<< "ERROR";
}