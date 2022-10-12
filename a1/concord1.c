#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_NUM 100
#define MAX_LINE_LENGTH 70
#define MAX_EXCL_WORD_NUM 20
#define MAX_EXCL_WORD_LENGTH 20

void get_exclusion_words(char *excl);
void print_array(int num, char *str);

int main(){
	char first_lines[2][5];
	char excl_words[MAX_EXCL_WORD_NUM][MAX_EXCL_WORD_LENGTH];
	char lines[MAX_LINE_NUM][MAX_LINE_LENGTH];
	
	get_exclusion_words(excl_words);
	print_array(MAX_EXCL_WORD_NUM, excl_words);
}

void get_exclusion_words(char **excl){
	char **cur_line;
	cur_line = fgets(excl[0], MAX_EXCL_WORD_LENGTH, stdin);
	char stop_point = "\"\"\"\"";
	int i = 1;
	while(strncmp(cur_line, stop_point, 5) != 0){
		cur_line = fgets(excl[i], MAX_EXCL_WORD_LENGTH, stdin);
		i++;
	}
	
}

void print_array(int num, char *str){
	for(int i = 0; i < num; i++){
		printf("%s", str[i]);
	}
}
