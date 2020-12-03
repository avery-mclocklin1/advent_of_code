#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXPENSE_REPORT "input"

/* Returns number of lines in report */
int get_report_length(FILE *fp)
{
	int count = 0;
	char c;

	rewind(fp);
	for (c = getc(fp); c != EOF; c = getc(fp)) {
		if (c == '\n') {
			count = count + 1;
		}
	}

	return count;
}

/* Reads each line of the report, cast types to integer in array */
void read_report(FILE *fp, int *rep)
{
	char buff[10];

	rewind(fp);
	for( int i = 0; fgets(buff, 10, fp) != NULL; i++ ) {
		rep[i] = atoi(buff);
	}
}

/* Search and compare up array until element pair equals 2020.
 * Return multiplication of the two elements.
 */
int find_pair(int *rep, int f_len)
{
	for (int i = 0; i < f_len-1; i++) {
		for (int j = i+1; j < f_len; j++) {
			if (rep[i]+rep[j] == 2020) {
				return rep[i] * rep[j];
			}
		}
	}

	return 0;
}

int main(void)
{
	FILE *report;
	int f_len;
	int *rep_array;
	int pair_multi;

	report = fopen(EXPENSE_REPORT, "r");

	if (report == NULL) {
		printf("Could not open file %s\n", EXPENSE_REPORT);
		return 1;
	}

	f_len = get_report_length(report);
	rep_array = (int*)calloc(f_len, sizeof(int));
	read_report(report, rep_array);
	pair_multi = find_pair(rep_array, f_len);

	if ( pair_multi )
		printf("Found pair multiplication: %i\n", pair_multi);
	else 
		printf("Failed to accurately find pair\n");

	free(rep_array);
	fclose(report);

	return 0;
}
