#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <QProcess>
#include <QDesktopServices>
#include <QFile>
#include <include/JlCompress.h>
#include <tchar.h>
#include <QString>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#define TITLE "Planetarian SnowGlobe ����������װ����"
#pragma push_macro("slots")
#undef slots
//#include <python/include/Python.h>
#pragma pop_macro("slots")
#pragma execution_character_set("utf-8")

namespace text{
void INSTALL(void);
void DOWNLOAD(void);
void DOWNLOAD_BEFORE(void);

void INSTALL(void)
{
    if( (_access( "SiglusEngine.exe", 0 )) != -1 && (_access( "Gameexe.dat", 0 )) != -1 && ((_access( "Scene.pck", 0 )) != -1 || (_access( "SiglusEngine.exe.org", 0 )) != -1))
       {
          QMessageBox::StandardButton result=QMessageBox::question(NULL, TITLE,"�Ƿ�Ҫ��װ����������");
          if (result == QMessageBox::Yes)
          {
/*            �˷�����Ҫ��Python�������������Python��ϵͳ������Python������̫�鷳�ˡ���
              Py_Initialize();
              PyRun_SimpleString("from PyCode import install");
              PyRun_SimpleString("install()");
              Py_Finalize();
              ����ֱ�ӵ������õ�exe���գ�
*/            QProcess::execute("PyCode.exe -i");
              QMessageBox::StandardButton choice = QMessageBox::question(NULL,TITLE,"����������װ��ɣ���˫��SiglusEngine_CHS.exe�ļ����к�������Ϸ����SiglusEngine.exeΪ����ԭ�棩\n\n�Ƿ����������Ѻ���������˫����Ч��Ļed��\n��СԼ200MB.");
              if (choice == QMessageBox::Yes)
              {
                  DOWNLOAD();
              }
              else
              {
                  QMessageBox::information(NULL,TITLE,"ף���������������~��");
              }
          }
       }
    else
       {
        QMessageBox::critical(NULL,TITLE, "��Ϸ���岻�������뽫����������������Ϸ���������ļ��У�");
    }
}

void DOWNLOAD(void)
{
    system("PyCode.exe -d");
    HANDLE handle = CreateFile(_T(".\\mov\\staff.avi"), FILE_READ_EA,
    FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (handle != INVALID_HANDLE_VALUE)
    {
         int size = GetFileSize(handle, NULL);
         CloseHandle(handle);
         if ((size == 204479650) || ((size > 204479550) && (size < 204479750)))
         {
             QMessageBox::information(NULL,TITLE,"ed������ɣ�ף���������������~");
         }
         else
         {
             QMessageBox::critical(NULL,TITLE,"����ʧ�ܣ������ԣ�");
         }
    }
    else
    {
        QMessageBox::critical(NULL,TITLE,"����ʧ�ܣ������ԣ�");
    }
}
void DOWNLOAD_BEFORE(void)
{
    QMessageBox::StandardButton choice = QMessageBox::question(NULL,TITLE,"�Ƿ����������Ѻ���������˫����Ч��Ļed��\n��СԼ200MB.");
    if (choice == QMessageBox::Yes)
    {
        DOWNLOAD();
    }
}
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->InstallButton->connect(ui->InstallButton,&QPushButton::clicked,this,&text::INSTALL);
    ui->DownloadButton->connect(ui->DownloadButton,&QPushButton::clicked,this,&text::DOWNLOAD_BEFORE);
    //ui->checkBox_3->connect(ui->checkBox_3,&QCheckBox::clicked,this,NULL);
}
MainWindow::~MainWindow()
{
    delete ui;
}
