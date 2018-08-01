#include <iostream>
#include <string>

using namespace std;

string strTokenize(char** p){
	if(p == NULL || *p == NULL || **p == '\0')return "";
	string str;

	while(**p == ' ' || **p == '\n')(*p)++;
	while(**p != ' ' && **p != '\0' && **p != '\n'){
		str.push_back(**p);
		(*p)++;
			}
	str.push_back('\0');
	return str;
		}

int strCount(char* p){
	int cnt = 0;
	if(!p)return 0;

	while(*p == ' ')p++;

	while(*p != '\0' && *p != '\n'){
		while(*p != ' ' && *p != '\0' && *p != '\n')p++;
		while(*p == ' ' && *p != '\0' && *p != '\n')p++;
		cnt++;
			}
	return cnt;
		}
