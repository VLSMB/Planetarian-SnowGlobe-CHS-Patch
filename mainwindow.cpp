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
#define TITLE "Planetarian SnowGlobe 汉化补丁安装程序"
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
          QMessageBox::StandardButton result=QMessageBox::question(NULL, TITLE,"是否要安装汉化补丁？");
          if (result == QMessageBox::Yes)
          {
/*            此方法需要有Python环境，如果在无Python的系统现配置Python环境就太麻烦了……
              Py_Initialize();
              PyRun_SimpleString("from PyCode import install");
              PyRun_SimpleString("install()");
              Py_Finalize();
              于是直接导入编译好的exe（恼）
*/            QProcess::execute("PyCode.exe -i");
              QMessageBox::StandardButton choice = QMessageBox::question(NULL,TITLE,"汉化补丁安装完成，请双击SiglusEngine_CHS.exe文件运行汉化版游戏！（SiglusEngine.exe为日文原版）\n\n是否在线下载已汉化的中日双语特效字幕ed？\n大小约200MB.");
              if (choice == QMessageBox::Yes)
              {
                  DOWNLOAD();
              }
              else
              {
                  QMessageBox::information(NULL,TITLE,"祝您在星象馆玩得愉快~！");
              }
          }
       }
    else
       {
        QMessageBox::critical(NULL,TITLE, "游戏本体不完整！请将汉化补丁运行在游戏本体所在文件夹！");
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
             QMessageBox::information(NULL,TITLE,"ed下载完成，祝您在星象馆玩得愉快~");
         }
         else
         {
             QMessageBox::critical(NULL,TITLE,"下载失败，请重试！");
         }
    }
    else
    {
        QMessageBox::critical(NULL,TITLE,"下载失败，请重试！");
    }
}
void DOWNLOAD_BEFORE(void)
{
    QMessageBox::StandardButton choice = QMessageBox::question(NULL,TITLE,"是否在线下载已汉化的中日双语特效字幕ed？\n大小约200MB.");
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
