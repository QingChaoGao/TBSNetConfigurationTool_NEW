#pragma execution_character_set("utf-8")

#include "hdmioptiongui.h"
#include "ui_hdmioptiongui.h"
#include "iconhelper.h"
#define  ITMEL(n)   ITMEL##n
#define SetInputFmt(n)          ui->lin_InFmt->setText(n)
#define GetProgrameName         ui->lin_PgmNa->text()
#define SetProgrameName(n)      ui->lin_PgmNa->setText(n)
#define GetProgrameNo           ui->lin_PgmNo->text().toInt()
#define SetProgrameNo(n)        ui->lin_PgmNo->setText(n)
#define GetVpid                 ui->lin_Vpid->text().toInt()
#define SetVpid(n)              ui->lin_Vpid->setText(n)
#define GetApid                 ui->lin_Apid->text().toInt()
#define setApid(n)              ui->lin_Apid->setText(n)
#define GetPcr                  ui->lin_Pcr->text().toInt()
#define SetPcr(n)               ui->lin_Pcr->setText(n)
#define GetPmt                  ui->lin_Pmt->text().toInt()
#define SetPmt(n)               ui->lin_Pmt->setText(n)
#define Get_100M_Ip             ui->lin_100M_Ip->text()
#define Set_100M_Ip(n)          ui->lin_100M_Ip->setText(n)
#define Get_100M_NetSn          ui->lin_100M_NetMac->text()
#define Set_100M_NetSn(n)       ui->lin_100M_NetMac->setText(n)

#define Get_1G_Ip               ui->lin_1G_Ip->text()
#define Set_1G_Ip(n)            ui->lin_1G_Ip->setText(n)
#define Get_1G_NetSn            ui->lin_1G_NetMac->text()
#define Set_1G_NetSn(n)         ui->lin_1G_NetMac->setText(n)

#define GetHprofile             ui->com_Hprofile->currentIndex()
#define SetHprofile(n)          ui->com_Hprofile->setCurrentIndex(n)
#define GetHlevel               ui->com_Hlevel->currentIndex()
#define SetHlevel(n)            ui->com_Hlevel->setCurrentIndex(n)
#define GetW                    ui->lin_Wid->text().toInt()
#define SetW(n)                 ui->lin_Wid->setText(n)
#define GetH                    ui->lin_Hig->text().toInt()
#define SetH(n)                 ui->lin_Hig->setText(n)
#define GetAvBR                 ui->lin_AvBitRte->text().toInt()
#define SetAvBR(n)              ui->lin_AvBitRte->setText(n)
#define GetFrame                ui->lin_Enco->text().toInt()
#define SetFrame(n)             ui->lin_Enco->setText(n)
#define SetMute(n)              ui->che_Mute->setCheckState(((n) ? (Qt::Checked) : (Qt::Unchecked)))  //设置
#define SetHDCP(n)              ui->che_DHCP->setCheckState(((n) ? (Qt::Checked) : (Qt::Unchecked)))  //设置
#define GetMute                 ui->che_Mute->isChecked() // == Qt::Checked

/*5301*/
#define GetRtpOrUdp             ui->com_SelectRtpUdp->currentIndex()
#define SetRtpOrUdp(n)          ui->com_SelectRtpUdp->setCurrentIndex(n)
#define GetOpenCloseTs          ui->com_OpenCloseTs->currentIndex()
#define SetOpenCloseTs(n)       ui->com_OpenCloseTs->setCurrentIndex(n)
#define GetTarIp                ui->lin_TarIp->text()
#define SetTarIp(n)             ui->lin_TarIp->setText(n)
#define GetTarPort              ui->lin_TarPort->text()
#define SetTarPort(n)           ui->lin_TarPort->setText(n)
#define SetAout(n)				ui->com_Aout->setCurrentIndex(n)
#define GetAout		     	    ui->com_Aout->currentIndex()
#define SetAFre(n)				ui->com_AFre->setCurrentIndex(n)
#define GetAFre	     		    ui->com_AFre->currentIndex()

#define GetPacketSize     		ui->com_PacketSize->currentIndex()

Hdmioptiongui::Hdmioptiongui(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Hdmioptiongui)
{
	ui->setupUi(this);
	initForm();
	getNetTuners();

}

Hdmioptiongui::~Hdmioptiongui()
{
	swflg = 1;
	u8 a = 0;
	if (udpfd > 2) {
		if (2 != local_ip_port_mac_flg) {
			a = 0;
			tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
			if (1 == maincpu) {
				maincpu = 0;
				u32 t = typeId;
				typeId = 6316;
				tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
				typeId = t;

			}
			tbs.udpClose(udpfd);
		}
	}
	for (int i = 0; i < netnum; i++) {
		for (int j = 0; j < 16; j++) {
			if (-1 != netf[i]->Item_tuner[j]) {
				delete netf[i]->Item[j];
				netf[i]->Item[j] = NULL;
			}
		}
	}
	for (int i = 0; i < netnum; i++) {
		if (netf[i]->PItem != NULL) {
			delete netf[i]->PItem;
		}
		netf[i]->PItem = NULL;
		delete netf[i];
		netf[i] = NULL;
	}
	delete[]netf;
	delete ui;

}


int Hdmioptiongui::getswitchstatus(NetInfor *nf)
{
	u8 status = 0x0f;
	int i = 0;
	int j = 0;
	udpfd = tbs.udpOpen(nf->ipaddr, nf->ipport);

	//for (i = 0; i < 4; i++) {
		//tuner = i * 4;
	typeId = 6316;
	tbs.udp_REG64_rd(0x4000 + 20, 1, &status);
	qDebug("status:%#x", status);
	for (i = 0; i < 4; i++) {
		if (0 == ((status >> i) & 0x01)) {
			for (j = 0; j < 4; j++) {
				nf->Item_tuner[i * 4 + j] = i * 4 + j;
			}
		}
		else {
			for (j = 0; j < 4; j++) {
				nf->Item_tuner[i * 4 + j] = -1;
			}
		}
	}

	//qDebug("status:%#x %#x %#x %#x", tmpid[0], tmpid[1], tmpid[2], tmpid[3]);
	/**
	if (0x0863 == *(u16*)tmpid) {
		for (j = 0; j < 4; j++) {
			nf->Item_tuner[i * 4 + j] = i * 4 + j;
		}
	}
	else {
		for (j = 0; j < 4; j++) {
			nf->Item_tuner[i * 4 + j] = -1;
		}
	}
	*/
	//}
	tbs.udpClose(udpfd);
	udpfd = 0;
	tuner = 0;
	typeId = 0;
	return 0;
}

