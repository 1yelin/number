#pragma once
#include "BasicWidget.h"
#include "ConFigure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text = "Button", int x = 0, int y = 0, int w = 170, int h = 50);
    void show() override;



private:
    std::string m_text;



};

