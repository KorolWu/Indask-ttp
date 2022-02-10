#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QLabel>
#include <QScreen>
#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QMainWindow>
#include <QTextEdit>
#include "sharedata.h"
#include <QDateTime>
#include <QDir>
#include <QStandardItemModel>
#include <QPushButton>
#include <QGroupBox>
#include <QTimer>
#include <QCoreApplication>


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
    bool printFlow();
};
#endif // MAINWINDOW_H
