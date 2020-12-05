#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255

/* Returns number of lines in file */
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

/* Reads by character in file, if within character criteria will assign correct indecies in matrix */
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

/* Traverses a 2d matrix until using a run(x-axis) and rise(y-axis) scheme.
 * If the indexed value is a char '#' then a counter is incremented by one.
 * Returns count
 */
int count_collisions(char **array, size_t len, size_t width, int rise, int run)
{
	int count = 0;
	int diff;
	int i = 0;
	int j = 0;

	while (1) {
		/* Determine if run exceeds sub_array bounds */
		diff = width - j;
		if ( diff <= run ) {
			j = run - diff;
		} else {
			j = j + run;
		}

		i = i + rise;
		if (i >= len)	// in-case rise exceeds array bounds
			break;

		if ( array[i][j] == '#' )
			count++;
	}

	return count;
}

int main(void)
{
	FILE *tree_file;
	size_t f_len, f_width;
	char buff[MAX_BUFF_LEN];
	char **array;
	char *sub_array;
	int collisions = 1;
	int count;
	int rise[] = {1,1,1,1,2};
	int run[] = {1,3,5,7,1};


	tree_file = fopen(PROG_INPUT, "r");
	f_len = get_file_length(tree_file);
	f_width = strlen(fgets(buff, MAX_BUFF_LEN, tree_file)) - 1;
	rewind(tree_file);
	
	/* Build 2d matrix */
	array = (char**)calloc(f_len, sizeof(char**));
	for (int i = 0; i < f_len; i++) {
		sub_array = (char*)calloc(f_width, sizeof(char*));
		array[i] = sub_array;
	}

	populate_2d_array(tree_file, array, f_len, f_width);

	/* Print populated matrix */
	for (int i = 0; i < f_len; i++) {
		for (int j = 0; j < f_width; j++) {
			printf("%c", array[i][j]);
		}
		printf("\n");
	}

	printf("f_len: %li\tf_width: %li\n", f_len, f_width);

	/* Aggregate collisions in cumulative product */
	for (int i = 0; i < 5; i++) {
		count = count_collisions(array, f_len, f_width, rise[i], run[i]);
		collisions *= count;
		printf("rise: %i, run: %i, count: %i, collisions *= %i\n", rise[i], run[i], count, collisions);
	}
	printf("Tree collisions: %i\n", collisions);

	/* Be free */
	for (int i = 0; i < f_len; i++) {
		free(array[i]);
	}
	free(array);

	return 0;
}
