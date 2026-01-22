#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "validation.h"

#define MAX_LINE_SIZE 256

//helper function to trim trailing newline and whitespace
static void trim_newline(char *str) {
	size_t len = strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || isspace(str[len - 1]))) {
		str[len - 1] = '\0';
		len--;
	}
}

int parse_file(FILE *input, student_t **students, int *total_stu) {

	char line[MAX_LINE_SIZE];

	if (fgets(line, MAX_LINE_SIZE, input) == NULL) {
		fprintf(stderr, "Error: Failed to read number of students\n");
		return 0;
	}

	if (sscanf(line, "%d", total_stu) != 1 || *total_stu <= 0) {
		fprintf(stderr, "Error: Invalid number of students\n");
		return 0;
	}

	//allocate memory for students
	*students = malloc((*total_stu) * sizeof(student_t));
	if (*students == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for students\n");
		return 0;
	}

	int stu_count = 0;
	while (stu_count < *total_stu) {
		//read student ID
		if (fgets(line, MAX_LINE_SIZE, input) == NULL) {
			fprintf(stderr, "Error: Failed to read student ID for student %d\n", stu_count + 1);
			return 0;
		}
		trim_newline(line);
		
		if (strlen(line) == 0 || strlen(line) >= WORD_SIZE) {
			fprintf(stderr, "Error: Invalid student ID length for student %d\n", stu_count + 1);
			return 0;
		}
		
		strncpy((*students)[stu_count].stu_id, line, WORD_SIZE - 1);
		(*students)[stu_count].stu_id[WORD_SIZE - 1] = '\0';

		//validate the student id
		if (!validate_stu_id((*students)[stu_count].stu_id)) {
			fprintf(stderr, "Error: Invalid student ID '%s' for student %d (must be alphanumeric)\n", 
					(*students)[stu_count].stu_id, stu_count + 1);
			return 0;
		}

		//read student name (can contain spaces)
		if (fgets(line, MAX_LINE_SIZE, input) == NULL) {
			fprintf(stderr, "Error: Failed to read student name for student %d\n", stu_count + 1);
			return 0;
		}
		trim_newline(line);
		
		if (strlen(line) == 0 || strlen(line) >= NAME_SIZE) {
			fprintf(stderr, "Error: Invalid student name length for student %d\n", stu_count + 1);
			return 0;
		}
		
		strncpy((*students)[stu_count].stu_name, line, NAME_SIZE - 1);
		(*students)[stu_count].stu_name[NAME_SIZE - 1] = '\0';

		//validate the student name
		if (!validate_stu_name((*students)[stu_count].stu_name)) {
			fprintf(stderr, "Error: Invalid student name '%s' for student %d (only alphabets and spaces allowed)\n", 
					(*students)[stu_count].stu_name, stu_count + 1);
			return 0;
		}

		//read subjects
		for (int i = 0; i < MAX_SUBJECTS; i++) {
			if (fgets(line, MAX_LINE_SIZE, input) == NULL) {
				fprintf(stderr, "Error: Failed to read subject %d for student %d\n", 
						i + 1, stu_count + 1);
				return 0;
			}
			
			if (sscanf(line, "%s %d %d", (*students)[stu_count].subjects[i].sub_name,
						&((*students)[stu_count].subjects[i].min_marks), 
						&((*students)[stu_count].subjects[i].maj_marks)) != 3) {
				fprintf(stderr, "Error: Invalid subject format for subject %d, student %d\n", 
						i + 1, stu_count + 1);
				return 0;
			}

			//validate subject name
			if (!validate_subject_name((*students)[stu_count].subjects[i].sub_name)) {
				fprintf(stderr, "Error: Invalid subject name '%s' for student %d\n", 
						(*students)[stu_count].subjects[i].sub_name, stu_count + 1);
				return 0;
			}

			//validate the marks
			if (!validate_sub_marks((*students)[stu_count].subjects[i].min_marks, 
									(*students)[stu_count].subjects[i].maj_marks)) {
				fprintf(stderr, "Error: Invalid marks for subject '%s', student %d (Minor: 0-40, Major: 0-60)\n", 
						(*students)[stu_count].subjects[i].sub_name, stu_count + 1);
				return 0;
			}
		}

		stu_count++;
	}

	//debug_print_students(*students, *total_stu);

	return 1;
}
/*
void debug_print_students(const student_t *students, int total_stu) {
	printf("\n=== Debug: Parsed Student Data ===\n");
	for (int i = 0; i < total_stu; i++) {
		printf("Student %d\n", i + 1);
		printf("  ID   : %s\n", students[i].stu_id);
		printf("  Name : %s\n", students[i].stu_name);

		for (int j = 0; j < MAX_SUBJECTS; j++) {
			printf("  Subject %d:\n", j + 1);
			printf("    Name       : %s\n", students[i].subjects[j].sub_name);
			printf("    Minor Marks: %d\n", students[i].subjects[j].min_marks);
			printf("    Major Marks: %d\n", students[i].subjects[j].maj_marks);
		}

		printf("\n");
	}
	printf("=================================\n\n");
}
*/
