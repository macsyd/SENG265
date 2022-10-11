#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_NUM = 100;
#define MAX_LINE_LENGTH = 70;
#define MAX_EXCL_WORD_NUM = 20;
#define MAX_EXCL_WORD_LENGTH = 20;

int main(){
	char *excl_words[MAX_EXCL_WORD_NUM][MAX_EXCL_WORD_LENGTH];

}

void get_exclusion_words(char *excl){
	fgets(excl, MAX_EXCL_WORD_LENGTH, stdin);
}
