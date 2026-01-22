#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "student.h"
#include "computation.h"

void compute_student_results(student_t *student) {
	int has_failed = 0;
	student->total_marks = 0;

	//calculate total marks and check for failures
	for(int i = 0; i < MAX_SUBJECTS; i++) {
		int sub_marks = student->subjects[i].min_marks + student->subjects[i].maj_marks;

		//minimum passing marks is 50 per subject
		if(sub_marks < 50) {
			has_failed = 1;
		}
		student->total_marks += sub_marks;
	}

	//calculate percentage (total possible marks = 5 subjects * 100 = 500)
	student->percentage = (student->total_marks / 500.0f) * 100.0f;

	//assign grade
	student->grade = assign_grade(student->percentage, has_failed);

	return;
}

grade_t assign_grade(float percentage, int has_failed) {
	//if failed in any subject, grade is F
	if(has_failed) return GRADE_F;

	//grade assignment based on percentage
	if (percentage >= 90) return GRADE_O;
	if (percentage >= 85) return GRADE_A_PLUS;
	if (percentage >= 75) return GRADE_A;
	if (percentage >= 65) return GRADE_B_PLUS;
	if (percentage >= 60) return GRADE_B;
	if (percentage >= 55) return GRADE_C;
	if (percentage >= 50) return GRADE_D;

	return GRADE_F;
}

class_t* class_avg(student_t *students, int total_stu) {
	class_t *class_stats = malloc(sizeof(class_t));
	if (class_stats == NULL) {
		return NULL;
	}

	float highest = 0, lowest = INT_MAX;
	int class_total = 0;

	for(int i = 0; i < total_stu; i++) {
		class_total += students[i].total_marks;

		if(students[i].total_marks > highest) {
			class_stats->class_highest = students[i].total_marks;
			highest = class_stats->class_highest;
		}

		if(students[i].total_marks < lowest) {
			class_stats->class_lowest  = students[i].total_marks;
			lowest = class_stats->class_lowest;
		}
	}

	class_stats->class_avg = (float)class_total/total_stu;

	return class_stats;
}
