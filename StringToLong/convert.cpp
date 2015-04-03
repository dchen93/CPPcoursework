/* 

stringToLong(string s)

Functionality: 
* converts a string to a long int
* converts by evaluating each char by its ascii value
* throws exception when char is not a number
* accurately handles negative numbers

Known Limitations:
* requires function call in a try-catch block for accurate usage, which is cumbersome.
		however, this is a necessity, unless we specify a specific int to return that denotes
		we found an illegal char in the string. A string that translates to aforementioned int 
		would incorrectly denote that we found an illegal char.

*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;


/////////////////////////////////////
/*      STRINGTOLONG FUNCTION      */
/////////////////////////////////////
long int stringToLong(string s){
	long int number = 0,len;
	bool negative = false; // whether number is negative

	len = s.length(); // length of string

	if(s[0] == '-'){
		negative = true;
		len--;
	}

	for(long int i = negative; i < s.length(); i++){ // starting from the most significant digit
		if((int)s[i] > 57 || (int)s[i] < 48){ // if char NaN, throw error
			throw -1;
		}
		number += ((int)s[i] - 48) * pow(10,--len); // add that digit to the correct place in number
	}

	if(negative){
		number = -1 * number;
	}

	return number;
}


////////////////////////////////////
/*     MAIN FUNCTION - TESTING    */
////////////////////////////////////
int main(){
	long int i,j,k;
	string test0,test1,test2;

	test0 = "0123456789";
	test1 = "-51";
	test2 = "abc";

	i = stringToLong(test0);
	j = stringToLong(test1);

	// test for when string isn't a number
	try
	{
		k = stringToLong(test2);
	}
	catch(int& e) // e would be -1 in this case
	{
		cout << "Correct -- " << test2 << " is not a number" << endl; // print string that is NaN
	}

	if(i == 123456789 && j == -51){
		cout << "success" << endl;
	}else{
		cout << "failure" << endl;
	}

	return 0;
}