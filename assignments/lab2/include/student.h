#ifndef STUDENT_H
#define STUDENT_H

#define MAX_SUBJECTS 5
#define WORD_SIZE 64
#define NAME_SIZE 128

typedef enum grade {
	GRADE_O,
	GRADE_A_PLUS,
	GRADE_A,
	GRADE_B_PLUS,
	GRADE_B,
	GRADE_C,
	GRADE_D,
	GRADE_F
} grade_t;

typedef struct subject {
	char sub_name[WORD_SIZE];
	int min_marks;
	int maj_marks;
} subject_t;

typedef struct student {
	char stu_id[WORD_SIZE];
	char stu_name[NAME_SIZE];
	subject_t subjects[MAX_SUBJECTS];
	int total_marks;
	float percentage;
	grade_t grade;
} student_t;

typedef struct class_total {
	float class_avg;
	int class_highest;
	int class_lowest;
} class_t;

#endif
