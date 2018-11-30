#include "tbsfunc.h"
int netdevno = 0;
u8  tuner = 0;
u16 tbschipid = 0;
u8  rwbuf[RWNO] = { 0 };
int col = 0;
int col_n = 0;
u32 typeId = 0;
u8 local_ip_port_mac_flg = 0;
bool noSingleFlg = 0;
int isIPSettingFlg = 0;
u8 loadflg = 0;
bool maincpu = 0;
struct sockaddr_in udpsockaddr;
MATCH_IP mip[16] = { 0 };
int comchangeflg = 0;
int hstflg = 0; 
u8 netseg = 0;
int timeoutflg = 0;
int uncheckflg = 0;
int reflashflg = 0; 
int uselessflg = 0;
int selecttunerflg = 0;
#ifdef Q_OS_WIN //windows
SOCKET udpfd;
WSADATA wsaData;
int len = 0;
#else
int udpfd = 0;
socklen_t len = 0;
#endif
tbsfunc::tbsfunc()
{

}

tbsfunc::~tbsfunc()
{
}

void tbsfunc::REG64_rd(int subAddr, unsigned char num, unsigned char * rdbuffer)
{
	switch (typeId) {
	case 6316:
		udp_REG64_rd(subAddr, num, rdbuffer);
		break;
	case 63081:
		udp_REG64_rd_child(subAddr, num, rdbuffer);
		break;
	default:
		break;
	}
	return;
}
void tbsfunc::REG64_wt(int subAddr, unsigned char num, unsigned char * wtbuffer)
{
	switch (typeId) {
	case 6316:
		udp_REG64_wt(subAddr, num, wtbuffer);
		break;
	case 63081:
		udp_REG64_wt_child(subAddr, num, wtbuffer);
		break;
	default:
		break;
	}
	return;
}


unsigned char tbsfunc::check_host_free_REG64()
{
	unsigned char tmp_buff[8];
	int i = 0;

	do
	{
		REG64_rd(MAP_FPGA_BASEADDR + HOST_STATUS, 1, tmp_buff);
		//qDebug() <<"tmpbf = "<< tmp_buff[0];
		if ((tmp_buff[0] & 4) == 4)
		{
			QMSLEEP(2);
			i++;
		}
	} while (((tmp_buff[0] & 4) == 4) && (i < 1500));  //2 second timeout;

	if (i == 1500)
		return 0;  //host busy and timeout;
	else
		return 1;
}
//--------------------------------------------------------------------------------------------

unsigned char tbsfunc::Check_host_status_REG64(unsigned char status)
{
	unsigned char tmp_buff[8] = { 0 };
	int i = 0;

	do
	{
		REG64_rd(MAP_FPGA_BASEADDR + HOST_STATUS, 4, tmp_buff);
		//if (1 == networkflg) {
			//for(int i = 0;i < 4;i++)
			//	qDebug("tmp_buff[%d]:%#02x", i,tmp_buff[i]);
		//}
		if ((tmp_buff[0] & 1) != status)
		{
			QMSLEEP(3);
			i++;
		}

	} while (((tmp_buff[0] & 1) != status) && (i < 1500));  //3 second timeout;

	if (i == 1500)
		return 0;  // timeout;
	else
		return 1;
}
//--------------------------------------------------------------------------------------------

unsigned char tbsfunc::read_from_external_memory(int addr, unsigned char num, unsigned char *buff)
{
	unsigned char i, tmp_buff[8];

	if (num == 0)
	{
		qDebug(" read_from_external_memory parameter error! [num == 0]");
		return 0;
	}
	else if (num > 8)
	{
		qDebug(" read_from_external_memory parameter error! [num >8]");
		return 0;
	}
	for (i = 0; i < num; i++)
		buff[i] = 0xff;

	//check_host_free;...............................
	if (check_host_free_REG64() == 0)
	{
		qDebug(" wait for host free timeout! ");
		//return 0;
	}

	//read tag;
	tmp_buff[0] = 0x31;
	tmp_buff[1] = num;
	tmp_buff[2] = (unsigned char)(addr >> 8);
	tmp_buff[3] = (unsigned char)(addr & 255);
	REG64_wt(MAP_FPGA_BASEADDR + WRITE_CMD, 4, tmp_buff);

	//check_host_active;...............................
	if (Check_host_status_REG64(0) == 0)
	{
		qDebug(" wait for host active timeout!");
		//return 0;
	}
	qDebug("111111111111111111111");
	//release cs;
	REG64_wt(MAP_FPGA_BASEADDR + RELEASE_CS, 1, tmp_buff);

	qDebug("222222222222222222");

	//check host work done;...........................
	if (Check_host_status_REG64(1) == 0)
	{
		qDebug("wait for host work done timeout!");
		//return 0;
	}
	qDebug("333333333333");

	//read back;
	//REG64_rd(MAP_FPGA_BASEADDR + READ_DATA, num, buff);

	return 1;
}
//--------------------------------------------------------------------------------------------

