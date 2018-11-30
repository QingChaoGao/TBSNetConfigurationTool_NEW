/********************************************************************************
** Form generated from reading UI file 'hdmioptiongui.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HDMIOPTIONGUI_H
#define UI_HDMIOPTIONGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hdmioptiongui
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labIco;
    QLabel *labTitle;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetMenu;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnMenu_Min;
    QPushButton *btnMenu_Close;
    QPushButton *btnMenu_Max;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QGridLayout *gridLayout_8;
    QGroupBox *gbx_SelectPage;
    QHBoxLayout *horizontalLayout;
    QSlider *sli_H;
    QRadioButton *rad_Hdmi;
    QSpacerItem *horizontalSpacer_6;
    QRadioButton *rad_Net;
    QSpacerItem *horizontalSpacer_9;
    QWidget *widget;
    QGridLayout *gridLayout_12;
    QStackedWidget *sta_DevWdeget;
    QWidget *page_hdmi;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_6;
    QLabel *label_21;
    QPushButton *btn_Refresh;
    QLineEdit *lin_HDMIMac;
    QTreeWidget *tree_Dev;
    QGroupBox *gro_OutFmt;
    QGridLayout *gridLayout_4;
    QGroupBox *gro_Mode;
    QHBoxLayout *horizontalLayout_15;
    QRadioButton *rad_Aut;
    QSpacerItem *horizontalSpacer_13;
    QRadioButton *rad_Man;
    QSpacerItem *horizontalSpacer_14;
    QRadioButton *rad_Adv;
    QCheckBox *che_Mute;
    QStackedWidget *sta_Mode;
    QWidget *pag_Ato;
    QVBoxLayout *verticalLayout_13;
    QLabel *lab_Aut;
    QWidget *pag_Man;
    QGridLayout *gridLayout_5;
    QRadioButton *rad_Good;
    QRadioButton *rad_Fair;
    QRadioButton *rad_Mob;
    QRadioButton *rad_Ult;
    QRadioButton *rad_Su;
    QRadioButton *rad_Exc;
    QRadioButton *rad_Poor;
    QWidget *pag_Adv;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *lab_enico;
    QLabel *label_11;
    QLineEdit *lin_Hig;
    QLineEdit *lin_AvBitRte;
    QLabel *label_12;
    QLabel *label_16;
    QLineEdit *lin_Enco;
    QLabel *label_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_8;
    QComboBox *com_Hprofile;
    QLabel *label_9;
    QComboBox *com_Hlevel;
    QLineEdit *lin_Wid;
    QGroupBox *group;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lin_Apid;
    QLineEdit *lin_PgmNa;
    QLineEdit *lin_PgmNo;
    QLabel *lab_PgmNo;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_8;
    QLineEdit *lin_Pcr;
    QLabel *label_6;
    QComboBox *com_Aout;
    QLineEdit *lin_Pmt;
    QLineEdit *lin_Vpid;
    QComboBox *com_AFre;
    QLabel *label_7;
    QLabel *label;
    QPushButton *btn_Res;
    QPushButton *btn_Run;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lin_InFmt;
    QWidget *page_Net;
    QTabWidget *tabNetwork;
    QWidget *TabStreaming;
    QGridLayout *gridLayout_11;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *com_PacketSize;
    QTableWidget *tabW_Streaming;
    QCheckBox *che_Check_all;
    QSpacerItem *horizontalSpacer_10;
    QWidget *TabIpSetting;
    QGridLayout *gridLayout_13;
    QGroupBox *gSetting;
    QGridLayout *gridLayout_16;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_15;
    QLabel *label_24;
    QLabel *label_17;
    QLineEdit *lin_100M_Ip;
    QLineEdit *lin_100M_Mask;
    QLineEdit *lin_100M_Gateway;
    QLabel *label_22;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_9;
    QLabel *label_23;
    QLineEdit *lin_1G_Mask;
    QLineEdit *lin_1G_Gateway;
    QLabel *label_20;
    QLabel *label_18;
    QCheckBox *che_DHCP;
    QLineEdit *lin_1G_Ip;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_14;
    QComboBox *com_Netlist;
    QPushButton *btn_Restart;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_Download;
    QPushButton *btn_Upload;
    QPushButton *btn_Set;

    void setupUi(QDialog *Hdmioptiongui)
    {
        if (Hdmioptiongui->objectName().isEmpty())
            Hdmioptiongui->setObjectName(QStringLiteral("Hdmioptiongui"));
        Hdmioptiongui->setEnabled(true);
        Hdmioptiongui->resize(1072, 710);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Hdmioptiongui->sizePolicy().hasHeightForWidth());
        Hdmioptiongui->setSizePolicy(sizePolicy);
        Hdmioptiongui->setLayoutDirection(Qt::LeftToRight);
        Hdmioptiongui->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(Hdmioptiongui);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widgetTitle = new QWidget(Hdmioptiongui);
        widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(widgetTitle);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        labIco = new QLabel(widgetTitle);
        labIco->setObjectName(QStringLiteral("labIco"));
        labIco->setStyleSheet(QStringLiteral(""));
        labIco->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labIco);

        labTitle = new QLabel(widgetTitle);
        labTitle->setObjectName(QStringLiteral("labTitle"));
        labTitle->setStyleSheet(QStringLiteral(""));
        labTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labTitle);

        widgetTop = new QWidget(widgetTitle);
        widgetTop->setObjectName(QStringLiteral("widgetTop"));
        horizontalLayout_3 = new QHBoxLayout(widgetTop);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_2->addWidget(widgetTop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widgetMenu = new QWidget(widgetTitle);
        widgetMenu->setObjectName(QStringLiteral("widgetMenu"));
        gridLayout_2 = new QGridLayout(widgetMenu);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 3);

        btnMenu_Min = new QPushButton(widgetMenu);
        btnMenu_Min->setObjectName(QStringLiteral("btnMenu_Min"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
        btnMenu_Min->setSizePolicy(sizePolicy2);
        btnMenu_Min->setMinimumSize(QSize(30, 30));
        btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Min->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Min, 0, 1, 1, 1);

        btnMenu_Close = new QPushButton(widgetMenu);
        btnMenu_Close->setObjectName(QStringLiteral("btnMenu_Close"));
        sizePolicy2.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy2);
        btnMenu_Close->setMinimumSize(QSize(30, 30));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Close, 0, 3, 1, 1);

        btnMenu_Max = new QPushButton(widgetMenu);
        btnMenu_Max->setObjectName(QStringLiteral("btnMenu_Max"));
        sizePolicy2.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
        btnMenu_Max->setSizePolicy(sizePolicy2);
        btnMenu_Max->setMinimumSize(QSize(30, 30));
        btnMenu_Max->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(btnMenu_Max, 0, 2, 1, 1);


        horizontalLayout_2->addWidget(widgetMenu);


        verticalLayout->addWidget(widgetTitle);

        stackedWidget = new QStackedWidget(Hdmioptiongui);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page1 = new QWidget();
        page1->setObjectName(QStringLiteral("page1"));
        page1->setAutoFillBackground(false);
        gridLayout_8 = new QGridLayout(page1);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gbx_SelectPage = new QGroupBox(page1);
        gbx_SelectPage->setObjectName(QStringLiteral("gbx_SelectPage"));
        sizePolicy.setHeightForWidth(gbx_SelectPage->sizePolicy().hasHeightForWidth());
        gbx_SelectPage->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(gbx_SelectPage);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sli_H = new QSlider(gbx_SelectPage);
        sli_H->setObjectName(QStringLiteral("sli_H"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sli_H->sizePolicy().hasHeightForWidth());
        sli_H->setSizePolicy(sizePolicy3);
        sli_H->setMinimum(6);
        sli_H->setMaximum(72);
        sli_H->setValue(9);
        sli_H->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sli_H);

        rad_Hdmi = new QRadioButton(gbx_SelectPage);
        rad_Hdmi->setObjectName(QStringLiteral("rad_Hdmi"));

        horizontalLayout->addWidget(rad_Hdmi);

        horizontalSpacer_6 = new QSpacerItem(241, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        rad_Net = new QRadioButton(gbx_SelectPage);
        rad_Net->setObjectName(QStringLiteral("rad_Net"));

        horizontalLayout->addWidget(rad_Net);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        horizontalLayout->setStretch(0, 9);
        horizontalLayout->setStretch(1, 9);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 9);
        horizontalLayout->setStretch(4, 1);

        gridLayout_8->addWidget(gbx_SelectPage, 1, 0, 1, 1);

        widget = new QWidget(page1);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout_12 = new QGridLayout(widget);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        sta_DevWdeget = new QStackedWidget(widget);
        sta_DevWdeget->setObjectName(QStringLiteral("sta_DevWdeget"));
        sizePolicy.setHeightForWidth(sta_DevWdeget->sizePolicy().hasHeightForWidth());
        sta_DevWdeget->setSizePolicy(sizePolicy);
        page_hdmi = new QWidget();
        page_hdmi->setObjectName(QStringLiteral("page_hdmi"));
        gridLayout_10 = new QGridLayout(page_hdmi);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_21 = new QLabel(page_hdmi);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_6->addWidget(label_21, 2, 0, 1, 1);

        btn_Refresh = new QPushButton(page_hdmi);
        btn_Refresh->setObjectName(QStringLiteral("btn_Refresh"));
        sizePolicy3.setHeightForWidth(btn_Refresh->sizePolicy().hasHeightForWidth());
        btn_Refresh->setSizePolicy(sizePolicy3);
        btn_Refresh->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0);"));

        gridLayout_6->addWidget(btn_Refresh, 0, 0, 1, 2);

        lin_HDMIMac = new QLineEdit(page_hdmi);
        lin_HDMIMac->setObjectName(QStringLiteral("lin_HDMIMac"));
        lin_HDMIMac->setReadOnly(true);

        gridLayout_6->addWidget(lin_HDMIMac, 2, 1, 1, 1);

        tree_Dev = new QTreeWidget(page_hdmi);
        tree_Dev->setObjectName(QStringLiteral("tree_Dev"));
        sizePolicy.setHeightForWidth(tree_Dev->sizePolicy().hasHeightForWidth());
        tree_Dev->setSizePolicy(sizePolicy);
        tree_Dev->setStyleSheet(QStringLiteral(""));
        tree_Dev->setIconSize(QSize(25, 25));
        tree_Dev->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        tree_Dev->setAllColumnsShowFocus(false);
        tree_Dev->setHeaderHidden(false);
        tree_Dev->setColumnCount(1);
        tree_Dev->header()->setCascadingSectionResizes(false);
        tree_Dev->header()->setHighlightSections(false);

        gridLayout_6->addWidget(tree_Dev, 1, 0, 1, 2);

        gridLayout_6->setRowStretch(0, 1);

        gridLayout_10->addLayout(gridLayout_6, 0, 0, 2, 1);

        gro_OutFmt = new QGroupBox(page_hdmi);
        gro_OutFmt->setObjectName(QStringLiteral("gro_OutFmt"));
        sizePolicy.setHeightForWidth(gro_OutFmt->sizePolicy().hasHeightForWidth());
        gro_OutFmt->setSizePolicy(sizePolicy);
        gro_OutFmt->setLayoutDirection(Qt::LeftToRight);
        gridLayout_4 = new QGridLayout(gro_OutFmt);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gro_Mode = new QGroupBox(gro_OutFmt);
        gro_Mode->setObjectName(QStringLiteral("gro_Mode"));
        sizePolicy3.setHeightForWidth(gro_Mode->sizePolicy().hasHeightForWidth());
        gro_Mode->setSizePolicy(sizePolicy3);
        horizontalLayout_15 = new QHBoxLayout(gro_Mode);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        rad_Aut = new QRadioButton(gro_Mode);
        rad_Aut->setObjectName(QStringLiteral("rad_Aut"));

        horizontalLayout_15->addWidget(rad_Aut);

        horizontalSpacer_13 = new QSpacerItem(75, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_13);

        rad_Man = new QRadioButton(gro_Mode);
        rad_Man->setObjectName(QStringLiteral("rad_Man"));

        horizontalLayout_15->addWidget(rad_Man);

        horizontalSpacer_14 = new QSpacerItem(75, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        rad_Adv = new QRadioButton(gro_Mode);
        rad_Adv->setObjectName(QStringLiteral("rad_Adv"));

        horizontalLayout_15->addWidget(rad_Adv);


        gridLayout_4->addWidget(gro_Mode, 2, 0, 1, 1);

        che_Mute = new QCheckBox(gro_OutFmt);
        che_Mute->setObjectName(QStringLiteral("che_Mute"));

        gridLayout_4->addWidget(che_Mute, 1, 0, 1, 1);

        sta_Mode = new QStackedWidget(gro_OutFmt);
        sta_Mode->setObjectName(QStringLiteral("sta_Mode"));
        pag_Ato = new QWidget();
        pag_Ato->setObjectName(QStringLiteral("pag_Ato"));
        verticalLayout_13 = new QVBoxLayout(pag_Ato);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        lab_Aut = new QLabel(pag_Ato);
        lab_Aut->setObjectName(QStringLiteral("lab_Aut"));

        verticalLayout_13->addWidget(lab_Aut);

        sta_Mode->addWidget(pag_Ato);
        pag_Man = new QWidget();
        pag_Man->setObjectName(QStringLiteral("pag_Man"));
        gridLayout_5 = new QGridLayout(pag_Man);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        rad_Good = new QRadioButton(pag_Man);
        rad_Good->setObjectName(QStringLiteral("rad_Good"));

        gridLayout_5->addWidget(rad_Good, 3, 0, 1, 1);

        rad_Fair = new QRadioButton(pag_Man);
        rad_Fair->setObjectName(QStringLiteral("rad_Fair"));

        gridLayout_5->addWidget(rad_Fair, 4, 0, 1, 1);

        rad_Mob = new QRadioButton(pag_Man);
        rad_Mob->setObjectName(QStringLiteral("rad_Mob"));

        gridLayout_5->addWidget(rad_Mob, 6, 0, 1, 1);

        rad_Ult = new QRadioButton(pag_Man);
        rad_Ult->setObjectName(QStringLiteral("rad_Ult"));

        gridLayout_5->addWidget(rad_Ult, 1, 0, 1, 1);

        rad_Su = new QRadioButton(pag_Man);
        rad_Su->setObjectName(QStringLiteral("rad_Su"));

        gridLayout_5->addWidget(rad_Su, 0, 0, 1, 1);

        rad_Exc = new QRadioButton(pag_Man);
        rad_Exc->setObjectName(QStringLiteral("rad_Exc"));

        gridLayout_5->addWidget(rad_Exc, 2, 0, 1, 1);

        rad_Poor = new QRadioButton(pag_Man);
        rad_Poor->setObjectName(QStringLiteral("rad_Poor"));

        gridLayout_5->addWidget(rad_Poor, 5, 0, 1, 1);

        sta_Mode->addWidget(pag_Man);
        pag_Adv = new QWidget();
        pag_Adv->setObjectName(QStringLiteral("pag_Adv"));
        gridLayout = new QGridLayout(pag_Adv);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_10 = new QLabel(pag_Adv);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        lab_enico = new QLabel(pag_Adv);
        lab_enico->setObjectName(QStringLiteral("lab_enico"));
        sizePolicy.setHeightForWidth(lab_enico->sizePolicy().hasHeightForWidth());
        lab_enico->setSizePolicy(sizePolicy);
        lab_enico->setLayoutDirection(Qt::RightToLeft);
        lab_enico->setAutoFillBackground(false);

        gridLayout->addWidget(lab_enico, 2, 3, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        label_11 = new QLabel(pag_Adv);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        lin_Hig = new QLineEdit(pag_Adv);
        lin_Hig->setObjectName(QStringLiteral("lin_Hig"));
        sizePolicy3.setHeightForWidth(lin_Hig->sizePolicy().hasHeightForWidth());
        lin_Hig->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lin_Hig, 2, 4, 1, 1);

        lin_AvBitRte = new QLineEdit(pag_Adv);
        lin_AvBitRte->setObjectName(QStringLiteral("lin_AvBitRte"));
        sizePolicy3.setHeightForWidth(lin_AvBitRte->sizePolicy().hasHeightForWidth());
        lin_AvBitRte->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lin_AvBitRte, 3, 2, 1, 3);

        label_12 = new QLabel(pag_Adv);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_12, 3, 0, 1, 1);

        label_16 = new QLabel(pag_Adv);
        label_16->setObjectName(QStringLiteral("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_16, 3, 5, 1, 1);

        lin_Enco = new QLineEdit(pag_Adv);
        lin_Enco->setObjectName(QStringLiteral("lin_Enco"));
        sizePolicy3.setHeightForWidth(lin_Enco->sizePolicy().hasHeightForWidth());
        lin_Enco->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lin_Enco, 4, 2, 1, 3);

        label_15 = new QLabel(pag_Adv);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_15, 4, 5, 1, 1);

        label_13 = new QLabel(pag_Adv);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_13, 4, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 4, 1, 1, 1);

        com_Hprofile = new QComboBox(pag_Adv);
        com_Hprofile->addItem(QString());
        com_Hprofile->addItem(QString());
        com_Hprofile->setObjectName(QStringLiteral("com_Hprofile"));
        sizePolicy3.setHeightForWidth(com_Hprofile->sizePolicy().hasHeightForWidth());
        com_Hprofile->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(com_Hprofile, 0, 2, 1, 3);

        label_9 = new QLabel(pag_Adv);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        com_Hlevel = new QComboBox(pag_Adv);
        com_Hlevel->addItem(QString());
        com_Hlevel->addItem(QString());
        com_Hlevel->addItem(QString());
        com_Hlevel->addItem(QString());
        com_Hlevel->addItem(QString());
        com_Hlevel->addItem(QString());
        com_Hlevel->setObjectName(QStringLiteral("com_Hlevel"));
        sizePolicy3.setHeightForWidth(com_Hlevel->sizePolicy().hasHeightForWidth());
        com_Hlevel->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(com_Hlevel, 1, 2, 1, 3);

        lin_Wid = new QLineEdit(pag_Adv);
        lin_Wid->setObjectName(QStringLiteral("lin_Wid"));
        sizePolicy3.setHeightForWidth(lin_Wid->sizePolicy().hasHeightForWidth());
        lin_Wid->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(lin_Wid, 2, 2, 1, 1);

        sta_Mode->addWidget(pag_Adv);
        com_Hprofile->raise();
        label_10->raise();
        com_Hlevel->raise();
        label_11->raise();
        lin_Wid->raise();
        lab_enico->raise();
        lin_Hig->raise();
        label_12->raise();
        lin_AvBitRte->raise();
        label_16->raise();
        label_13->raise();
        lin_Enco->raise();
        label_15->raise();
        label_9->raise();

        gridLayout_4->addWidget(sta_Mode, 3, 0, 1, 1);


        gridLayout_10->addWidget(gro_OutFmt, 0, 1, 1, 1);

        group = new QGroupBox(page_hdmi);
        group->setObjectName(QStringLiteral("group"));
        sizePolicy.setHeightForWidth(group->sizePolicy().hasHeightForWidth());
        group->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(group);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(group);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_4, 5, 3, 1, 1);

        label_3 = new QLabel(group);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        lin_Apid = new QLineEdit(group);
        lin_Apid->setObjectName(QStringLiteral("lin_Apid"));
        sizePolicy3.setHeightForWidth(lin_Apid->sizePolicy().hasHeightForWidth());
        lin_Apid->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_Apid, 3, 4, 1, 1);

        lin_PgmNa = new QLineEdit(group);
        lin_PgmNa->setObjectName(QStringLiteral("lin_PgmNa"));
        sizePolicy3.setHeightForWidth(lin_PgmNa->sizePolicy().hasHeightForWidth());
        lin_PgmNa->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_PgmNa, 2, 1, 1, 1);

        lin_PgmNo = new QLineEdit(group);
        lin_PgmNo->setObjectName(QStringLiteral("lin_PgmNo"));
        sizePolicy3.setHeightForWidth(lin_PgmNo->sizePolicy().hasHeightForWidth());
        lin_PgmNo->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_PgmNo, 2, 4, 1, 1);

        lab_PgmNo = new QLabel(group);
        lab_PgmNo->setObjectName(QStringLiteral("lab_PgmNo"));
        sizePolicy.setHeightForWidth(lab_PgmNo->sizePolicy().hasHeightForWidth());
        lab_PgmNo->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lab_PgmNo, 2, 3, 1, 1);

        label_5 = new QLabel(group);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_5, 3, 0, 1, 1);

        label_2 = new QLabel(group);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_8 = new QLabel(group);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_8, 4, 3, 1, 1);

        lin_Pcr = new QLineEdit(group);
        lin_Pcr->setObjectName(QStringLiteral("lin_Pcr"));
        sizePolicy3.setHeightForWidth(lin_Pcr->sizePolicy().hasHeightForWidth());
        lin_Pcr->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_Pcr, 4, 1, 1, 1);

        label_6 = new QLabel(group);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_6, 3, 3, 1, 1);

        com_Aout = new QComboBox(group);
        com_Aout->addItem(QString());
        com_Aout->setObjectName(QStringLiteral("com_Aout"));
        sizePolicy3.setHeightForWidth(com_Aout->sizePolicy().hasHeightForWidth());
        com_Aout->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(com_Aout, 5, 1, 1, 1);

        lin_Pmt = new QLineEdit(group);
        lin_Pmt->setObjectName(QStringLiteral("lin_Pmt"));
        sizePolicy3.setHeightForWidth(lin_Pmt->sizePolicy().hasHeightForWidth());
        lin_Pmt->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_Pmt, 4, 4, 1, 1);

        lin_Vpid = new QLineEdit(group);
        lin_Vpid->setObjectName(QStringLiteral("lin_Vpid"));
        sizePolicy3.setHeightForWidth(lin_Vpid->sizePolicy().hasHeightForWidth());
        lin_Vpid->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(lin_Vpid, 3, 1, 1, 1);

        com_AFre = new QComboBox(group);
        com_AFre->addItem(QString());
        com_AFre->addItem(QString());
        com_AFre->addItem(QString());
        com_AFre->addItem(QString());
        com_AFre->setObjectName(QStringLiteral("com_AFre"));
        sizePolicy3.setHeightForWidth(com_AFre->sizePolicy().hasHeightForWidth());
        com_AFre->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(com_AFre, 5, 4, 1, 1);

        label_7 = new QLabel(group);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_7, 4, 0, 1, 1);

        label = new QLabel(group);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label, 5, 0, 1, 1);

        btn_Res = new QPushButton(group);
        btn_Res->setObjectName(QStringLiteral("btn_Res"));
        sizePolicy3.setHeightForWidth(btn_Res->sizePolicy().hasHeightForWidth());
        btn_Res->setSizePolicy(sizePolicy3);
        btn_Res->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0);"));

        gridLayout_3->addWidget(btn_Res, 6, 0, 1, 1);

        btn_Run = new QPushButton(group);
        btn_Run->setObjectName(QStringLiteral("btn_Run"));
        sizePolicy3.setHeightForWidth(btn_Run->sizePolicy().hasHeightForWidth());
        btn_Run->setSizePolicy(sizePolicy3);
        btn_Run->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0);"));

        gridLayout_3->addWidget(btn_Run, 6, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        lin_InFmt = new QLineEdit(group);
        lin_InFmt->setObjectName(QStringLiteral("lin_InFmt"));
        sizePolicy3.setHeightForWidth(lin_InFmt->sizePolicy().hasHeightForWidth());
        lin_InFmt->setSizePolicy(sizePolicy3);
        lin_InFmt->setReadOnly(true);

        gridLayout_3->addWidget(lin_InFmt, 1, 1, 1, 4);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);
        gridLayout_3->setColumnStretch(3, 1);
        gridLayout_3->setColumnStretch(4, 1);

        gridLayout_10->addWidget(group, 1, 1, 1, 1);

        gridLayout_10->setColumnStretch(0, 1);
        gridLayout_10->setColumnStretch(1, 3);
        sta_DevWdeget->addWidget(page_hdmi);
        page_Net = new QWidget();
        page_Net->setObjectName(QStringLiteral("page_Net"));
        sizePolicy.setHeightForWidth(page_Net->sizePolicy().hasHeightForWidth());
        page_Net->setSizePolicy(sizePolicy);
        tabNetwork = new QTabWidget(page_Net);
        tabNetwork->setObjectName(QStringLiteral("tabNetwork"));
        tabNetwork->setGeometry(QRect(10, 50, 1021, 441));
        TabStreaming = new QWidget();
        TabStreaming->setObjectName(QStringLiteral("TabStreaming"));
        gridLayout_11 = new QGridLayout(TabStreaming);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        com_PacketSize = new QComboBox(TabStreaming);
        com_PacketSize->setObjectName(QStringLiteral("com_PacketSize"));

        gridLayout_11->addWidget(com_PacketSize, 0, 1, 1, 1);

        tabW_Streaming = new QTableWidget(TabStreaming);
        tabW_Streaming->setObjectName(QStringLiteral("tabW_Streaming"));
        tabW_Streaming->setLayoutDirection(Qt::LeftToRight);

        gridLayout_11->addWidget(tabW_Streaming, 1, 0, 1, 5);

        che_Check_all = new QCheckBox(TabStreaming);
        che_Check_all->setObjectName(QStringLiteral("che_Check_all"));

        gridLayout_11->addWidget(che_Check_all, 0, 3, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_10, 0, 2, 1, 1);

        gridLayout_11->setColumnStretch(0, 9);
        gridLayout_11->setColumnStretch(1, 2);
        tabNetwork->addTab(TabStreaming, QString());
        TabIpSetting = new QWidget();
        TabIpSetting->setObjectName(QStringLiteral("TabIpSetting"));
        gridLayout_13 = new QGridLayout(TabIpSetting);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        gSetting = new QGroupBox(TabIpSetting);
        gSetting->setObjectName(QStringLiteral("gSetting"));
        gridLayout_16 = new QGridLayout(gSetting);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        groupBox = new QGroupBox(gSetting);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_15 = new QGridLayout(groupBox);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QStringLiteral("label_24"));
        sizePolicy1.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(label_24, 0, 0, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(label_17, 1, 0, 1, 1);

        lin_100M_Ip = new QLineEdit(groupBox);
        lin_100M_Ip->setObjectName(QStringLiteral("lin_100M_Ip"));
        sizePolicy3.setHeightForWidth(lin_100M_Ip->sizePolicy().hasHeightForWidth());
        lin_100M_Ip->setSizePolicy(sizePolicy3);

        gridLayout_15->addWidget(lin_100M_Ip, 0, 1, 1, 1);

        lin_100M_Mask = new QLineEdit(groupBox);
        lin_100M_Mask->setObjectName(QStringLiteral("lin_100M_Mask"));

        gridLayout_15->addWidget(lin_100M_Mask, 1, 1, 1, 1);

        lin_100M_Gateway = new QLineEdit(groupBox);
        lin_100M_Gateway->setObjectName(QStringLiteral("lin_100M_Gateway"));

        gridLayout_15->addWidget(lin_100M_Gateway, 2, 1, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));
        sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(label_22, 2, 0, 1, 1);


        gridLayout_16->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(gSetting);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_9 = new QGridLayout(groupBox_2);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));
        sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label_23, 3, 0, 1, 1);

        lin_1G_Mask = new QLineEdit(groupBox_2);
        lin_1G_Mask->setObjectName(QStringLiteral("lin_1G_Mask"));

        gridLayout_9->addWidget(lin_1G_Mask, 2, 1, 1, 1);

        lin_1G_Gateway = new QLineEdit(groupBox_2);
        lin_1G_Gateway->setObjectName(QStringLiteral("lin_1G_Gateway"));

        gridLayout_9->addWidget(lin_1G_Gateway, 3, 1, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label_20, 2, 0, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label_18, 1, 0, 1, 1);

        che_DHCP = new QCheckBox(groupBox_2);
        che_DHCP->setObjectName(QStringLiteral("che_DHCP"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(che_DHCP->sizePolicy().hasHeightForWidth());
        che_DHCP->setSizePolicy(sizePolicy4);

        gridLayout_9->addWidget(che_DHCP, 0, 0, 1, 1);

        lin_1G_Ip = new QLineEdit(groupBox_2);
        lin_1G_Ip->setObjectName(QStringLiteral("lin_1G_Ip"));

        gridLayout_9->addWidget(lin_1G_Ip, 1, 1, 1, 1);


        gridLayout_16->addWidget(groupBox_2, 1, 0, 1, 1);


        gridLayout_13->addWidget(gSetting, 1, 0, 1, 1);

        tabNetwork->addTab(TabIpSetting, QString());
        horizontalLayoutWidget = new QWidget(page_Net);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 1021, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_14 = new QLabel(horizontalLayoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy5);

        horizontalLayout_4->addWidget(label_14);

        com_Netlist = new QComboBox(horizontalLayoutWidget);
        com_Netlist->setObjectName(QStringLiteral("com_Netlist"));

        horizontalLayout_4->addWidget(com_Netlist);

        btn_Restart = new QPushButton(horizontalLayoutWidget);
        btn_Restart->setObjectName(QStringLiteral("btn_Restart"));
        btn_Restart->setEnabled(true);
        btn_Restart->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0);"));

        horizontalLayout_4->addWidget(btn_Restart);

        horizontalSpacer_5 = new QSpacerItem(75, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 6);
        horizontalLayout_4->setStretch(3, 2);
        horizontalLayout_4->setStretch(4, 1);
        btn_Download = new QPushButton(page_Net);
        btn_Download->setObjectName(QStringLiteral("btn_Download"));
        btn_Download->setGeometry(QRect(11, 501, 201, 23));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(btn_Download->sizePolicy().hasHeightForWidth());
        btn_Download->setSizePolicy(sizePolicy6);
        btn_Download->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0)"));
        btn_Upload = new QPushButton(page_Net);
        btn_Upload->setObjectName(QStringLiteral("btn_Upload"));
        btn_Upload->setGeometry(QRect(229, 501, 201, 23));
        sizePolicy6.setHeightForWidth(btn_Upload->sizePolicy().hasHeightForWidth());
        btn_Upload->setSizePolicy(sizePolicy6);
        btn_Upload->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0)"));
        btn_Set = new QPushButton(page_Net);
        btn_Set->setObjectName(QStringLiteral("btn_Set"));
        btn_Set->setGeometry(QRect(830, 501, 200, 23));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(200);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(btn_Set->sizePolicy().hasHeightForWidth());
        btn_Set->setSizePolicy(sizePolicy7);
        btn_Set->setMinimumSize(QSize(200, 0));
        btn_Set->setStyleSheet(QStringLiteral("background-color: rgb(0, 40, 0);"));
        sta_DevWdeget->addWidget(page_Net);

        gridLayout_12->addWidget(sta_DevWdeget, 0, 0, 1, 1);


        gridLayout_8->addWidget(widget, 2, 0, 1, 1);

        gridLayout_8->setRowStretch(2, 1);
        stackedWidget->addWidget(page1);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(Hdmioptiongui);

        stackedWidget->setCurrentIndex(0);
        sta_DevWdeget->setCurrentIndex(1);
        sta_Mode->setCurrentIndex(2);
        com_Hprofile->setCurrentIndex(0);
        tabNetwork->setCurrentIndex(0);
        com_PacketSize->setCurrentIndex(-1);
        com_Netlist->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Hdmioptiongui);
    } // setupUi

    void retranslateUi(QDialog *Hdmioptiongui)
    {
        Hdmioptiongui->setWindowTitle(QApplication::translate("Hdmioptiongui", "Form", nullptr));
        labIco->setText(QString());
        labTitle->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Min->setToolTip(QApplication::translate("Hdmioptiongui", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Min->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("Hdmioptiongui", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        btnMenu_Max->setText(QString());
        gbx_SelectPage->setTitle(QString());
        rad_Hdmi->setText(QApplication::translate("Hdmioptiongui", "HDMI Capture Card Setting", nullptr));
        rad_Net->setText(QApplication::translate("Hdmioptiongui", " Streaming&&Network Setting", nullptr));
        label_21->setText(QApplication::translate("Hdmioptiongui", "MAC for HDMI:", nullptr));
        btn_Refresh->setText(QApplication::translate("Hdmioptiongui", "Refresh Devices", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_Dev->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Hdmioptiongui", "Device", nullptr));
        gro_OutFmt->setTitle(QApplication::translate("Hdmioptiongui", "OutputFormat:", nullptr));
        gro_Mode->setTitle(QString());
        rad_Aut->setText(QApplication::translate("Hdmioptiongui", "Auto", nullptr));
        rad_Man->setText(QApplication::translate("Hdmioptiongui", "Manual", nullptr));
        rad_Adv->setText(QApplication::translate("Hdmioptiongui", "Advanced", nullptr));
        che_Mute->setText(QApplication::translate("Hdmioptiongui", "Mute", nullptr));
        lab_Aut->setText(QApplication::translate("Hdmioptiongui", "Output resolution, code rate and frame rate will be identical to inputs.", nullptr));
        rad_Good->setText(QApplication::translate("Hdmioptiongui", "Good(1120*640)", nullptr));
        rad_Fair->setText(QApplication::translate("Hdmioptiongui", "Fair(960*540)", nullptr));
        rad_Mob->setText(QApplication::translate("Hdmioptiongui", "Mobile(480*272)", nullptr));
        rad_Ult->setText(QApplication::translate("Hdmioptiongui", "Ultra(1440*1080)", nullptr));
        rad_Su->setText(QApplication::translate("Hdmioptiongui", "Super(1920*1080)", nullptr));
        rad_Exc->setText(QApplication::translate("Hdmioptiongui", "Excellent(1280*720)", nullptr));
        rad_Poor->setText(QApplication::translate("Hdmioptiongui", "Poor(800*480)", nullptr));
        label_10->setText(QApplication::translate("Hdmioptiongui", "H.264 Level:", nullptr));
        lab_enico->setText(QString());
        label_11->setText(QApplication::translate("Hdmioptiongui", "Resolution", nullptr));
        lin_Hig->setText(QApplication::translate("Hdmioptiongui", "720", nullptr));
        lin_AvBitRte->setText(QApplication::translate("Hdmioptiongui", "5000", nullptr));
        label_12->setText(QApplication::translate("Hdmioptiongui", "Average BitRate:", nullptr));
        label_16->setText(QApplication::translate("Hdmioptiongui", "(350-18000k)", nullptr));
        lin_Enco->setText(QApplication::translate("Hdmioptiongui", "60", nullptr));
        label_15->setText(QApplication::translate("Hdmioptiongui", "(24-60)", nullptr));
        label_13->setText(QApplication::translate("Hdmioptiongui", "Encoding FrameRate: ", nullptr));
        com_Hprofile->setItemText(0, QApplication::translate("Hdmioptiongui", "Hight Profile", nullptr));
        com_Hprofile->setItemText(1, QApplication::translate("Hdmioptiongui", "Main Profile", nullptr));

        label_9->setText(QApplication::translate("Hdmioptiongui", "H.264 Profile", nullptr));
        com_Hlevel->setItemText(0, QApplication::translate("Hdmioptiongui", "level 3", nullptr));
        com_Hlevel->setItemText(1, QApplication::translate("Hdmioptiongui", "level 3.1", nullptr));
        com_Hlevel->setItemText(2, QApplication::translate("Hdmioptiongui", "level 3.2", nullptr));
        com_Hlevel->setItemText(3, QApplication::translate("Hdmioptiongui", "level 4", nullptr));
        com_Hlevel->setItemText(4, QApplication::translate("Hdmioptiongui", "level 4.1", nullptr));
        com_Hlevel->setItemText(5, QApplication::translate("Hdmioptiongui", "level 4.2", nullptr));

        lin_Wid->setText(QApplication::translate("Hdmioptiongui", "1280", nullptr));
        label_4->setText(QApplication::translate("Hdmioptiongui", "Audio Freq:", nullptr));
        label_3->setText(QApplication::translate("Hdmioptiongui", "Programe Name: ", nullptr));
        lab_PgmNo->setText(QApplication::translate("Hdmioptiongui", "Program No.:", nullptr));
        label_5->setText(QApplication::translate("Hdmioptiongui", "V_PID:", nullptr));
        label_2->setText(QApplication::translate("Hdmioptiongui", "Input Format:", nullptr));
        label_8->setText(QApplication::translate("Hdmioptiongui", "PMT:", nullptr));
        label_6->setText(QApplication::translate("Hdmioptiongui", "A_PID:", nullptr));
        com_Aout->setItemText(0, QApplication::translate("Hdmioptiongui", "HdmiModule", nullptr));

        com_AFre->setItemText(0, QApplication::translate("Hdmioptiongui", "48k", nullptr));
        com_AFre->setItemText(1, QApplication::translate("Hdmioptiongui", "44.1k", nullptr));
        com_AFre->setItemText(2, QApplication::translate("Hdmioptiongui", "32k", nullptr));
        com_AFre->setItemText(3, QApplication::translate("Hdmioptiongui", "Auto", nullptr));

        label_7->setText(QApplication::translate("Hdmioptiongui", "PCR:", nullptr));
        label->setText(QApplication::translate("Hdmioptiongui", "Audio Input:", nullptr));
        btn_Res->setText(QApplication::translate("Hdmioptiongui", "Load Defaults", nullptr));
        btn_Run->setText(QApplication::translate("Hdmioptiongui", "Apply", nullptr));
        che_Check_all->setText(QApplication::translate("Hdmioptiongui", "Check all", nullptr));
        tabNetwork->setTabText(tabNetwork->indexOf(TabStreaming), QApplication::translate("Hdmioptiongui", "Streaming     ", nullptr));
        gSetting->setTitle(QString());
        groupBox->setTitle(QApplication::translate("Hdmioptiongui", "100M Network:", nullptr));
        label_24->setText(QApplication::translate("Hdmioptiongui", "Local IP&&Server Port:", nullptr));
        label_17->setText(QApplication::translate("Hdmioptiongui", "Local Netmask:", nullptr));
        lin_100M_Ip->setText(QString());
        label_22->setText(QApplication::translate("Hdmioptiongui", "local Gateway:", nullptr));
        groupBox_2->setTitle(QApplication::translate("Hdmioptiongui", "1000M Network:", nullptr));
        label_23->setText(QApplication::translate("Hdmioptiongui", "local Gateway:", nullptr));
        label_20->setText(QApplication::translate("Hdmioptiongui", "Local Netmask:", nullptr));
        label_18->setText(QApplication::translate("Hdmioptiongui", "Local IP&&Server Port:", nullptr));
        che_DHCP->setText(QApplication::translate("Hdmioptiongui", " Enable DHCP", nullptr));
        tabNetwork->setTabText(tabNetwork->indexOf(TabIpSetting), QApplication::translate("Hdmioptiongui", "IP Setting    ", nullptr));
        label_14->setText(QApplication::translate("Hdmioptiongui", "Network device list:", nullptr));
        btn_Restart->setText(QApplication::translate("Hdmioptiongui", "Restart", nullptr));
        btn_Download->setText(QApplication::translate("Hdmioptiongui", "Export", nullptr));
        btn_Upload->setText(QApplication::translate("Hdmioptiongui", "Import ", nullptr));
        btn_Set->setText(QApplication::translate("Hdmioptiongui", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hdmioptiongui: public Ui_Hdmioptiongui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HDMIOPTIONGUI_H
