#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <string.h>

using namespace std;

class wordTrain{
  
  float abs(float x){
	if(x > 0)return x;
	else return -x;
				}

  void GradientClip(vector< vector<float> >& M, float th){
	float max = abs(M[0][0]);

	for(int i=0;i<M.size();i++)
		for(int j=0;j<M[i].size();j++)
			if(max < abs(M[i][j]))max = abs(M[i][j]);

	if(th < max)
		for(int i=0;i<M.size();i++)
                	for(int j=0;j<M[i].size();j++)
                        	M[i][j] *= float(th/max);

	return;
				}

  void GradientClip(vector< vector<float> >& M, float th, int target_no){
        float max = abs(M[target_no][0]);

        for(int i=0;i<M[target_no].size();i++)
                        if(max < abs(M[target_no][i]))max = abs(M[target_no][i]);

        if(th < max)
              for(int i=0;i<M[target_no].size();i++)
                       M[target_no][i] *= float(th/max);

        return;
                                }
 

  vector<float> activateFunc(vector<float> u){
	float sum = 0;
	vector<float> y;

	y.resize(u.size());

	for(int i=0;i<u.size();i++)sum += exp(u[i]);
	for(int i=0;i<u.size();i++)y[i] = exp(u[i])/sum;

	return y;
				}

  void backPropagation(int target_no, int n_gram, char** sent, int sent_size, char** lexicon, map<string, int> lexicon_map, vector< vector<float> >& W, vector< vector<float> >& V, int hidden_size, float LS){


	//if the word is out of vocabulary, give up
	if(lexicon_map.find(sent[target_no])==lexicon_map.end())return;

	MatrixOperation mop;
	Continuous_bag_of_word cbow;
	
	int n, lexicon_size = lexicon_map.size();
	float EH, sum;
	char** ngram = new char*[n_gram*2];
	vector<float> target_vec, h, u, y, Y;
	vector< vector<float> > V_tmp = V;

	//try to find all the context
	for(int i=0;i<2*n_gram;i++)ngram[i] = new char[64];

	n = 0;
	for(int i= max(0, target_no - n_gram); i < target_no; i++)strcpy(ngram[n++], sent[i]);
	for(int i= target_no + 1;i <= min(sent_size - 1, target_no + n_gram); i++){
			if(lexicon_map.find(sent[i])!=lexicon_map.end())strcpy(ngram[n++], sent[i]);
					}

	if(n==0)return; //Don't do anything if there is no context word

	target_vec = cbow.word_to_vec(sent[target_no], lexicon_map);

	//forward propagation
	h = mop.multiply(target_vec, W); //hidden layer
	u = mop.multiply(h, V); //output before being activated
	y = activateFunc(u); //output after being activated

	//set context words as 1, otherwise 0

	Y.resize(y.size());
        for(int i=0;i<Y.size();i++)Y[i] = 0;
        for(int i=0;i<n;i++)Y[lexicon_map[ngram[i]]] = 1;

	//Update weights in V

	for(int i=0;i<y.size();i++)
		for(int j=0;j<hidden_size;j++)
			 V[j][i] -= LS * h[j] * (y[i] - Y[i]);

	//Update weights in W

	int i = lexicon_map[sent[target_no]];

		for(int j=0;j<hidden_size;j++){ //hidden layer
			EH = 0;
			for(int k=0;k<lexicon_size;k++) // y layer
				EH += (y[k] - Y[k]) * V_tmp[j][k];

			W[i][j] -= LS*EH * target_vec[i];
					}
	return;
	}

public:
	//train each sentence
	bool trainModel(FILE* fp, int n_gram, char** lexicon, map<string, int> lexicon_map, vector< vector<float> >& W, vector< vector<float> >& V, int hidden_size, float LS){

        int n, target_no, sent_len=0, lexicon_size;
        char** sent, w[64], *filename;

	if(fp == NULL)return false;

	rewind(fp);
	//count words in the sentence
        while(fscanf(fp, "%s", w)!=EOF)sent_len++;

        sent = new char*[sent_len];
        for(int i=0;i<sent_len;i++)sent[i] = new char[64];
        rewind(fp);
        n = 0;

	//store sentence in an array
        while(fscanf(fp, "%s", w)!=EOF)strcpy(sent[n++], w);

	//show sentence

	cout << ": ";
        for(int i=0;i<sent_len;i++)printf("%s ", sent[i]);
        cout << endl;

	//start back propagation
	for(int i=0;i<sent_len;i++){
		if(lexicon_map.find(sent[i]) != lexicon_map.end())GradientClip(W, 1, lexicon_map[sent[i]]);
		GradientClip(V, 1);
        	backPropagation(i, n_gram, sent, sent_len, lexicon, lexicon_map, W, V, hidden_size, LS);
						}
	return true;
				}
};
