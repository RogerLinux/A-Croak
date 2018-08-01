#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool StringComp(char a, char b){
	return a < b;
		}

int main(){

	char* arr = new char[10];

	srand(time(NULL));

	for(int i=0;i<10;i++)arr[i] = rand()%('z' - 'a') + 'a';
	for(int i=0;i<10;i++)cout << arr[i];
	cout << endl;

	sort(arr, arr+10, StringComp);

	for(int i=0;i<10;i++)cout << arr[i];
	cout << endl;

	delete[] arr;
		}
