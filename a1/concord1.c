#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_NUM 100
#define MAX_LINE_LENGTH 70+1
#define MAX_EXCL_WORD_NUM 20+1
#define MAX_EXCL_WORD_LENGTH 20+1

/*void get_exclusion_words(char *excl);*/
void print_array(int num, char *str);

int main(){
	char first_lines[5];
	char excl_words[MAX_EXCL_WORD_NUM][MAX_EXCL_WORD_LENGTH];
	char lines[MAX_LINE_NUM][MAX_LINE_LENGTH];

	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);
	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);
	/*get_exclusion_words(excl_words);
	print_array(MAX_EXCL_WORD_NUM, excl_words);*/
	//read in excl words
	char *cur_line;
	cur_line = fgets(excl_words[0], MAX_EXCL_WORD_LENGTH -1, stdin);
	/*char stop_point = "\"\"\"\"";*/
	int i = 1;
	while(strncmp(cur_line, "\"\"\"\"", 4) != 0){
		cur_line = fgets(excl_words[i], MAX_EXCL_WORD_LENGTH-1, stdin);
		i++;
	}
	for(int i = 0; i < MAX_EXCL_WORD_NUM -1; i++){
		printf("%s", excl_words[i]);
	}
	//printf("%s", excl_words[0]);
	//printf("%s", excl_words[1]);
	//read in everything
	int num_lines = 0;
	while(fgets(lines[num_lines], MAX_LINE_LENGTH-1, stdin) != NULL){
		printf("%s", lines[num_lines]);
		num_lines++;
	}
}

/*void get_exclusion_words(char **excl){
	char **cur_line;
	cur_line = fgets(excl[0], MAX_EXCL_WORD_LENGTH, stdin);
	char stop_point = "\"\"\"\"";
	int i = 1;
	while(strncmp(cur_line, stop_point, 5) != 0){
		cur_line = fgets(excl[i], MAX_EXCL_WORD_LENGTH, stdin);
		i++;
	}
	
}*/
/*
void print_array(char str[num][other_num]){
	for(int i = 0; i < num; i++){
		printf("%s", str[i]);
	}
}*/