unsigned char tbsfunc::write_to_external_memory(int addr, unsigned char num, unsigned char *buff)
{
	unsigned char i, tmp_buff[8];

	if (num > 8)
	{
		qDebug(" write_to_external_memory parameter error! [num >8]");
		return 0;
	}

	//check_host_free;...............................
	if (check_host_free_REG64() == 0)
	{
		qDebug(" wait for host free timeout!");
		return 0;
	}

	if (num != 0)
	{
		for (i = 0; i < num; i++)
			tmp_buff[i] = buff[i];
		REG64_wt(MAP_FPGA_BASEADDR + WRITE_DATA, num, tmp_buff);
	}

	//write tag;
	tmp_buff[0] = 0x30;
	tmp_buff[1] = num;
	tmp_buff[2] = (unsigned char)(addr >> 8);
	tmp_buff[3] = (unsigned char)(addr & 255);
	REG64_wt(MAP_FPGA_BASEADDR + WRITE_CMD, 4, tmp_buff);

	//check_host_active;...............................
	if (Check_host_status_REG64(0) == 0)
	{
		qDebug(" wait for host active timeout!");
		//return 0;
	}

	//release cs;
	REG64_wt(MAP_FPGA_BASEADDR + RELEASE_CS, 1, tmp_buff);
	//0x11 ?= 0x55 5s

	if (-1 == checkI2cBusStatus()) {
		//	return 0;
	}
	if (Check_host_status_REG64(1) == 0)
	{
		qDebug("wait for host work done timeout!");
		return 1;
	}
	return 0;
}


void tbsfunc::HardRST()
{
	u32 t = typeId;
	typeId = 6316;
	u8 tmpbuf[4] = { 0xff,0xff,0xff,0xff };
	REG64_wt(0x4014, 4, tmpbuf);
	QMSLEEP(2000);
	tmpbuf[0] = 0x00;
	REG64_wt(0x4014, 4, tmpbuf);
	typeId = t;
	hstflg = 1;
}

bool tbsfunc::monopolizeCpu_w_REG64(int m_addr, unsigned char * wtbuff, unsigned char num)
{
	unsigned char i, tmp_buff[8];

	if (num > 8)
	{
		qDebug(" write_to_external_memory parameter error! [num >8]");
		return 0;
	}

	//check_host_free;...............................
	if (check_host_free_REG64() == 0)
	{
		qDebug(" wait for host free timeout!");
		return 0;
	}

	if (num != 0)
	{
		for (i = 0; i < num; i++)
			tmp_buff[i] = wtbuff[i];
		REG64_wt(MAP_FPGA_BASEADDR + WRITE_DATA, num, tmp_buff);
	}

	//write tag;
	tmp_buff[0] = 0x32;
	tmp_buff[1] = num;
	tmp_buff[2] = (unsigned char)(m_addr >> 8);
	tmp_buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(MAP_FPGA_BASEADDR + WRITE_CMD, 4, tmp_buff);

	//check_host_active;...............................
	if (Check_host_status_REG64(0) == 0)
	{
		qDebug(" wait for host active timeout!");
		//return 0;
	}

	//release cs;
	REG64_wt(MAP_FPGA_BASEADDR + RELEASE_CS, 1, tmp_buff);
	if (-1 == checkI2cBusStatus()) {
		//	return 0;
	}
	//check host work done;...........................
	if (Check_host_status_REG64(1) == 0)
	{
		qDebug("wait for host work done timeout!");
		return 0;
	}

	return 1;
}

bool tbsfunc::monopolizeCpu_r_REG64(int m_addr, unsigned char * rdbuff, unsigned char num)
{
	unsigned char i, tmp_buff[8];

	if (num == 0)
	{
		qDebug(" read_from_external_memory parameter error! [num == 0]");
		return 0;
	}
	else if (num > 8)
	{
		qDebug(" read_from_external_memory parameter error! [num >8]");
		return 0;
	}
	for (i = 0; i < num; i++)
		rdbuff[i] = 0xff;

	//check_host_free;...............................
	if (check_host_free_REG64() == 0)
	{
		qDebug(" wait for host free timeout! ");
		return 0;
	}

	//read tag;
	tmp_buff[0] = 0x33;
	tmp_buff[1] = num;
	tmp_buff[2] = (unsigned char)(m_addr >> 8);
	tmp_buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(MAP_FPGA_BASEADDR + WRITE_CMD, 4, tmp_buff);

	//check_host_active;...............................
	if (Check_host_status_REG64(0) == 0)
	{
		qDebug(" wait for host active timeout!");
		//return 0;
	}

	//release cs;
	REG64_wt(MAP_FPGA_BASEADDR + RELEASE_CS, 1, tmp_buff);

	//check host work done;...........................
	if (Check_host_status_REG64(1) == 0)
	{
		qDebug("wait for host work done timeout!");
		return 0;
	}
	//read back;
	REG64_rd(MAP_FPGA_BASEADDR + READ_DATA, num, rdbuff);

	return false;
}

