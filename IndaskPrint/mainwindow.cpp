#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace QsLogging;

#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&MainWindow::onTimout);
    m_timer->start(300);


    //程序当前运行目录
    m_path = QCoreApplication::applicationDirPath();
    // initParameter();
    initSqlite();
    initMainUI();
    initLogInstance();
    initLWidget();

    AxisStruct axisStruct;
    axisStruct.acc = 0.5;
    axisStruct.dcc = 0.5;
    axisStruct.vMax  = 200000;
    axisStruct.homeVmax = 60000;


    ShareData::getInstance()->m_axisParameterMap.insert(1,axisStruct);
    ShareData::getInstance()->m_axisParameterMap.insert(2,axisStruct);
    //-----------init DomNet------------
    m_inited = m_dmNetControl.openCar();
    m_inited &= m_dmNetControl.initCar();
    if(m_inited == 0)
    {
        QLOG_INFO()<<"init dmcDevice success;";

    }
    //init Pccwork thread
    m_pccWork = new PccWork();
    m_pccWork->moveToThread(&m_thread);
    connect(&m_thread, &QThread::finished, m_pccWork, &QObject::deleteLater);
    connect(this,&MainWindow::startPccWork,m_pccWork,&PccWork::work);
    m_thread.start();

    //----------init ttpDevice----------
    bool ret =  m_ttpDevice.openDevice();
    if(ret == true)
    {
        QLOG_INFO()<<"init ttpDevice success";
        emit startPccWork();
    }


}

MainWindow::~MainWindow()
{
    m_dmNetControl.disConnected();
    ShareData::getInstance()->deleteInstance();
    while (RVAL_OK != PiClosePrinter()) {}

    if(m_pccWork != nullptr) m_pccWork->m_StopFlag = false;

    m_thread.quit();
    m_thread.wait();
    delete ui;
}

void MainWindow::start()
{

    if(true == m_isHomed)
    {
        //先到打印初始位置
        int dis = 516300; //abs position
        QMap<uint16_t, int> posMap;
        posMap.insert(1,dis);
        posMap.insert(2,393000);
        int result = m_dmNetControl.ppMove(posMap);
        if(result != 0)
            return;
        delay_msc(500);
        //将图传给pcc

        if(printFlow_test() == true)
        {
            delay_msc(1500);
            if(true == m_isHomed)
            {
                // int abs_x = 516300; //abs position
                int temp_x = 516300;
                QMap<uint16_t, int> posMap;
                for(int i = 0; i< 4; i++)
                {

                     QLOG_INFO()<<QString("正在打印第 %1 Pass").arg(i);
                    int dis = 393000; //abs position
                    // y move +
                    posMap.clear();
                    posMap.insert(2,648000);
                    int result = m_dmNetControl.ppMove(posMap);

                    delay_msc(1000);
                    if(result == 0)
                    {
                        posMap.clear();
                        temp_x -= 28;
                        posMap.insert(1,temp_x);
                        posMap.insert(2,dis);
                        result = m_dmNetControl.ppMove(posMap);
                        if(result != 0 )
                            return;
                    }
                    else
                        return;
                    delay_msc(1000);
                }

                posMap.clear();
                posMap.insert(1,5);
                posMap.insert(2,5);
                int result = m_dmNetControl.ppMove(posMap);
                if(result != 0 )
                    return;
                QLOG_INFO()<<"打印完成";
            }
        }

    }

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
    m_pccTableWidget->hide();
    m_pXaxisStatus->hide();
    m_pYaxisStatus->hide();
    m_pCamera->hide();
}

