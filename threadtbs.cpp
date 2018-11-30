#include "threadtbs.h"
volatile bool swflg = 0;
volatile u8 mode = 0;
QString i_path;
volatile u8 workMode = 0;
volatile u8 manNo = 0;
u8 PNo = 0;
volatile int Vpid = 0;
volatile int Apid = 0;
volatile int Pmt = 0;
volatile int Pcr = 0;
volatile int HpFile = 0;
volatile int HpLevel = 0;
volatile int PixW = 0;
volatile int PixH = 0;
volatile int BitRate = 0;
volatile int Frame = 0;
volatile int MuteEn = 0;
u8 Pname[24] = { '0' };
u8 Local_parameter_100M[17] = { 0 };
u8 Local_parameter_1G[17] = { 0 };
u8 audio_parameter[2] = { 0 };
StreamingForm sf[16];
int tunerarry[16] = { 0 };

u8 packetsize = 7;

threadTbs::threadTbs() :QThread()
{
	swflg = 0;
	m = new Msg();
	m->ok = 0;
	m->type = 0;
	m->progress = 0;
}

threadTbs::~threadTbs()
{

}

void threadTbs::writeBuffer()
{
	m->ok = 1;
	m->type = 1;
	m->progress = 0;
	emit sendMsg(m);
	switch (workMode) {
	case 1:
		//1.AutoMode
		autoMode();
		break;
	case 2:
		//2.ManualMode
		manualMoe();
		break;
	case 3:
		//3.AdvancedMode
		advancedMode();
		break;
	default:
		break;
	}
	//4.setMute
	setMute();
	//5.setProgrameName
	setPorgname();
	//6.setProgrameNo
	setProgramNo();
	//7.setProgramePid
	setPid();
	//8.setAudioSourceAndFreq
	setAudioSourceAndFreq();

	et.reHdmi();
	m->ok = 1;
	m->type = 2;
	m->progress = 0;
	emit sendMsg(m);
	QMSLEEP(2);
	m->ok = 1;
	m->type = 4;
	m->progress = 0;
	emit sendMsg(m);
	return;
}

void threadTbs::autoMode()
{
	u8 tepdate[4] = { 0 };
	//set to 24cxx 0x14 to 1
	tepdate[0] = 1;
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x14, tepdate, 1);
	tepdate[0] = 0;
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x15, tepdate, 1);
}

void threadTbs::manualMoe()
{
	u8 tepdate[4] = { 0 };
	//set to 24cxx 0x14 to 0 and 0x15 to num
	tepdate[0] = 0;
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x14, tepdate, 1);
	tepdate[0] = manNo;
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x15, tepdate, 1);
	//qDebug("set output format to manual mode:");
	//SetCaptureFormat(0,num);
}

void threadTbs::advancedMode()
{
	u8 tepdate[4] = { 0 };
	//set to 24cxx 0x14 to 0 and 0x15 to 0
	tepdate[0] = 0;
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x14, tepdate, 1);
	et.target_ext_memory_rd_wt(WRITE, (tuner % 4) * 0x80 + 0x15, tepdate, 1);
	//qDebug("set output format to advanced: %d,%d,%d,%d,%d,%d",ad.profileNum,ad.levelNum,ad.H_Num,ad.V_Num,ad.bitrateNum,ad.frameNum);

	int outsettingAddress[11];
	int outsettingFormat[11];

	outsettingAddress[0] = 0x1526; // profileLevel
	outsettingAddress[1] = 0x152c; // H
	outsettingAddress[2] = 0x152e; // V
	outsettingAddress[3] = 0x1532; // biteRate
	outsettingAddress[4] = 0x1534;
	outsettingAddress[5] = 0x1536;
	outsettingAddress[6] = 0x1538;
	outsettingAddress[7] = 0x1104;
	outsettingAddress[8] = 0x1584; // framRate
	outsettingAddress[9] = 0x1586;
	outsettingAddress[10] = 0x1588;

	if (HpFile == 1)
		HpLevel += 512; // Main profile
	else
		HpLevel += 256; // high profile

	//write data
	outsettingFormat[0] = HpLevel;
	outsettingFormat[1] = PixW;
	outsettingFormat[2] = PixH;

	outsettingFormat[3] = BitRate * 2.5;
	outsettingFormat[4] = BitRate * 2;
	outsettingFormat[5] = BitRate;
	outsettingFormat[6] = BitRate * 0.5;
	outsettingFormat[7] = BitRate * 3.5;

	outsettingFormat[8] = 0;
	outsettingFormat[9] = Frame * 2;
	outsettingFormat[10] = 1;

	unsigned char iwrNum[4] = { 0 };
	iwrNum[1] = 11;
	et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x10, iwrNum, 2);
	et.write_M23Register(11, outsettingAddress, outsettingFormat);
}

