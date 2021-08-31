//qlabel_doubleclick.cpp
#include "qlabel_doubleclick.h"

qlabel_doubleclick::qlabel_doubleclick(QWidget *parent) : QLabel(parent){

}

qlabel_doubleclick::~qlabel_doubleclick(){}

#include<QDebug>
void qlabel_doubleclick::mouseDoubleClickEvent(QMouseEvent *event){
    //qDebug() << "nm?";
    emit setQlabel();
}
