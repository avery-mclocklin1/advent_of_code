#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255

/* Returns number of lines in report */
int get_file_length(FILE *fp)
{
	int count = 0;
	char c;

	for (c = getc(fp); c != EOF; c = getc(fp)) {
		if (c == '\n') {
			count = count + 1;
		}
	}
	rewind(fp);

	return count;
}

/* Reads by character in file, if within character criteria will assign correct indecies within matrix */
void populate_2d_array(FILE *fp, char **array, size_t len, size_t width)
{
	char c;
	int i = 0;
	int j = 0;

	for (c = getc(fp); c != EOF; c = getc(fp)) {
		if ((c == '#') || (c == '.')) {
			if (j == width) {
				j = 0;
				i++;
			}
			array[i][j] = c;
			j++;
		}
	}
	rewind(fp);
}

int main(void)
{
	FILE *tree_file;
	size_t f_len, f_width;
	char buff[MAX_BUFF_LEN];
	char **array;
	char *sub_array;

	tree_file = fopen(PROG_INPUT, "r");
	f_len = get_file_length(tree_file);
	f_width = strlen(fgets(buff, MAX_BUFF_LEN, tree_file)) - 1;
	rewind(tree_file);
	
	array = (char**)calloc(f_len, sizeof(char**));
	for (int i = 0; i < f_len; i++) {
		sub_array = (char*)calloc(f_width, sizeof(char*));
		array[i] = sub_array;
	}

	populate_array(tree_file, array, f_len, f_width);

	//for (int i = 0; i < f_len; i++) {
	//	memset(array[i], 'X', f_width);
	//	printf("%s\n", array[i]);
	//}

	for (int i = 0; i < f_len; i++) {
		for (int j = 0; j < f_width; j++) {
			printf("%c", array[i][j]);
		}
		printf("\n");
	}

	printf("f_len: %li\tf_width: %li\n", f_len, f_width);

	return 0;
}
