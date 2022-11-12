#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINES 1000
char *lines[MAX_LINES];
int   num_lines;


int compare(const void *s, const void *t)
{
    return strcmp(*(char **)s, *(char **)t);
}


int main(int argc, char *argv[])
{
    int i;
    FILE *infile;
    char *buffer;

    /* size_t is really another name for an int, but using
     * this silences a compiler warning when using getline().
     */
    size_t buffer_len;


    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(1);
    }

    for (i = 0; i < MAX_LINES; i++) {
        lines[i] = NULL;
    }

    num_lines = 0;
    buffer = NULL;

    // HINT: Use getline()
    
    while(getline(&buffer, &buffer_len, infile) != -1){
        char *temp = malloc(sizeof(char)*buffer_len);
	if(temp == NULL){
            printf("Malloc didn't work");
            exit(1);
        }
	//strncpy(temp, buffer, strlen(buffer));
	lines[num_lines] = temp;
        //lines[num_lines][strlen(temp)-1] = 0;
	num_lines++;
	//getline(&buffer, &buffer_len, infile);
    }
    
    qsort(lines, num_lines+1, sizeof(char*), compare);
    for(int i = 0; i < num_lines+1; i++){
        printf("%s\n", lines[i]);
        free(lines[i]);
    }
    fclose(infile);
}
