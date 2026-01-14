#include <stdio.h>
#include <stdlib.h>
#include "report.h"
#include "computation.h"

const char* grade_to_string(grade_t grade) {
	switch(grade) {
		case GRADE_O:
			return "O";
		case GRADE_A_PLUS:
			return "A+";
		case GRADE_A:
			return "A";
		case GRADE_B_PLUS:
			return "B+";
		case GRADE_B:
			return "B";
		case GRADE_C:
			return "C";
		case GRADE_D:
			return "D";
		case GRADE_F:
			return "F";
		default:
			return "Unknown";
	}
}

void write_report(FILE *output, const student_t *students, int total_students) {

	fprintf(output, "%-8s %-15s %-15s %-15s %-15s %-15s %-15s %-8s %-10s %-6s\n","ID", "Name", "Subject1", "Subject2", "Subject3", "Subject4", "Subject5"			, "Total", "Percentage", "Grade");

	//print each student as one row
	for (int i = 0; i < total_students; i++) {
		const student_t *s = &students[i];

		//print student ID and name
		fprintf(output, "%-8s %-15s ", s->stu_id, s->stu_name);

		//print each subject with name and total marks
		for (int j = 0; j < MAX_SUBJECTS; j++) {
			int sub_total = s->subjects[j].min_marks + s->subjects[j].maj_marks;
			fprintf(output, "%-10s(%3d) ", s->subjects[j].sub_name, sub_total);
		}

		//print total marks, percentage, and grade
		fprintf(output, "%-8d %-10.2f %-6s\n", s->total_marks, s->percentage, grade_to_string(s->grade));
	}

	fprintf(output, "\n");

	//use class_avg function to calculate statistics
	class_t *class_stats = class_avg((student_t *)students, total_students);
	if (class_stats == NULL) {
		fprintf(stderr, "Error: Failed to calculate class statistics\n");
		return;
	}

	//calculate grade distribution
	int grade_count[8] = {0};
	for (int i = 0; i < total_students; i++) {
		grade_count[students[i].grade]++;
	}

	//calculate percentages for highest and lowest
	float highest_percentage = (class_stats->class_highest / 500.0f) * 100.0f;
	float lowest_percentage = (class_stats->class_lowest / 500.0f) * 100.0f;
	float avg_percentage = (class_stats->class_avg / 500.0f) * 100.0f;

	//print class statistics
	fprintf(output, "Class Average Percentage: %.2f%%\n", avg_percentage);
	fprintf(output, "Highest Percentage      : %.2f%%\n", highest_percentage);
	fprintf(output, "Lowest Percentage       : %.2f%%\n", lowest_percentage);

	fprintf(output, "\n");

	fprintf(output, "O  : %d student(s)\n", grade_count[GRADE_O]);
	fprintf(output, "A+ : %d student(s)\n", grade_count[GRADE_A_PLUS]);
	fprintf(output, "A  : %d student(s)\n", grade_count[GRADE_A]);
	fprintf(output, "B+ : %d student(s)\n", grade_count[GRADE_B_PLUS]);
	fprintf(output, "B  : %d student(s)\n", grade_count[GRADE_B]);
	fprintf(output, "C  : %d student(s)\n", grade_count[GRADE_C]);
	fprintf(output, "D  : %d student(s)\n", grade_count[GRADE_D]);
	fprintf(output, "F  : %d student(s)\n", grade_count[GRADE_F]);

	//free allocated memory
	free(class_stats);
}
