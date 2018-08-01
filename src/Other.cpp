#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

char* fgetline(FILE* fp, int buffer_size, int line){
	char* sent = new char[buffer_size];
	int n=0, newline=0;
	char c;
	
	while(newline + 1 != line)
		if(fgetc(fp) == '\n')newline++;
	do{
		c = fgetc(fp);
		sent[n++] = c;
			}while(c != '\n');
	return sent;
			}

char** catch_to_list(FILE* fp, int* words){
	char** sent;
	int num=0, N=0;
	char str[64];

	while(fscanf(fp, "%s", str)!=EOF)num++;
	rewind(fp);
	*words = num;
	sent = new char*[num];
	for(int n=0;n<num;n++)sent[n] = new char[64];
	
	while(fscanf(fp, "%s", str)!=EOF){
		for(int n=0;n<strlen(str);n++)sent[N][n] = str[n];
		N++;
				}
	return sent;
				}

