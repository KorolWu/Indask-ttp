#ifndef PCCANDHDCSTATUSWIDGET_H
#define PCCANDHDCSTATUSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include "Delegate/labeldelegateV1.h"

class PccAndHdcStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PccAndHdcStatusWidget(QWidget *parent = nullptr);
    void chnangeTableData();
private:
    int m_width;
    const  QString   headstlye ="QHeaderView:section{height:32px;font:16px;border:3;"
                                "color: #4B7A93;background-color: #302D3E;};";

    void initUi();
    void SetTableviewsetColumnWidth();
    QStringList m_nameList;
    QLabel *m_pName[4];
    QLabel *m_pValue[4];

    QVBoxLayout *m_vbox;

    QTableView * m_pTabView;

    QStandardItemModel *m_pModel;
signals:

};

#endif // PCCANDHDCSTATUSWIDGET_H
