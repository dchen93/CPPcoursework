#include "phrase.h"

using namespace std;

Phrase (string str){
	input_phrase = str;
}

void complete(const Dict &d){
		
	vector<string>::iterator x;
	vector<string> temp = d.phrases;
	for(x=temp.begin(); x!=temp.end(); x++){
		string st=*x;
		int q=st.length();
	
		if(completion.size()==10){
			return;
		}

		if (st.compare(0,input_phrase.length(),input_phrase) == 0){ // position 0 to end of input_sentence, compared to any part of sentences[i] of the input sentence length
			completion.push_back(*x);		
		} 
	}	
}
	
void check(const Dict &d){
	
	vector<int> hd;
	int cdist;
	int in_len=input_phrase.length();
	int l;
	string in_str;

	vector<string>::iterator x;
	vector<string> temp = d.phrases;		
	for(x=temp.begin(); x!=temp.end(); x++){
		in_str=input_phrase;
		string st=*x;

		if(st==" "){
			hd.push_back(100);
			continue;
		}
			
		int st_len=st.length();
		st.erase(st_len-1); // removes the space
		
		cdist=abs(st_len-in_len);
			
		if (in_len<st_len){
			st=st.substr(0,in_len);
			l=in_len;
		}
			
		if (in_len>st_len){
			in_str=in_str.substr(0,st_len);
			l=st_len;
		}
			
		for (int n=0; n<l; n++){
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

			if(strvec.size()==20){
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

void show(){
	endl (cout);
	cout<<"PHRASE completion for: "<<input_phrase<<endl;
	cout<<"------------------------------"<<endl;
	for(int x=0; x<completion.size(); x++){
		cout<<completion[x]<<endl;
	}
	endl (cout);

	cout<<"PHRASE correction for: "<<input_phrase<<endl;
	cout<<"------------------------------"<<endl;
	for(int x=0; x<checked.size(); x++){
		cout<<checked[x]<<endl;
	} 
	endl (cout);
}