int tbsfunc::reHdmi()
{
	u8 tmpbuf[4] = { 0 };
	target_ext_memory_rd_wt(WRITE, ADDRESS_HDMI(tuner % 4) + 0x08, tmpbuf, 1);
	return 0;
}


void tbsfunc::write_M23Register(int num, int* m23_addr, int* m23_data)
{
	unsigned char tmpM23addr[4];
	unsigned char tmpM23data[4];
	int i = 0;

	for (i = 0; i < num; i++)
	{
		tmpM23addr[0] = (*(m23_addr + i) & 0xff00) >> 8;
		tmpM23addr[1] = *(m23_addr + i) & 0xff;
		tmpM23addr[2] = 0;
		tmpM23addr[3] = 0;


		tmpM23data[0] = (*(m23_data + i) & 0xff00) >> 8;
		tmpM23data[1] = *(m23_data + i) & 0xff;
		tmpM23data[2] = 0;
		tmpM23data[3] = 0;
		target_ext_memory_rd_wt(WRITE, 0x80 * (tuner%4) + 0x20 + i * 4, tmpM23addr, 2);
		target_ext_memory_rd_wt(WRITE, 0x80 * (tuner%4) + 0x22 + i * 4, tmpM23data, 2);
		qDebug("addr:%04x  data:%04x", *(u16*)tmpM23addr, *(u16*)tmpM23data);

	}

	return;
}

bool tbsfunc::monopolizeCpu_r_REG32(int m_addr, unsigned char *rdbuff, unsigned char num)
{
	unsigned char i, buff[8];

	if (num == 0)
	{
		qDebug(" rd error! (num == 0) ");
		return 0;

	}
	else if (num > 8)
	{
		qDebug(" rd error! (num >8) ");
		return 0;

	}

	//...check host free -->......................
	if (Check_host_status(1) == 0)
	{
		qDebug(" wait for host free timeout!");
		return 0;
	}

	//...wt data & cs to low-->...................
	buff[0] = 0x33;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(0x4000 + 0 * 4, 4, buff);  //cs low;

										//...ck host received data & process-->........
	if (Check_host_status(0) == 0)
	{
		qDebug(" wait for host active timeout! ");
		//return 0;
	}

	//...cs high................................

	REG64_wt(0x4000 + 3 * 4, 4, buff);  //cs high;
	//...check host work done-->..................
	if (wait_for_host_workdone() == 0)
	{
		qDebug(" wait host work done timeout! ");
		return 0;
	}

	REG64_rd(0x4000 + 1 * 4, 4, &buff[0]);
	REG64_rd(0x4000 + 2 * 4, 4, &buff[4]);
	for (i = 0; i < num; i++)
		rdbuff[i] = buff[i];
	return 1;
}

int tbsfunc::monopolizeCpu_w_REG32(int m_addr, unsigned char *wtbuff, unsigned char num)
{
	unsigned char i = 0;
	unsigned char buff[8] = { 0 };

	if (num == 0)
	{
		qDebug(" wt error! (num == 0)  \n");
		return 0;

	}
	else if (num > 8)
	{
		qDebug(" wt error! (num >8) ");
		return 0;

	}
	//...check host free -->......................
	if (Check_host_status(1) == 0)
	{
		qDebug(" wait for host free timeout!");
		return 0;
	}
	//...wt data & cs to low-->...................
	for (i = 0; i < num; i++)
		buff[i] = wtbuff[i];
	REG64_wt(0x4000 + 2 * 4, 4, &buff[4]);
	REG64_wt(0x4000 + 1 * 4, 4, &buff[0]);

	buff[0] = 0x32;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(0x4000 + 0 * 4, 4, buff);  //cs low;

										//...ck host received data & process-->........
	if (Check_host_status(0) == 0)
	{
		qDebug(" wait for host active timeout! ");
		//return 0;
	}

	//...cs high................................

	REG64_wt(0x4000 + 3 * 4, 4, buff);  //cs high;

										//...check host work done-->..................
	if (wait_for_host_workdone() == 0)
	{
		qDebug(" wait host work done timeout! ");
		return 0;
	}
	return 1;
}

