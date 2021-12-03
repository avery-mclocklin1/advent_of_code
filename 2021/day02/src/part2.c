#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/inc/parseinput.h"

#define INPUT "/home/avery/misc/advent_of_code/2021/inputs/day02"

int main(void) {
	FILE *report;
	int f_len;
	int depth = 0, hzl = 0, aim = 0; // Depth, Horizontal, and aim coordinates.
	keyValueInt_t **kv_array;

	report = fopen(INPUT, "r");
	f_len = get_report_length(report);

	kv_array = (keyValueInt_t**)calloc(f_len, sizeof(keyValueInt_t*));
	
	read_report_kv_int(report, kv_array);

	for (int i = 0; i < f_len; i++) {
		if (!strcmp(kv_array[i]->key, "up")) {
			aim -= kv_array[i]->value;
		}
		else if(!strcmp(kv_array[i]->key, "down")) {
			aim += kv_array[i]->value;
		}
		else if(!strcmp(kv_array[i]->key, "forward")) {
			hzl += kv_array[i]->value;
			depth += aim * kv_array[i]->value;
		}
	}

	printf("Multiplied Horizontal and Depth: %i\n", depth * hzl);

	/* Clean up */
	for (int i = 0; i < f_len; i++) {
		free(kv_array[i]);
	}
	free(kv_array);


	return 0;
}