void MainWindow::initMainUI()
{
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect(0,0,1800,1000); //=  screen->availableVirtualGeometry();
    ShareData::getInstance()->m_width = screenRect.width()-2;
    ShareData::getInstance()->m_heitht = screenRect.height()-40;
    this->resize(ShareData::getInstance()->m_width,ShareData::getInstance()->m_heitht);
    this->setWindowTitle("HS_P66");
    this->setObjectName("mainWindow");
    m_hsLog = new QLabel(this);
    m_hsLog->setStyleSheet("background:transparent;");
    m_hsLog->resize(ShareData::getInstance()->m_width/2,ShareData::getInstance()->m_heitht/10 -2);
    m_hsLogTest = new QLabel(this);
    //m_hsLogTest->setText("HS-P66");
    m_hsLogTest->setMinimumWidth(200);
    m_hsLogTest->move(ShareData::getInstance()->m_width/6-40,70);
    m_hsLogTest->setStyleSheet("font:Times;font-size:40px; color: rgb(135, 206, 250);");
    QPixmap pix = QPixmap(":/image/d2f05f6daaab4c0804d1da9a0c3b599.jpg");
    pix.scaled(QSize(ShareData::getInstance()->m_width/6,ShareData::getInstance()->m_heitht/10 -2),Qt::KeepAspectRatio);
    m_hsLog->setPixmap(pix);
    m_LWidget =new QWidget(this);//左边放 treeView 窗体
    m_LWidget->move(0,ShareData::getInstance()->m_heitht/10);
    m_LWidget->resize(ShareData::getInstance()->m_width/7,ShareData::getInstance()->m_heitht);
    m_LWidget->setStyleSheet("background-color:rgb(48, 74, 129)");

    int offect = 30;
    m_start = new QPushButton("启动",this);
    m_start->resize(ShareData::getInstance()->m_width/20,ShareData::getInstance()->m_heitht/17);
    m_start->move(ShareData::getInstance()->m_width/10*9+offect,15);
    m_start->setIcon(QIcon(":/src/Image/start"));
    connect(m_start,&QPushButton::clicked,this,&MainWindow::start);

    m_reset = new QPushButton("复位",this);
    m_reset->resize(ShareData::getInstance()->m_width/20,ShareData::getInstance()->m_heitht/17);
    m_reset->move(ShareData::getInstance()->m_width/10*8+offect+80,15);
    m_reset->setIcon(QIcon(":/src/Image/reset_o"));

    m_emg = new QPushButton("急停",this);
    connect(m_emg,&QPushButton::clicked,this,&MainWindow::emgStop);
    m_emg->resize(ShareData::getInstance()->m_width/20,ShareData::getInstance()->m_heitht/17);
    m_emg->move(ShareData::getInstance()->m_width/10*7+offect+160,15);
    m_emg->setIcon(QIcon(":/src/Image/emg"));

    m_home= new QPushButton("原点",this);
    connect(m_home,&QPushButton::clicked,this,&MainWindow::home);
    m_home->resize(ShareData::getInstance()->m_width/20,ShareData::getInstance()->m_heitht/17);
    m_home->move(ShareData::getInstance()->m_width/10*6+offect+230,15);
    m_home->setIcon(QIcon(":/src/Image/home"));
    //this->setStyleSheet("#mainWindow{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.753358, y2:0.795, stop:0.196532 rgba(46, 70, 124, 255), stop:1 rgba(87, 153, 230, 255));}");
    this->setStyleSheet("#mainWindow{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.753358, y2:0.795, stop:0.196532 rgba(46, 70, 124, 255), stop:1 rgba(87, 153, 230, 255));}"\
                        "QPushButton{background-color:rgb(190,190,190);border-radius: 5px;font:18px;}"\
                        "QPushButton:hover{background-color:rgb(210,210,210);}"\
                        "QPushButton:pressed{background-color:rgb(160,160,160);}");

    m_MainWidget = new QWidget(this);
    m_MainWidget->move(ShareData::getInstance()->m_width/7+3,ShareData::getInstance()->m_heitht/10);
    m_MainWidget->resize(ShareData::getInstance()->m_width/6*5+25,ShareData::getInstance()->m_heitht-10);
    m_pLogText = new QTextEdit(m_MainWidget);
    m_pLogText->move(3,m_MainWidget->height()/5*3+100);
    m_pLogText->resize(m_MainWidget->width()-15,m_MainWidget->height()/5-15);
    m_pLogText->setStyleSheet("font-family:Times; font:17px;color:white;background:transparent;border-width: 1px;border-color:rgb(150,150,150); border-style: solid;border-radius:10px;");

    // p_positionManager = new PositionManager(m_MainWidget);
    //  p_positionManager->hide();

    m_pccTableWidget = new PccAndHdcStatusWidget(m_MainWidget);
    m_pccTableWidget->move(2,20);
    m_pccTableWidget->hide();


    m_pXaxisStatus = new AxisStatusWidget("X",m_MainWidget);
    m_pXaxisStatus->move(2,20);
    m_pXaxisStatus->hide();
    m_pYaxisStatus = new AxisStatusWidget("Y",m_MainWidget);
    m_pYaxisStatus->move(0,100);
    m_pYaxisStatus->hide();


    //camera init
    m_pCamera = new CameraWidget(m_MainWidget);
    m_pCamera->hide();

}

