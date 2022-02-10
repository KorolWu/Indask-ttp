#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")
//using namespace QsLogging;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //程序当前运行目录
    m_path = QCoreApplication::applicationDirPath();
   // initParameter();
    initSqlite();
    initMainUI();
    initLogInstance();
    initLWidget();
    QString fileName = "E:\\HS-P66\\ADLINK\\ADLINKBoard.xml";

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::start()
{




}
///
/// \brief MainWindow::initParameter
/// 从ini 文件里面读取各轴的速度参数
///
void MainWindow::initParameter()
{
    for (int i = 0;i < 18; i++ ) {
        int axisId = 0;
        if(i >7)
            axisId = i + 6;
        else
            axisId = i;
        getIniParameter(axisId);

    }

}

bool MainWindow::initSqlite()
{

   return 0;
}

void MainWindow::getIniParameter(const int axisId)
{

}

void MainWindow::childrenFormHide()
{
//    p_ioForm->hide();
//    p_axisCheck->hide();
//    p_visionForm->hide();
//    p_parameter->hide();
//    p_xxy->hide();
//    p_positionManager->hide();
//    m_pNozzle->hide();

}

void MainWindow::initMainUI()
{
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect(0,0,1800,1000); //=  screen->availableVirtualGeometry();
    ShareData::GetInstance()->m_width = screenRect.width()-2;
    ShareData::GetInstance()->m_heitht = screenRect.height()-40;
    this->resize(ShareData::GetInstance()->m_width,ShareData::GetInstance()->m_heitht);
    this->setWindowTitle("HS_P66");
    this->setObjectName("mainWindow");
    m_hsLog = new QLabel(this);
    m_hsLog->resize(ShareData::GetInstance()->m_width/6,ShareData::GetInstance()->m_heitht/10 -2);
    m_hsLogTest = new QLabel(this);
    //m_hsLogTest->setText("HS-P66");
    m_hsLogTest->setMinimumWidth(200);
    m_hsLogTest->move(ShareData::GetInstance()->m_width/6-40,70);
    m_hsLogTest->setStyleSheet("font:Times;font-size:40px; color: rgb(135, 206, 250);");
    QPixmap pix = QPixmap(":/image/APPSTARTCN.png");
    pix.scaled(QSize(ShareData::GetInstance()->m_width/6,ShareData::GetInstance()->m_heitht/10 -2),Qt::KeepAspectRatio);
    m_hsLog->setPixmap(pix);
    m_LWidget =new QWidget(this);//左边放 treeView 窗体
    m_LWidget->move(0,ShareData::GetInstance()->m_heitht/10);
    m_LWidget->resize(ShareData::GetInstance()->m_width/7,ShareData::GetInstance()->m_heitht);
    m_LWidget->setStyleSheet("background-color:rgb(48, 74, 129)");

    int offect = 30;
    m_start = new QPushButton("启动",this);
    m_start->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_start->move(ShareData::GetInstance()->m_width/10*9+offect,15);
    m_start->setIcon(QIcon(":/src/Image/start"));
    connect(m_start,&QPushButton::clicked,this,&MainWindow::start);

    m_reset = new QPushButton("复位",this);
    m_reset->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_reset->move(ShareData::GetInstance()->m_width/10*8+offect+80,15);
    m_reset->setIcon(QIcon(":/src/Image/reset_o"));

    m_emg = new QPushButton("急停",this);
    connect(m_emg,&QPushButton::clicked,this,&MainWindow::emgStop);
    m_emg->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_emg->move(ShareData::GetInstance()->m_width/10*7+offect+160,15);
    m_emg->setIcon(QIcon(":/src/Image/emg"));

    m_home= new QPushButton("原点",this);
    connect(m_home,&QPushButton::clicked,this,&MainWindow::home);
    m_home->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_home->move(ShareData::GetInstance()->m_width/10*6+offect+230,15);
    m_home->setIcon(QIcon(":/src/Image/home"));
   //this->setStyleSheet("#mainWindow{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.753358, y2:0.795, stop:0.196532 rgba(46, 70, 124, 255), stop:1 rgba(87, 153, 230, 255));}");
    this->setStyleSheet("#mainWindow{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.753358, y2:0.795, stop:0.196532 rgba(46, 70, 124, 255), stop:1 rgba(87, 153, 230, 255));}"\
                "QPushButton{background-color:rgb(190,190,190);border-radius: 5px;font:18px;}"\
                        "QPushButton:hover{background-color:rgb(210,210,210);}"\
    "QPushButton:pressed{background-color:rgb(160,160,160);}");

    m_MainWidget = new QWidget(this);
    m_MainWidget->move(ShareData::GetInstance()->m_width/7+3,ShareData::GetInstance()->m_heitht/10);
    m_MainWidget->resize(ShareData::GetInstance()->m_width/6*5+25,ShareData::GetInstance()->m_heitht-10);
    m_pLogText = new QTextEdit(m_MainWidget);
    m_pLogText->move(3,m_MainWidget->height()/5*3+100);
    m_pLogText->resize(m_MainWidget->width()-15,m_MainWidget->height()/5-15);
    m_pLogText->setStyleSheet("font-family:Times; font:17px;background:transparent;border-width: 1px;border-color:rgb(150,150,150); border-style: solid;border-radius:10px;");

   // p_positionManager = new PositionManager(m_MainWidget);
  //  p_positionManager->hide();

}

