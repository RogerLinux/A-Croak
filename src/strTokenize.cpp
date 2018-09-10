using namespace std;

//Return a word in the row
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

//Remove all omiiied char in sentence
void removeChar(char* ptr, char omit){
	char* p = ptr;
	while(*p != '\0'){
		if(*p != omit)*ptr++ = *p;
		p++;
				}
	*ptr = '\0';
	return;
			}
