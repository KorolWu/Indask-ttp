#include "pccandhdcstatuswidget.h"
#include "sharedata.h"

#pragma execution_character_set("utf-8")
///
/// \brief PccAndHdcStatusWidget::PccAndHdcStatusWidget
/// \param parent
///
///
///
PccAndHdcStatusWidget::PccAndHdcStatusWidget(QWidget *parent) : QWidget(parent)
{
    m_vbox = new QVBoxLayout();
    m_nameList<<"PrintStatus:"<<"docCount:"<<"JobCount:"<<"Position:";
    m_width = 1200;
    this->resize(m_width,200);
    initUi();
    this->setStyleSheet("QLabel{color:#FFFFFF;font:20px;}");

}

void PccAndHdcStatusWidget::chnangeTableData()
{
    //SetTableviewsetColumnWidth();
    uint32_t headNum = 2;
    ePRINTERSTATE printState = ShareData::getInstance()->m_pccStatusMap[headNum].appStatus.PrinterState;
    switch (printState) {
    case MPS_DISCONNECTED:
        m_pValue[0]->setText("链接失败");
        break;
    case MPS_CONNECTED:
        m_pValue[0]->setText("链接成功");
        break;
    case MPS_IDLE:
        m_pValue[0]->setText("等待打印");
        break;
    case MPS_READY:
        m_pValue[0]->setText("等待触发");
        break;
    case MPS_PRINTING:
        m_pValue[0]->setText("打印中");
        break;
    case MPS_INITIALIZING:
        m_pValue[0]->setText("cofFPGA");
        break;
    case MPS_STARTUP:
        m_pValue[0]->setText("Starting up");
        break;
    default:
        m_pValue[0]->setText(QString("%1").arg(printState));
    }


    m_pValue[1]->setText(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].appStatus.PrintCount));
    m_pValue[2]->setText(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].appStatus.DocCount));
    m_pValue[3]->setText(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].pccStatus.EncoderCount));

    m_pModel->setItem(0, 0, new QStandardItem(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.HeadNumber));//喷头号
    eHeadState headState = ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.HeadState;
    QString headStateStr = "";
    switch (headState) {
    case ST_OFF:
        headStateStr = "power off";
        break;
    case ST_NOCONN:
        headStateStr = "DisConnect";
        break;
    case ST_NOTUSED:
        headStateStr = "Not Used";
        break;
    case ST_HDPWR:
        headStateStr = "power On";
        break;
    case ST_RUNNING:
        headStateStr = "Ready";
        break;
    default:
        headStateStr = QString("%1").arg(headState);
        break;
    }
     m_pModel->setItem(0, 0, new QStandardItem(QString("%1").arg(headNum)));//喷头状态
    m_pModel->setItem(0, 1, new QStandardItem(headStateStr));//喷头状态
    m_pModel->setItem(0, 2, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.Temperature2* 0.1)));
    m_pModel->setItem(0, 3, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.Voltages[0]* 0.1)));
    m_pModel->setItem(0, 4, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.Voltages[1]* 0.1)));
    m_pModel->setItem(0, 5, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.Voltages[4]* 0.1)));
    m_pModel->setItem(0, 6, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.Voltages[5]* 0.1)));
    m_pModel->setItem(0, 7, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.PccNumber)));
    m_pModel->setItem(0, 8, new QStandardItem(QString("%1").arg(ShareData::getInstance()->m_pccStatusMap[headNum].headerStatus.HeadVoltage)));
    SetTableviewsetColumnWidth();
}

void PccAndHdcStatusWidget::initUi()
{
    QHBoxLayout *hbox = new QHBoxLayout();
    for (int i = 0; i < 4 ;i ++ ) {

        m_pName[i] = new QLabel(this);
        m_pValue[i] = new QLabel(this);
        hbox->addWidget(m_pName[i]);
        hbox->addWidget(m_pValue[i]);
        hbox->addStretch();
        m_pName[i]->setText(m_nameList[i]);

        if(i == 1 || i == 3)
        {
            m_vbox->addLayout(hbox);
            hbox = new QHBoxLayout();
        }
    }

    m_pTabView = new QTableView(this);
    m_pTabView->horizontalHeader()->setStyleSheet(headstlye);
    m_pTabView->move(5,60);
    m_pTabView->verticalHeader()->hide();
    m_pTabView->resize(m_width-8,200);
    m_vbox->addWidget(m_pTabView);
    m_pModel = new QStandardItemModel();
    //model->setQuery("select * from t_sub_taskInfo;");
    //model->query();
    m_pTabView->setModel(m_pModel);

    this->setLayout(m_vbox);
    m_pTabView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTabView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    LabelDelegateV1 *l1 = new LabelDelegateV1();
    m_pTabView->setItemDelegateForColumn(1,l1);
    m_pTabView->setItemDelegateForColumn(5,l1);

    QStringList header;
    header<<"喷头ID"<<"喷头状态"<<"喷头温度"<<"电压LA"<<"电压LB"<<"电压RA"<<"电压RB"<<"PccNumber"<<"HeadVoltage";
//    for(int i = 0 ;i <header.size();i++)
//    {
//        m_pModel->setHeaderData(i, Qt::Horizontal, header.at(i));
//    }
    m_pModel->setHorizontalHeaderLabels(header);

    m_pTabView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    SetTableviewsetColumnWidth();
   // m_pTabView->horizontalHeader()->setMinimumHeight(10);
    m_pTabView->setFont(QFont("宋体",10)); //设置字体

    //this->setLayout(m_vbox);
}

void PccAndHdcStatusWidget::SetTableviewsetColumnWidth()
{
    m_pTabView->setColumnWidth(0,m_width/20*2);
    m_pTabView->setColumnWidth(1,m_width/20*2);
    m_pTabView->setColumnWidth(2,m_width/20*2);
    m_pTabView->setColumnWidth(3,m_width/20*2);

    m_pTabView->setColumnWidth(4,m_width/20*2);
    m_pTabView->setColumnWidth(5,m_width/20*2);
    m_pTabView->setColumnWidth(6,m_width/20*2);
    m_pTabView->setColumnWidth(7,m_width/20*2);
    m_pTabView->setColumnWidth(8,m_width/20*3.5);
   // m_pTabView->horizontalHeader()->setMinimumHeight(10);
    m_pTabView->setFont(QFont("宋体",10)); //设置字体
}
