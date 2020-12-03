#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PROG_INPUT "input"
#define MAX_BUFF_LEN 255
#define PASSWORD_LEN 50

typedef struct {
	int pos1;
	int pos2;
	char c;
	char pass[PASSWORD_LEN];
} password_credential_t;

/* Returns 1 for a correct password, 0 for an incorrect password */
int correct_pass(password_credential_t *pass_cred)
{
	int correct = 0;
	char a, b;
	
	a = pass_cred->pass[pass_cred->pos1];
	b = pass_cred->pass[pass_cred->pos2];

	if ( ((a == pass_cred->c) || (b == pass_cred->c)) && (a != b) ) {
		correct = 1;
	}

	return correct;
}

/* Reads each line of the file, parses each line into password struct,
 * returns total correct password count
 */
void parse_line(char *buff, password_credential_t *pass_cred)
{
	char pos_buff[3];

	/* Parse min value, convert to int, store in pass_cred struct */ 
	for ( ; *buff != '-'; buff++ ) {
		strncat(pos_buff, buff, 1);
	}
	pass_cred->pos1 = atoi(pos_buff) - 1;
	pos_buff[0] = '\0';			// reset char array 
	buff = buff+1;				// skip over '-'

	/* Parse max value, convert to int, store in pass_cred struct */
	for ( ; *buff != ' '; buff++ ) {
		strncat(pos_buff, buff, 1);
	}
	pass_cred->pos2 = atoi(pos_buff) - 1;
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
		if ( i < 10 )
			printf("%s\nPOS1: %i, POS2: %i, CHAR: %c, PASS: %s\n\n", buff, pass_cred.pos1, pass_cred.pos2, pass_cred.c, pass_cred.pass);
		count = count + correct_pass(&pass_cred);
	}

	printf("Correct password count: %i\n", count);

	return 0;
}