bool tbsfunc::monopolizeCpu_w(int m_addr, unsigned char * wtbuff, unsigned char num)
{
	switch (typeId) {
	case 63081:
	case 6316:
		return monopolizeCpu_w_REG32(m_addr, wtbuff, num);
		break;
	default:
		break;
	}
	return 1;
}

bool tbsfunc::monopolizeCpu_r(int m_addr, unsigned char * rdbuff, unsigned char num)
{
	switch (typeId) {
	case 63081:
	case 6316:
		return monopolizeCpu_r_REG32(m_addr, rdbuff, num);
		break;
	default:
		break;
	}
	return 1;
}

void tbsfunc::read_M23Register(int num, int* m23_data)
{
	unsigned char tmpM23data[4];
	int i = 0;

	for (i = 0; i < num; i++)
	{
		//read the data from register
		//read_24cxx( 0x22+i*4,2, tmpM23data);
		target_ext_memory_rd_wt(READ, 0x80 * (tuner %4) + 0x22 + i * 4, tmpM23data, 2);
		*(m23_data + i) = tmpM23data[1] & 0xff;
		*(m23_data + i) += ((tmpM23data[0] << 8) & 0xff00);
	}

	return;
}

//===............................................................................

unsigned char tbsfunc::ext_ram_write(int ram_addr, unsigned char *wtbff, int wt_size)
{
	int i, k, x8byte;
	unsigned char finishbyte;
	x8byte = wt_size / 8;
	finishbyte = (unsigned char)(wt_size & 7);

	//first send & remainder bytes.
	if (finishbyte == 0)
	{
		finishbyte = 8;
		x8byte -= 1;
	}
	ext_one_time_wt(ram_addr, wtbff, finishbyte);

	i = finishbyte;
	if (x8byte != 0)
	{
		for (k = 0; k < x8byte; k++)
			ext_one_time_wt((ram_addr + i + k * 8), &wtbff[i + k * 8], 8);
	}

	return 0;
}

//===............................................................................

unsigned char tbsfunc::ext_one_time_wt(int m_addr, unsigned char *wtbuff, unsigned char num) {
	switch (typeId) {
	case 63081:
	case 6316:
		return ext_one_time_wt_REG32(m_addr, wtbuff, num);
		break;
	default:
		break;
	}
	return 0;
}

unsigned char tbsfunc::ext_one_time_rd(int m_addr, unsigned char *rdbuff, unsigned char num) {
	switch (typeId) {
	case 63081:
	case 6316:
		return ext_one_time_rd_REG32(m_addr, rdbuff, num);
		break;
	default:
		break;
	}
	return 0;
}

unsigned char tbsfunc::ext_one_time_rd_REG32(int m_addr, unsigned char *rdbuff, unsigned char num)
{
	unsigned char i, buff[8];

	if (num == 0)
	{
		qDebug(" rd error! (num == 0)  ");
		return false;

	}
	else if (num > 8)
	{
		qDebug(" rd error! (num >8) ");
		return false;

	}
	//...check host free -->......................
	if (Check_host_status(1) == 0)
	{
		qDebug(" wait for host free timeout!");
		return false;
	}
	//...wt data & cs to low-->...................
	buff[0] = 0x31;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(0x4000 + 0 * 4, 4, buff);	  //cs low;

//	QMSLEEP(1);
	//...ck host received data & process-->........
	if (Check_host_status(0) == 0)
	{
		qDebug(" wait for host active timeout! ");
		REG64_wt(0x4000 + 3 * 4, 4, buff);	  //cs high;
		return false;
	}

	//...cs high................................
	REG64_wt(0x4000 + 3 * 4, 4, buff);	  //cs high;
	//...check host work done-->..................
	if (wait_for_host_workdone() == 0)
	{
		qDebug(" wait host work done timeout!");
		return false;
	}
	REG64_rd(0x4000 + 1 * 4, 4, &buff[0]);
	REG64_rd(0x4000 + 2 * 4, 4, &buff[4]);

	for (i = 0; i < num; i++)
		rdbuff[i] = buff[i];
	return true;
}
//===............................................................................


