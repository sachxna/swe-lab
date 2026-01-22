# MODULE SPECIFICATION

This contains the specifications for each of the modules in the /src file for the project.

## Module : main.c

### Purpose

This module is responsible for starting and running the entire program/application

### Input

- the functions in the module take no inputs

### Preconditions:

Preconditions for this module are:
- have an input file at data/input.txt

### Logic:

1. initialise the input and output file pointers, the array of students to NULL, and set total students to 0
2. set the input file pointer to input file. if pointer is NULL, print error message and go to cleanup
3. parse the input file. if unable to parse, go to cleanup
4. validate the parsed data for duplicate values. if unable to validate, go to cleanup
5. for each student in the file
	- compute the result of the student
6. set the output file pointer. if pointer is NULL, print error and go to cleanup
7. write the report into the output file
8. on cleanup, close file pointers and free students array
9. return and exit the application

### Output:

This module does not directly compute or return student statistics.
It coordinates the execution of the application by invoking other
modules and ensures that the final report is generated

### Dependencies

This module depends on the headers:
- stdio.h : for file input/output operations
- stdlib.h : for dynamic memory management
- student.h : for student data structures
- parser.h : for input parsing functions
- validation.h : for validation functions
- computation.h : for result computation functions
- report.h : for report generation functions

## Module: parser.c

### Purpose

This module is used to read the input file, and extract student details from the file. This module is responsible for reading the data for each student and sending it for processing it/validation. The module contains 2 functions: parse_file() and trim_newline. 

### Input

1. parse_file()
	- the input file (FILE *input)
	- an array of structures to track students (student_t **students)
	- variable to track total number of students processed (int *total_stu)
2. trim_newline()
	- the string that is to be trimmed of newline

### Preconditions:

Preconditions for this module are:
- initialising file pointers and variables that will be passed to parse.c
- point the input file pointer to the input file

### Logic:

1. initialise the buffer for reading lines from the file of maxsize 256B
2. if file is empty, return failure status to caller
3. if number of students in line 1 of the file is <= 0 OR if there is more than one number in line 1, return failure status to caller
4. allocate the memory for the array of structs, where each element of the array is a struct that contains the details of one student
5. if memory allocation fails, exit the application
6. initialise a counter to keep track of number of students processed
7. process each student details while the number of students processed is < number of students in file:
	- read the next line. if NULL, exit the application
	- call the auxillary function 'trim_newline()' on the line just read to trim any newlines from the line
	- if its empty OR if the size of the line is >= buffer size, exit the application
	- copy the student id from the buffer to the appropriate variable in the struct, and append '\0' to the end of the string.
	- validate the student id -> if not valid, exit the application
	- read the next line for student name following the same process as above, and validate the name. if invalid, exit the application
	- for each of the next 5 lines:
		* if the line is NULL, exit the application
		* if each line does not contain 3 items: name of subject, minor marks and major marks, exit the application. else, read the items and store them in the appropriate variables in the struct
		* validate the subject name and the subject marks. if invalid, exit the application
8. return to main()

### Output:

The module parses the lines in the input file and sets the appropriate variables in the struct that contains the student details and the subject details. on error, it displays an error message and exits from the application. on success, the array 'student_t students[n]' contains the details of the 'n' students

### Dependencies:

### Dependencies

This module depends on the headers:
- stdio.h : for file input operations
- stdlib.h : for dynamic memory allocation
- string.h : for string manipulation functions
- ctype.h : for character classification functions
- student.h : for student and subject data structures
- parser.h : for function declarations of this module
- validation.h : for data validation functions

## Module : validation.c

### Purpose

This module is used to validate the data read from the file before storing it in the respective variables in the structs. 

### Input

1. validate_stu_id()
	- string of student id

2. validate_stu_name()
	- string of student name

3. validate_subject_name()
	- string of subject name

4. validate_sub_marks()
	- 2 integers, major marks and minor marks

### Preconditions:

Preconditions for this module are:
- read the strings that are to be passed as input to the functions before calling the functions themselves.

### Logic:

1. validate_stu_id(ID):
	1. if ID is NULL or empty, return 0
	2. for each character in ID, if it is not alphanumeric, return 0
	3. return 1

2. validate_stu_name(name):
	1. if name is NULL or empty, return 0
	2. for each character in name, if it is not a space and is not an alphabet, return 0
	3. return 1

