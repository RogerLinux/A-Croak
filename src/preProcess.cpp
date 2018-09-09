using namespace std;

#define omit_table_size 8

bool omitSymbol(char c){
	for(int n = 0; n < omit_table_size; n++)
		if(c == omit_table[n])return true;

	return false;
			}

bool removeSymbol(char* sent){
	if(!sent)return false; //No input
	char* ptr = sent;

	while(*ptr != '\0'){
		if(omitSymbol(*ptr))
			*ptr = ' '; //Remove the useless symbols
		ptr++;
				}
	return true;
		}

bool capitalToLowercase(char* sent){
	if(!sent)return false;

	char* ptr = sent;

	while(*ptr != '\0'){
		if(*ptr >= 'A' && *ptr <= 'Z')
			*ptr += ('a' - 'A');
		ptr++;
				}
	return true;
		}

//To remove suffix "s" and "ed"
bool removeSandEd(char* sent){
	if(!sent)return false;

	char* ptr = sent;
	int len = 0;
	char* new_sent = NULL, *new_ptr = NULL;
	string str;
	string::iterator it;

	while(*ptr++ != '\0')len++;
	ptr = sent;
	//Allocate new memory section for modified sentence

	new_sent = new char[len + 1];
	new_ptr = new_sent;

	str = strTokenize(&ptr);

	while(str.size()){

		//Go to the last
		it = str.begin();
		while(it != str.end() && *it != '\0')it++;

		if(*(it - 1) == 's')
			*(it - 1) = '\0';
		else if(*(it - 1) == 'd' && *(it - 2) == 'e')
			*(it - 2) = '\0';

		for(it = str.begin(); it != str.end() && *it != '\0'; it++){
			*new_ptr = *it;
			new_ptr++;
					}
		*new_ptr++ = ' ';
		str = strTokenize(&ptr); //Go to next word
				}

	*new_ptr = '\0';

	//Go to head of the sentences
	ptr = sent;
	new_ptr = new_sent;

	//Update original sentence

	while(*new_ptr != '\0'){
		*ptr = *new_ptr;
		ptr++;
		new_ptr++;
			}

	*ptr = '\0';

	delete[] new_sent;
	return true;
		}
