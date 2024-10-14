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

	//����������
	void run();

	//�˵�
	int menu();

	//1.��ʾ���е�ѧ��
	void display();
	//2.���
	void add();
	//3.ɾ��
	void erase();
	//4.�޸�
	void modify();
	//5.����
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

private: //��ȡ�ļ�������ѧ����Ϣ
	std::string m_header;
	std::vector<Student> vec_stu;

private: //�鿴ѧ�����
	std::unique_ptr<Table> m_showTable;
	std::unique_ptr<PushButton> m_addBtn; //���ѧ����ť
	std::unique_ptr<LineEdit> m_addEdit;

	std::unique_ptr<PushButton> m_delBtn; //ɾ��ѧ����ť
	std::unique_ptr<LineEdit> m_delEdit;
	std::unique_ptr<Table> m_delTable;
};

