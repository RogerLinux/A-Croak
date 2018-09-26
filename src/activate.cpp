//Sigmoid function
vector<float> sigmoid(vector<float> u){
	vector<float> y;

	y.resize(u.size());

	for(int i=0;i < u.size(); i++)y[i] = exp(u[i])/(1 + exp(u[i]));

	return y;
				}

//Function for hidden layers
float sigmoid(float u){
	float val = (exp(u) - exp(-u))/(exp(u) + exp(-u));

	return val;
				}

float tanH(float u){
	float val = (exp(u) - exp(-u))/(exp(u) + exp(-u));

	return val;
				}

vector<float> tanH(vector<float> u){
	vector<float> y;

	y.resize(u.size());

	for(int i = 0; i < u.size(); i++)y[i] = (exp(u[i]) - exp(-u[i]))/(exp(u[i]) + exp(-u[i]));

	return y;
				}
