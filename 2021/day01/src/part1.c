#include <stdio.h>
#include <stdlib.h>

#include "../../lib/inc/parseinput.h"

#define INPUT "/home/avery/misc/advent_of_code/2021/inputs/day01"

int main(void) {

	FILE *report;
	int f_len, diff, increases = 0;
	int *depths;

	/* Parse input */
	report = fopen(INPUT, "r");
	f_len = get_report_length(report);
	depths = (int*)calloc(f_len, sizeof(int));
	read_report_int(report, depths);

	/* Calculate diff, determine increases */
	for (int i = 1; i <= f_len; i++) {
		diff = depths[i] - depths[i-1];
		if (diff > 0)
			increases++;
	}

	printf("Number of Increases: %i\n", increases);

	/* Clean-up */
	free(depths);
	fclose(report);

	return 0;
}

