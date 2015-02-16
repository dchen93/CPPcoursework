#include "word.h"

using namespace std;

Word::Word (string str){
	input_word = str;
}

void Word::complete(const Dict &d){
	vector<string>::iterator x;
	vector<int>::iterator y;
	vector<string> temp = d.words;
	vector<int> clen;
	vector<string> sortvec;
	vector<string> chosenstr;
	int p;
	
	for(x=temp.begin(); x!=temp.end(); x++){
		string st=*x;

		if(completion.size()==10){
			break;
		} 
		if (st.compare(0,input_word.length(),input_word) == 0){ // position 0 to end of input_sentence, compared to any part of sentences[i] of the input sentence length
			chosenstr.push_back(*x);		
			clen.push_back((*x).length());
		} 
	}	
	
	for(int n=0; n<400; n++){
		sortvec.clear();
		for(y=clen.begin(); y!=clen.end(); y++){
			p=y-clen.begin();
			if((*y)==n){
				sortvec.push_back(chosenstr[p]);
			}
		}
		
		sort(sortvec.begin(),sortvec.end());	
		for(x=sortvec.begin(); x!=sortvec.end(); x++){
			completion.push_back(*x);
			
			if(completion.size()==10){
				n=900;
				break;	
			}				
		}
	}

}

void Word::check(const Dict &d){
	vector<int> hd;
	int cdist;
	int in_len=input_word.length();
	int slen;
	string in_str;
		
	vector<string>::iterator x;
	vector<string> temp = d.words;		
	for(x=temp.begin(); x!=temp.end(); x++){
		
		in_str=input_word;
		string st=*x;
		if(st=="."){
			hd.push_back(100);
			continue;
		}
			
		int st_len=st.length();
		//st.erase(st_len-1);
			
		cdist=abs(st_len-in_len);
			
		if (in_len<st_len){
			st=st.substr(0,in_len);
			slen=in_len;
		}
			
		if (in_len>st_len){
			in_str=in_str.substr(0,st_len);
			slen=st_len;
		}
		else
			slen = st_len;

		for (int n=0; n<slen; n++){
			if(st[n]!=in_str[n]){
				cdist=cdist+1;
			}
		}

		hd.push_back(cdist);
			
	}
		
		
	int hdpos;
	vector<int>::iterator y;	
	vector<int> dvec;
	vector<string> strvec;
	for(int num=0;  num<100; num++){	
		strvec.clear();	
		for(y=hd.begin(); y!=hd.end(); y++){
			hdpos=y-hd.begin();
			if(strvec.size()==100){
				num=101;
				break;					
			} 
			if((*y)==num){
				strvec.push_back(temp[hdpos]); //strvect
			}
		}	
			
		sort(strvec.begin(),strvec.end());	
		for(x=strvec.begin(); x!=strvec.end(); x++){
			checked.push_back(*x);
				
			if(checked.size()==10){
				num=101;
				break;	
			}									
		}
	}	 	
}

void Word::show(){
	endl (cout);
	cout<<"WORD completion for: "<<input_word<<endl;
	cout<<"------------------------------"<<endl;
	for(unsigned int x=0; x<completion.size(); x++){
		cout<<completion[x]<<endl;
	}
	endl (cout);

	cout<<"WORD correction for: "<<input_word<<endl;
	cout<<"------------------------------"<<endl;
	for(unsigned int x=0; x<checked.size(); x++){
		cout<<checked[x]<<endl;
	} 
	endl (cout);
}