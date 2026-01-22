#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "student.h"

int parse_file(FILE *input, student_t **students, int *total_stu);
//void debug_print_students(const student_t *students, int total_stu);

#endif
