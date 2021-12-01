#include <stdio.h>
#include <stdlib.h>

#include "../../lib/inc/parseinput.h"

#define INPUT "/home/avery/misc/advent_of_code/2021/inputs/day01"

int add3(int i, int* d) {
	return d[i] + d[i+1] + d[i+2];
}

int main(void) {

	FILE *report;
	int f_len, diff, increases = 0;
	int *depths;

	/* Parse input */
	report = fopen(INPUT, "r");
	f_len = get_report_length(report);
	printf("f_len: %i\n", f_len);
	depths = (int*)calloc(f_len, sizeof(int));
	read_report(report, depths);

	/* Calculate diff, determine increases */
	for (int i = 1; i <= f_len-2; i++) {
		diff = add3(i, depths) - add3(i-1, depths);
		if (diff > 0)
			increases++;
	}

	printf("Number of Increases: %i\n", increases);

	/* Clean-up */
	free(depths);
	fclose(report);

	return 0;
}

