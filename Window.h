#pragma once
#include "ConFigure.h"
#include <vector>
#include "PushButton.h"

class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTilte(const std::string& title);
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	//����������������
	//�ж���û����Ϣ
	inline static bool hasMsg() { return ::peekmessage(&m_msg); }  //EM_MOUSE | EM_KEY
	inline static EASYXMSG& getMsg() { return m_msg; }


private:
	HWND m_handle; //���ھ��
	inline static ExMessage m_msg; //��Ϣ


};
//C++17֮ǰ��Ҫ��cpp�ļ���ͷ����������һ�²���    ExMessage Window::m_msg;
//C++17֮��ֻ��Ҫ��ǰ�����inline       inline ExMessage Window::m_msg;
