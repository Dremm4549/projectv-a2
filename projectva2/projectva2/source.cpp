/*
* FILE : source.cp
* PROJECT : CSCN73030 - Assignment #2
* PROGRAMMER : Michael Dremo
* FIRST VERSION : 2023-08-17
* DESCRIPTION : Simple test harness to perform read operations to store student data into a vector. Addtionally implenting compiler directives
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define PRE_RELASE

struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
};

STUDENT_DATA createStudent(std::string line);

int main(void) {
#ifdef PRE_RELASE
	std::cout << "Running Pre-Relase source code" << std::endl;
#else
	std::cout << "Running standard release source code" << std::endl;
#endif // PRE_RELASE

	std::vector<STUDENT_DATA> studentVector;
	STUDENT_DATA studentObj;
	std::ifstream ifs;

#ifdef PRE_RELASE
	ifs.open("../StudentData_Emails.txt", std::ifstream::in);
#else
	ifs.open("../StudentData.txt", std::ifstream::in);
#endif 

	if (ifs.is_open()) {
		std::string studentInfo;

		while (std::getline(ifs, studentInfo))
		{
			studentObj = createStudent(studentInfo);
			studentVector.push_back(studentObj);
		}
		ifs.close();
	}
	else
	{
		std::cout << "ERROR: Cant open resource" << std::endl;
	}

#ifdef _DEBUG
	for (int i = 0; i < studentVector.size(); i++)
	{
		std::cout << studentVector[i].firstName << " " << studentVector[i].lastName << std::endl;
	}
#endif
	return 1;
}

/*
* FUNCTION : createStudent
*
* DESCRIPTION : This function will take a string of input representing the
*				current line we just read parsing the student information and creating
*				a student object and returning that student to the function it was just called from
*
* PARAMETERS : std::string The line that was just read
*
* RETURNS : An object struct representing a student
*/

STUDENT_DATA createStudent(std::string input) {
	const char delim = ',';
	STUDENT_DATA student;

	std::string parsedString;
	std::istringstream studentName(input);
	std::string names[2];

	int nameCounter = 0;

	while (!studentName.eof()) {
		std::getline(studentName, parsedString, delim);

		if (nameCounter == 0)
		{
			student.lastName = parsedString;
		}
		else if (parsedString[0] == ' ' && nameCounter == 1)
		{
			parsedString.erase(parsedString.begin());
			student.firstName = parsedString;
			nameCounter = 0;
		}
		nameCounter++;
	}
	return student;
}