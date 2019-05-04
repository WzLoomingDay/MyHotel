#ifndef SHOWMEALDETAIL_H
#define SHOWMEALDETAIL_H

#include <QWidget>

#include <QVector>

struct MealMessage
{
    QString id;
    QString name;
    QString number;
};
namespace Ui {
class ShowMealDetail;
}

class ShowMealDetail : public QWidget
{
    Q_OBJECT

public:

    static ShowMealDetail * GetmealDetail(QString &data);
    ~ShowMealDetail();
    void closeEvent(QCloseEvent *event = nullptr);
    void AnalyiseData(QString data);
private slots:
    void on_pb_sure_clicked();
    void showMealDetail();


private:
    explicit ShowMealDetail(QWidget *parent = 0);
    static ShowMealDetail* m_mealdetail;
    Ui::ShowMealDetail *ui;
    static QString m_data;

    QVector<struct MealMessage> m_mealmessage;
};

#endif // SHOWMEALDETAIL_H
