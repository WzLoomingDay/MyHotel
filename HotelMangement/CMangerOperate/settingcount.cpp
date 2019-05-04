#include "settingcount.h"
#include "ui_settingcount.h"

SettingCount::SettingCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingCount)
{
    ui->setupUi(this);
}

SettingCount::~SettingCount()
{
    delete ui;
}