int Hdmioptiongui::initStreamingForm()
{
	/**
	for (int j = 0; j < 16; j++) {
		if (-1 != netf[col_n]->Item_tuner[j]) {
			sf[j].ip = QString("192.168.8.%1").arg(100 + j);
			sf[j].port = 5400 + j;
			sf[j].protocol = 1;
			sf[j].switchTS = 1;
		}
	}
	*/
	//release
	uncheckflg = 0;
	for (int i = 0; i < 16; i++) {
		if (NULL != comBoxProtocol[i]) {
			delete comBoxProtocol[i];
			comBoxProtocol[i] = NULL;
		}
		if (NULL != cheBoxTS[i]) {
			delete cheBoxTS[i];
			cheBoxTS[i] = NULL;
		}

		if (NULL != hLayoutTS[i]) {
			delete hLayoutTS[i];
			hLayoutTS[i] = NULL;
		}
		if (NULL != widgetTS[i]) {
			delete widgetTS[i];
			widgetTS[i] = NULL;
		}
		if (NULL != labelStauts[i]) {
			delete labelStauts[i];
			labelStauts[i] = NULL;
		}
	}
	tabWS->clear();
	tabWS->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tabWS->setWindowTitle("Streaming");
	tabWS->setRowCount(netf[col_n]->validCaptureNum);
	tabWS->setColumnCount(6);
	//QTableWidgetItem *item = new QTableWidgetItem();
	//item->setCheckState(Qt::Checked);
	//item->setText(QString("Enable/Disenable"));
	//tabWS->setHorizontalHeaderItem(3, item);
	QStringList row_header;
	row_header << "Unicast/Multicast IP" << "Port" << "Null Packed" << "Net Protocol" << "Enable/Disable" << "Streaming Status";   //表头
	tabWS->setHorizontalHeaderLabels(row_header);

	QStringList column_header;
	int j = 0;
	for (int i = 0; i < 16; i++) {
		if (-1 != netf[col_n]->Item_tuner[i]) {
			column_header.append(QObject::tr("Capture %1").arg(i));
			//ip
			tabWS->setItem(j, 0, new QTableWidgetItem(sf[i].ip));
			//tabWS->item(j, 0)->setTextAlignment(Qt::AlignCenter);
			//port
			tabWS->setItem(j, 1, new QTableWidgetItem(QString("%1").arg(sf[i].port)));
			//tabWS->item(j, 1)->setTextAlignment(Qt::AlignCenter);

			comBoxNullPacked[i] = new QComboBox();
			comBoxNullPacked[i]->addItem(QObject::tr("No"));
			comBoxNullPacked[i]->addItem(QObject::tr("Always"));
			comBoxNullPacked[i]->setCurrentIndex(sf[i].nullpacked);
			comBoxNullPacked[i]->setEnabled(true);
			tabWS->setCellWidget(j, 2, comBoxNullPacked[i]);//////////////////////////////////

			//Net Protocol
			comBoxProtocol[i] = new QComboBox();
			comBoxProtocol[i]->addItem(QObject::tr("UDP"));
			comBoxProtocol[i]->addItem(QObject::tr("RTP"));
			comBoxProtocol[i]->setCurrentIndex(sf[i].protocol);
			comBoxProtocol[i]->setEnabled(true);
			tabWS->setCellWidget(j, 3, comBoxProtocol[i]);
			//check
			cheBoxTS[i] = new QCheckBox();
			cheBoxTS[i]->setCheckState((sf[i].switchTS) ? (Qt::Checked) : (Qt::Unchecked));
			cheBoxTS[i]->setEnabled(true);
			cheBoxTS[i]->setText(QString(""));
			//tabWS->setCellWidget(j, 3, cheBoxTS[j]);
			hLayoutTS[i] = new QHBoxLayout();
			widgetTS[i] = new QWidget(tabWS);
			hLayoutTS[i]->addWidget(cheBoxTS[i]);
			hLayoutTS[i]->setMargin(0);                          // 必须添加, 否则CheckBox不能正常显示
			hLayoutTS[i]->setAlignment(cheBoxTS[i], Qt::AlignCenter);
			widgetTS[i]->setLayout(hLayoutTS[i]);
			tabWS->setCellWidget(j, 4, widgetTS[i]);
			if (0 == sf[i].switchTS) {
				uncheckflg = 1;
			}

			QString picpath = QString("");
			if (0 == sf[i].streamStatus) {
				picpath = QString(":/image/gled.png");
			}
			else if (1 == sf[i].streamStatus) {
				picpath = QString(":/image/rled.png");
			}
			labelStauts[i] = new QLabel();
			labelStauts[i]->setPixmap(QPixmap(picpath).scaled(QSize(25, 25), Qt::KeepAspectRatio));
			labelStauts[i]->setAlignment(Qt::AlignHCenter);
			tabWS->setCellWidget(j, 5, labelStauts[i]);
			j++;
		}
	}
	if (1 == uncheckflg) {
		ui->che_Check_all->setCheckState(Qt::Unchecked);
	}
	else if (0 == uncheckflg) {
		ui->che_Check_all->setCheckState(Qt::Checked);
	}
	tabWS->setVerticalHeaderLabels(column_header);
	tabWS->show();
	uncheckflg = 2;
	return 0;
}

int Hdmioptiongui::Refresh()
{
	// release net dev
	u8 a = 0;
	if (udpfd > 2) {
		if (2 != local_ip_port_mac_flg) {
			a = 0;
			tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
			if (1 == maincpu) {
				maincpu = 0;
				typeId = 6316;
				tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
				typeId = 0;
			}
			udpfd = tbs.udpClose(udpfd);
		}
	}
	if (1 == hstflg) {
		maincpu = 0;
		typeId = 0;
		hstflg = 0;
	}

	for (int i = 0; i < netnum; i++) {
		for (int j = 0; j < 16; j++) {
			if (-1 != netf[i]->Item_tuner[j]) {
				delete netf[i]->Item[j];
				netf[i]->Item[j] = NULL;
			}
			netf[i]->Item_tuner[j] = 0;
		}
	}
	for (int i = 0; i < netnum; i++) {
		if (netf[i]->PItem != NULL) {
			delete netf[i]->PItem;

		}
		netf[i]->PItem = NULL;
		delete netf[i];
		netf[i] = NULL;
	}
	delete[]netf;
	netf = NULL;
	typeId = 0;
	col_n = 0;
	comchangeflg = 0;
	ui->com_Netlist->clear();
	/**
	ui->lin_100M_Ip->setText(QString(""));
	ui->lin_100M_Mask->setText(QString(""));
	ui->lin_100M_Gateway->setText(QString(""));

	ui->lin_1G_Ip->setText(QString(""));
	ui->lin_1G_Mask->setText(QString(""));
	ui->lin_1G_Gateway->setText(QString(""));
	ui->che_DHCP->setCheckState(Qt::Unchecked);
	*/
	selecttunerflg = 0;
	getNetTuners();
	return 0;
}

int Hdmioptiongui::readNetwork(int idx)
{
	u8 a = 0;
	if (1 == maincpu) {
		maincpu = 0;
		u32 t = typeId;
		typeId = 6316;
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
		typeId = t;
	}
	if (63081 == typeId) {
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
	}
	udpfd = tbs.udpClose(udpfd);
	col_n = idx;
	tbs.useless(netf[col_n]->ipaddr, netf[col_n]->ipport);
	udpfd = tbs.udpOpen(netf[col_n]->ipaddr, netf[col_n]->ipport);
	if (udpfd < 3) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return -1;
		}
		return -1;
	}
	//test
	//QMessageBox *qbox_1 = new  QMessageBox();
	//qbox_1->setWindowTitle(tr("information"));
	//qbox_1->setText(QString("Device is configuring,please wait.."));
	//qbox_1->setStandardButtons(0);
	//qbox_1->setFont(QFont("Microsoft Yahei", fontsize + 9));
	//qbox_1->setProperty("Form", true);
	//qbox_1->exec();

	typeId = 6316;
	a = 1;
	tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	maincpu = 1;
	//	typeId = 63081;
	//tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	for (int i = 0; i < 16; i++) {
		tunerarry[i] = netf[col_n]->Item_tuner[i];
	}
	//if (1 == isIPSettingFlg) {
	getLocal_IP_Port_MAC();
	//}
	//else if (0 == isIPSettingFlg) {
	getStreamingArg();
	initStreamingForm();
	//}
	//qbox_1->close();
	//delete qbox_1;
	return 0;
}


int Hdmioptiongui::readBuffer()
{
	//1.inputfmt
	Iputfmt();
	//2.hdmi mac
	getSn();
	//3.outputfmt
	outputfmt();
	//4.mute
	getMute();
	//5.name
	getName();
	//6.no
	getNo();
	//7.pid
	getPid();
	//8.audio Source and audio Freq
	getAudioSourceAndFreq();
	//9.getLocal_IP_Port_MAC
	//getLocal_IP_Port_MAC();
	//10.getStreamingArg
	//getStreamingArg();

	//qDebug("typeId = %d", typeId);
	return 0;
}

int Hdmioptiongui::Iputfmt()
{
	char showbuf[32];
	unsigned char tmpbuf[8];
	unsigned short VRow, VColumn;
	unsigned short VFreq;
	unsigned short VScan;
	char cScan;
	tbs.target_ext_memory_rd_wt(READ, ADDRESS_HDMI((tuner % 4)) + OFFSET_START, tmpbuf, 8);
	VColumn = ((tmpbuf[6] << 8) + tmpbuf[7]);
	VRow = ((tmpbuf[4] << 8) + tmpbuf[5]);
	VFreq = tmpbuf[2];
	VScan = tmpbuf[1] & 0x1;
	if (VFreq >= 57 && VFreq <= 60)
		VFreq = 60;
	if (VFreq >= 47 && VFreq <= 50)
		VFreq = 50;
	if (VFreq == 23)
		VFreq = 24;
	cScan = (VScan == 1) ? 'I' : 'p';
	sprintf(showbuf, "%d*%d%c  %dHZ", \
		VRow, VColumn, cScan, VFreq);

	if (0 == tmpbuf[0]) {
		SetInputFmt(QString("No input source"));
		noSingleFlg = 1;
	}
	else {
		SetInputFmt(showbuf);
		noSingleFlg = 0;
	}
	return 0;
}