void threadTbs::setMute()
{
	unsigned char temdate[4] = { 0 };
	temdate[0] = MuteEn;
	et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x16, temdate, 1);
}

void threadTbs::setPorgname()
{

	unsigned char temdate[4] = { 0 };
	int len = 0;
	int i = 0;
	u8 *tempName = Pname;
	while (*tempName++)len++;
	for (int i = 0; i < len; i++) {
		qDebug() << "Pname:" << (char)Pname[i];
	}
	qDebug("len:%d", len);
	temdate[0] = 0x60;
	et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x12, temdate, 1);
	temdate[0] = len; //progname len
	et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x13, temdate, 1);
	et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x60, tempName, len);
	for (i = 0; i < len + 1; i++)
	{
		if (i == len) {
			temdate[0] = '\0';
		}
		else {
			temdate[0] = *(Pname + i); //progname len
		}
		qDebug() << "char:" << (char)temdate[0];
		et.target_ext_memory_rd_wt(WRITE, 0x80 * (tuner % 4) + 0x60 + i, temdate, 1);
	}

}

void threadTbs::setProgramNo()
{
	et.target_ext_memory_rd_wt(WRITE, PROGRAM_START_NO((tuner % 4)), &PNo, 1);
}

void threadTbs::setPid()
{
	u8 tmpbuf[8] = { 0 };
	tmpbuf[0] = Pmt >> 8 & 0xff;
	tmpbuf[1] = Pmt & 0xff;
	tmpbuf[2] = Pcr >> 8 & 0xff;
	tmpbuf[3] = Pcr & 0xff;
	tmpbuf[4] = Vpid >> 8 & 0xff;
	tmpbuf[5] = Vpid & 0xff;
	tmpbuf[6] = Apid >> 8 & 0xff;
	tmpbuf[7] = Apid & 0xff;
	et.target_ext_memory_rd_wt(WRITE, PID((tuner % 4)), tmpbuf, 8);
}

int threadTbs::setAudioSourceAndFreq()
{
	//u8 tmpbuf[8];
	//eg: 0x17 = 1; 0x18 = 1;
	//tmpbuf[0] = 0; //0->hdmi 1->audio
	//tmpbuf[1] = 0; //00->48k,01->44.1k,10->32k
	qDebug() << "audio_parameter:" << audio_parameter[0];
	et.target_ext_memory_rd_wt(WRITE, GPIOBASE_ADDR + AUDIIO_FREQ_SELECT_OFFSETADDR + 0x80 * (tuner % 4), audio_parameter, 1);

	return 0;
}

int threadTbs::setLocal_IP_Port_MAC()
{
	u8 ret = 0;
	//int offset = 0;
	u32 t = typeId;
	m->ok = 1;
	m->type = 8;
	m->progress = 0;
	emit sendMsg(m);
	for (int i = 0; i < 16; i++) {
		qDebug("Local_parameter_100M[%d] = %d", i, Local_parameter_100M[i]);
	}
	for (int i = 0; i < 16; i++) {
		qDebug("Local_parameter_1G[%d] = %d", i, Local_parameter_1G[i]);
	}
	typeId = 6316;
	//et.udp_REG64_rd(0x4000 + 24, 1, &ret);
	et.target_ext_memory_rd_wt(WRITE, 0x00 + 0x80, &Local_parameter_100M[0], 8);
	et.target_ext_memory_rd_wt(WRITE, 0x180, &Local_parameter_100M[8], 8);
	memset(Local_parameter_100M, 0, 16);

	et.target_ext_memory_rd_wt(WRITE, 0x00 + 0x00, &Local_parameter_1G[0], 8);
	//et.REG64_wt(0x100, 8, &Local_parameter_1G[8]);
	et.target_ext_memory_rd_wt(WRITE, 0x100, &Local_parameter_1G[8], 8);

	memset(Local_parameter_1G, 0, 16);
	typeId = t;

	et.HardRST();
	local_ip_port_mac_flg = 2;
	QMSLEEP(24980);

	m->ok = 1;
	m->type = 9;
	m->progress = 0;
	emit sendMsg(m);
	QMSLEEP(2);
	m->ok = 1;
	m->type = 5;
	m->progress = 0;
	emit sendMsg(m);
	return 0;
}

