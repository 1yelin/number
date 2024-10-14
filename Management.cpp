#include "Management.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Student.h"
#include <algorithm>
using namespace std;


Management::Management()
{
    readFile("./images/student.txt");
    ::loadimage(&m_bk, "./images/bk.png", Window::width(), Window::height());
    ::settextstyle(25, 0, "宋体");

    //主界面按钮初始化
    menu_btns.emplace_back(new PushButton("查看学生"));
    menu_btns.emplace_back(new PushButton("添加学生"));
    menu_btns.emplace_back(new PushButton("删除学生"));
    menu_btns.emplace_back(new PushButton("修改学生"));
    menu_btns.emplace_back(new PushButton("查找学生"));
    menu_btns.emplace_back(new PushButton("退出系统"));
    for (int i = 0; i < menu_btns.size(); i++)
    {
        menu_btns[i]->setFixedSize(250, 50);

        int bx = (Window::width() - menu_btns[i]->width()) / 2;

        int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
        int by = vspace + i * menu_btns[i]->height();

        menu_btns[i]->move(bx, by);
    }

    //初始化查看学生的表格
    m_showTable.reset(new Table);
    m_showTable->setRowCount(16);
    m_showTable->setHeader(m_header);
    updateShowTable();
    //m_showTable->show();

    m_showTable->move(50, 50);

 /*   for (auto& val : vec_stu)
    {
        m_showTable->insertData(val.formatInfo());
    }
*/

    //让表格居中，（不知道我运行为啥有问题，可能那边表格读取的时候本来的原因）
    //m_showTable->move((Window::width() - m_showTable->width()) / 2, 100);


    //添加学生
    m_addBtn.reset(new PushButton("添加", 670, 260, 140, 60));
    m_addEdit.reset(new LineEdit(150, 260, 500, 60));
    m_addEdit->setTitle("请输入学生信息");
    m_addEdit->setHitText("请按照\n\t<学号 姓名 班级 数学 语文 英语>\n格式输入学生信息");

    //删除学生
    m_delBtn.reset(new PushButton("删除", 670, 260, 140, 60));
    m_delEdit.reset(new LineEdit(150, 260, 500, 60));
    m_delEdit->setTitle("请输入学生学号");
    m_delEdit->setHitText("请输入学生学号");

    m_delTable.reset(new Table);
    m_delTable->setHeader(m_header);
    m_delTable->move(m_delEdit->x()- 70, m_delEdit->y() + 150);// 修改删除格子的位置
    m_delTable->setRowCount(1);

}

void Management::run()
{
    //获取菜单的返回值
    m_op = Menu;
    Window::beginDraw();
    while (true)
    {
        Window::clear();
        drawBackground();

        if (Window::hasMsg())
        {
           switch (Window::getMsg().message)
           {
           case WM_KEYDOWN:  //按键按下
               if (Window::getMsg().vkcode == VK_ESCAPE) //按ESC退出操作,返回主界面
               {
                   m_op = Menu;
               }
               break;
               
           default:     //鼠标操作
               eventLoop();
  
               break;
           }
        }

        switch (m_op)
        {
        case Menu:
            m_op = menu();
            break;
        case Management::Display:
            display();
            break;
        case Management::Insert:
            add();
            break;
        case Management::Remove:
            erase();
            break;
        case Management::Modify:
            modify();
            break;
        case Management::Search:
            search();
            break;
        default:
            saveFile("./images/test.txt");
            exit(666);
            break;
        }
        Window::flushDraw();
        Window::getMsg().message = 0;
    }
    Window::endDraw();
}

int Management::menu()
{
    for (int i = 0; i < menu_btns.size(); i++)
    {
        menu_btns[i]->show();
        menu_btns[i]->event();
        if (menu_btns[i] -> isClicked())
        {
            return i;
        }
    }

    return Menu;
}

void Management::display()
{
    m_showTable->show();
 //   cout << "display" << endl;
}

