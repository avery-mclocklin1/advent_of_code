#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255

/* Check string for keywords, if keyword isn't present return zero, otherwise return 1. */
int is_valid(char *buff)
{
	char *keys[7] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	for (int i = 0; i < 7; i++) {
		if (strstr(buff, keys[i]) == NULL)
			return 0;
	}

	return 1;
}

/* Reads file line by line and collects contents into buffer until an empty line.
 * Buffer contents are checked whether they constitue a valid passport.
 * Returns total valid count.
 */
int count_valid_passports(FILE *fp)
{
	int count = 0;
	char gets_buff[MAX_BUFF_LEN], batch_buff[MAX_BUFF_LEN];

	while (fgets(gets_buff, MAX_BUFF_LEN, fp) != NULL) {
		/* Process batch as you've reached an empty line */
		if ( gets_buff[0] == '\n' ) {
			count += is_valid(batch_buff);
			memset(batch_buff, '\0', MAX_BUFF_LEN);			// Clear batch buffer
			continue;
		}

		strcat(batch_buff, gets_buff);
	}

	return count;
}

int main(void) 
{
	FILE *passports_file;

	passports_file = fopen(PROG_INPUT, "r");
	if (passports_file == NULL ) {
		printf("Unable to open file: %s. Exiting", PROG_INPUT);
		exit(1);
	}

	printf("Number of valid passports: %i\n", count_valid_passports(passports_file));

	return 0; 
}

