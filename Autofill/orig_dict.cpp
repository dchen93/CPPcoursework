#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>


using namespace std;

class Dict{
	private:
		string filename;

	public:
		string full;
		string word;
		string phrase;
		char** sentence;
		
		
		Dict (string v){
			filename=v;
			sentence=parse();
		};
		
		//other periods than end of sentence
		char** parse(){
		
		  int plc=0;
		  int cnt=0;
		  int n=1;
			string temp;
			ifstream infile;
			
			infile.open(filename.c_str());
			while(!infile.eof()){
				getline(infile,temp); // Saves the line in STRING.
				full.append(temp);
			}
			full[full.length()] = '\0';  //won't this delete the last string in the array
			infile.close();
			
			char fuller[full.size()];
			strcpy(fuller,full.c_str());
			
			for (int i=0; i<strlen(fuller); i++ ){
			  if(fuller[i]=='\0'){
			    break;
			  } 
			  else if(fuller[i]=='.'){
			    
			    cnt++;  
			  }
			
			}
			
			char** tsent = new char*[cnt];
			for(int i = 0; i < cnt; ++i)
				tsent[i] = new char[100000];
			
			
			int len=0;
			int num=0;
			
			for (int i=0; i<strlen(fuller); i++){
			
			  if(fuller[i]!='.'){
			    tsent[num][len]=fuller[i];   //do we add period into the sentence
			    len++;
			  }
			  else{
			    len++;
			    tsent[num][len]='\0';
			    num++;
			    len=0;
			  }
			
			} 
			
			
			//tsent holds the sentences;
			
			  
			return ;
			
			
		};
			
			
			
};



/*int main() {

  Dict d("data.txt");
  
  
  char** str=d.sentence;
  cout<<str[0]<<endl;
  cout<<str[1]<<endl;
  cout<<str[2]<<endl;
  cout<<str[3]<<endl; 
  
  

   
  
  
  return 0; 
}  */
