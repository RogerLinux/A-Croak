#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <a-croak.cpp>
#include <sortTool.cpp>

using namespace std;

int main(int argc, char** argv){

	FILE* fp_weight = fopen(argv[1], "r");
	FILE* fp_lexicon = fopen(argv[2], "r");
	int n, m;//n (row) is word vector dimension, m (col) is hidden layer dimension
	float tmp;
	char w[64], filename[128];

	vector<float> target_vec;
	vector<vector <float> > W, V;
	map<string, int> lexicon_map;
	vector<float> num_list;
	vector<string> str_list;
	char** lexicon;

	sentenceProcess sp;
	Matrix M;
	wordTrain wt;

	if(fp_weight == NULL || fp_lexicon == NULL){
		cout << "Usage: similarity model lexicon" << endl << endl;
		cout << "model: Trained model" << endl;
		cout << "lexicon: Trained words" << endl;
		cout << "0 is OK" << endl;
		cout << "1 is wrong" << endl;
		return 1;
				}

	fscanf(fp_weight, "%d %d", &n, &m);

	W.resize(n);
	for(int i=0;i<n;i++)W[i].resize(m);
	V.resize(m);
	for(int i=0;i<m;i++)V[i].resize(n);

	lexicon = new char*[n];
	for(int i=0;i<n;i++)lexicon[i] = new char[64];

	cout << "Reading the model ..." << endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			fscanf(fp_weight, "%f ", &tmp);
			W[i][j] = tmp;
						}
	for(int i=0;i<m;i++)
                for(int j=0;j<n;j++){
                        fscanf(fp_weight, "%f ", &tmp);
                        V[i][j] = tmp;          
                                                }

	lexicon_map = sp.lexicon_creator(fp_lexicon);
	rewind(fp_lexicon);
	lexicon = sp.lexicon_creator(fp_lexicon, &n);

	cout << "Which word do you want ?" << endl;
	scanf("%s", w);
	if(lexicon_map.find(w)==lexicon_map.end())return 2;

	target_vec = sp.word_to_vec(w, lexicon_map);

	vector<float> h = M.multiply(target_vec, W);
	vector<float> u = M.multiply(h, V);
	vector<float> y = wt.activateFunc(u);

	//for(int i=0;i<y.size();i++)fprintf(fp, "%f %d %s\n", y[i], i, lexicon[i]);
	for(int i = 0; i < y.size(); i++)num_list.push_back(y[i]);
	for(int i = 0; i < y.size(); i++)str_list.push_back(lexicon[i]);

	pairSort(str_list.begin(), str_list.end(), num_list.begin(), num_list.end());

	sprintf(filename, "%s_on_%s", w, argv[1]);

	FILE* ptr_exp = fopen(filename, "w");
	if(!ptr_exp)return 1;

	for(int i = str_list.size() - 1; i >= 0; i--){
		int j;
		char* c = new char [128];
		for(j = 0; j < str_list[i].size() && str_list[i][j] != '\0' && j < 128; j++){
			c[j] = str_list[i][j];
				}
		c[j] = '\0';
		fprintf(ptr_exp, "%s %f\n", c, num_list[i]);
		delete[] c;
				}
	fclose(ptr_exp);
	return 0;
		}
