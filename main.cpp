#include "Management.h"
#include "Window.h"
#include "Table.h"
#include <iostream>

int main222()
{
	auto res = Table::split("2147483647\t陈佳欣\t计算机1401\t78\t88\t99");

	for (auto& val : res)
	{

		std::cout << val << " ";
	}

	return 0;
}




int main()
{
	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTilte("学生成绩管理系统");

	Management m;
	m.run();

	return w.exec(); //防止闪退
}