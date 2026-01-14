#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "validation.h"

int validate_stu_id(const char *stu_id) {
	//check if null or empty string
	if(stu_id == NULL || stu_id[0] == '\0') {
		return 0;
	}

	//check each character is alphanumeric
	for(const char *p = stu_id; *p != '\0'; p++) {
		if(!isalnum((unsigned char) *p)) {
			return 0;
		}
	}

	return 1;
}

int validate_stu_name(const char *stu_name) {
	//check if null or empty string
	if(stu_name == NULL || stu_name[0] == '\0') {
		return 0;
	}

	//check each character is alphabet or space
	for(const char *p = stu_name; *p != '\0'; p++) {
		if(!isalpha((unsigned char) *p) && *p != ' ') {
			return 0;
		}
	}

	return 1;
}

int validate_subject_name(const char *sub_name) {
	//check if null or empty string
	if(sub_name == NULL || sub_name[0] == '\0') {
		return 0;
	}

	//subject names can be alphanumeric (e.g., "Math", "Physics", "CS101")
	for(const char *p = sub_name; *p != '\0'; p++) {
		if(!isalnum((unsigned char) *p)) {
			return 0;
		}
	}

	return 1;
}

int validate_sub_marks(int min_marks, int maj_marks) {
	//minor marks: 0-40, major marks: 0-60
	if(min_marks >= 0 && min_marks <= 40 &&
		maj_marks >= 0 && maj_marks <= 60) {
		return 1;
	}

	return 0;
}

int validate_students(student_t *students, int total_stu) {
	//check for duplicate student IDs
	for(int i = 0; i < total_stu; i++) {
		for(int j = i + 1; j < total_stu; j++) {
			if(strcmp(students[i].stu_id, students[j].stu_id) == 0) {
				fprintf(stderr, "Error: Duplicate student ID found: %s\n", students[i].stu_id);
				return 0;
			}
		}
	}

	return 1;
}