unsigned char tbsfunc::ext_one_time_wt_REG32(int m_addr, unsigned char *wtbuff, unsigned char num)
{
	unsigned char i, buff[8];

	if (num == 0)
	{
		qDebug(" wt error! (num == 0) ");
		return false;

	}
	else if (num > 8)
	{
		qDebug(" wt error! (num >8) ");
		return false;

	}
	//...check host free -->......................
	if (Check_host_status(1) == 0)
	{
		qDebug(" wait for host free timeout! ");
		return false;
	}

	//...wt data & cs to low-->...................
	for (i = 0; i < num; i++)
		buff[i] = wtbuff[i];
	REG64_wt(0x4000 + 2 * 4, 4, &buff[4]);
	REG64_wt(0x4000 + 1 * 4, 4, &buff[0]);

	buff[0] = 0x30;
	buff[1] = num;
	buff[2] = (unsigned char)(m_addr >> 8);
	buff[3] = (unsigned char)(m_addr & 255);
	REG64_wt(0x4000 + 0 * 4, 4, buff); //cs low;
	//QMSLEEP(1);
	//...ck host received data & process-->........
	if (Check_host_status(0) == 0)
	{
		qDebug(" wait for host active timeout!");
		REG64_wt(0x4000 + 3 * 4, 4, buff); //cs high;
		return false;
	}

	//...cs high................................
	REG64_wt(0x4000 + 3 * 4, 4, buff); //cs high;

	//...check host work done-->..................
	if (wait_for_host_workdone() == 0)
	{
		qDebug(" wait host work done timeout!");
		return false;
	}
	return true;
}


unsigned char tbsfunc::ext_ram_read(int ram_addr, unsigned char *rdbff, int rd_size)
{
	int i, k, x8byte;
	unsigned char finishbyte, buff[8];
	// qDebug("ram_addr:%#x\n",ram_addr);
	x8byte = rd_size / 8;
	finishbyte = (unsigned char)(rd_size & 7);
	//first send & remainder bytes.
	if (finishbyte == 0)
	{
		finishbyte = 8;
		x8byte -= 1;
	}
	ext_one_time_rd(ram_addr, rdbff, finishbyte);

	i = finishbyte;
	if (x8byte != 0)
	{
		for (k = 0; k < x8byte; k++)
			ext_one_time_rd((ram_addr + i + k * 8), &rdbff[i + k * 8], 8);
	}

	return 0;
}

unsigned char tbsfunc::target_ext_memory_rd_wt(unsigned char tg_mode,
	int tg_addr,
	unsigned char *buff,
	int tg_size)
{
	if (tg_mode == READ) {

		return ext_ram_read(tg_addr, buff, tg_size);
	}
	else if (tg_mode == WRITE) {

		return ext_ram_write(tg_addr, buff, tg_size);

	}
	else
		qDebug("[target_external_memory_rd_wt] read write mode error!");
	return 0;
}


int tbsfunc::udp_checkI2cBusStatus()
{
	u8 tmpbuf[8] = { 0 };
	int i = 0;
	udp_REG64_wt(0xfff5, 8, tmpbuf);
	memset(tmpbuf, 0, 8);
	udp_REG64_rd(0xfff5, 8, tmpbuf);
	for (i = 0; i < 8; i++) {
		if (0x80 != (u8)tmpbuf[i]) {
			qDebug() << "udp check i2c bus status is busy !!!";
			return -1;
		}
	}
	return 0;
}

int tbsfunc::checkI2cBusStatus()
{
	switch (typeId) {
	case 5301:
		return udp_checkI2cBusStatus();
		break;
	default:
		break;
	}
	return -1;
}

int tbsfunc::reRunNetWork()
{
	//fe00  ==> rerunnetwork
	u8 tmpbuf[4] = { 0 };
	target_ext_memory_rd_wt(WRITE, 0xff10, tmpbuf, 1);
	return 0;
}


int tbsfunc::reRtpUdpStreaming()
{
	u8 tmpbuf[4] = { 0 };
	target_ext_memory_rd_wt(WRITE, 0xff18, tmpbuf, 1);

	return 0;
}



void tbsfunc::udp_REG64_rd(int subAddr, unsigned char num, unsigned char * rdbuffer)
{
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	int n = 0;
	int j = 0;
	// 27bit address
	sendbuff[0] = 0xc0 + (u8)((subAddr & 0x07000000) >> 24);
	sendbuff[1] = (u8)((subAddr & 0x00ff0000) >> 16);
	sendbuff[2] = (u8)((subAddr & 0x0000ff00) >> 8);
	sendbuff[3] = (u8)((subAddr & 0x000000ff));

	//sendbuff[2] = 0x80;
	//sendbuff[3] = 0x20;
	n = sendto(udpfd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
		qDebug() << "udp_REG64_rd:sendto time out";
		return;
	}
	n = recvfrom(udpfd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
		qDebug() << "udp_REG64_rd:recvfrom3 time out";
		return;
	}
	for (int i = 0; i < 12; i++) {
		//	qDebug("udp_REG64_rd recv:%d=%02x", i, (u8)recvbuff[i]);
		if ((i > 3) && (j < num)) {
			rdbuffer[j] = (u8)recvbuff[i];
			j++;
		}
	}
	return;
}

