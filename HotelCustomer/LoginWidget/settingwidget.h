#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();
signals:
    void signalSettingIp(QString ip);
public slots:
    void slotShowSetting();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
