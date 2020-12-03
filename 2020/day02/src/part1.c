#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255
#define PASSWORD_LEN 50

typedef struct {
	int min;
	int max;
	char c;
	char pass[PASSWORD_LEN];
} password_credential_t;

/* Returns 1 for a correct password, 0 for an incorrect password */
int correct_pass(password_credential_t *pass_cred)
{
	int count = 0;

	for ( int i = 0; i < strlen(pass_cred->pass); i++ ) {
		if ( pass_cred->pass[i] == pass_cred->c ) 
			count = count + 1;
	}

	if ( (count >= pass_cred->min) && (count <= pass_cred->max) ) 
		return 1;
	else
		return 0;
}

/* Reads each line of the file, parses each line into password struct */
void parse_line(char *buff, password_credential_t *pass_cred)
{
	char min_max_buff[3];

	/* Parse min value, convert to int, store in pass_cred struct */ 
	for ( ; *buff != '-'; buff++ ) {
		strncat(min_max_buff, buff, 1);
	}
	pass_cred->min = atoi(min_max_buff);
	min_max_buff[0] = '\0';			// reset char array 
	buff = buff+1;				// skip over '-'

	/* Parse max value, convert to int, store in pass_cred struct */
	for ( ; *buff != ' '; buff++ ) {
		strncat(min_max_buff, buff, 1);
	}
	pass_cred->max = atoi(min_max_buff);
	buff = buff+1; 				// skip over ' '

	/* Parse special char */
	pass_cred->c = *buff;
	buff = buff+3; 				// skip over ": "

	/* Parse password */
	for ( ; (*buff != '\n') && (*buff != '\0'); buff++ ) {
		strncat(pass_cred->pass, buff, 1);
	}
}

int main(void)
{
	FILE *pass_file;
	char buff[MAX_BUFF_LEN];
	int count = 0;
	password_credential_t pass_cred;

	pass_file = fopen(PROG_INPUT, "r");
	for( int i = 0; fgets(buff, MAX_BUFF_LEN, pass_file) != NULL; i++ ) {
		memset( pass_cred.pass, '\0', sizeof(char)*PASSWORD_LEN );
		parse_line(buff, &pass_cred);
		count = count + correct_pass(&pass_cred);
	}

	printf("Correct password count: %i\n", count);

	return 0;
}
