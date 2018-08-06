#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <math.h>
#include <strTokenize.cpp>

using namespace std;

/*float abs(float x){
	if(x < 0)return -x;
	else return x;
			}*/

float max(float x, float y){
	if(x > y)return x;
	else return y;
			}

vector< vector<float> > weight_assign(int row, int col, int type){
               vector< vector<float> > matr;
               float x = row;

		matr.resize(row);

                for(int n=0;n<row;n++)matr[n].resize(col);
                if(type == 0)
                        for(int n=0;n<row;n++)
                                for(int m=0;m<col;m++)
                                        matr[n][m] = 0;

                else
                         for(int n=0;n<row;n++)
                                 for(int m=0;m<col;m++)
                                         matr[n][m] = float((rand()%2000 - 1000)/(1000*sqrt(x)));
                return matr;
                                        }

class sentenceProcess{

	int n, m, k; //basic meaningless parameters
	float fln; //basic float-point numbers
	char w[64]; //tmp word buffer
	vector<float> vec; //vectors
	vector< vector<float> > matr; //matrices

public:

	char* lexicon_creator(FILE* fp, char* filename){

		FILE* fp_tmp = fopen(".tmp", "w");
		char command[1024];

		rewind(fp);
		while(fscanf(fp, "%s", w)!=EOF)fprintf(fp_tmp, "%s\n", w);
		fclose(fp_tmp);

		sprintf(command, "sort .tmp | uniq -c | sort -k 1 -n -r > %s", filename);

		system(command);
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

class Matrix{

	vector< vector <float> > arr;

public:
	void show(vector<float> vec){
		for(int n=0;n<vec.size();n++)cout << vec[n] << " ";
		cout << endl;

		return;
				}

	void show(vector< vector<float> > M){
			for(int n=0;n<M.size();n++){
				for(int m=0;m<M[n].size();m++)
					cout << M[n][m] << " ";
				cout << endl;
				}
			return;
					}

	void show(vector< vector<char> > M){
                         for(int n=0;n<M.size();n++){
                                 for(int m=0;m<M[n].size();m++)
                                         cout << M[n][m];
                                 cout << endl;
                                 }
                         return;
                                         }

	vector< vector<float> > transpose(vector< vector<float> > A){
			arr.resize(A[0].size());
			for(int i=0;i<A[0].size();i++)arr[i].resize(A.size());
			for(int n=0;n<arr.size();n++)
				for(int m=0;m<arr[n].size();m++)
					arr[n][m] = A[m][n];
			return arr;
					}

	vector <float> add(vector<float> A, vector<float> B){
		vector<float> vec;

		for(int n=0;n<A.size();n++)vec.push_back(A[n] + B[n]);
		return vec;	
					}

	vector< vector<float> > add(vector< vector<float> > A, vector< vector<float> > B){
			int M= A.size(), n;

			arr.resize(M);
			for(int i=0;i<M;i++)arr[i].resize(A[i].size());

			for(int n=0;n<M;n++)
				for(int m=0;m<A[n].size();m++)
					arr[n][m] = A[n][m] + B[n][m];
			return arr;
					}

	vector< vector<float> > scalar(vector< vector<float> >A, float a){
			arr.resize(A.size());
			for(int n=0;n<A.size();n++)arr[n].resize(A[n].size());
			for(int n=0;n<A.size();n++)
				for(int m=0;m<A[n].size();m++)
					arr[n][m] = a*A[n][m];
			return arr;
					}

	float dot(vector<float> A, vector<float> B){
			float val = 0;
			for(int n=0;n<A.size();n++)val += A[n] * B[n];
			return val;
					}

	vector<float> multiply(vector<float> A, vector< vector<float> > B){
			vector<float> vec;
			float tmp;
			for(int n=0;n<B[0].size();n++){
				tmp = 0;
				for(int m=0;m<A.size();m++)tmp += A[m] * B[m][n];
				vec.push_back(tmp);
						}
			return vec;
					}

	vector< vector <float> > multiply(vector< vector<float> >A, vector< vector<float> >B){
			arr.resize(A.size());
			for(int i=0;i<A.size();i++)arr[i].resize(B[0].size());

			for(int n=0;n<arr.size();n++)
				for(int m=0;m<arr[n].size();m++)
					arr[n][m] = 0;

			for(int n=0;n<arr.size();n++)
				for(int m=0;m<arr[n].size();m++)
					for(int k=0;k<B.size();k++)
						arr[n][m] += A[n][k] * B[k][m];
			return arr;
					}
				};

class wordTrain{

  void GradientClip(vector< vector<float> >& M, float th){
	float max = 0;

	for(int i=0;i<M.size();i++)
		for(int j=0;j<M[i].size();j++){
			if(M[i][j] > th)M[i][j] = th;
			else if(M[i][j] < -th)M[i][j] = -th;
							}
	return;

	th *= M.size() * M[0].size();

	for(int i=0;i<M.size();i++)
		for(int j=0;j<M[i].size();j++)max += M[i][j] * M[i][j];

	max = sqrt(max);

	if(th < max)
		for(int i=0;i<M.size();i++)
                	for(int j=0;j<M[i].size();j++)
                        	M[i][j] *= float(th/max);

	return;
				}

  void GradientClip(vector< vector<float> >& M, float th, int target_no){
        float max = 0;

	for(int i=0;i<M[target_no].size();i++){
		if(M[target_no][i] > th)M[target_no][i] = th;
		else if(M[target_no][i] < -th)M[target_no][i] = -th;
					}

	return;

	th *= M[target_no].size();

        for(int i=0;i<M[target_no].size();i++)max = M[target_no][i] * M[target_no][i];

	max = sqrt(max);

        if(th < max)
              for(int i=0;i<M[target_no].size();i++)
                       M[target_no][i] *= float(th/max);

        return;
                                }
public: 
	//sigmoid function
  vector<float> activateFunc(vector<float> u){
	vector<float> y;

	y.resize(u.size());

	for(int i=0;i<u.size();i++)y[i] = exp(u[i])/(1 + exp(u[i]));

	return y;
				}

  void backPropagation(int target_no, int n_gram, char** sent, int sent_size, char** lexicon, map<string, int> lexicon_map, vector< vector<float> >& W, vector< vector<float> >& V, int hidden_size, float LS){


	//if the word is out of vocabulary, give up
	if(lexicon_map.find(sent[target_no])==lexicon_map.end())return;

	Matrix M;
	sentenceProcess sp;
	
	int n, lexicon_size = lexicon_map.size();
	float EH, sum;
	char** ngram = new char*[n_gram*2];
	vector<float> target_vec, h, u, y, Y;
	vector< vector<float> > V_tmp = V;

	//try to find all the context
	for(int i=0;i<2*n_gram;i++)ngram[i] = new char[64];

	n = 0;
	for(int i= max(0, target_no - n_gram); i < target_no; i++)
			if(lexicon_map.find(sent[i])!=lexicon_map.end())
				strcpy(ngram[n++], sent[i]);
	for(int i= target_no + 1;i <= min(sent_size - 1, target_no + n_gram); i++)
			if(lexicon_map.find(sent[i])!=lexicon_map.end())
				strcpy(ngram[n++], sent[i]);

	if(n==0)return; //Don't do anything if there is no context word

	//target_vec = sp.word_to_vec(sent[target_no], lexicon_map);
	h.resize(hidden_size);
	//forward propagation
	for(int i=0;i<hidden_size;i++)h[i] = W[lexicon_map[sent[target_no]]][i];
	//h = M.multiply(target_vec, W); //hidden layer
	u = M.multiply(h, V); //output before being activated
	y = activateFunc(u); //output after being activated

	//set context words as 1, otherwise 0

	Y.resize(y.size());
        for(int i=0;i<Y.size();i++)Y[i] = 0;
        for(int i=0;i<n;i++)Y[lexicon_map[ngram[i]]] = 1;

	//Update weights in V

	for(int i=0;i<y.size();i++){
		for(int j=0;j<hidden_size;j++){
			V[j][i] -= LS * h[j] * max(y[i] - y[i] * y[i], 0.000001) * (y[i] - Y[i]);
			//V[j][i] -= cos(u[i]) * LS * h[j] * (y[i] - Y[i]);
					} 
				}

	//Update weights in W

	int i = lexicon_map[sent[target_no]];

		for(int j=0;j<hidden_size;j++){ //hidden layer
			EH = 0;
			for(int k=0;k<lexicon_size;k++){ // y layer
				EH += (y[k] - Y[k]) * max(y[k] * (1 - y[k]), 0.000001) * V_tmp[j][k];
				//EH += (y[k] - Y[k]) * V_tmp[j][k];
						}
			//W[i][j] -= LS * EH * target_vec[i];
			W[i][j] -= LS * EH;
					}

	for(int i=0;i<2*n_gram;i++)delete[] ngram[i];
	delete[] ngram;

	return;
	}

public:
	//train each sentence
	bool trainModel(char* str, int n_gram, char** lexicon, map<string, int> lexicon_map, vector< vector<float> >& W, vector< vector<float> >& V, int hidden_size, float LS){

        int n, target_no, sent_len=0, lexicon_size;
        char** sent, w[64], *filename, *p = str;
	string s;
	vector< vector<float> > M_tmp;

	if(!p)return false;

	//count words in the sentence
        //while(fscanf(fp, "%s", w)!=EOF)sent_len++;
	sent_len = strCount(p);

        sent = new char*[sent_len];
        for(int i=0;i<sent_len;i++)sent[i] = new char[64];
        n = 0;

	//store sentence in an array
        //while(fscanf(fp, "%s", w)!=EOF)strcpy(sent[n++], w);
	for(int i = 0; i < sent_len; i++){
		s = strTokenize(&p);
		for(int j = 0; j < s.size(); j++)sent[i][j] = s[j];
				}

	//show sentence
	cout << ": ";
        for(int i=0;i<sent_len;i++)printf("%s ", sent[i]);
        cout << endl;

	Matrix M;

	//start back propagation
	for(int i=0;i<sent_len;i++){
		if(lexicon_map.find(sent[i]) != lexicon_map.end())GradientClip(W, 1, lexicon_map[sent[i]]);
		GradientClip(V, 1);
        	backPropagation(i, n_gram, sent, sent_len, lexicon, lexicon_map, W, V, hidden_size, LS);
					}

	for(int i=0;i<sent_len;i++)delete[] sent[i];
	delete[] sent;

	return true;
				}
};
