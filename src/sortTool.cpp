#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(vector<float>::iterator it1, vector<float>::iterator it2){
	if(it1 == it2)return;
	float tmp = *it1;

	*it1 = *it2;
	*it2 = tmp;

	return;
				}

void swap(vector<string>::iterator it1, vector<string>::iterator it2){
	if(it1 == it2)return;
	string str = *it1;

	*it1 = *it2;
	*it2 = str;

	return;
				}

void pairSort(vector<string>::iterator str_begin, vector<string>::iterator str_end, vector<float>::iterator num_begin, vector<float>::iterator num_end){

	if(str_begin + 1 == str_end || str_begin == str_end)return;
	else if(str_begin > str_end)return;

	string p_str = *str_begin;
	float p_n = *(num_end - 1);
	vector<float>::iterator it_head, it_tail;
	vector<string>::iterator str_head, str_tail;

	it_head = num_begin;
	it_tail = num_end - 1;

	str_head = str_begin;
	str_tail = str_end - 1;

	while(it_head != it_tail){
		if(p_n < *it_head){
			swap(it_head, --it_tail);
			swap(str_head, --str_tail);
					}
		else {
			it_head++;
			str_head++;
					}
				}

	swap(it_head, num_end - 1);
	swap(str_head, str_end - 1);

	pairSort(str_begin, str_head, num_begin, it_head);
	pairSort(str_head + 1, str_end, it_head + 1, num_end);

	return;
			}
