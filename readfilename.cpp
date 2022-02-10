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

string getFilePath(const string& path);
 
string getFileName(const string& path);
 
string getFileExtension(const string& path);

void search();

void bookmark();

int main(){
    
    //set path
    string fullpath = "C:\\Users\\eak_k\\Downloads\\C\\Git Beginner\\SourcePrikProject\\text.txt";
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
 
 /*
   //file size 
   ifstream  myfile(  "text.txt"  ,ios::binary);
   myfile.seekg(0 , ios:: end);
   float file_size =  myfile.tellg();
   if(file_size<1024)
   {
      cout<< file_size<<" bytes";
   }
   else if(file_size>=1024 and file_size<(1024*1024))
   {
    file_size=file_size/1024;
    cout<< file_size<<" Kbytes";
   }
   else if(file_size>=(1024*1024) and file_size<(1024*1024*1024))
   {
     file_size=file_size/(1024*1024);
     cout<< file_size<<" Mbytes";
   }
   else if(file_size>=(1024*1024*1024) and file_size<(1024.00*1024*1024*1024))
   {
     file_size=file_size/(1024*1024*1024);
     cout<< file_size<<" Gbytes";
   }
   else if(file_size>=(1024.00*1024*1024*1024) and file_size<(1024.00*1024*1024*1024*1024))
   {
     file_size=file_size/(1024.00*1024*1024*1024);
     cout<< file_size<<" Tbytes";
   }
/*
    
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
	