void tbsfunc::udp_REG64_wt(int subAddr, unsigned char num, unsigned char * wtbuffer)
{
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	int n = 0;
	int i = 0;
	int j = 0;

	// 27bit address
	sendbuff[0] = 0x00 + (u8)((subAddr & 0x07000000) >> 24);
	sendbuff[1] = (u8)((subAddr & 0x00ff0000) >> 16);
	sendbuff[2] = (u8)((subAddr & 0x0000ff00) >> 8);
	sendbuff[3] = (u8)((subAddr & 0x000000ff));

	for (i = 0; i < num; i++) {
		sendbuff[i + 4] = wtbuffer[i];
	}
	n = sendto(udpfd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
		qDebug() << "udp_REG64_wt:sendto time out";
		return;
	}

	memset(recvbuff, 0, 64);
	n = recvfrom(udpfd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
		qDebug() << "udp_REG64_wt:recvfrom time out";
		return;
	}
	for (int i = 0; i < 12; i++) {
		//qDebug("udp_REG64_wt:recv:%d=%02x", i, (u8)recvbuff[i]);
	}
	return;
}

void tbsfunc::udp_REG64_rd_child(int subAddr, unsigned char num, unsigned char * rdbuffer)
{
	unsigned char i, tmp[8];
	if (num == 0)
	{
		qDebug(" rd error! (num == 0)  ");
		return;
	}
	else if (num > 4)
	{
		qDebug(" rd error! (num >4) ");
		return;

	}
	tmp[0] = 0x80;//read; bit7 = 1;
	tmp[1] = 0; //don't care; 
	tmp[2] = (unsigned char)((subAddr >> 8) & 0xff);	 //address high;
	tmp[3] = (unsigned char)(subAddr & 0xff); 		 //address low;
	udp_REG64_wt(NET_100M_ADDR((tuner / 4)) + NET100M_CMD, 4, tmp);
	// ack done;
	i = 0;
	do {
		udp_REG64_rd(NET_100M_ADDR((tuner / 4)) + NET100M_ACK, 4, tmp);
		QMSLEEP(1);
		i++;
		//} while ((i < 200) && (tmp[0] == 255));
	} while ((i < 200) && (tmp[0] != 0x83));

	if (i == 200)
	{
		qDebug("[udp_REG64_rd_child] check udp_cmd done timeout, Exit!");
		return;
	}
	udp_REG64_rd(NET_100M_ADDR((tuner / 4)) + NET100M_RDDT, num, rdbuffer);
	for (int j = 0; j < 4; j++) {
		//qDebug("r:%d", rdbuffer[j]);
	}
	return;
}

void tbsfunc::udp_REG64_wt_child(int subAddr, unsigned char num, unsigned char * wtbuffer)
{
	unsigned char i, tmp[8];
	if (num == 0)
	{
		qDebug(" wt error! (num == 0)  ");
		return;
	}
	else if (num > 4)
	{
		qDebug(" wt error! (num >4) ");
		return;

	}
	for (int j = 0; j < 4; j++) {
		//qDebug("w:%d", buff[j]);
	}
	udp_REG64_wt(NET_100M_ADDR((tuner / 4)) + NET100M_DT32, num, wtbuffer);
	tmp[0] = 0; //write; bit7 = 0;
	tmp[1] = 0; //don't care; 
	tmp[2] = (unsigned char)((subAddr >> 8) & 0xff);	 //address high;
	tmp[3] = (unsigned char)(subAddr & 0xff); 		 //address low;
	udp_REG64_wt(NET_100M_ADDR((tuner / 4)) + NET100M_CMD, 4, tmp);
	// ack done;
	i = 0;
	do {
		udp_REG64_rd(NET_100M_ADDR((tuner / 4)) + NET100M_ACK, 4, tmp);
		QMSLEEP(1);
		i++;
		//	} while ((i < 200) && (tmp[0] == 255));
	} while ((i < 200) && (tmp[0] != 0x83));

	if (i == 200)
	{
		qDebug("[udp_REG64_wt_child] check udp_cmd done timeout, Exit!");
		return;
	}
	return;
}

