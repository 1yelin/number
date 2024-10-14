#include "Management.h"
#include "Window.h"
#include "Table.h"
#include <iostream>

int main222()
{
	auto res = Table::split("2147483647\t�¼���\t�����1401\t78\t88\t99");

	for (auto& val : res)
	{

		std::cout << val << " ";
	}

	return 0;
}




int main()
{
	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTilte("ѧ���ɼ�����ϵͳ");

	Management m;
	m.run();

	return w.exec(); //��ֹ����
}