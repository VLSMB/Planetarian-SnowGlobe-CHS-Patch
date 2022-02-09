#include "mainwindow.cpp"
#include <QApplication>
#include <QProcess>
#include <QDesktopServices>
#include <QMessageBox>
#include <QString>
#include <QMainWindow>
#include <QFile>
#include <windows.h>
#include <tchar.h>
#include <QDir>
#include <direct.h>
#include <iostream>

#pragma execution_character_set("utf-8")


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // 感谢团佬的技术支持
    QApplication a(argc, argv);
    MainWindow w;
// 解压PycCode.exe
    QString resProfiex = "exe";
    QString resFileName = "PyCode.exe";
    QString saveFile= "PyCode.exe";
    QString resFile;
    resFile=":/"+resProfiex+"/"+resFileName;
    QFile file;
    file.copy(resFile,saveFile);
//hide the file
    SetFileAttributes(_T(".\\PyCode.exe"),FILE_ATTRIBUTE_HIDDEN);
// initizing
    w.setFixedSize(545, 460);
    w.move(100,100);
    // check the version with Python
    QProcess::execute("PyCode.exe -v");
    if (_access( "Config.old", 0 ) != -1)
        // Use Python to check whether the patch is new,if not,then make a file
    {
        QMessageBox::StandardButton choice = QMessageBox::question(NULL,TITLE,"现在有新版本的汉化补丁，是否要到稻荷社区下载更新？");
        if (choice == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl("https://bbs.inapom.com/2866.html"));
        }
        DeleteFile(_T(".\\Config.old"));
    }
    w.show();
    //delete PyCode.exe
    a.exec();
    QProcess::execute("taskkill.exe /f /t /im PyCode.exe");
    DeleteFile(_T(".\\PyCode.exe"));
    return 0;
}