void MainWindow::initLWidget()
{
    p_treeView = new QTreeView(m_LWidget);
    p_treeView->setStyleSheet("QTreeView{border: 1px solid lightgray;}"
                              "QTreeView::item {height: 40px;border-radius: 2px;border: 1px solid transparent;background: transparent;color: white;}"
                              "QTreeView::item:has-children {border: none;border-bottom: 1px solid lightgray;}"
                              "QTreeView::item:hover {border: 1px solid rgb(87, 153, 230);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(46, 70, 124),"
                              "stop: 0.5 rgb(87, 153, 230), stop: 1.0 rgb(87, 153, 230));}"
                              "QTreeView::item:selected {border: 1px solid rgb(87, 153, 230);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(46, 70, 124),"
                              "stop: 0.5 rgb(87, 153, 230), stop: 1.0 rgb(87, 153, 230));}"
                              );
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(ShareData::getInstance()->m_width/7,ShareData::getInstance()->m_heitht);
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
        Logger& logger = Logger::instance();
        logger.setLoggingLevel(QsLogging::TraceLevel);

    //  添加文件为目的地
        const QString sLogPath(QDir(QApplication::applicationDirPath()).filePath("log.txt"));
        DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                           sLogPath, EnableLogRotation, MaxSizeBytes(512*1024), MaxOldLogCount(5)));
        logger.addDestination(fileDestination);



           //添加到textEdit
           DestinationPtr objectDestination(DestinationFactory::MakeFunctorDestination(this, SLOT(appendLog(QString,int))));
           logger.addDestination(objectDestination);


         QLOG_ERROR() << "5-error Qlog 日志记录模块启动";

}

