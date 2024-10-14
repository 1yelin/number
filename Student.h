#pragma once
#include "ConFigure.h"
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 chinese, uint32 english);
	std::string formatInfo();  //��ʽ������
	static Student fromString(const std::string& str);
public:
	//ѧ��			����		�༶		��ѧ		����		Ӣ��
	uint32 number;
	std::string name;
	std::string grade;
	uint32 math;
	uint32 chinese;
	uint32 english;
};

