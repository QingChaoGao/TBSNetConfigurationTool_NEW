#ifndef HDMIOPTIONGUI_H
#define HDMIOPTIONGUI_H
#include <QDialog>
#include "tbsfunc.h"
#include "threadtbs.h"
#include "appinit.h"
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include "mymesg.h"

namespace Ui {
class Hdmioptiongui;
}

class Hdmioptiongui : public QDialog
{
    Q_OBJECT

public:
    explicit Hdmioptiongui(QWidget *parent = 0);
    ~Hdmioptiongui();
	void initForm();
	int  getNetTuners(void);
	void init_sql(QString path);
	void updateStream_sql(StreamingForm *stream);
	void readStream_sql(StreamingForm *stream);
	QString getHostIpAddress(void);
	u8 getNetworkSegment(QString ip);

	int readBuffer(void);
    //encoded
	int Iputfmt();
    int getSn();
    int outputfmt();
    int getMute();
    int getName();
    int getNo();
    int getPid();
	int getAudioSourceAndFreq();
	//net 
	int getLocal_IP_Port_MAC();
	int getStreamingArg();
	//get child device
	int getswitchstatus(NetInfor * nf);
	int initStreamingForm();

	int Refresh();
	int readNetwork(int idx);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::Hdmioptiongui *ui;
    tbsfunc tbs;
    threadTbs *th;
    u8 emflg;
    int width;
    int height;
    int width_s;
    int height_s;
    int fontsize;
	int netnum;
	QMessageBox *qbox;
	NetInfor **netf;
	QComboBox *comBoxProtocol[16];
	QComboBox *comBoxNullPacked[16];
	QCheckBox *cheBoxTS[16];
	QHBoxLayout *hLayoutTS[16];
	QWidget *widgetTS[16];
	QLabel *labelStauts[16];
	QTableWidget *tabWS;
	QSqlDatabase database;
	QSqlQuery *sql_query;
    Mymesg *myDialog;

private slots:
    void radioClick();
    void radioClick_M(); 
	void radioClick_HN();
    void showSelectedImage(QTreeWidgetItem * item, int column); //点击树节点事件
    void show_status(Msg* g);
	void showNetTuners(QString qs);
    void on_btn_Run_clicked();
	void on_btn_Set_clicked();
    void on_sli_H_valueChanged(int value);
    void on_btn_Res_clicked();
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
	void on_tabNetwork_currentChanged(int idx);
	void on_com_Aout_currentIndexChanged(int idx);
	void on_com_Netlist_currentIndexChanged(int idx);
	void on_che_Check_all_stateChanged(int idx);
	void on_btn_Download_clicked();
	void on_btn_Upload_clicked();
	void on_btn_Refresh_clicked();
	void on_btn_Restart_clicked();
};
#endif