void MainWindow::onTreeviewClicked(const QModelIndex &index)
{
    childrenFormHide();
    QString row_name = index.data().toString();
    if(row_name == "运动控制")
    {
        childrenFormHide();
        m_pXaxisStatus->show();

        m_pYaxisStatus->show();
    }
    else if(row_name == "喷头管理")
    {
        m_pccTableWidget->show();
    }
    else if(row_name =="视觉管理")
    {
        m_pCamera->show();
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

bool MainWindow::printFlow_test()
{
    const _TCHAR* bitmap1 = nullptr; _TCHAR* bitmap2 = nullptr; _TCHAR* bitmap3 = nullptr; _TCHAR* bitmap4 = nullptr;
    uint32* ImageBuffer = nullptr; uint32* SecondBuffer = nullptr; uint32* ImageBuffer3 = nullptr; uint32* SecondBuffer4 = nullptr;

    DWORD jobid = 0;					// Default to 0
    DWORD jobtype = JT_FIFO;			// Default to Preload path
    DWORD res = RES_HIGH;				// Default to high resolution 分辨率
    DWORD docwidth = 674;//3770;				// Default to A4 length @ 300dpi 文档宽度
    DWORD ncopies = 1;					// Default to 1 copy of the document
    DWORD docid = 1;					// Default to a document ID of 1
    int scanning = 1;					// Default to not scanning 0 = not scan;


    _TCHAR file[] = TEXT("D:\\SplitImage\\a.bmp");
    _TCHAR file2[] = TEXT("D:\\SplitImage\\b.bmp");
    _TCHAR file3[] = TEXT("D:\\SplitImage\\c.bmp");
    _TCHAR file4[] = TEXT("D:\\SplitImage\\d.bmp");
    bitmap1 = file;//reinterpret_cast<wchar_t*>(m_imagePath.utf16());
    bitmap2 = file2;
    bitmap3 = file3;
    bitmap4 = file4;

    // Attempt to open the file and create the image command, for later use.
    ImageBuffer = MakeBitmap(bitmap1);
    SecondBuffer = MakeBitmap(bitmap2);
    ImageBuffer3 = MakeBitmap(bitmap3);
    SecondBuffer4 = MakeBitmap(bitmap4);
    if (ImageBuffer != nullptr) {


        // Everything ok, so start printing now

        // Reset the printer
        //1 clear data
        //2  set home
        //3  heae power on
        m_ttpDevice.InitialisePrinter(scanning);

        // Specify the parameters of the job
        if (m_ttpDevice.StartJob(jobid, jobtype, res, docwidth)) {

            //
            // Number of documents to send.  For FIFO, each copy of the
            // document is sent by the application; FIFO is typically used for
            // variable data, although in this example all documents are identical.
            // For preload, the document is repeated from PCC memory, so only
            // needs to be sent once
            //
            int cycle = (JT_PRELOAD == jobtype) ? 1 : ncopies;

            for (int i = 0; i < cycle; i++) {

                // Start the document
                m_ttpDevice.Start(scanning, jobtype, ncopies, docid);

                // Send the image.  We already created the header when we generated the ImageBuffer,
                // so all we need to do here is send the ImageBuffer
                qDebug()<<"Sending Image";
                m_ttpDevice.SendImage(ImageBuffer);
                // Finished sending images, send the end doc command
                m_ttpDevice.EndDoc();

                // If using scanning printing, send the second document
                if (scanning) {
                    m_ttpDevice.ScanSendDoc(SecondBuffer);
                    m_ttpDevice.ScanSendDoc(ImageBuffer3);
                    m_ttpDevice.ScanSendDoc(SecondBuffer4);
                }

            }

            // Finished sending the document, send the end job command
            m_ttpDevice.EndJob();



            if (SecondBuffer) {
                free(SecondBuffer);
            }
        }
        free(ImageBuffer);
        return true;
    }
    return false;

    // All done now, close the printer interface, by calling PiClosePrinter until the interface closes
    //korol dont want close in here
    //            qDebug()<<"Closing Printer Interface";
    //            while (!PiCanClosePrinter()) {
    //                Sleep(100);
    //            }
    //            while (RVAL_OK != PiClosePrinter()) {}
    // Look out for Monitor log message: "Application Detached"
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
    QVector<uint16> axisVec;
    axisVec.append(1);
    axisVec.append(2);
    int ret = m_dmNetControl.move2homes(axisVec);
    if(ret == 0)
    {
        m_isHomed = true;
        QLOG_INFO()<<"回原点完成";
    }
}

void MainWindow::emgStop()
{


}

void MainWindow::onTimout()
{
    if(m_inited == 0)
    {
        //        int x =  m_dmNetControl.getPosition(1);
        //        int y =  m_dmNetControl.getPosition(2);
        //        ui->xValue->setText(QString("%1").arg(x));
        //        ui->yValue->setText(QString("%1").arg(y));

        uint64_t status =  m_dmNetControl.getAxisStatus(1);
        m_pXaxisStatus->changeStatus(status);
        status = m_dmNetControl.getAxisStatus(2);
        m_pYaxisStatus->changeStatus(status);
    }
    m_pccTableWidget->chnangeTableData();
}

