#include "labeldelegateV1.h"
#include <QDebug>
#include <QApplication>
#include <QPainter>
LabelDelegateV1::LabelDelegateV1()
{

}

void LabelDelegateV1::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();
    if(str == "Ready")
        painter->setBrush(QColor(71,214,105));
    else if(str == "b")
        painter->setBrush(QColor(200,200,200));
    else if(str == "c")
        painter->setBrush(QColor(170,255,255));
    else if(str == "d")
         painter->setBrush(QColor(170,255,127));
    else if(str == "e")
         painter->setBrush(QColor(190,190,190));
    else if(str == "f")
        painter->setBrush(QColor(152,251,152));
    else if(str == "power off")
        painter->setBrush(QColor(205,92,92));
    else if(str == "充电")
        painter->setBrush(QColor(255, 255,0));
    else
        painter->setBrush(QColor(255,200,0));
    painter->setPen(Qt::white);
    painter->drawRect( option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4 );
    painter->setFont(QFont("Arial", 10));
    painter->setPen(Qt::black);
    painter->drawText(option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4, Qt::AlignCenter, str);
}


