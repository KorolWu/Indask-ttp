#ifndef AXISSTATUSWIDGET_H
#define AXISSTATUSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AxisStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AxisStatusWidget(QString axisName, QWidget *parent = nullptr);

    void changeStatus(const uint64_t status);

signals:
private:
    int m_width;
    QString m_axisName;
    QHBoxLayout *m_hbox;
    void initUI();
    QLabel *m_pName[9];
    QLabel *m_pStatus[9];
    QList<QString> m_labelNameList;

};

#endif // AXISSTATUSWIDGET_H