3. validate_subject_name(sub_name):
	1. if the subject name is NULL or empty, return 0
	2. if the characters of the subject name are not alphanumeric, return 0
	3. return 1

4. validate_sub_marks(min_marks, maj_marks):
	1. if minor marks are between [0,40] and major marks are between [0,60], return 1; else return 0

5. validate_students(list of students, total students):
	1. for each student in the array, check every other student. if the ID of any 2 students are equal, display error message and return 0.
	2. else return 1

### Output:

This module is responsible for the validation of the data that is parsed from the input file by parser.c . The output of each function, if data is invalid, is 0; else it is 1

### Dependencies

This module depends on the headers:
- stdio.h : for error reporting using fprintf
- string.h : for string comparison functions
- ctype.h : for character classification functions
- student.h : for student data structures
- validation.h : for function declarations of this module

## Module : computation.c

### Purpose

This module is responsible for the computation various data that is to be displayed in the report, such as student marks, grades, etc.

### Input

1. compute_student_results()
	- list of students

2. assign_grade()
	- percentage obtained by student
	- if the student has failed or not

3. class_avg()
	- list of students
	- total number of students

### Preconditions:

Preconditions for this module are:
- all the relevant student data be parsed from the input file, validated and stored in the respective variables

### Logic:

1. compute_student_results(student):
	1. set a value to check if student has failed, has_failed = 0
	2. set the total marks of student = 0
	3. for each of the subject taken by the student
		- set subject marks = sum of minor marks and major marks in that subject
		- if subject marks < 50, set has_failed = 1
		- add the current subject marks to the total marks obtained by student
	4. set student percentage = total marks obtained by 500 multiplied by 100
	5. assign a grade to the student based on the percentage obtained by calling assign_grade()
	6. return

2. assign_grade(percentage, hasfailed):
	1. if student has failed, return GRADE_F
	2. based on the percentage obtained, return an appropriate grade
	3. as default, return GRADE_F
	
3. class_avg(listofstudents, totalstudents):
	1. initialise a struct to hold class statistics. if it doesnt initialise, return NULL
	2. initialise variables highest = 0, lowest = INF, classtotal = 0
	3. for each student in the class:
		1. add the students total marks to the class total
		2. if the students total marks is greater than the current highest marks, set that students marks as the current highest marks in the class
		3. if the students total marks is lesser than the current lowest marks, set that students marks as the current lowest marks in the class
	4. set classaverage  = classtotal/totalstudents
	5. return classstats

### Output:

This module is responsible for returning the statistics of the students in the class. The output of the functions are:
- compute_student_results(): sets the retsult of a student in the student structure after computing marks
- assign_grade(): assigns grades to a student based on percentage and if they have failed in any subject
- class_avg(): set the statistics of the class in the relevant structure after computation

### Dependencies:

### Dependencies

This module depends on the headers:
- stdio.h : for error reporting
- stdlib.h : for dynamic memory allocation
- limits.h : for integer boundary values (INT_MAX)
- student.h : for student and class data structures
- computation.h : for function declarations of this module

## Module : report.c

### Purpose

This module is used to print the report of the finla computations onto the output file.

### Input

1. grade_to_string()
	- the students' grade

2. write_report()
	- file pointer to the output file
	- the student array
	- total number of students

### Preconditions:

Preconditions for this module are:
- all the computations on the students be performed and accurate results be stored in the relevant variables in the student structure

### Logic:

1. write_report(output file pointer, list of students, total number of students):
	1. print the format of the output onto the file, with appropriate headings such as student name, ID, subjects, percentage, total marks, etc
	2. for each student in the list of students
		- print the student name and id
		- for each subject taken by the student
			* print the subject name and the marks obtained in that subject
		- print all relevant student statistics like percentage, marks, and grade assigned by using the grade_to_string() function
	4. calculate the class statistics, and if the initialised memory == NULL, print error and return
	5. print the class statistics into the file, along with details of number of students who scored a particular grade, etc.
	6. free all memory allocated

2. grade_to_string(grade):
	1. based on the input grade, return the string of the appropriate grade

### Output:

This module is used to print out the results of the calculations on the input file of students into an output file. The outputs of the functions are:
- write_report(): an output file with all relevant statistics
- grade_to_string(): conversion of type grade_t to string to be able to print into file

### Dependencies

This module depends on the headers:
- stdio.h : for formatted file output
- stdlib.h : for dynamic memory management
- student.h : for student and grade data structures
- computation.h : for class statistics computation
- report.h : for function declarations of this module
