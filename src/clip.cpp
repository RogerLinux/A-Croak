#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

  void GradientClip(vector< vector<float> >& M, float th){
	float max = 0;

	for(int i=0;i<M.size();i++)
		for(int j=0;j<M[i].size();j++){
			if(M[i][j] > th)M[i][j] = th;
			else if(M[i][j] < -th)M[i][j] = -th;
							}
	return;
				}

  void GradientClip(vector< vector<float> >& M, float th, int target_no){
        float max = 0;

	for(int i=0;i<M[target_no].size();i++){
		if(M[target_no][i] > th)M[target_no][i] = th;
		else if(M[target_no][i] < -th)M[target_no][i] = -th;
					}
	return;
                                } 
