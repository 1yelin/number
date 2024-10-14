#pragma once
#include "ConFigure.h"
using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 chinese, uint32 english);
	std::string formatInfo();  //格式化数据
	static Student fromString(const std::string& str);
public:
	//学号			姓名		班级		数学		语文		英语
	uint32 number;
	std::string name;
	std::string grade;
	uint32 math;
	uint32 chinese;
	uint32 english;
};

