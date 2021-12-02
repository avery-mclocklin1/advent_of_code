/* Include file for parsing input files */

typedef struct keyValueInt_s {
	char key[20];
	int value;
} keyValueInt_t;

int get_report_length(FILE *fp);
void read_report_int(FILE *fp, int *rep);
void read_report_kv_int(FILE *fp, keyValueInt_t **kv_array);
