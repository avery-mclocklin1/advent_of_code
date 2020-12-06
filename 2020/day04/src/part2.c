#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255

typedef struct passport_s {
	int16_t	byr;
	int16_t	iyr;
	int16_t	eyr;
	int16_t	hgt;
	int 	hcl;
	char 	ecl[4];
	int 	pid;
	int 	cid;
} passport_t;

size_t word_size(char *str) 
{
	size_t size = 0;

	while ( ! ((*str == ' ') || (*str == '\n')) ) {
		str++;
		size++;
	}

	return size;
}

/* Check string for keywords, if keyword isn't present return zero, otherwise return 1. */
int is_valid(char *buff)
{
	char *start;
	char value[32];
	char *keys[7] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	char *ecls[7] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
	size_t size;
	char *unit;
	passport_t passport;

	for (int i = 0; i < 7; i++) {
		if ((start = strstr(buff, keys[i])) == NULL)
			return 0;

		start += 4; 	// skip "key:"

		if ( ! strcmp(keys[i], "byr") ) {
			size = word_size(start);
			strncpy(value, start, size);
			passport.byr = atoi(value);
			if ((size != 4) ||
				(passport.byr > 2002) ||
				(passport.byr < 1920))
			{
				return 0;
			}
		} 
		else if ( ! strcmp(keys[i], "iyr") ) {
			size = word_size(start);
			strncpy(value, start, size);
			passport.iyr = atoi(value);
			if ((size != 4) ||
				(passport.iyr > 2020) ||
				(passport.iyr < 2010))
			{
				return 0;
			}
		}
		else if ( ! strcmp(keys[i], "eyr") ) {
			size = word_size(start);
			strncpy(value, start, size);
			passport.eyr = atoi(value);
			if ((size != 4) ||
				(passport.eyr > 2030) ||
				(passport.eyr < 2020))
			{
				return 0;
			}
		}
		else if ( ! strcmp(keys[i], "hgt") ) {
			size = word_size(start);
			strncpy(value, start, size);
			if (((unit = strstr(value, "cm")) == NULL) &&
				((unit = strstr(value, "in")) == NULL))
			{
				return 0;
			}
			printf("unit: %c, ", *unit);
			value[size-2] = '\0';
			passport.hgt = atoi(value);

			if (((*unit == 'c') && ((passport.hgt > 193) || (passport.hgt < 150))) ||
				((*unit == 'i') && ((passport.hgt >  76) || (passport.hgt <  59))))
			{
				return 0;
			}
		}
		else if ( ! strcmp(keys[i], "hcl") ) {
			size = word_size(start);
			strncpy(value, start, size);
			if ((*value != '#') || (size != 7))
				return 0;

			for (int i = 1; i < size; i++) {
				if ( ! isxdigit(value[i]) )
					return 0;
			}
		}
		else if ( ! strcmp(keys[i], "ecl") ) {
			int8_t hit = 0;

			size = word_size(start);
			strncpy(value, start, size);
			value[size] = '\0';
			printf("size: %li ", size);
			if (size > 3)
				return 0;

			/* Check for one occurance of correct eye color */
			for (int i = 0; i < 7; i++) {
				if (strstr(buff, ecls[i]) != NULL) 
					hit++;
			}
			if (hit != 1)
				return 0;
		}
		else if ( ! strcmp(keys[i], "pid") ) {
			size = word_size(start);
			strncpy(value, start, size);
			if ( (size != 9) )  //|| (value[0] != '0')
				return 0;
		}
		printf("%s: %s\n", keys[i], value);
	}

	printf("\n");
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

	count += is_valid(batch_buff);

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
