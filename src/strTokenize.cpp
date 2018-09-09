using namespace std;

//return a word in the row
string strTokenize(char** p){
	if(p == NULL || *p == NULL || **p == '\0')return "";
	string str;

	while(**p == ' ' || **p == '\n')(*p)++;
	while(**p != ' ' && **p != '\0' && **p != '\n'){
		str.push_back(**p);
		(*p)++;
			}
	str.push_back('\0');
	return str;
		}

//Count words in each sentence
int strCount(char* ptr){
	int cnt = 0;
	if(!ptr)return 0;

	char* p = ptr;

	while(*p == ' ')p++;

	while(*p != '\0' && *p != '\n'){
		while(*p != ' ' && *p != '\0' && *p != '\n')p++;
		while(*p == ' ' && *p != '\0' && *p != '\n')p++;
		cnt++;
			}
	return cnt;
		}
