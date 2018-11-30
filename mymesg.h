#ifndef MYMESG_H
#define MYMESG_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class Mymesg;
}

class Mymesg : public QDialog
{
    Q_OBJECT

public:
    explicit Mymesg(QWidget *parent = 0);
    ~Mymesg();
	void starttimer(QString title,int cnt_time);
private slots:
    void timeoutfunc(void);
private:
    Ui::Mymesg *ui;
    QTimer *mytimer;
    int count;
};

#endif // MYMESG_H
