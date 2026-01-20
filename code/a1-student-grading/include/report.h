#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>
#include "student.h"

void write_report(FILE *output, const student_t *students, int total_students);
const char* grade_to_string(grade_t grade);

#endif
