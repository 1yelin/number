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
    ::settextstyle(25, 0, "����");

    //�����水ť��ʼ��
    menu_btns.emplace_back(new PushButton("�鿴ѧ��"));
    menu_btns.emplace_back(new PushButton("���ѧ��"));
    menu_btns.emplace_back(new PushButton("ɾ��ѧ��"));
    menu_btns.emplace_back(new PushButton("�޸�ѧ��"));
    menu_btns.emplace_back(new PushButton("����ѧ��"));
    menu_btns.emplace_back(new PushButton("�˳�ϵͳ"));
    for (int i = 0; i < menu_btns.size(); i++)
    {
        menu_btns[i]->setFixedSize(250, 50);

        int bx = (Window::width() - menu_btns[i]->width()) / 2;

        int vspace = (Window::height() - menu_btns.size() * menu_btns[i]->height()) / 2;
        int by = vspace + i * menu_btns[i]->height();

        menu_btns[i]->move(bx, by);
    }

    //��ʼ���鿴ѧ���ı��
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

    //�ñ����У�����֪��������Ϊɶ�����⣬�����Ǳ߱���ȡ��ʱ������ԭ��
    //m_showTable->move((Window::width() - m_showTable->width()) / 2, 100);


    //���ѧ��
    m_addBtn.reset(new PushButton("���", 670, 260, 140, 60));
    m_addEdit.reset(new LineEdit(150, 260, 500, 60));
    m_addEdit->setTitle("������ѧ����Ϣ");
    m_addEdit->setHitText("�밴��\n\t<ѧ�� ���� �༶ ��ѧ ���� Ӣ��>\n��ʽ����ѧ����Ϣ");

    //ɾ��ѧ��
    m_delBtn.reset(new PushButton("ɾ��", 670, 260, 140, 60));
    m_delEdit.reset(new LineEdit(150, 260, 500, 60));
    m_delEdit->setTitle("������ѧ��ѧ��");
    m_delEdit->setHitText("������ѧ��ѧ��");

    m_delTable.reset(new Table);
    m_delTable->setHeader(m_header);
    m_delTable->move(m_delEdit->x()- 70, m_delEdit->y() + 150);// �޸�ɾ�����ӵ�λ��
    m_delTable->setRowCount(1);

}

void Management::run()
{
    //��ȡ�˵��ķ���ֵ
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
           case WM_KEYDOWN:  //��������
               if (Window::getMsg().vkcode == VK_ESCAPE) //��ESC�˳�����,����������
               {
                   m_op = Menu;
               }
               break;
               
           default:     //������
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
    const char* title = "������ѧ����Ϣ<ѧ�� ���� �༶ ��ѧ ���� Ӣ��>";
    settextstyle(36, 0, "����");
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
    const char* title = "������Ҫɾ����ѧ����ѧ��";
    settextstyle(36, 0, "����");
    outtextxy((Window::width() - textwidth(title)) / 2, 150, title);


    m_delBtn->show();
    m_delEdit->show();

    m_delTable->show(); //�������ɾ����ʱ����и���

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
            outtextxy(m_delEdit->x(), m_delEdit->y() + 70, std::string("�Բ���û���ҵ�ѧ��Ϊ" + str + "��ѧ����Ϣ").data());
        }
        else
        {
            m_delTable->insertData(it->formatInfo()); 
            //m_delEdit->clear(); //����Ӱ�첻��
           // std::cout << "cout:" << m_delTable->rowCount() << std::endl;

        }
        m_delEdit->clear(); //����Ӱ�첻��
        
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
    //��ȡ��ͷ
    char buf[1024] = { 0 };
    read.getline(buf, 1024);
    m_header = buf;
    cout << buf << endl;
    //��ȡ����
    while (!read.eof())
    {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        //��������
        if (strlen(data) == 0)
            break;

        //��ʽ����ȡ
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

    //д��ͷ
    m_header += "\n";
    write.write(m_header.c_str(), m_header.size());


    //д����
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
