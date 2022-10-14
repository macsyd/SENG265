#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_NUM 100
#define MAX_LINE_LENGTH 70+1
#define MAX_EXCL_WORD_NUM 20+1
#define MAX_EXCL_WORD_LENGTH 20+1
#define MAX_NUM_INDEX_WORDS 100

int check_if_excl(char *tok, int num);
void remove_newlines(char *str);
int compare_words(const void * a, const void * b);
int check_if_index_word(char *tok, char *word);
void print_line(char *line, char *index_word);

char excl_words[MAX_EXCL_WORD_NUM][MAX_EXCL_WORD_LENGTH];
char lines[MAX_LINE_NUM][MAX_LINE_LENGTH];
char indexed_lines[MAX_NUM_INDEX_WORDS][MAX_LINE_LENGTH];

int main(){
	char first_lines[5];

	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);
	fgets(first_lines, MAX_EXCL_WORD_LENGTH-1, stdin);

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

	//read in everything
	int num_lines = 0;
	while(fgets(lines[num_lines], MAX_LINE_LENGTH-1, stdin) != NULL){
		remove_newlines(lines[num_lines]);
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
	
	/*sort words to index*/
	qsort(indexed_lines[0], num_indexes, sizeof(char)*MAX_LINE_LENGTH, compare_words);

	for(int i = 0; i < num_indexes; i++){
		for(int j = 0; j < num_lines; j++){
			strncpy(current_line, lines[j], MAX_LINE_LENGTH);
			char *token = strtok(current_line, " ");
			while(token != NULL){
				if(check_if_index_word(token, indexed_lines[i])){
					/*output line*/
					print_line(lines[j], indexed_lines[i]);
				}
				token = strtok(NULL, " ");
			}
		}
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

int compare_words(const void * a, const void * b){
	return strncmp(a, b, MAX_LINE_LENGTH);
}

int check_if_index_word(char *tok, char *word){
	if(strncmp(tok, word, MAX_LINE_LENGTH) == 0){
		return 1;
	}
	else{
		return 0;
	}
}

void print_line(char *line, char *index_word){
	char this_line[MAX_LINE_LENGTH];
	strncpy(this_line, line, MAX_LINE_LENGTH);
	char *token = strtok(this_line, " ");
	while(token != NULL){
		if(strncmp(token, index_word, MAX_LINE_LENGTH) == 0){
			int len = strlen(token);
			for(int i = 0; i < len; i++){
				printf("%c", toupper(token[i]));
			}
		}else{
			printf("%s", token);
		}
		token = strtok(NULL, " ");
		if(token != NULL){
			printf(" ");
		}
	}
	printf("\n");
}
