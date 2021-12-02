/* The following functions are helper functions for parsing file input
 * provided by the Advent of Code project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/inc/parseinput.h"

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
void read_report_int(FILE *fp, int *rep)
{
	char buff[10];

	rewind(fp);
	for( int i = 0; fgets(buff, 10, fp) != NULL; i++ ) {
		rep[i] = atoi(buff);
	}
}

void populate_kv_int(char *buff, keyValueInt_t *kv) {
	const char delim = ' ';
	char *token;

	token = strtok(buff, &delim);
	strcpy(kv->key, token);

	token = strtok(NULL, &delim);
	kv->value = atoi(token);
}

void read_report_kv_int(FILE *fp, keyValueInt_t **kv_array) {
	char buff[30];
	keyValueInt_t* kv;

	rewind(fp);
	for( int i = 0; fgets(buff, 30, fp) != NULL; i++ ) {
		kv = (keyValueInt_t*)calloc(1, sizeof(keyValueInt_t));
		populate_kv_int(buff, kv);
		kv_array[i] = kv;
	}
	
}
