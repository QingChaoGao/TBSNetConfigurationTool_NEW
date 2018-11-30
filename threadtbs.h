#ifndef THREADTBS_H
#define THREADTBS_H
#include <QThread>
#include "tbsfunc.h"
extern volatile bool swflg;
extern volatile u8 mode;
extern QString i_path;
extern volatile u8 workMode;
extern volatile u8 manNo;
//ui vaule
extern  u8 PNo;
extern volatile int Vpid;
extern volatile int Apid;
extern volatile int Pmt;
extern volatile int Pcr;
extern volatile int HpFile;
extern volatile int HpLevel;
extern volatile int PixW;
extern volatile int PixH;
extern volatile int BitRate;
extern volatile int Frame;
extern volatile int MuteEn;
extern u8 Pname[24];
extern u8 Local_parameter_100M[17];
extern u8 Local_parameter_1G[17];
extern u8 audio_parameter[2];
extern StreamingForm sf[16];
extern int tunerarry[16];

extern u8 packetsize;

class threadTbs:public QThread
{
    Q_OBJECT
public:
    explicit threadTbs();
    ~threadTbs();
    void writeBuffer();
    void autoMode();
    void manualMoe();
    void advancedMode();
    void setMute();
    void setPorgname();
    void setProgramNo();
    void setPid();
	int setAudioSourceAndFreq();
	/***udpMulticast*******/
	void udpMulticastClinet(void);
	/********net**************/
	int setLocal_IP_Port_MAC();
	int setStreamingArg();
	int showUI_start();
	int showUI_end();
	void restart_device();
signals:
    void sendMsg(Msg* g);
	void sendIp(QString qs);
protected:
    void run();
private:
    tbsfunc et;
    Msg *m;
};

#endif // THREADTBS_H