bool tbsfunc::Check_host_status(unsigned char cs)
{
	unsigned char j, tmp[4];
	int i;
	int count = 0;
	int time =4000;
	bool ret = 0;
	//if (1 == uselessflg) {
	//	time = 10;
	//}

	j = 1;
	for (i = 0; ((i < time) && j); i++)
	{
		REG64_rd(0x4000 + 0 * 4, 4, tmp);
		if ((tmp[0] & 1) != cs)
		{
			j = 1;
			ret = 0;
			QMSLEEP(1); //delay 500uS;
					  //        count++;
		}
		else {
			ret = 1;
			j = 0;
		}
	}
	//   qDebug("ctime: %d us\n", count*500);
	//return (j != 4000);
	return ret;
}

bool tbsfunc::wait_for_host_workdone()  //3 seconds timeout;
{
	unsigned char j, tmp[4];
	int i;
	int count = 0;
	bool ret = 0;
	int time = 600;
	j = 0;
	//if (1 == uselessflg) {
	//	time = 10;
	//}
	for (i = 0; ((i < time) && (j == 0)); i++)
	{
		REG64_rd(0x4000 + 0 * 4, 4, tmp);
		j = (tmp[0] & 1);
		if (j == 0) {
			QMSLEEP(5);  //delay 5mS
			//		      count ++;
			ret = 0;
		}
		else {
			ret = 1;
		}
	}
	   // qDebug("wtime: %d ms\n", count*5);
	//return (j != 600);
	return ret;
}

u8 tbsfunc::mcu_is_busy()
{
	u8 tmp[4] = { 0 };
	int typeIdcpy = typeId;
	typeId = 63081;
	REG64_rd(0x4000 + 0x0c, 1, tmp);
	typeId = typeIdcpy;
	return (tmp[0] & 0x80);
}

