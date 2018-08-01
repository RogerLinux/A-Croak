#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <math.h>

using namespace std;

class Continuous_bag_of_word{

	int n, m, k; //basic meaningless parameters
	float fln; //basic float-point numbers
	char w[64]; //tmp word buffer
	vector<float> vec; //vectors
	vector< vector<float> > matr; //matrices

public:
	vector< vector<float> > matrices_creator(int row, int col, int type){
		matr.resize(row);
		float x = row;

		for(n=0;n<row;n++)matr[n].resize(col);
		if(type == 0)
			for(n=0;n<row;n++)
				for(m=0;m<col;m++)
					matr[n][m] = 0;

		else
                         for(n=0;n<row;n++)
                                 for(m=0;m<col;m++)
                                         matr[n][m] = float((rand()%2000 - 1000)/(1000*sqrt(x)));
		return matr;
					}

	char* word_list_creator(FILE* fp){
		map<string, int> list;
		map<string, int>::iterator it;
		char filename[] = "lexicon.txt";
		FILE* fp_tmp = fopen(".tmp", "w");

		rewind(fp);
		while(fscanf(fp, "%s", w)!=EOF)fprintf(fp_tmp, "%s\n", w);
		fclose(fp_tmp);

		system("sort .tmp | uniq -c | sort -k 1 -n -r > lexicon.txt");
		system("rm -f .tmp");
		
		return filename;
					}

	map<string, int> lexicon_creator(FILE* fp){

		map<string, int> lexicon_map;

		n = 0;
		while(fscanf(fp, "%d %s", &m, w)!=EOF)lexicon_map[w] = n++;

		return lexicon_map;
					}

	char** lexicon_creator(FILE* fp, int* lexicon_size){ //redesign this func
		char** lexicon;
		int num = 0, no;

		while(fscanf(fp, "%d %s", &no, w)!=EOF)num++;

		lexicon = new char*[num];
		for(n=0;n<num;n++)lexicon[n] = new char[64];

		n = 0;
		rewind(fp);
		while(fscanf(fp, "%d %s", &no, w)!=EOF)strcpy(lexicon[n++], w);

		*lexicon_size = num;

		return lexicon;
					}

	vector<float> word_to_vec(char* target, map<string, int> lexicon_map){
		vec.resize(lexicon_map.size());

		for(int i=0;i<vec.size();i++)vec[i] = 0;
		vec[lexicon_map[target]] = 1;

		return vec;
						}
				};
