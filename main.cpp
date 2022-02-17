#include<stdio.h>
#include<QApplication>
#include<QQmlApplicationEngine>
#include<QQmlContext>
#include<QDebug>
#include<QFont>
#include"appmange.h"
int main(int arg,char*args[]){


 // qDebug()<<"USE OPENGL"<< qputenv("QSG_RHI_BACKEND","opengl");//https://doc.qt.io/qt-6/qtcharts-changes-qt6.html  use opengl

  QApplication app(arg,args);

  AppMange AppMange_(arg,args);




  return app.exec();
}
