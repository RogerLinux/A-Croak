#include <iostream>
#include <string>
#include "strTokenize.cpp"

using namespace std;

int main(){

	int n = 0;
	char ss[64], str[] = "    How     are ,,, you . Roger!!! !", *p = str;
	string s;
	cout << str << endl;

	do{
		s = strTokenize(&p);
		if(!s.empty()){
			for(int i = 0; i < s.size(); i++)ss[i] = s[i];
			printf("%s\n", ss);
			cout << s << endl << endl;		}
			}while(s.size() > 0);
	cout << endl;

	p = str;
	cout << strCount(p) << endl;
	return 0;
		}
