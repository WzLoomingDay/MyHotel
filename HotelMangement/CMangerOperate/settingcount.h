#ifndef SETTINGCOUNT_H
#define SETTINGCOUNT_H

#include <QWidget>

namespace Ui {
class SettingCount;
}

class SettingCount : public QWidget
{
    Q_OBJECT

public:
    explicit SettingCount(QWidget *parent = 0);
    ~SettingCount();

private:
    Ui::SettingCount *ui;
};

#endif // SETTINGCOUNT_H
