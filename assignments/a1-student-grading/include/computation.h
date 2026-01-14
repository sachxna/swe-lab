#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "student.h"

void compute_student_results(student_t *student);
grade_t assign_grade(float percentage, int has_failed);
class_t* class_avg(student_t *students, int total_stu);

#endif
