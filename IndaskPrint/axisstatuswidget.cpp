#include "axisstatuswidget.h"

AxisStatusWidget::AxisStatusWidget(QString axisName, QWidget *parent) : QWidget(parent)
{
    m_width = parent->width() - 206;
    m_labelNameList<<"Mol1"<<"Ml2"<<"TG"<<"SrOn"<<"Err"<<"Inp"<<"S1"<<"PEL"<<"MEL";
    this->resize(m_width,50);
    m_hbox = new QHBoxLayout();

    m_axisName = axisName;
    QLabel * axisLabel = new QLabel(this);
    axisLabel->setMaximumWidth(40);
    axisLabel->setText(axisName);
    axisLabel->setStyleSheet("color:white;font:22px;");
    QVBoxLayout *v = new QVBoxLayout();
    v->addWidget(axisLabel);
    m_hbox->addLayout(v);

    initUI();
}


void AxisStatusWidget::changeStatus(const uint64_t status)
{
    if((status >> 1 & 0x1) == 1)
    {
        m_pStatus[0]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
         m_pStatus[0]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 2 & 0x1) == 1)
    {
        m_pStatus[1]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[1]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 7 & 0x1) == 1)
    {
        m_pStatus[2]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[2]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 8 & 0x1) == 1)
    {
        m_pStatus[3]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[3]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 9 & 0x1) == 1)
    {
        m_pStatus[4]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[4]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 10 & 0x1) == 1)
    {
        m_pStatus[5]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[5]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 12 & 0x1) == 1)
    {
        m_pStatus[6]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[6]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 14 & 0x1) == 1)
    {
        m_pStatus[7]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[7]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
    if((status >> 15 & 0x1) == 1)
    {
        m_pStatus[8]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
    }
    else
        m_pStatus[8]->setStyleSheet("border-radius:10px;background-color: rgb(125, 125, 125);");
}

void AxisStatusWidget::initUI()
{
    QVBoxLayout *vbox = nullptr;
    for(int i = 0 ; i < 9; i++)
    {
        vbox = new QVBoxLayout();
        m_pName[i] = new QLabel(this);
        m_pName[i]->setText(m_labelNameList[i]);
        m_pName[i]->setStyleSheet("border-radius:10px;color: rgb(255, 254, 254);font:18px;");
        m_pStatus[i] = new QLabel(this);
        m_pStatus[i]->setFixedSize(20,20);
        m_pStatus[i]->setStyleSheet("border-radius:10px;background-color: rgb(255, 0, 0);");
        vbox->addWidget(m_pName[i]);
        vbox->addWidget(m_pStatus[i]);

        m_hbox->addLayout(vbox);

    }
    vbox->addStretch();
    this->setLayout(m_hbox);
}
