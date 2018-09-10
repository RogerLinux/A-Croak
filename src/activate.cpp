//Sigmoid function
vector<float> activateFunc(vector<float> u){
	vector<float> y;

	y.resize(u.size());

	for(int i=0;i < u.size(); i++)y[i] = exp(u[i])/(1 + exp(u[i]));

	return y;
				}

//Function for hidden layers
vector<float> activateFuncHidden(vector<float> u){
	vector<float> y;

	y.resize(u.size());

	for(int i = 0; i < u.size(); i++)y[i] = (exp(u[i]) - exp(-u[i]))/(exp(u[i]) + exp(-u[i]));

	return y;
				}