int Hdmioptiongui::getSn()
{
	u8 bytes[6];
	char showbuf[32];
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x08, bytes, 6);
	sprintf(showbuf, "%02x:%02x:%02x:%02x:%02x:%02x", \
		bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5]);
	ui->lin_HDMIMac->setText(showbuf);
	//qDebug("mac:%s",showbuf);
	return 0;
}


int Hdmioptiongui::outputfmt()
{
	u8 iwrNum[8] = { 0 };
	int outsettingFormat[11] = { 0 };
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x14, iwrNum, 1);

	if (iwrNum[0] == 1) // auto or not
	{
		qDebug("the latest setting is Auto mode!");
		iwrNum[0] = 1;
		iwrNum[1] = 0;
		iwrNum[2] = 0;
		ui->rad_Aut->setChecked(1);
		ui->sta_Mode->setCurrentIndex(0);
		workMode = 1;
		return 0;
	}
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x15, iwrNum, 1);
	if (iwrNum[0] != 0) // manual or not
	{
		ui->rad_Man->setChecked(1);
		ui->sta_Mode->setCurrentIndex(1);
		manNo = iwrNum[0];
		workMode = 2;
		switch (manNo)
		{
		case 1:
			qDebug("super 1920*1080");
			ui->rad_Su->setChecked(1);
			break;
		case 2:
			ui->rad_Ult->setChecked(1);
			qDebug("ultra 1440*1080 ");
			break;
		case 3:
			ui->rad_Exc->setChecked(1);

			qDebug("excellent 1280*720");
			break;
		case 4:
			ui->rad_Good->setChecked(1);
			qDebug("good 1120*640");
			break;
		case 5:
			ui->rad_Fair->setChecked(1);
			qDebug("fair 960*540");
			break;
		case 6:
			ui->rad_Poor->setChecked(1);
			qDebug("poor 800*480");
			break;
		case 7:
			ui->rad_Mob->setChecked(1);
			qDebug("mobile 480*272");
			break;
		default:
			qDebug("no");
			break;
		}
		return 0;
	}
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x10, iwrNum, 2);
	if (iwrNum[1] == 11)
	{
		workMode = 3;
		qDebug("the latest setting is Advance mode!");
		int level[6] = { 30,31,32,40,41,42 };
		tbs.read_M23Register(11, outsettingFormat);
		ui->rad_Adv->setChecked(1);
		ui->sta_Mode->setCurrentIndex(2);

		SetW(QString("%1").arg(outsettingFormat[1]));
		SetH(QString("%1").arg(outsettingFormat[2]));
		SetFrame(QString("%1").arg(outsettingFormat[9] / 2));
		SetAvBR(QString("%1").arg(outsettingFormat[5]));
		if (outsettingFormat[0] > 512) {
			SetHprofile(1);
			switch (outsettingFormat[0] - 512) {
			case 30:
				SetHlevel(0);
				break;
			case 31:
				SetHlevel(1);
				break;
			case 32:
				SetHlevel(2);
				break;
			case 40:
				SetHlevel(3);
				break;
			case 41:
				SetHlevel(4);
				break;
			case 42:
				SetHlevel(5);
				break;
			default:
				break;
			}
		}
		else {
			SetHprofile(0);
			switch (outsettingFormat[0] - 256) {
			case 30:
				SetHlevel(0);
				break;
			case 31:
				SetHlevel(1);
				break;
			case 32:
				SetHlevel(2);
				break;
			case 40:
				SetHlevel(3);
				break;
			case 41:
				SetHlevel(4);
				break;
			case 42:
				SetHlevel(5);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}


int Hdmioptiongui::getMute()
{
	unsigned char temdate[4] = { 0 };
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x16, temdate, 1);
	if (1 == temdate[0]) {
		SetMute(1);
	}
	else {
		SetMute(0);
	}
	return 0;
}


int Hdmioptiongui::getName()
{
	unsigned char temdate[4] = { 0 };
	int len = 0;
	int i = 0;
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x12, temdate, 1);
	if (0x60 != temdate[0]) {
		return 0;
	}
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x13, temdate, 1);
	len = temdate[0];
	char programe[64] = { '0' };

	for (i = 0; i < len; i++)
	{
		tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x60 + i, (u8*)&programe[i], 1);
	}
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x60, (u8*)programe, len);
	SetProgrameName(programe);

	return 0;
}


int Hdmioptiongui::getNo()
{
	ui->lin_PgmNo->setDisabled(0);
	u8 num = 0;
	tbs.target_ext_memory_rd_wt(READ, PROGRAM_START_NO(tuner % 4), &num, 1);
	SetProgrameNo(QString("%1").arg(num));
	return 0;
}


int Hdmioptiongui::getPid()
{
	ui->lin_Vpid->setDisabled(0);
	ui->lin_Apid->setDisabled(0);
	ui->lin_Pcr->setDisabled(0);
	ui->lin_Pmt->setDisabled(0);
	u8 tmpbuf[8] = { 0 };
	for (int i = 0; i < 8; i++) {
		tbs.target_ext_memory_rd_wt(READ, PID((tuner % 4)) + i, &tmpbuf[i], 1);
	}
	u8 eachpid[2];
	eachpid[1] = tmpbuf[0];
	eachpid[0] = tmpbuf[1];
	SetPmt(QString("%1").arg(*(u16*)eachpid));
	eachpid[1] = tmpbuf[2];
	eachpid[0] = tmpbuf[3];
	SetPcr(QString("%1").arg(*(u16*)eachpid));
	eachpid[1] = tmpbuf[4];
	eachpid[0] = tmpbuf[5];
	SetVpid(QString("%1").arg(*(u16*)eachpid));
	eachpid[1] = tmpbuf[6];
	eachpid[0] = tmpbuf[7];
	setApid(QString("%1").arg(*(u16*)eachpid));
	return 0;
}

int Hdmioptiongui::getAudioSourceAndFreq()
{
	u8 tmpbuf[8];
	tbs.target_ext_memory_rd_wt(READ,
		GPIOBASE_ADDR + AUDIIO_FREQ_SELECT_OFFSETADDR + ((tuner % 4) * 0x80),
		tmpbuf, 1);
	u8 audioFreq = tmpbuf[0] & 0x03;
	qDebug() << "audioFreq:" << audioFreq;
	SetAFre(audioFreq);
	return 0;
}