void MainWindow::initLWidget()
{
    p_treeView = new QTreeView(m_LWidget);
    p_treeView->setStyleSheet("QTreeView{border: 1px solid lightgray;}"
                              "QTreeView::item {height: 40px;border-radius: 2px;border: 1px solid transparent;background: transparent;color: white;}"
                              "QTreeView::item:has-children {border: none;border-bottom: 1px solid lightgray;}"
                              "QTreeView::item:hover {border: 1px solid rgb(170, 190, 230);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              "QTreeView::item:selected {border: 1px solid rgb(230, 240, 250);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              );
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(ShareData::GetInstance()->m_width/7,ShareData::GetInstance()->m_heitht);
    p_treeStandarModel = new QStandardItemModel(p_treeView);
    p_treeView->setModel(p_treeStandarModel);
    p_treeView->setFont(QFont("宋体",18));
    p_treeView->header();
    p_treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    p_standarItem = new QStandardItem("运动控制");
    p_standarItem->setIcon(QIcon(":/src/Image/move.png"));
    p_ordersItem = new QStandardItem("参数设置");
    p_ordersItem->setIcon(QIcon(":/src/Image/seting.png"));
    p_loginroleItem = new  QStandardItem("IO监视");
    p_singlAxisControl = new QStandardItem("单轴运动");
    p_xxyItem = new QStandardItem("XXY载台");
    p_positionItem = new QStandardItem("点位管理");

    p_standarItem->appendRow(p_ordersItem);
    p_standarItem->appendRow(p_loginroleItem);
    p_standarItem->appendRow(p_singlAxisControl);
    p_standarItem->appendRow(p_xxyItem);
    p_standarItem->appendRow(p_positionItem);

    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("视觉管理");
    p_standarItem->setIcon(QIcon(":/src/Image/vision.png"));
    p_agvItem = new QStandardItem("参数设置");
    p_agvItem->setIcon(QIcon(":/src/Image/seting.png"));
    p_standarItem->appendRow(p_agvItem);
    p_elevator = new QStandardItem("CCD_1");
    p_elevator->setIcon(QIcon(":/resouse/Image/elevator.png"));
    p_standarItem->appendRow(p_elevator);
    p_runer = new QStandardItem("CCD_2");
    p_runer->setIcon(QIcon(":/resouse/Image/elevator.png"));
    p_standarItem->appendRow(p_runer);
    p_treeStandarModel->appendRow(p_standarItem);

    p_standarItem = new QStandardItem("喷头管理");
    p_standarItem->setIcon(QIcon(":/src/Image/log.png"));
    p_treeStandarModel->appendRow(p_standarItem);
}

void MainWindow::initLogInstance()
{
//    Logger& logger = Logger::instance();
//    logger.setLoggingLevel(QsLogging::TraceLevel);

////  添加文件为目的地
//    const QString sLogPath(QDir(QApplication::applicationDirPath()).filePath("log.txt"));
//    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
//                                       sLogPath, EnableLogRotation, MaxSizeBytes(512*1024), MaxOldLogCount(5)));
//    logger.addDestination(fileDestination);



//       //添加到textEdit
//       DestinationPtr objectDestination(DestinationFactory::MakeFunctorDestination(this, SLOT(appendLog(QString,int))));
//       logger.addDestination(objectDestination);


//     QLOG_ERROR() << "5-error Qlog 日志记录模块启动";

}

void MainWindow::onTreeviewClicked(const QModelIndex &index)
{
    childrenFormHide();
    QString row_name = index.data().toString();
    if(row_name == "单轴运动")
    {
        //qDebug()<<"handle 权限管理...";
    }

}

int MainWindow::initAdlinkDriver(const QString &fileName)
{
        return 0;
}

///
/// \brief MainWindow::beginIn
/// \return
///
bool MainWindow::beginIn(const int &dir)
{

   return true;
}

bool MainWindow::getGlass()
{

    return false;
}

bool MainWindow::printX()
{

    return true;
}

bool MainWindow::printFlow()
{


    return true;
}

void MainWindow::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}


void MainWindow::appendLog(const QString &message, int level)
{
    m_pLogText->append(message + " " + QString::number(level));
}

///
/// \brief MainWindow::home
///
void MainWindow::home()
{
    //需要判断里面时候有料，如果有料不可以启动回原点流程


}

void MainWindow::emgStop()
{


}

