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

	//按键操作和鼠标操作
	//判断有没有消息
	inline static bool hasMsg() { return ::peekmessage(&m_msg); }  //EM_MOUSE | EM_KEY
	inline static EASYXMSG& getMsg() { return m_msg; }


private:
	HWND m_handle; //窗口句柄
	inline static ExMessage m_msg; //消息


};
//C++17之前需要在cpp文件开头中这样定义一下才行    ExMessage Window::m_msg;
//C++17之后，只需要在前面添加inline       inline ExMessage Window::m_msg;
