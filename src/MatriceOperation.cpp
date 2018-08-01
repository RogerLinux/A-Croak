#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

class MatrixOperation{

	//vector<float> vector;
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