int threadTbs::setStreamingArg()
{
	u8 streamingbuf[16];
	u32 t = 0;
	m->ok = 1;
	m->type = 1;
	m->progress = 0;
	emit sendMsg(m);
	typeId = 6316;

	u32 NullPackedAddr = 0x50;
   		
	qDebug("set packetsize = %d", packetsize);

	for (int i = 0; i < 16; i++) {
		if (-1 != tunerarry[i]) {
			streamingbuf[0] = sf[i].switchTS;
			streamingbuf[1] = sf[i].protocol;
			streamingbuf[2] = sf[i].ip.section('.', 0, 0).trimmed().toInt();
			streamingbuf[3] = sf[i].ip.section('.', 1, 1).trimmed().toInt();
			streamingbuf[4] = sf[i].ip.section('.', 2, 2).trimmed().toInt();
			streamingbuf[5] = sf[i].ip.section('.', 3, 3).trimmed().toInt();
			streamingbuf[12] = (sf[i].port >> 8) & 0x0ff;
			streamingbuf[13] = sf[i].port & 0x0ff;
			et.target_ext_memory_rd_wt(WRITE, NET_BASE_ADDR_CHILD(i / 4)\
				+ OFFICE_CHILD_HDMI(i % 4), streamingbuf, 6);
			et.target_ext_memory_rd_wt(WRITE, NET_BASE_ADDR_CHILD(i / 4)\
				+ OFFICE_CHILD_HDMI(i % 4) + 0x0c, &streamingbuf[12], 2);

			if (0 <= i && i <= 3)
				NullPackedAddr = 0x50 + (i % 4);
			else if (4 <= i && i <= 7)
				NullPackedAddr = 0xD0 + (i % 4);
			else if (8 <= i && i <= 11)
				NullPackedAddr = 0x150 + (i % 4);
			else if (12 <= i && i <= 15)
				NullPackedAddr = 0x1D0 + (i % 4);

			streamingbuf[14] = sf[i].nullpacked;
			qDebug("set NullPackedAddr = %04x sf[%d].nullpacked= %d", NullPackedAddr, i, sf[i].nullpacked);
			et.target_ext_memory_rd_wt(WRITE, NullPackedAddr, &streamingbuf[14], 1);

			et.target_ext_memory_rd_wt(WRITE, 0x55, &packetsize, 1);

			et.target_ext_memory_rd_wt(WRITE, 0xff08, (u8*)&i, 1);/*ÉèÖÃÉúÐ§*/
			///qDebug() << "tar ip3:" << sf[i].ip;
		}
	}
	typeId = t;
	m->ok = 1;
	m->type = 2;
	m->progress = 0;
	emit sendMsg(m);
	QMSLEEP(2);

	m->ok = 1;
	m->type = 6;
	m->progress = 0;
	emit sendMsg(m);
	return 0;

}

int threadTbs::showUI_start()
{
	m->ok = 1;
	m->type = 1;
	m->progress = 0;
	emit sendMsg(m);
	return 0;
}

int threadTbs::showUI_end()
{
	m->ok = 1;
	m->type = 2;
	m->progress = 0;
	emit sendMsg(m);
	return 0;
}
void threadTbs::restart_device()
{
	int n = 0;
	int i = 0;
	int j = 0;
	int ufd = -1;
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };

	sendbuff[0] = 0x00;//read
	sendbuff[1] = 0x00;
	sendbuff[2] = 0x40;
	sendbuff[3] = 0xff;
	sendbuff[4] = 0x54;
	sendbuff[5] = 0x42;
	sendbuff[6] = 0x53;
	sendbuff[7] = 0x5f;
	sendbuff[8] = 0x52;
	sendbuff[9] = 0x53;
	sendbuff[10] = 0x54;
	sendbuff[11] = 0x4e;


	n = sendto(udpfd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
		qDebug("udp_REG64_wt:sendto time out\n!");
		return;
	}

	memset(recvbuff, 0, 64);
	n = recvfrom(udpfd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
		qDebug("udp_REG64_wt:recvfrom time out\n!");
		return;
	}
	for (i = 0; i < 12; i++) {
		qDebug("recvbuff[%d] = %02x", i, (u8)recvbuff[i]);
	}
	if ((recvbuff[0] & 0xff) == 0x00 && (recvbuff[1] & 0xff) == 0x88 &&
		(recvbuff[2] & 0xff) == 0x40 && (recvbuff[3] & 0xff) == 0xff &&
		(recvbuff[4] & 0xff) == 0x54 && (recvbuff[5] & 0xff) == 0x42 &&
		(recvbuff[6] & 0xff) == 0x53 && (recvbuff[7] & 0xff) == 0x5f &&
		(recvbuff[8] & 0xff) == 0x52 && (recvbuff[9] & 0xff) == 0x53 &&
		(recvbuff[10] & 0xff) == 0x54 && (recvbuff[11] & 0xff) == 0x4e) {
		m->ok = 1;
		m->type = 10;
		m->progress = 0;
		emit sendMsg(m);

		QMSLEEP(24980);

		m->ok = 1;
		m->type = 9;
		m->progress = 0;
		emit sendMsg(m);
		QMSLEEP(2);
		m->ok = 1;
		m->type = 5;
		m->progress = 0;
		emit sendMsg(m);
	}
	else {
		m->ok = 1;
		m->type = 11;
		m->progress = 0;
		emit sendMsg(m);
		qDebug("Restart the failure\n");
	}
	return;
}

