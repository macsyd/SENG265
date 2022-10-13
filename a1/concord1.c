#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_NUM 100
#define MAX_LINE_LENGTH 70+1
#define MAX_EXCL_WORD_NUM 20+1
#define MAX_EXCL_WORD_LENGTH 20+1
#define MAX_NUM_INDEX_WORDS 100

/*void get_exclusion_words(char *excl);*/
void print_array(int num, char *str);
int check_if_excl(char *tok, int num);
void remove_newlines(char *str);

char excl_words[MAX_EXCL_WORD_NUM][MAX_EXCL_WORD_LENGTH];
char lines[MAX_LINE_NUM][MAX_LINE_LENGTH];
char indexed_lines[MAX_NUM_INDEX_WORDS][MAX_LINE_LENGTH];

int main(){
	char first_lines[5];

	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);
	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);
	/*get_exclusion_words(excl_words);
	print_array(MAX_EXCL_WORD_NUM, excl_words);*/
	//read in excl words
	char *cur_line;
	cur_line = fgets(excl_words[0], MAX_EXCL_WORD_LENGTH -1, stdin);
	remove_newlines(excl_words[0]);
	int num_excl_words = 0;
	while(strncmp(cur_line, "\"\"\"\"", 4) != 0){
		num_excl_words++;
		cur_line = fgets(excl_words[num_excl_words], MAX_EXCL_WORD_LENGTH-1, stdin);
		remove_newlines(excl_words[num_excl_words]);
	}
	printf("exclusion words:\n");
	for(int i = 0; i < num_excl_words; i++){
		printf("%s", excl_words[i]);
	}

	//read in everything
	printf("input lines:\n");
	int num_lines = 0;
	while(fgets(lines[num_lines], MAX_LINE_LENGTH-1, stdin) != NULL){
		printf("%s", lines[num_lines]);
		num_lines++;
	}

	/*indexing*/
	int num_indexes = 0;
	char current_line[MAX_LINE_LENGTH];
	for(int i = 0; i < num_lines; i++){
		strncpy(current_line, lines[i], MAX_LINE_LENGTH);
		char *token = strtok(current_line, " ");
		while(token != NULL){
			if(check_if_excl(token, num_excl_words)){
				/*yes index*/
				strncpy(indexed_lines[num_indexes], token, MAX_LINE_LENGTH);
				num_indexes++;
			}
			token = strtok(NULL, " ");
		}
	}
	printf("words to index:\n");
	for(int i = 0; i < num_indexes; i++){
		printf("%s\n", indexed_lines[i]);
	}
}

int check_if_excl(char *tok, int num){
	for(int j = 0; j < num; j++){
		if(strncmp(tok, excl_words[j], MAX_EXCL_WORD_LENGTH) == 0){
			return 0;
		}
	}
	return 1;
}

void remove_newlines(char *str){
	int num = 0;
	while(str[num] != '\0'){
		num++;
	}
	if(str[num-1] == '\n'){
		str[num-1] = '\0';
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
