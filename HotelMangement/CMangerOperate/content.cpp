#include "content.h"

Content::Content(QWidget *parent):QFrame(parent)
{

    stack =new QStackedWidget(this);//创建堆栈窗口
    stack->setFrameStyle(QFrame::Panel|QFrame::Raised);//
    m_userMange = new UserMange();
    m_customerMange = new CustomerMange();
    m_searchIncome = new searchIncome();
    m_settingcount = new settingcount();
    m_settingmeal = new settingmeal();
    m_settingroom = new settingroom();
    mm_settingroom = new mSettingRoom();
    stack->addWidget(m_userMange);
    stack->addWidget(m_customerMange);
    stack->addWidget(m_settingmeal);
    stack->addWidget(mm_settingroom);
    stack->addWidget(m_settingcount);
    stack->addWidget(m_searchIncome);

    AmendBtn =new QPushButton(tr("修改"));
    CloseBtn =new QPushButton(tr("关闭"));
    QHBoxLayout *BtnLayout =new QHBoxLayout;//一个水平排列布局
    BtnLayout->addStretch(1);//在按钮前插入一个占位符
    BtnLayout->addWidget(AmendBtn);//
    BtnLayout->addWidget(CloseBtn);

    QVBoxLayout *RightLayout =new QVBoxLayout(this);//纵向布局
    RightLayout->setMargin(10);//设置边缘
    RightLayout->setSpacing(6);//设置间距
    RightLayout->addWidget(stack);
    RightLayout->addLayout(BtnLayout);
}