int Hdmioptiongui::getLocal_IP_Port_MAC()
{

#if 1
	u8 tmpbuf[14] = { 0 };
	u8 g_or_100M = 0;
	u32 t = typeId;
	typeId = 6316;
	tbs.udp_REG64_rd(0x4000 + 24, 1, &g_or_100M);
	//0. 0x00 ~0x27  100M
	tbs.target_ext_memory_rd_wt(READ, 0x00 + 0x80, tmpbuf, 14);
	//1.ip and port
	QString qstripandport_100M;
	tmpbuf[6] = tmpbuf[4];
	qstripandport_100M.sprintf("%d.%d.%d.%d:%d", tmpbuf[0], tmpbuf[1], tmpbuf[2], \
		tmpbuf[3], *(u16*)&tmpbuf[5]);
	//QString qstrip_100M = QString("TBS8030:");
	//qstrip_100M.append(qstripandport_100M);
	ui->lin_100M_Ip->setText(qstripandport_100M);
	//qDebug() << qstrip_100M;
	//if (0 == g_or_100M) { //100m
		//netf[col_n]->PItem->setText(0, qstrip_100M);
		//ui->com_Netlist->setItemText(col_n, qstrip_100M);
	//}
	/**
	//2.net mac
	QString qstrmac_100M;
	qstrmac_100M.sprintf("%02x:%02x:%02x:%02x:%02x:%02x", tmpbuf[8], tmpbuf[9], tmpbuf[10], \
		tmpbuf[11], tmpbuf[12], tmpbuf[13]);
	ui->lin_100M_NetMac->setText(qstrmac_100M);
	qDebug() << qstrmac_100M;
	**/
	tbs.target_ext_memory_rd_wt(READ, 0x180, tmpbuf, 8); //100m
	QString qstrnetmask_100M;
	qstrnetmask_100M.sprintf("%d.%d.%d.%d", tmpbuf[0], tmpbuf[1], tmpbuf[2], tmpbuf[3]);
	ui->lin_100M_Mask->setText(qstrnetmask_100M);

	QString qstrgateway_100M;
	qstrgateway_100M.sprintf("%d.%d.%d.%d", tmpbuf[4], tmpbuf[5], tmpbuf[6], tmpbuf[7]);
	ui->lin_100M_Gateway->setText(qstrgateway_100M);
	memset(tmpbuf, 0, 14);

	//0. 0x00 ~0x27 1g
	tbs.target_ext_memory_rd_wt(READ, 0x00, tmpbuf, 14);
	//1.ip and port
	QString qstripandport_1G;
	tmpbuf[6] = tmpbuf[4];
	qstripandport_1G.sprintf("%d.%d.%d.%d:%d", tmpbuf[0], tmpbuf[1], tmpbuf[2], \
		tmpbuf[3], *(u16*)&tmpbuf[5]);
	//QString qstrip_1G = QString("TBS8030:");
	//qstrip_1G.append(qstripandport_1G);
	ui->lin_1G_Ip->setText(qstripandport_1G);
	//qDebug() << qstrip_1G;

	//if (1 == g_or_100M) { //1g
	//	netf[col_n]->PItem->setText(0, qstrip_1G);
	//	ui->com_Netlist->setItemText(col_n, qstrip_1G);
	//}
	/**
	//2.net mac
	QString qstrmac_1G;
	qstrmac_1G.sprintf("%02x:%02x:%02x:%02x:%02x:%02x", tmpbuf[8], tmpbuf[9], tmpbuf[10], \
		tmpbuf[11], tmpbuf[12], tmpbuf[13]);
	qDebug() << qstrmac_1G;
	ui->lin_1G_NetMac->setText(qstrmac_1G);
	**/
	if (1 == (tmpbuf[7] & (0x01))) {//auto
		SetHDCP(1);
	}
	else if (0 == (tmpbuf[7] & (0x01))) {//manal
		SetHDCP(0);
	}
	tbs.target_ext_memory_rd_wt(READ, 0x100, tmpbuf, 8); //100m
	QString qstrnetmask_1G;
	qstrnetmask_1G.sprintf("%d.%d.%d.%d", tmpbuf[0], tmpbuf[1], tmpbuf[2], tmpbuf[3]);
	ui->lin_1G_Mask->setText(qstrnetmask_1G);
	QString qstrgateway_1G;
	qstrgateway_1G.sprintf("%d.%d.%d.%d", tmpbuf[4], tmpbuf[5], tmpbuf[6], tmpbuf[7]);
	ui->lin_1G_Gateway->setText(qstrgateway_1G);
	memset(tmpbuf, 0, 14);
	typeId = t;
#endif
	return 0;
}

int Hdmioptiongui::getStreamingArg()
{
#if 1
	u8 tmpbuf[15] = { 0 };
	u8 tmp[3] = { 0 };
	u32 t = typeId;
	typeId = 6316;
	tbs.REG64_rd(0x4000 + 7 * 4, 2, &tmp[1]);
	tmp[0] = tmp[2];

	u32 NullPackedAddr = 0x50;

	u8 packetsize = 1;
	tbs.target_ext_memory_rd_wt(READ, 0x55, &packetsize, 1);
	ui->com_PacketSize->clear();
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 1"), 1);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 2"), 2);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 3"), 3);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 4"), 4);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 5"), 5);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 6"), 6);
	ui->com_PacketSize->addItem(QObject::tr("packet size 188 * 7"), 7);
	//ui->com_PacketSize->setCurrentIndex(packetsize);
	qDebug("get packetsize = %d", packetsize);
	//packetsize =(u8)(ui->com_PacketSize->itemData(packetsize).toInt());
	//qDebug("get packetsize = %d", packetsize);
	if (1 <= packetsize && packetsize <= 7) {
		packetsize = packetsize - 1;
		ui->com_PacketSize->setCurrentIndex(packetsize);
	}
	else
	{
		ui->com_PacketSize->clear();
		qDebug("Failed to get empty package size");
		//return 0;
	}
	ui->com_PacketSize->setEnabled(true);

	for (int i = 0; i < 2; i++) {
		qDebug("tmp[%d] = %#02x", i, tmp[i]);
	}
	for (int i = 0; i < 16; i++) {
		if (-1 != netf[col_n]->Item_tuner[i]) {
			memset(tmpbuf, 0, 15);
			if (0 <= i && i <= 3)
				NullPackedAddr = 0x50 + (i % 4);
			else if (4 <= i && i <= 7)
				NullPackedAddr = 0xD0 + (i % 4);
			else if (8 <= i && i <= 11)
				NullPackedAddr = 0x150 + (i % 4);
			else if (12 <= i && i <= 15)
				NullPackedAddr = 0x1D0 + (i % 4);
			tbs.target_ext_memory_rd_wt(READ, NullPackedAddr, tmpbuf, 1);
			sf[i].nullpacked = tmpbuf[0] & 0x01;
			qDebug("Get NullPackedAddr = %04x", NullPackedAddr);
			qDebug("Get sf[%d].nullpacked = %d", i, sf[i].nullpacked);

			memset(tmpbuf, 0, 15);
			tbs.target_ext_memory_rd_wt(READ, NET_BASE_ADDR_CHILD(i / 4)\
				+ OFFICE_CHILD_HDMI(i % 4), tmpbuf, 14);
			sf[i].switchTS = tmpbuf[0] & 0x01;
			sf[i].protocol = tmpbuf[1] & 0x01;
			sf[i].ip = QString("%1.%2.%3.%4").arg(tmpbuf[2])\
				.arg(tmpbuf[3]).arg(tmpbuf[4]).arg(tmpbuf[5]);
			tmpbuf[14] = tmpbuf[12];
			sf[i].port = *(u16*)&tmpbuf[13];
			sf[i].streamStatus = ((*(u16*)&tmp[0]) >> i) & 0x01;
			qDebug() << "tar ip:" << sf[i].ip;
		}
	}
	typeId = t;
#endif
	return 0;
}



bool Hdmioptiongui::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick) {
		if (watched == ui->widgetTitle) {
			on_btnMenu_Max_clicked();
			return true;
		}
	}

	return QWidget::eventFilter(watched, event);
}


void Hdmioptiongui::radioClick()
{
	QRadioButton *r = (QRadioButton *)sender();
	QString name = r->text();

	QList<QRadioButton *> rads = ui->gro_Mode->findChildren<QRadioButton *>();
	foreach(QRadioButton *ra, rads) {
		if (ra == r) {
			ra->setChecked(true);
		}
		else {
			ra->setChecked(false);
		}
	}

	if (name == "Auto") {
		ui->sta_Mode->setCurrentIndex(0);
		workMode = 1;
	}
	else if (name == "Manual") {
		ui->sta_Mode->setCurrentIndex(1);
		workMode = 2;
	}
	else if (name == "Advanced") {
		ui->sta_Mode->setCurrentIndex(2);
		workMode = 3;
	}
}

void Hdmioptiongui::radioClick_M()
{
	QRadioButton *rb = (QRadioButton *)sender();
	QString name = rb->text();

	QList<QRadioButton *> mas = ui->pag_Man->findChildren<QRadioButton *>();
	foreach(QRadioButton *ma, mas) {
		if (ma == rb) {
			ma->setChecked(true);
		}
		else {
			ma->setChecked(false);
		}
	}

	if (name == "Super(1920*1080)") {
		qDebug() << "s";
		manNo = 1;
	}
	else if (name == "Ultra(1440*1080)") {
		qDebug() << "u";
		manNo = 2;
	}
	else if (name == "Excellent(1280*720)") {
		qDebug() << "e";
		manNo = 3;
	}
	else if (name == "Good(1120*640)") {
		qDebug() << "g";
		manNo = 4;
	}
	else if (name == "Fair(960*540)") {
		qDebug() << "f";
		manNo = 5;
	}
	else if (name == "Poor(800*480)") {
		qDebug() << "p";
		manNo = 6;
	}
	else if (name == "Mobile(480*272)") {
		qDebug() << "m";
		manNo = 7;
	}
}