void Management::add()
{
    const char* title = "请输入学生信息<学号 姓名 班级 数学 语文 英语>";
    settextstyle(36, 0, "楷体");
    outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

    m_addBtn->show();
    m_addEdit->show();
    auto str = m_addEdit->text();
    if (m_addBtn->isClicked() && !str.empty())
    {
       vec_stu.push_back(Student::fromString(m_addEdit->text()));

       std::replace(str.begin(), str.end(), ' ', '\t');
       m_showTable->insertData(str);                       //
       m_addEdit->clear();
    }

}

void Management::erase()
{
    const char* title = "请输入要删除的学生的学号";
    settextstyle(36, 0, "楷体");
    outtextxy((Window::width() - textwidth(title)) / 2, 150, title);


    m_delBtn->show();
    m_delEdit->show();

    m_delTable->show(); //加上这个删除的时候才有格子

    if(m_delTable->rowCount() != 0)
        m_delTable->show();

    auto& str = m_delEdit->text();
    if (m_delEdit->textChanged())
    {
        auto it = std::find_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
            {
                return std::to_string(stu.number) == str;
            });
        if (it == vec_stu.end())
        {
            outtextxy(m_delEdit->x(), m_delEdit->y() + 70, std::string("对不起，没有找到学号为" + str + "的学生信息").data());
        }
        else
        {
            m_delTable->insertData(it->formatInfo()); 
            //m_delEdit->clear(); //好像影响不大
           // std::cout << "cout:" << m_delTable->rowCount() << std::endl;

        }
        m_delEdit->clear(); //好像影响不大
        
    }

    if (m_delBtn->isClicked())
    {
        auto it = std::remove_if(vec_stu.begin(), vec_stu.end(), [=](const Student& stu)
            {
                return std::to_string(stu.number) == str;
            });
/*        if (it != vec_stu.end())
        {
            m_delEdit->clear();
            m_delTable->clear();
        }
        */

        vec_stu.erase(it, vec_stu.end());
        updateShowTable();
        m_op = Menu;


    }
}

void Management::modify()
{
    outtextxy(0, 0, "modify");
    cout << "modify" << endl;
}

void Management::search()
{
    outtextxy(0, 0, "search");
    cout << "search" << endl;
}

void Management::drawBackground()
{
    ::putimage(0, 0, &m_bk);
}

void Management::eventLoop()
{
    m_showTable->event();

    m_addBtn->event();
    m_addEdit->event();

    m_delBtn->event();
    m_delEdit->event();
    m_delTable->event();
}

void Management::readFile(const std::string& fileName)
{
    fstream read(fileName, ios::in);
    if (!read.is_open())
    {
        return;
    }
    //读取表头
    char buf[1024] = { 0 };
    read.getline(buf, 1024);
    m_header = buf;
    cout << buf << endl;
    //读取数据
    while (!read.eof())
    {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        //跳过空行
        if (strlen(data) == 0)
            break;

        //格式化读取
        Student stu;
        stringstream ss(data);
        ss >> stu.number >> stu.name >> stu.grade >> stu.math >> stu.chinese >> stu.english;
        vec_stu.push_back(stu);
        //cout << stu.number << stu.name << stu.grade << stu.math << stu.chinese << stu.english << endl;
    }

    read.close();
}

void Management::saveFile(const std::string& fileName)
{
    fstream write(fileName, ios::out | ios::trunc);
    if (!write.is_open())
    {
        cerr << fileName << "file open failed" << endl;
        return;
    }

    //写表头
    m_header += "\n";
    write.write(m_header.c_str(), m_header.size());


    //写数据
    for (auto& val : vec_stu)
    {
        std::string info = val.formatInfo();
        write.write(info.c_str(), info.size());
    }

    write.close();
}

void Management::updateShowTable()
{
    m_showTable->clear();
    for (auto& val : vec_stu)
     {
       m_showTable->insertData(val.formatInfo());
     }
}
