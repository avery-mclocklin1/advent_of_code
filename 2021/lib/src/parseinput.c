/* The following functions are helper functions for parsing file input
 * provided by the Advent of Code project.
 */

#include <stdio.h>
#include <stdlib.h>

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

