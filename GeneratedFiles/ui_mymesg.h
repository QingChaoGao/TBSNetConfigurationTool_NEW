/********************************************************************************
** Form generated from reading UI file 'mymesg.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMESG_H
#define UI_MYMESG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_Mymesg
{
public:
    QGridLayout *gridLayout;
    QLabel *lab_MyDisplay;
    QProgressBar *bar_MyDIsplay;

    void setupUi(QDialog *Mymesg)
    {
        if (Mymesg->objectName().isEmpty())
            Mymesg->setObjectName(QStringLiteral("Mymesg"));
        Mymesg->resize(520, 110);
        gridLayout = new QGridLayout(Mymesg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lab_MyDisplay = new QLabel(Mymesg);
        lab_MyDisplay->setObjectName(QStringLiteral("lab_MyDisplay"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lab_MyDisplay->sizePolicy().hasHeightForWidth());
        lab_MyDisplay->setSizePolicy(sizePolicy);
        lab_MyDisplay->setWordWrap(true);

        gridLayout->addWidget(lab_MyDisplay, 0, 0, 1, 1);

        bar_MyDIsplay = new QProgressBar(Mymesg);
        bar_MyDIsplay->setObjectName(QStringLiteral("bar_MyDIsplay"));
        bar_MyDIsplay->setStyleSheet(QStringLiteral(""));
        bar_MyDIsplay->setMaximum(99);
        bar_MyDIsplay->setValue(0);

        gridLayout->addWidget(bar_MyDIsplay, 1, 0, 1, 1);


        retranslateUi(Mymesg);

        QMetaObject::connectSlotsByName(Mymesg);
    } // setupUi

    void retranslateUi(QDialog *Mymesg)
    {
        Mymesg->setWindowTitle(QApplication::translate("Mymesg", "infromation", nullptr));
        lab_MyDisplay->setText(QApplication::translate("Mymesg", "The device is being configured, please wait..", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mymesg: public Ui_Mymesg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMESG_H
