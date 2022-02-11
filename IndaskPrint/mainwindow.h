#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "stdafx.h"

// Standard libraries
#include <stdio.h>
#include <time.h>

// Meteor specific includes
#include "PrinterInterface.h"	// Contains definitions for all the Meteor library functions
#include "Meteor.h"				// Definition of common datatypes and constants

// Utility functions for handling bitmaps and generating image commands in the correct format
#include "Bitmaps.h"
#include <QFont>
#include <QLabel>
#include <QScreen>
#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QTextEdit>
#include "sharedata.h"
#include <QDateTime>
#include <QDir>
#include <QStandardItemModel>
#include <QPushButton>
#include <QGroupBox>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include "Bitmaps.h"
#include "pccandhdcstatuswidget.h"
#include "axisstatuswidget.h"
#include "Camera/camerawidget.h"
#include "QsLog.h"
#include "Delta/dmcnetcontrol.h"
#include "ttpdevice.h"
#include "pccwork.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void start();
    void appendLog(const QString &message, int level);
    void home();
    void emgStop();
    void onTimout();
private:
    Ui::MainWindow *ui;
    QLabel *m_hsLog;
    QWidget *m_LWidget;
    QPushButton *m_emg;
    QTreeView* p_treeView;
    QStandardItemModel* p_treeStandarModel;
    QLabel *m_hsLogTest;
    QPushButton *m_start;
    QPushButton *m_reset;
    QPushButton *m_home;
    QWidget *m_MainWidget;
    QStandardItem *p_standarItem;
    QStandardItem *p_ordersItem;
    QStandardItem *p_agvItem;
    QStandardItem *p_loginroleItem;
    QStandardItem *p_singlAxisControl;
    QStandardItem *p_elevator;
    QStandardItem *p_runer;
    QStandardItem *p_xxyItem;
    QStandardItem *p_positionItem;
    QTextEdit *m_pLogText;
    QString m_path;
    int m_inited = 1;   //是否初始化通过
    bool m_isHomed = false; //是否回过原点
    void initParameter();
    bool initSqlite();
    void getIniParameter(const int axisId);
    void childrenFormHide();
    void initMainUI();
    void initLWidget();
    void initLogInstance();
    void onTreeviewClicked(const QModelIndex &index);
    int initAdlinkDriver(const QString &fileName);
    void delay_msc(int msc);
    //flow
    bool beginIn(const int &dir);
    bool getGlass();
    bool printX();
    bool printFlow_test();

    QTimer *m_timer;



    //------------------pccStateTableWidget------
    PccAndHdcStatusWidget* m_pccTableWidget;

    //------------------axisStatusWidget--------
    AxisStatusWidget* m_pXaxisStatus;
    AxisStatusWidget* m_pYaxisStatus;

     CameraWidget *m_pCamera;
     //-----------------axisMove-----------
     DmcNetControl m_dmNetControl;
     //-----------------printDevice--------
    TtpDevice m_ttpDevice;
    PccWork* m_pccWork;
    QThread m_thread;
signals:
    void startPccWork();
};
#endif // MAINWINDOW_H
