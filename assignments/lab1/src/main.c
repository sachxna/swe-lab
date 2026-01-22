#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "parser.h"
#include "validation.h"
#include "computation.h"
#include "report.h"

int main()
{
	FILE *input = NULL;
	FILE *output = NULL;
	student_t *students = NULL;
	int total_students = 0;

	input = fopen("data/input.txt", "r");
	if (input == NULL) {
		perror("Failed to open input file");
		goto cleanup;
	}

	if (!parse_file(input, &students, &total_students)) {
		fprintf(stderr, "Parsing failed\n");
		goto cleanup;
	}

	if (!validate_students(students, total_students)) {
		fprintf(stderr, "Validation failed\n");
		goto cleanup;
	}

	for (int i = 0; i < total_students; i++) {
		compute_student_results(&students[i]);
	}

	//output for the program
	output = fopen("data/output.txt", "w");
	if (output == NULL) {
		perror("Failed to open output file");
		goto cleanup;
	}

	write_report(output, students, total_students);

cleanup:
	if (input)
		fclose(input);
	if (output)
		fclose(output);
	free(students);

	return 0;
}
