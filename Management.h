#pragma once
#include "Window.h"
#include <vector>
#include "Student.h"
#include "Table.h"
#include "LineEdit.h"
#include "PushButton.h"
#include <memory>

class Management
{
	enum Operator
	{
		Display,
		Insert,
		Remove,
		Modify,
		Search,
		Menu = 66,
	};

public:
	Management();

	//启动管理类
	void run();

	//菜单
	int menu();

	//1.显示所有的学生
	void display();
	//2.添加
	void add();
	//3.删除
	void erase();
	//4.修改
	void modify();
	//5.查找
	void search();

	void drawBackground();
	void eventLoop();

	void readFile(const std::string& fileName);
	void saveFile(const std::string& fileName);

	void updateShowTable();

private:
	int m_op;
	IMAGE m_bk;

	std::vector<std::unique_ptr<PushButton>> menu_btns;

private: //读取文件，保存学生信息
	std::string m_header;
	std::vector<Student> vec_stu;

private: //查看学生表格
	std::unique_ptr<Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn; //添加学生按钮
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn; //删除学生按钮
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table> m_delTable;
};