#ifdef Q_OS_WIN //windows
SOCKET tbsfunc::udpOpen(QString ipaddr, int ipport)
{
	SOCKET ufd;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	int timeout = 3000;
#else

int tbsfunc::udpOpen(QString ipaddr, int ipport)
{
	int ufd = 0;
	struct timeval timeout = { 3,0 };
#endif
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	/*create Socket*/
	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		qDebug() << "fail to socket";
		return 0;
	}

	/*set sockaddr_in*/
	memset(&udpsockaddr, 0, sizeof(udpsockaddr));
	udpsockaddr.sin_family = AF_INET;
	udpsockaddr.sin_port = htons(ipport);
	udpsockaddr.sin_addr.s_addr = inet_addr(ipaddr.toStdString().data());
	len = sizeof(udpsockaddr);
	setsockopt(ufd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(ufd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	/**
	int n = 0;

	//1.begin w 0x0fff5
	sendbuff[0] = 0x00;
	sendbuff[1] = 0x00;
	sendbuff[2] = 0xff;
	sendbuff[3] = 0xf5;

	n = sendto(ufd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
	qDebug() << "sendto1 time out";
	return 0;
	}

	memset(recvbuff, 0, 64);

	n = recvfrom(ufd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
	qDebug() << "recvfrom1 time out";
	return 0;
	}

	//2.r 0x0fff5
	sendbuff[0] = 0xc0;
	sendbuff[1] = 0x00;
	sendbuff[2] = 0xff;
	sendbuff[3] = 0xf5;

	n = sendto(ufd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
	if (n < 0) {
	qDebug() << "sendto2 time out";
	return 0;
	}

	//3.wait 3s=> recv 64'h8080_8080_8080_8080 is ok,64'h0505_0505_0505_0505 is busy
	memset(recvbuff, 0, 64);
	n = recvfrom(ufd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
	if (n < 0) {
	qDebug() << "recvfrom2 time out";
	return 0;
	}
	u8 tmpbuf[8] = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };
	int j = 0;
	for (int i = 0; i < 12; i++) {
	if (tmpbuf[j] == (u8)recvbuff[i]) {
	if (8 == ++j) {
	qDebug() << "Getting right to use is successful";
	break;
	}
	}
	}
	if (j < 8) {
	qDebug() << "Getting right to use is failed ";
	return 0;
	}
	*/
	return ufd;
}

#ifdef Q_OS_WIN //windows
SOCKET tbsfunc::udpClose(SOCKET ufd)
{
#else
int tbsfunc::udpClose(int ufd)
{
#endif
	int n = 0;
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	len = sizeof(udpsockaddr);
	if (ufd > 2) {
		/*
		//5.end=> w 0xfffa free dev
		sendbuff[0] = 0x00;
		sendbuff[1] = 0x00;
		sendbuff[2] = 0xff;
		sendbuff[3] = 0xfa;
		n = sendto(ufd, sendbuff, 64, 0, (struct sockaddr*)&udpsockaddr, len);
		if (n < 0) {
		qDebug() << "sendto4 time out";
		return 0;
		}

		memset(recvbuff, 0, 64);
		n = recvfrom(ufd, recvbuff, 64, 0, (struct sockaddr*)&udpsockaddr, &len);
		if (n < 0) {
		qDebug() << "recvfrom4 time out";
		return 0;
		}
		*/
#ifdef Q_OS_WIN //windows
		closesocket(ufd);
		WSACleanup();
#else
		::close(ufd);
#endif
		return 0;
	}
	return ufd;
}


#ifdef Q_OS_WIN //windows
SOCKET tbsfunc::udpOpen_no(QString ipaddr, int ipport)
{
	SOCKET ufd;
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	int timeout = 0;
	unsigned long ul = 1;
#else

int tbsfunc::udpOpen_no(QString ipaddr, int ipport)
{
	int ufd = 0;
	struct timeval timeout = { 0,0 };
#endif
	char sendbuff[64] = { 0 };
	char recvbuff[64] = { 0 };
	/*create Socket*/
	if ((ufd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		qDebug() << "fail to socket";
		return 0;
	}
	/*set sockaddr_in*/
	memset(&udpsockaddr, 0, sizeof(udpsockaddr));
	udpsockaddr.sin_family = AF_INET;
	udpsockaddr.sin_port = htons(ipport);
	udpsockaddr.sin_addr.s_addr = inet_addr(ipaddr.toStdString().data());
	len = sizeof(udpsockaddr);
	//setsockopt(ufd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	//setsockopt(ufd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
#ifdef Q_OS_WIN //windows
	ioctlsocket(ufd, FIONBIO, (unsigned long *)&ul);//设置成非阻塞模式。

#else
	int flag = fcntl(ufd, F_GETFL, 0);
	flag |= O_NONBLOCK;
	if (fcntl(ufd, F_SETFL, flag) < 0)
	{
		qDebug("fcntl");
		return ufd;

	}
#endif 
	//if (ret == SOCKET_ERROR)//设置失败。

	//{
	//	return ufd;
	//}

	return ufd;
}

int  tbsfunc::matchIp(QString ip, int port, int c)
{

	u8 M[14] = { 0 };
	int i = 0;
	int ret = 0;
	memset(M, 0, 14);
	useless(ip, port);

	//qDebug("%s:%d", ip.toLatin1().data(), port);
	udpfd = udpOpen(ip.toLatin1().data(), port);
	typeId = 6316;
	target_ext_memory_rd_wt(READ, 0x80 + 0x00, M, 14);//100m
	M[6] = M[4];
	QString  qst;
	qst.sprintf("%d.%d.%d.%d", M[0], M[1], M[2], M[3]);
	QString  macqst;
	macqst.sprintf("%02x:%02x:%02x:%02x:%02x:%02x", M[8], M[9], M[10], M[11], M[12], M[13]);
	for (i = 0; i < c; i++) {
		qDebug() << qst << "========" << macqst << "=====" << *(u16*)&M[5] << "====" << mip[i].ip << "====" << mip[i].mac << "======" << mip[i].port;
		if ((qst == mip[i].ip) && (mip[i].port == *(u16*)&M[5]) && (mip[i].mac == macqst)) {
			ret = 0;
		}
		else {
			ret = -1;
		}
	}
	udpClose(udpfd);
	udpfd = 0;
	typeId = 0;
	return ret;

}
int tbsfunc::get_1000M_or_100M(QString ip, int port)
{
	u8 M[8] = { 0 };
	int i = 0;
	int j = 0;
	udpfd = udpOpen(ip.toLatin1().data(), port);
	memset(M, 0, 8);
	udp_REG64_rd(0x4000 + 24, 1, M);
	udpClose(udpfd);
	udpfd = 0;
	typeId = 0;
	return (M[0] & 0x01);
}

int tbsfunc::getNetMac(QString ip, int port, u8 * mac, int g)
{
	int offset = 0;
	udpfd = udpOpen(ip.toLatin1().data(), port);
	if (0 == g) {
		offset = 0x80;
	}
	else if (1 == g) {
		offset = 0;
	}
	//0. 0x00 ~0x27
	typeId = 6316;
	target_ext_memory_rd_wt(READ, 0x00 + 0x08 + offset, mac, 6);
	udpClose(udpfd);
	udpfd = 0;
	typeId = 0;
	return 0;
}

int tbsfunc::useless(QString ip, int port)
{
	u8 a = 0;
	udpfd = udpOpen_no(ip.toLatin1().data(), port);
	typeId = 6316;
	//uselessflg = 1;
	qDebug("********useless**01*********");
	target_ext_memory_rd_wt(READ, 0x00, &a, 1);
	qDebug("********useless**02*********");
	//uselessflg = 0;
	udpClose(udpfd);
	udpfd = 0;
	typeId = 0;
	return 0;
}









