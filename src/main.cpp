#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string.h>
#include <a-croak.cpp>

using namespace std;

//void trainModel(FILE* fp, int n_gram, char** lexicon, map<string, int> lexicon_map, vector< vector<float> >& W, vector< vector<float> >& V, int hidden_size, float learning_speed)
int main(int argc, char** argv){

	sentenceProcess sp;
	Matrix M;
	wordTrain wt;

	if(argc != 6){
		cout << "Usage : A-croak text lexicon ngram hidden_dimension learning_rate" << endl;
		cout << "System would access to previous models (i.e. model.org) first, or it would randomly build a model if no model is in the same directory" << endl;
		cout << "Clipping Method has been used for avoiding gradient explosion" << endl;
		cout << "Return value: " << endl;
		cout << "0 is OK" << endl;
		cout << "1 is error" << endl;
		return 1;
				}

	FILE* fp = fopen(argv[1], "r"), *fp_sub, *fp_lex, *fp_mod;
	if(fp == NULL)return 1;
	int n, m, n_gram, hidden_size = 64, lexicon_size;
	float LS, tmp;
	char** lexicon, c = '\0', *str = new char[10000];
	map<string, int> lexicon_map;
	vector< vector<float> > W, V;

	//determine n-gram and hidden dimension
	n_gram = atoi(argv[3]);
	hidden_size = atoi(argv[4]);

	//build lexicon if no lexicon in the directory
	fp_lex = fopen(argv[2], "r");
	if(fp_lex==NULL)sp.lexicon_creator(fp, argv[2]);
	fclose(fp);
	fclose(fp_lex);

	fp_lex = fopen(argv[2], "r");
	if(fp_lex == NULL)return 1;

	//store lexicon
	lexicon = sp.lexicon_creator(fp_lex, &lexicon_size);
	rewind(fp_lex);
	lexicon_map = sp.lexicon_creator(fp_lex);
	rewind(fp_lex);

	if(lexicon_size > 100000){cout << "lexicon is too large" << endl;return 1;}

	//read model
	fp_mod = fopen("model", "r");

	if(fp_mod==NULL){
		cout << "Building a model ..." << endl;
		W = weight_assign(lexicon_size, hidden_size, 1);
		V = weight_assign(hidden_size, lexicon_size, 1);
				}
	else{
		fscanf(fp_mod, "%d %d", &n, &m);
		if(n != lexicon_size){cout << "ERROR: lexicon size and input dimension don't agree" << endl;return 1;}
		if(m != hidden_size){cout << "ERROR: hidden dimension and V don't agree" << endl;return 1;}
		W.resize(n);
        	for(int i=0;i<n;i++)W[i].resize(m);
        	V.resize(m);
        	for(int i=0;i<m;i++)V[i].resize(n);

        	cout << "Reading the model ..." << endl;
        	for(int i=0;i<n;i++)
                	for(int j=0;j<m;j++){
                        	fscanf(fp_mod, "%f ", &tmp);
                        	W[i][j] = tmp;
                                                }
        	for(int i=0;i<m;i++)
                	for(int j=0;j<n;j++){
                        	fscanf(fp_mod, "%f ", &tmp);
                        	V[i][j] = tmp;
                                                }
				}

	fclose(fp);
	fp = fopen(argv[1], "r");

	FILE* fp_w = fopen("model.org", "w");

	fprintf(fp_w, "%d %d\n", lexicon_size, hidden_size);

	for(int i=0;i<W.size();i++){
                for(int j=0;j<W[i].size();j++)fprintf(fp_w, "%f ", W[i][j]);
                        fprintf(fp_w, "\n");
                                }

	for(int i=0;i<V.size();i++){
                for(int j=0;j<V[i].size();j++)fprintf(fp_w, "%f ", V[i][j]);
                        fprintf(fp_w, "\n");
                                }
	int num = 0;

	if(argc==6)LS = atof(argv[5]);

	if(!fp)cout << "ERROR: Corpus not found" << endl;

	n = 0;

	while(fp){
		c = fgetc(fp);
		if(c == EOF)break;
		str[n++] = c;

		if(c=='\n' || c=='.'){
			char* ptr = str;
			if(strCount(ptr)){
				cout << num++ << " ";
				str[n] = '\0';
				//train one sentence
				wt.trainModel(str, n_gram, lexicon, lexicon_map, W, V, hidden_size, LS);
						}
			n = 0;
					}
				}

	fclose(fp_w);
	fp_w = fopen("model", "w");

	cout << "Saving model ..." << endl;

	fprintf(fp_w, "%d %d\n", lexicon_size, hidden_size);

	for(int i=0;i<W.size();i++){
		for(int j=0;j<W[i].size();j++)fprintf(fp_w, "%f ", W[i][j]);
			fprintf(fp_w, "\n");
				}

	fprintf(fp_w, "\n\n\n\n\n\n");

	for(int i=0;i<V.size();i++){
                for(int j=0;j<V[i].size();j++)fprintf(fp_w, "%f ", V[i][j]);
                        fprintf(fp_w, "\n");
                                }
	fclose(fp_w);
	for(int i=0;i<lexicon_size;i++)delete[] lexicon[i];
	delete[] lexicon;
	delete[] str;

	cout << "Analysis ends !!!" << endl;
	return 0;
				}