void Hdmioptiongui::radioClick_HN()
{
	QRadioButton *rhn = (QRadioButton *)sender();
	QString name = rhn->text();

	QList<QRadioButton *> hns = ui->gbx_SelectPage->findChildren<QRadioButton *>();
	foreach(QRadioButton *hn, hns) {
		if (hn == rhn) {
			hn->setChecked(true);
		}
		else {
			hn->setChecked(false);
		}
	}

	if (name == "HDMI Capture Card Setting") {
		ui->sta_DevWdeget->setCurrentIndex(0);

	}
	else if (name == " Streaming&&Network Setting") {
		ui->sta_DevWdeget->setCurrentIndex(1);
		ui->tabNetwork->setCurrentIndex(0);
	}
}

void Hdmioptiongui::showSelectedImage(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem *parent = item->parent();
	if (NULL == parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
	{
		return;
	}
	if (0 != mode) {
		return;
	}
	u8 a = 0;
	if (1 == maincpu) {
		maincpu = 0;
		u32 t = typeId;
		typeId = 6316;
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
		typeId = t;
	}
	if (63081 == typeId) {
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
	}
	udpfd = tbs.udpClose(udpfd);
	int ng = 0;
	int col_j = 0;
	for (int i = 0; i < netnum; i++) {
		for (int j = 0; j < 16; j++) {
			if (-1 != netf[i]->Item_tuner[j]) {
				netf[i]->Item[j]->setIcon(0, QIcon(":/qss/psblack/chun.png"));
				if (netf[i]->Item[j] == item) {
					col_n = i;
					col_j = j;
					ng = 1;
				}
			}
		}
	}
	if (ng == 0) {
		return;
	}
	tbs.useless(netf[col_n]->ipaddr, netf[col_n]->ipport);
	udpfd = tbs.udpOpen(netf[col_n]->ipaddr, netf[col_n]->ipport);
	if (udpfd < 3) {
		if (QMessageBox::Ok == QMessageBox::critical(this, tr("erro"),
			tr("Device connect fail          "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	//SetIp(QString("%1:%2").arg(netf[col_n]->ipaddr).arg(netf[col_n]->ipport));
	if (-1 != parent->text(0).indexOf("TBS8030")) {
		typeId = 63081;
		tuner = col_j;
	}
	else {
		typeId = 0;
		item->setIcon(0, QIcon(":/qss/psblack/chun.png"));
		Set_100M_Ip(QString(""));
		Set_1G_Ip(QString(""));
		return;
	}
	a = 1;
	qDebug("tuner:%d", tuner);
	typeId = 6316;
	tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	maincpu = 1;
	typeId = 63081;
	tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	for (int i = 0; i < 16; i++) {
		tunerarry[i] = netf[col_n]->Item_tuner[i];
	}
	readBuffer();
	item->setIcon(0, QIcon(":/qss/psblack/ch.png"));
	selecttunerflg = 1;
	//initStreamingForm();
	//ui->lin_NetNo->setDisabled(0);
	return;
}

void Hdmioptiongui::show_status(Msg *g)
{
	qDebug() << "show";
	u8 ret = 0;
	int col_bak = 0;
	int i = 0;

	int cnt_time = 250;

#if 1
	if (1 == g->type) {
		//test
		qbox = new  QMessageBox();
		qbox->setWindowTitle(tr("information"));
		qbox->setText(QString("Configuring now,please wait.."));
		qbox->setStandardButtons(0);
		qbox->setFont(QFont("Microsoft Yahei", fontsize + 9));
		qbox->setProperty("Form", true);
		qbox->exec();
		return;
	}

	if (2 == g->type) {
		while ((NULL == qbox) || (i < 10)) {
			QMSLEEP(1);
			i++;
		}
		if (NULL != qbox) {
			QMSLEEP(10);
			qbox->close();
			delete qbox;
		}
		return;
	}

	if (4 == g->type) {
		if (QMessageBox::Ok == QMessageBox::information(this, tr("information"),
			tr("Success                                    "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			readBuffer();
			local_ip_port_mac_flg = 0;
			/**
			if (1 == local_ip_port_mac_flg) {
				//tbs.HardRST();
				//netf[col_n]->ipaddr = GetIp.section(':', 0, 0).trimmed();
				//netf[col_n]->ipport = GetIp.section(':', 1, 1).trimmed().toInt();
				//qDebug() << "netfip:" << netf[col_n]->ipaddr << ":" << netf[col_n]->ipport;
				//udpsockaddr.sin_port = htons(netf[col_n]->ipport);
				//udpsockaddr.sin_addr.s_addr = inet_addr(netf[col_n]->ipaddr.toLatin1().data());
				local_ip_port_mac_flg = 0;
			}
			else {
				local_ip_port_mac_flg = 0;
			}
			*/
			loadflg = 0;
			return;
		}
		return;
	}

	if (5 == g->type) {
		if (QMessageBox::Ok == QMessageBox::information(this, tr("information"),
			tr("Success                                          "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			Refresh();
		}
		local_ip_port_mac_flg = 0;
		loadflg = 0;
		return;
	}

	if (6 == g->type) {
		if (QMessageBox::Ok == QMessageBox::information(this, tr("information"),
			tr("Success                                          "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			getStreamingArg();
			initStreamingForm();
			local_ip_port_mac_flg = 0;
			loadflg = 0;
			return;
		}
		return;
	}

	if (7 == g->type) {
		ui->com_Netlist->setCurrentIndex(0);
		readNetwork(0);
		comchangeflg = 1;
		//ui->com_Netlist->currentIndexChanged(col_n);
		return;
	}

	if (8 == g->type) {
		myDialog = new Mymesg();
		QString title = "The new IP is configuring, please wait..";
		myDialog->starttimer(title, cnt_time);
		myDialog->exec();
		return;
	}
	if (10 == g->type) {
		QString title = "The device is restaring, please wait..";
		myDialog = new Mymesg();
		myDialog->starttimer(title, cnt_time);
		myDialog->exec();
		return;
	}
	if (11 == g->type) {
		if (QMessageBox::Ok == QMessageBox::critical(this, tr("failure"),
			tr("Restart the failure"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			qDebug("nnnnnnnnnnnnnnnn");
			return;
		}
		return;
	}
	if (9 == g->type) {
		if (NULL != myDialog) {
			myDialog->close();
			delete myDialog;
			myDialog = NULL;
		}
		return;
	}


#endif
}


void Hdmioptiongui::showNetTuners(QString qs)
{
	qDebug() << "showNetTuners:" << qs;
	int i = 0;
	QString secipqst;
	QString ipqs = qs.section('/', 0, 0).trimmed();
	QString macqs = qs.section('/', 1, 1).trimmed();

	QString ipname = ipqs.section(':', 0, 0).trimmed();
	QString ipch = ipqs.section(':', 1, 1).trimmed();
	int portint = ipqs.section(':', 2, 2).trimmed().toInt();
	int ret = tbs.get_1000M_or_100M(ipch, portint);
	for (i = 0; i < netnum; i++) {
		if (macqs == netf[i]->mac_1g) {
			if (1 == ret) {
				secipqst = QString("TBS8030:%1:%2/%3:%4")
					.arg(ipch).arg(portint)
					.arg(netf[i]->ipaddr).arg(netf[i]->ipport);
				netf[i]->ipaddr = ipch;
				netf[i]->ipport = portint;
			}
			else if (0 == ret) {
				secipqst = QString("TBS8030:%1:%2/%3:%4")
					.arg(netf[i]->ipaddr).arg(netf[i]->ipport)
					.arg(ipch).arg(portint);
			}
			
			ui->com_Netlist->setItemText(i, secipqst);
			netf[i]->PItem->setText(0, secipqst);
			return;
		}
	}
	netf[netnum] = new NetInfor();
	netf[netnum]->mac_1g = macqs;
	netf[netnum]->flag_1g = ret;
	netf[netnum]->ipname = ipname;
	netf[netnum]->ipaddr = ipch;
	netf[netnum]->ipport = portint;
	char char_net[64] = { '\0' };
	sprintf(char_net, ":%s:%d", netf[netnum]->ipaddr.toLatin1().data(), netf[netnum]->ipport);
	QString PItemName = netf[netnum]->ipname;
	PItemName.append(char_net);
	/*************/
	ui->com_Netlist->addItem(PItemName, netnum);
	ui->tree_Dev->setIconSize(QSize(25, 25));
	netf[netnum]->PItem = new QTreeWidgetItem(ui->tree_Dev, QStringList(PItemName));
	netf[netnum]->PItem->setIcon(0, QIcon(":/qss/psblack/uilogo/net.png"));
	tbs.useless(netf[netnum]->ipaddr, netf[netnum]->ipport);
	getswitchstatus(netf[netnum]);
	tbs.useless(netf[netnum]->ipaddr, netf[netnum]->ipport);
	netf[netnum]->validCaptureNum = 0;
	for (i = 0; i < 16; i++) {
		if (-1 != netf[netnum]->Item_tuner[i]) {
			netf[netnum]->Item[i] = new QTreeWidgetItem(netf[netnum]->PItem,
				QStringList(QString("Capture %1").arg(i)));
			netf[netnum]->Item[i]->setIcon(0, QIcon(":/qss/psblack/chun.png"));
			netf[netnum]->PItem->addChild(netf[netnum]->Item[i]);
			netf[netnum]->validCaptureNum++;
		}
		else {
			netf[netnum]->Item[i] = NULL;
		}
	}

	ui->tree_Dev->expandAll();
	netnum++;
	return;
}



void Hdmioptiongui::on_btnMenu_Min_clicked()
{
	showMinimized();
}

void Hdmioptiongui::on_btnMenu_Max_clicked()
{
	static bool max = false;
	static QRect location = this->geometry();

	if (max) {
		this->setGeometry(location);
		width = width_s;
		height = height_s;
	}
	else {
		location = this->geometry();
		this->setGeometry(qApp->desktop()->availableGeometry());
		width = this->size().width();
		height = this->size().height();
	}

	this->setProperty("canMove", max);
	max = !max;
}

void Hdmioptiongui::on_btnMenu_Close_clicked()
{
	close();
}

void Hdmioptiongui::on_tabNetwork_currentChanged(int idx)
{
	isIPSettingFlg = idx; //0=> streaming, 1=> ipsetting
	if (0 == isIPSettingFlg) {
		ui->btn_Upload->show();
		ui->btn_Download->show();
	}
	else if (1 == isIPSettingFlg) {
		ui->btn_Upload->hide();
		ui->btn_Download->hide();
	}
}

void Hdmioptiongui::on_com_Aout_currentIndexChanged(int idx)
{
	if (0 == idx) { // hdmi
		ui->com_AFre->clear();
		ui->com_AFre->addItem("48k", 0);
		ui->com_AFre->addItem("44.1k", 1);
		ui->com_AFre->addItem("32k", 2);
		ui->com_AFre->addItem("Auto", 3);
	}
	else if (1 == idx) { // audio
		ui->com_AFre->clear();
		ui->com_AFre->addItem("48k", 0);
		ui->com_AFre->addItem("44.1k", 1);
		ui->com_AFre->addItem("32k", 2);

	}
	else {
		ui->com_AFre->clear();
	}
}

void Hdmioptiongui::on_com_Netlist_currentIndexChanged(int idx)
{
	if (1 != comchangeflg) {
		return;
	}
	if (0 != mode) {
		return;
	}
	u8 a = 0;
	qDebug("on_com_Netlist_currentIndexChanged idx = %d", idx);
	if (idx < 0) {
		//	if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
		//		tr("Without network device                       "),
		//		QMessageBox::Ok,
		//		QMessageBox::Ok)) {
		//		return;
		//	}
		return;
	}
	if (1 == maincpu) {
		maincpu = 0;
		u32 t = typeId;
		typeId = 6316;
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
		typeId = t;
	}
	if (63081 == typeId) {
		tbs.monopolizeCpu_w(0x00, &a, 1);//set 0
	}
	udpfd = tbs.udpClose(udpfd);
	col_n = idx;
	tbs.useless(netf[col_n]->ipaddr, netf[col_n]->ipport);
	udpfd = tbs.udpOpen(netf[col_n]->ipaddr, netf[col_n]->ipport);
	if (udpfd < 3) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	//test
	//QMessageBox *qbox_1 = new  QMessageBox();
	//qbox_1->setWindowTitle(tr("information"));
	//qbox_1->setText(QString("Device is configuring,please wait.."));
	//qbox_1->setStandardButtons(0);
	//qbox_1->setFont(QFont("Microsoft Yahei", fontsize + 9));
	//qbox_1->setProperty("Form", true);
	//qbox_1->exec();
	//mode = 8;
	typeId = 6316;
	a = 1;
	tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	maincpu = 1;
	//	typeId = 63081;
	//tbs.monopolizeCpu_w(0x00, &a, 1);//set 1
	for (int i = 0; i < 16; i++) {
		tunerarry[i] = netf[col_n]->Item_tuner[i];
	}
	//if (0 == isIPSettingFlg) {
	getStreamingArg();
	initStreamingForm();
	//}
	//else if (1 == isIPSettingFlg) {
	getLocal_IP_Port_MAC();
	//}
	//while (0 != mode) {
	//	QMSLEEP(1);
	//}
	//mode = 9;
}

void Hdmioptiongui::on_che_Check_all_stateChanged(int idx)
{
	int n = 0;
	if (uncheckflg < 2) {
		return;
	}
	if (2 == idx) {
		n = 1;
	}
	else if (0 == idx) {
		n = 0;
	}
	for (int i = 0; i < 16; i++) {
		if (-1 != netf[col_n]->Item_tuner[i]) {
			if (NULL != cheBoxTS[i]) {
				cheBoxTS[i]->setCheckState(((n) ? (Qt::Checked) : (Qt::Unchecked)));
			}
		}
	}

}

void Hdmioptiongui::on_btn_Download_clicked()
{
	QString  file_name = QFileDialog::getSaveFileName(this,
		tr("Save File"),
		"",
		tr("sql file(*.db)"),
		0);
	if (!file_name.isNull()) {
		init_sql(file_name);
		updateStream_sql(sf);
		database.close();
		delete sql_query;
		qDebug() << file_name;
	}
}

void Hdmioptiongui::on_btn_Upload_clicked()
{
	QString  file_name = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		"",
		tr("sql file(*.db);;"),
		0);
	if (!file_name.isNull()) {
		init_sql(file_name);
		readStream_sql(sf);
		initStreamingForm();
		database.close();
		delete sql_query;
		qDebug() << file_name;
	}
}

void Hdmioptiongui::on_btn_Refresh_clicked()
{
	if (QMessageBox::No == QMessageBox::question(this, tr("question"),
		tr("Refresh Devices?                             "),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::No)) {
		return;
	}
	reflashflg = 0;
	Refresh();
}

int Hdmioptiongui::getNetTuners()
{
	netf = new NetInfor*[64];
	netnum = 0;
	QString qstingip = getHostIpAddress();
	netseg = getNetworkSegment(qstingip);
	QMSLEEP(2);
	mode = 7;
	return 0;
}

void Hdmioptiongui::initForm()
{
	this->setProperty("form", true);
	this->setProperty("canMove", true);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


	//QPixmap icon(":/image/logo.png");
	QPixmap icon(":/qss/psblack/uilogo/logo.png");
	ui->labIco->setPixmap(icon);
	ui->labIco->resize(icon.width(), icon.height());
	//IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf099), 30);
	IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
	IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
	//IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf096));
	IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

	IconHelper::Instance()->setIcon(ui->lab_enico, QChar(0xf069), 30);

	//ui->widgetMenu->setVisible(false);
	ui->widgetTitle->installEventFilter(this);
	ui->widgetTitle->setProperty("form", "title");
	ui->widgetTop->setProperty("nav", "top");
	//ui->labTitle->setText("TBS CAPTURE");
	ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
	this->setWindowTitle(ui->labTitle->text());

	//ui->stackedWidget->setStyleSheet("QLabel{font:10pt;}");

	//单独设置指示器大小
	int addWidth = 20;
	int addHeight = 10;
	int rbtnWidth = 15;
	int ckWidth = 13;
	int scrWidth = 12;
	int borderWidth = 3;

	QStringList qss;
	qss.append(QString("QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{width:%1px;}").arg(addWidth));
	qss.append(QString("QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,"
		"QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{width:%1px;height:%1px;right:2px;}").arg(addHeight));
	qss.append(QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth));
	qss.append(QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth));
	qss.append(QString("QScrollBar:horizontal{min-height:%1px;border-radius:%2px;}QScrollBar::handle:horizontal{border-radius:%2px;}"
		"QScrollBar:vertical{min-width:%1px;border-radius:%2px;}QScrollBar::handle:vertical{border-radius:%2px;}").arg(scrWidth).arg(scrWidth / 2));
	qss.append(QString("QWidget#widget_top>QToolButton:pressed,QWidget#widget_top>QToolButton:hover,"
		"QWidget#widget_top>QToolButton:checked,QWidget#widget_top>QLabel:hover{"
		"border-width:0px 0px %1px 0px;}").arg(borderWidth));
	qss.append(QString("QWidget#widgetleft>QPushButton:checked,QWidget#widgetleft>QToolButton:checked,"
		"QWidget#widgetleft>QPushButton:pressed,QWidget#widgetleft>QToolButton:pressed{"
		"border-width:0px 0px 0px %1px;}").arg(borderWidth));

	this->setStyleSheet(qss.join(""));

	//QMessageBox{ color: red }
	//设置MODE按钮
	QList<QRadioButton *> rads = ui->gro_Mode->findChildren<QRadioButton *>();
	foreach(QRadioButton *rd, rads) {
		rd->setCheckable(true);
		connect(rd, SIGNAL(clicked()), this, SLOT(radioClick()));
	}
	//设置Manual按钮
	QList<QRadioButton *> mas = ui->pag_Man->findChildren<QRadioButton *>();
	foreach(QRadioButton *ma, mas) {
		ma->setCheckable(true);
		connect(ma, SIGNAL(clicked()), this, SLOT(radioClick_M()));
	}
	//设置Hdmi or NetWork page
	QList<QRadioButton *> hns = ui->gbx_SelectPage->findChildren<QRadioButton *>();
	foreach(QRadioButton *hn, hns) {
		hn->setCheckable(true);
		connect(hn, SIGNAL(clicked()), this, SLOT(radioClick_HN()));
	}
	ui->rad_Hdmi->click();
	ui->rad_Aut->click();
	connect(ui->tree_Dev, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(showSelectedImage(QTreeWidgetItem*, int)));
	emflg = 0;
	loadflg = 0;
	th = new threadTbs();
	connect(th, SIGNAL(sendMsg(Msg*)), this, SLOT(show_status(Msg*)));
	connect(th, SIGNAL(sendIp(QString)), this, SLOT(showNetTuners(QString)));
	th->start();
	width_s = this->size().width();
	height_s = this->size().height();
	width = width_s;
	height = height_s;
	fontsize = 0;
	for (int i = 0; i < 16; i++) {
		comBoxProtocol[i] = NULL;
		cheBoxTS[i] = NULL;
		labelStauts[i] = NULL;
		widgetTS[i] = NULL;
		hLayoutTS[i] = NULL;
		comBoxNullPacked[i] = NULL;
	}
	tabWS = ui->tabW_Streaming;
	myDialog = NULL;
}

void Hdmioptiongui::init_sql(QString path)
{
	//1.create sql
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		database = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName(path);
	}

	//2.open sql
	if (!database.open())
	{
		qDebug() << "Error: Failed to connect database." << database.lastError();
	}

	//3.create from
	sql_query = new QSqlQuery();
	QString create_sql = "create table streamValue (id int,IP varchar(20),Port int,protocol int,switchTS int)";
	sql_query->prepare(create_sql);
	if (!sql_query->exec())
	{
		qDebug() << "Error: Fail to create table." << sql_query->lastError();
	}
	else
	{
		qDebug() << "Table created!";
	}

	//4.select_sql

	QString select_sql = "select * from streamValue";
	if (!sql_query->exec(select_sql))
	{
		qDebug() << sql_query->lastError();
	}
	else
	{
		if (!(sql_query->next()))
		{
			//5.insert_sql
			QString insert_sql = "insert into streamValue values (?, ?, ?, ?, ?)";
			sql_query->prepare(insert_sql);

			for (int i = 0; i < 16; i++) {
				sql_query->addBindValue(i);
				sql_query->addBindValue("192.168.1.188");
				sql_query->addBindValue(4000 + i);
				sql_query->addBindValue(0);
				sql_query->addBindValue(0);

				if (!sql_query->exec())
				{
					qDebug() << sql_query->lastError();
				}
				else
				{
					qDebug("inserted i = %d", i);
				}
			}

		}
	}

	qDebug() << "init sql over";
}

void Hdmioptiongui::updateStream_sql(StreamingForm *stream)
{
	QString update_sql = "update streamValue set IP = :IP, Port = :Port,protocol = :protocol,switchTS =:switchTS where id = :id";
	sql_query->prepare(update_sql);

	for (int i = 0; i < 16; i++) {
		sql_query->bindValue(":IP", stream[i].ip.toLatin1().data());
		sql_query->bindValue(":Port", stream[i].port);
		sql_query->bindValue(":protocol", stream[i].protocol);
		sql_query->bindValue(":switchTS", stream[i].switchTS);
		sql_query->bindValue(":id", i);
		if (!sql_query->exec())
		{
			qDebug() << sql_query->lastError();
		}
		else
		{
			qDebug("updated i = %d", i);
		}
	}
	qDebug("updated over");
}

void Hdmioptiongui::readStream_sql(StreamingForm *stream)
{
	int id = 0;
	QString select_sql = "select * from streamValue";
	if (!sql_query->exec(select_sql))
	{
		qDebug() << sql_query->lastError();
	}
	else
	{
		while (sql_query->next())
		{
			id = sql_query->value(0).toInt();
			stream[id].ip = sql_query->value(1).toString();
			stream[id].port = sql_query->value(2).toInt();
			stream[id].protocol = sql_query->value(3).toInt();
			stream[id].switchTS = sql_query->value(4).toInt();
			//stream[id].streamStatus = 1;
			qDebug() << QString("%1:%2:%3:%4:%5").arg(id).arg(stream[id].ip).arg(stream[id].port)
				.arg(stream[id].protocol).arg(stream[id].switchTS);
		}
	}
}

QString Hdmioptiongui::getHostIpAddress(void)
{
	QString strIpAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// 获取第一个本主机的IPv4地址
	int nListSize = ipAddressesList.size();
	for (int i = 0; i < nListSize; ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			strIpAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	// 如果没有找到，则以本地IP地址为IP
	if (strIpAddress.isEmpty())
		strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
	qDebug() << "local PC ip:" << strIpAddress;
	return strIpAddress;
}

u8 Hdmioptiongui::getNetworkSegment(QString ip)
{
	int tmp[4] = { 0 };
	u8 NetSeg = 0;
	char *chip = ip.toLatin1().data();
	sscanf(chip, "%d.%d.%d.%d", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
	NetSeg = (u8)tmp[2];
	qDebug("NetworkSegment:%d", NetSeg);
	return NetSeg;
}

void Hdmioptiongui::on_btn_Run_clicked()
{
	if (1 != comchangeflg) {
		return;
	}
	if ((udpfd < 3) || (selecttunerflg == 0)) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}

	if (mode != 0) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device is busy,please wait..    "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}

	//get ui vaule
	memset(Pname, '\0', sizeof(Pname));
	QString str = GetProgrameName;
	QByteArray ba = str.toLatin1();
	char *ch = ba.data();
	int i = 0;
	while (ch[i] != '\0') {
		Pname[i] = (unsigned char)(ch[i]);
		i++;
	}
	int level[6] = { 30,31,32,40,41,42 };

	PNo = GetProgrameNo;
	Vpid = GetVpid;
	Apid = GetApid;
	Pmt = GetPmt;
	Pcr = GetPcr;
	HpFile = GetHprofile;
	HpLevel = level[GetHlevel];
	PixW = GetW;
	PixH = GetH;
	BitRate = GetAvBR;
	Frame = GetFrame;
	MuteEn = GetMute;
	//4.aout and afreq
	audio_parameter[0] = GetAFre;
	if (QMessageBox::No == QMessageBox::question(this, tr("question"),
		tr("Apply?                                      "),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::No)) {
		return;
	}
	mode = 6;
	return;
}

void Hdmioptiongui::on_btn_Restart_clicked()
{
	if (1 != comchangeflg) {
		return;
	}
	if (udpfd < 3) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	if (mode != 0) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device is busy,please wait..    "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	if (QMessageBox::No == QMessageBox::question(this, tr("question"),
		tr("Restart?                                      "),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::No)) {
		return;
	}

	mode = 10;

	return;

}

void Hdmioptiongui::on_btn_Set_clicked()
{
	if (1 != comchangeflg) {
		return;
	}
	if (udpfd < 3) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	if (mode != 0) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device is busy,please wait..    "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	int i = 0;
	int j = 0;
	int parameterbuf[16] = { 0 };
	memset(parameterbuf, 0, 16);
	if (0 == isIPSettingFlg) {
		//循环读取数据
		for (i = 0; i < 16; i++) {
			if (-1 != netf[col_n]->Item_tuner[i]) {
				if (tabWS->item(j, 0) != NULL) {               //一定要先判断非空，否则会报错
					sf[i].ip = tabWS->item(j, 0)->text();
					sf[i].port = tabWS->item(j, 1)->text().toInt();
				}

				QWidget * comboxW2 = tabWS->cellWidget(j, 2);//获得widget
				QComboBox *combox2 = (QComboBox*)comboxW2;//强制转化为QComboBox   
				sf[i].nullpacked = combox2->currentIndex();

				QWidget * comboxW3 = tabWS->cellWidget(j, 3);//获得widget
				QComboBox *combox3 = (QComboBox*)comboxW3;//强制转化为QComboBox   
				sf[i].protocol = combox3->currentIndex();

				QWidget * cheBoxW4 = tabWS->cellWidget(j, 4);//获得widget
				QCheckBox *cheBox4 = (QCheckBox *)cheBoxW4->children().at(1);
				sf[i].switchTS = cheBox4->isChecked();
				qDebug("sf[%d].switchTS  = %d", i, sf[i].switchTS);
				sf[i].streamStatus = 0;
				j++;
				//	qDebug()<<"tar ip2:"<< sf[i].ip;
				qDebug("set sf[%d].nullpacked = %d", i, sf[i].nullpacked);

			}
		}

		if (QMessageBox::No == QMessageBox::question(this, tr("question"),
			tr("Apply?                                      "),
			QMessageBox::No | QMessageBox::Yes,
			QMessageBox::No)) {
			return;
		}
		packetsize = (u8)(ui->com_PacketSize->itemData(GetPacketSize).toInt());
		mode = 5;
	}
	else if (1 == isIPSettingFlg) {
		//	if (udpfd < 3) {
		//	    netdevno = ui->com_Netlist->currentIndex();
		//		tbs.useless(netf[netdevno]->ipaddr, netf[netdevno]->ipport);
		//		typeId = 6316;
		//		udpfd = tbs.udpOpen(netf[netdevno]->ipaddr, netf[netdevno]->ipport);
		//	}
			//1.local net ip 100M
		char * netipCh_100M = Get_100M_Ip.toLatin1().data();
		sscanf(netipCh_100M, "%d.%d.%d.%d:%d", &parameterbuf[0], \
			&parameterbuf[1], &parameterbuf[2], &parameterbuf[3], &parameterbuf[4]);
		//2.local net port
		parameterbuf[5] = parameterbuf[4] % 256;
		parameterbuf[4] = (parameterbuf[4] / 256);
		parameterbuf[7] = 0;

		char *netmask_100M = ui->lin_100M_Mask->text().toLatin1().data();
		sscanf(netmask_100M, "%d.%d.%d.%d", &parameterbuf[8], \
			&parameterbuf[9], &parameterbuf[10], &parameterbuf[11]);
		char *netgateway_100M = ui->lin_100M_Gateway->text().toLatin1().data();
		sscanf(netgateway_100M, "%d.%d.%d.%d", &parameterbuf[12], \
			&parameterbuf[13], &parameterbuf[14], &parameterbuf[15]);

		/**
		//3.local net mac
		char * netmacCh_100M = Get_100M_NetSn.toLatin1().data();
		sscanf(netmacCh_100M, "%02x:%02x:%02x:%02x:%02x:%02x", &parameterbuf[8], \
			&parameterbuf[9], &parameterbuf[10], &parameterbuf[11], &parameterbuf[12], \
			&parameterbuf[13]);
		**/

		for (i = 0; i < 16; i++) {
			Local_parameter_100M[i] = parameterbuf[i];
			qDebug("Local_parameter_100M[%d] = %d", i, Local_parameter_100M[i]);
		}

		memset(parameterbuf, 0, 16);


		//1.local net ip 1G
		char * netipCh_1G = Get_1G_Ip.toLatin1().data();
		sscanf(netipCh_1G, "%d.%d.%d.%d:%d", &parameterbuf[0], \
			&parameterbuf[1], &parameterbuf[2], &parameterbuf[3], &parameterbuf[4]);
		//2.local net port
		parameterbuf[5] = parameterbuf[4] % 256;
		parameterbuf[4] = (parameterbuf[4] / 256);
		parameterbuf[7] = ui->che_DHCP->isChecked();

		char *netmask_1G = ui->lin_1G_Mask->text().toLatin1().data();
		sscanf(netmask_1G, "%d.%d.%d.%d", &parameterbuf[8], \
			&parameterbuf[9], &parameterbuf[10], &parameterbuf[11]);
		char *netgateway_1G = ui->lin_1G_Gateway->text().toLatin1().data();
		sscanf(netgateway_1G, "%d.%d.%d.%d", &parameterbuf[12], \
			&parameterbuf[13], &parameterbuf[14], &parameterbuf[15]);

		/**
		//3.local net mac
		char * netmacCh_1G = Get_100M_NetSn.toLatin1().data();
		sscanf(netmacCh_1G, "%02x:%02x:%02x:%02x:%02x:%02x", &parameterbuf[8], \
			&parameterbuf[9], &parameterbuf[10], &parameterbuf[11], &parameterbuf[12], \
			&parameterbuf[13]);

		**/
		for (i = 0; i < 16; i++) {
			Local_parameter_1G[i] = parameterbuf[i];
			qDebug("Local_parameter_1G[%d] = %d", i, Local_parameter_1G[i]);
		}

		if (QMessageBox::No == QMessageBox::question(this, tr("question"),
			tr("Apply?                                      "),
			QMessageBox::No | QMessageBox::Yes,
			QMessageBox::No)) {
			return;
		}
		local_ip_port_mac_flg = 1;
		mode = 4;
	}
	return;
}

void Hdmioptiongui::on_sli_H_valueChanged(int value)
{
	qDebug() << value;
	fontsize = value;
	this->setStyleSheet(QString("font:%1pt;").arg(value));
	ui->labTitle->setFont(QFont("Microsoft Yahei", 9 + value));
	//qDebug()<<width<<"*"<<height;
	this->resize(width, height);
	ui->tree_Dev->setIconSize(QSize(10 + value, 10 + value));
}

void Hdmioptiongui::on_btn_Res_clicked()
{
	if (1 != comchangeflg) {
		return;
	}
	if ((udpfd < 3) || (selecttunerflg == 0)) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device not selected,or open fail"),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	if (mode != 0) {
		if (QMessageBox::Ok == QMessageBox::warning(this, tr("warn"),
			tr("Device is busy,please wait..  "),
			QMessageBox::Ok,
			QMessageBox::Ok)) {
			return;
		}
		return;
	}
	//get ui vaule
	memset(Pname, '\0', sizeof(Pname));
	workMode = 1;
	char showbuf[64];
	u8 bytes[6];
	tbs.target_ext_memory_rd_wt(READ, 0x80 * (tuner % 4) + 0x08, bytes, 6);
	sprintf(showbuf, "HDMI%02x%02x%02x", \
		bytes[3], bytes[4], bytes[5]);
	QString str = QString(showbuf);
	//qDebug(str);
	QByteArray ba = str.toLatin1();
	char *ch = ba.data();
	int i = 0;
	while (ch[i] != '\0') {
		Pname[i] = (unsigned char)(ch[i]);
		i++;
	}
	PNo = (u8)(tuner + 1);
	Vpid = 260 + 10 * tuner;
	Apid = 261 + 10 * tuner;
	Pmt = 262 + 10 * tuner;
	Pcr = 263 + 10 * tuner;
	MuteEn = 0;
	//1.aout and afreq
	audio_parameter[0] = 3;
	if (QMessageBox::No == QMessageBox::question(this, tr("question"),
		tr("Load Defaults?                              "),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::No)) {
		return;
	}
	loadflg = 1;
	mode = 6;
}
