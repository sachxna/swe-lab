Overview

This project implements a Student Result Processing System in C.
The program reads student records from a file, validates the data, computes academic results, and generates a formatted report containing individual results and class-level statistics.

Features:

- Reads student data from an input file

Validates:

- Student ID format and uniqueness
- Student names (alphabetic characters and spaces only)
- Subject marks (minor and major limits)

Computes:

- Total marks and percentage per student
- Pass/fail based on subject-wise minimum marks
- Final grade based on percentage

Generates:

- Tabular student report
- Class average, highest, and lowest percentage
- Grade distribution
- Writes results to an output file

Project Structure:

student-result-system/

	Makefile
	README.md
	data/
		input.txt
		output.txt
	include/
		student.h
		subject.h
		parser.h
		validation.h
		computation.h
		report.h
	src/
		main.c
		parser.c
		validation.c
		computation.c
		report.c

Input File Format

The input file is plain text and follows this structure:

First line: number of students N

For each student (7 lines per student):

- Student ID
- Student Name
- Five subject lines, each containing:
	<SubjectName> <MinorMarks> <MajorMarks>

Example:

3
S101
Rahul Kumar
Mathematics 35 50
Physics 30 45
Chemistry 28 40
Biology 32 48
English 36 52
S102
Ananya Sharma
Mathematics 38 55
Physics 34 50
Chemistry 30 44
Biology 33 49
English 37 54
S103
Arjun Mehta
Mathematics 20 25
Physics 18 30
Chemistry 22 28
Biology 24 32
English 26 35

Validation Rules:

- Student ID:
	Alphanumeric only
	Must be unique

- Student Name:
	Alphabetic characters and spaces only

- Marks:
	Minor marks: 0–40
	Major marks: 0–60

- Passing Rule:
	Minimum of 50 marks per subject
	Failure in any subject results in an overall grade of F

- Grading Scheme

Grades are assigned based on overall percentage (provided all subjects are passed):

Percentage Range	Grade
≥ 90	O
85 – < 90	A+
75 – < 85	A
65 – < 75	B+
60 – < 65	B
55 – < 60	C
50 – < 55	D
< 50 or fail	F


Compilation:

- From the project root: make
- This generates the executable: student_system
- Running the Program: ./student_system
- Input is read from: data/input.txt
- Output is written to: data/output.txt

Output:

The output file contains:

A tabular listing of all students, where each row is a students detail of the format:

ID, Name,Total marks per subject, Overall total, Percentage, Grade

Class statistics:
Class average percentage
Highest and lowest percentage
Grade distribution

Assumptions and Notes:

I'm yet to fill this out, will do in the next commit
