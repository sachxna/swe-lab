#ifndef VALIDATION_H
#define VALIDATION_H

#include "student.h"

int validate_stu_id(const char *stu_id);
int validate_stu_name(const char *stu_name);
int validate_sub_marks(int min_marks, int maj_marks);
int validate_students(student_t *students, int total_stu);
int validate_subject_name(const char *sub_name);

#endif
