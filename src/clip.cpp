#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <math.h>

using namespace std;

float abs(float x){
	if(x < 0)return -x;
	else return x;
			}

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