void threadTbs::udpMulticastClinet()
{
	int timevalue = 1000;
	if (0 == reflashflg) {
		timevalue = 1000;
	}
	else {
		timevalue = 1000;
	}
	reflashflg++;

#ifdef Q_OS_WIN //windows
	SOCKET  Mfd;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	int timeout = timevalue;

#else           //linux
	int Mfd;
	struct timeval timeout = { 1,0 };
#endif
	struct sockaddr_in addr;
	char recvtmp[128] = { '\0' };
	char sendbuf[64] = { '\0' };
	char recvbuf[64] = { '\0' };
	u8 tmp[2] = { 0 };
	if ((Mfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		qDebug() << "fail to socket";
		return;
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("239.255.0.9");
	addr.sin_port = htons(21571);//0x5443
	len = sizeof(addr);
	setsockopt(Mfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(Mfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	sendbuf[0] = 0xc0;//read
	sendbuf[1] = 0xff;
	sendbuf[2] = 0xff;
	sendbuf[3] = 0xff;
	sendbuf[4] = 0x54;
	sendbuf[5] = 0x42;
	sendbuf[6] = 0x53;
	sendbuf[7] = 0x50;
	sendbuf[8] = 0x52;
	sendbuf[9] = 0x4f;
	sendbuf[10] = 0x44;
	sendbuf[11] = 0x54;
	//c0ffffff54425350524f4454
	if (sendto(Mfd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *) &addr, len) < 0)
	{
		qDebug() << " fail to sendto";
		return;
	}
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < 16) {
		int n = recvfrom(Mfd, recvbuf, 64, 0, (struct sockaddr *)&addr, &len);
		if (n < 0) {
			qDebug() << "scan ip dev over";
			if (i > 0) {
				m->ok = 1;
				m->type = 7;
				m->progress = 0;
				emit sendMsg(m);
			}
			else {
				comchangeflg = 0;
			}
			break;
		}
		else {
			if ((((u8)(0x80) != (u8)recvbuf[4]) &&
				((u8)(0x63) != (u8)recvbuf[4])) ||
				(((u8)(0x30) != (u8)recvbuf[5]) &&
				((u8)(0x16) != (u8)recvbuf[5])) ||
					(((u8)(0x00) != (u8)(recvbuf[12])) ||
				((u8)(0x22) != (u8)(recvbuf[13])) ||
						((u8)(0xab) != (u8)(recvbuf[14])))) {
				continue;
			}
			if (netseg != (u8)recvbuf[8]) {
				continue;
			}
			tmp[0] = (u8)recvbuf[11];
			tmp[1] = (u8)recvbuf[10];
			sprintf(recvtmp, "TBS%02x%02x:%d.%d.%d.%d:%d"
				"/%02x:%02x:%02x:%02x:%02x:%02x",
				(u8)0x80, (u8)0x30, (u8)recvbuf[6], \
				(u8)recvbuf[7], (u8)recvbuf[8],
				(u8)recvbuf[9], *(u16*)&tmp[0],
				(u8)recvbuf[12], (u8)recvbuf[13],
				(u8)recvbuf[14], (u8)recvbuf[15],
				(u8)recvbuf[16], (u8)recvbuf[17]);
			emit sendIp(QString(recvtmp));
			i++;
			QMSLEEP(1);
		}
		memset(recvbuf, 0, sizeof(recvbuf));
	}
#ifdef Q_OS_WIN //windows
	closesocket(Mfd);
	WSACleanup();
#else           //linux
	::close(Mfd);
#endif
	return;
}


void threadTbs::run()
{
	while (1 != swflg) {
		if (mode == 0) {
			QMSLEEP(1);
			continue;
		}
		switch (mode) {
		case 4:
			setLocal_IP_Port_MAC();
			break;
		case 5:
			setStreamingArg();
			break;
		case 6:
			writeBuffer();
			break;
		case 7:
			udpMulticastClinet();
			break;
		case 8:
			showUI_start();
			break;
		case 9:
			showUI_end();
			break;
		case 10:
			restart_device();
			break;
		}
		mode = 0;
	}
	delete m;
	this->quit();
	this->wait();
}
