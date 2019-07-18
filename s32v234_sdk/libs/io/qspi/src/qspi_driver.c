/*
 * qspi_driver.c
 *
 *
 *  Created on: 24 May 2015
 *      Author: Marie-Anne Le Menn
 *
 *  Comments: Based on driver for Halo developped by Ioseph Martinez
 */

#include "qspi_driver.h"


#define QSPI_FREQ

void quadspi_switch(unsigned int mode)
{
	SIUL2.MSCR[5].B.MUX_MODE = 0;	// GPIO mux mode selected
    SIUL2.MSCR[5].B.OBE = 1;		// output buffer enabled
    SIUL2.MSCR[5].B.DSE = 7;		// Drive Strenght
	
	if (mode == SWITCH_QSPI)
		SIUL2.GPDO[1].B.PDO_4n1 = 0; 
	else if (SWITCH_SD)
		SIUL2.GPDO[1].B.PDO_4n1 = 1; 
}

void QSPI_setup_hyp()
{
	uint32_t i;

//	MC_CGM_0.AC14_SC.B.SELCTL = 4; /* set ENET_PLL_DFS_3 as source  */
//	MC_CGM_0.AC14_DC0.R = 0x80070000; /* Division by 8 (i.e. 40MHz) */
	MC_CGM_0.AC14_SC.B.SELCTL = 1; /* set XOSRC as source  */
	MC_CGM_0.AC14_DC0.R = 0x80000000; /* Division by 0 (Strangely got 10Mhz instead of 40Mhz, to be verified with design) */


	SIUL2.MSCR[150].R = 0x0020D701;//0x0020C301; //QSPI0_A_SCK - V25 - PK6
	SIUL2.MSCR[149].R = 0x0020D701;//0x0020FF01;//0x0029F301; //QSPI0_A_CS0 w Pull up enabled - U25 - PK5

	SIUL2.MSCR[155].R = 0x0028D701; //0x0028C301; //QSPI0_A_D3 - V22 - PK11
	SIUL2.IMCR[823 - 512].R =  0x00000002;
	SIUL2.MSCR[154].R = 0x0028D701; //0x0028C301;//QSPI0_A_D2 - V21 - PK10
	SIUL2.IMCR[822 - 512].R =  0x00000002;
	SIUL2.MSCR[153].R = 0x0028D701; //0x0028C301;  //QSPI0_A_D1 - U23 - PK9
	SIUL2.IMCR[821 - 512].R =  0x00000002;
	SIUL2.MSCR[152].R = 0x0028D701; //0x0028C301;  //QSPI0_A_D0 - V23 - PK8
	SIUL2.IMCR[820 - 512].R =  0x00000002;

	SIUL2.MSCR[151].R = 0x0009E000;	// 0x0008D700; //QSPI0_A_DQS - U22 - PK7
	SIUL2.IMCR[819 - 512].R =  0x00000002;

	//SIUL2.MSCR[156].R = 0x0020D701;//0x0029F001; //QSPI0_B_CS0 w Pull up enabled - W25 - PK12

	SIUL2.MSCR[162].R = 0x0028D702; //0x0028C302; //QSPI0_B_D3	- R21 - PL2
	SIUL2.IMCR[827 - 512].R =  0x00000002;
	SIUL2.MSCR[161].R = 0x0028D702; //0x0028C302; //QSPI0_B_D2 - U24 - PL1
	SIUL2.IMCR[826 - 512].R =  0x00000002;
	SIUL2.MSCR[160].R = 0x0028D702; //0x0028C302; //QSPI0_B_D1 - U21 - PL0
	SIUL2.IMCR[825 - 512].R =  0x00000002;
	SIUL2.MSCR[159].R = 0x0028D702; //0x0028C302; //QSPI0_B_D0 - W23 - PK15
	SIUL2.IMCR[824 - 512].R =  0x00000002;
	SIUL2.MSCR[157].R = 0x0020D702; //0x0028C302; //QSPI0_CK# - B_SCK- V24 - PK13


	QuadSPI.MCR.B.MDIS = 0; //clear MDIS bit
	QuadSPI.BUF0IND.R = 0x0; //set AHB buffer size (64bits)
	QuadSPI.SFA1AD.R = FLASH_BASE_ADR + 0x4000000; //set top address of FA1 (size 512Mbit)
	QuadSPI.SFA2AD.R = FLASH_BASE_ADR + 0x4000000;  //set top address of FA2 (size 0Mbit)
	QuadSPI.SFB1AD.R = FLASH_BASE_ADR2 + 0x4000000;  //set top address of FB1 (size 512Mbit)
	QuadSPI.SFB2AD.R = FLASH_BASE_ADR2 + 0x4000000;  //set top address of FB2 (size 0Mbit) 0x203FFFFF

	QuadSPI.BUF0IND.R = 0x100; /* buffer0 size 512 bytes */
	QuadSPI.BUF1IND.R = 0x200; /* buffer1 size 0 bytes */
	QuadSPI.BUF2IND.R = 0x200; /* buffer2 size 0 bytes */
	QuadSPI.BUF3CR.R = 0x80000000;/* All masters use buffer 3 */

	QuadSPI.SFAR.R = FLASH_BASE_ADR;
	QuadSPI.MCR.B.DDR_EN = 1;
	QuadSPI.MCR.B.DQS_EN = 1;
	QuadSPI.SFACR.R = 0x00010003;
	QuadSPI.MCR.B.DQS_LAT_EN = 1;
	QuadSPI.FLSHCR.B.TDH=1;



	/* Set-up Read command for hyperflash */
	quadspi_read_hyp();	// The command will be used by default for any AHB access to the flash memory

} /* QSPI_setup */

//sector = -1 means chip erase
void quadspi_erase_hyp(int sector)
{
	unsigned int cmd;
	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xAA);
	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0x554,0x55);

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0x80);
	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xAA);

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0x554,0x55);

	if(sector == -1)	quadspi_send_instruction_hyp(FLASH_BASE_ADR+ 0xAAA,0x10);
	else				quadspi_send_instruction_hyp((sector&0xfffffffe),0x30);

	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);
}


void quadspi_program_word_hyp(unsigned int address, unsigned int word)
{
	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xAA);
	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0x554,0x55);

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xA0);
	quadspi_send_instruction_hyp(address,word);

	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);
}

void quadspi_program_hyp(unsigned int address, unsigned int *data, unsigned int bytes)
{
	int i,j,k,m;	// i: number total of bytes to flash	// k: number of bytes to flash at the next command	// m :number of word (16 bits) to flash at the next command
	unsigned int reg;
	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);

	address = (address&0xfffffffe);
	i = bytes&0xFFFFFFFE;
	if((address %128)!=0){
		k = 128 -(address %128);
	}
	else if(i>128) k = 128;
	else k = i;


	m = k>>2;
	if(k&3)	m++;

	//reduce frequency
	//reg = MC_CGM.AC8_DC0.R;
	//MC_CGM.AC8_DC0.R = 0x80020000; /* divide by 4 */
	do {

		quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xAA);
		quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0x554,0x55);
		quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0xA0);

		//prepare write/program instruction
		QuadSPI.SFAR.R = address;
		quadspi_set_lut(60,QSPI_LUT(ADDR_DDR,3,0x18,CMD_DDR,3,0x00));
		quadspi_set_lut(61,QSPI_LUT(WRITE_DDR,3,2,CADDR_DDR,3,0x10));
		quadspi_set_lut(62,0);
		// tx buffer
		QuadSPI.MCR.B.CLR_TXF = 1;
		QuadSPI.FR.R = 0x08000000;
		// load write data
		for(j = 0; j<m; j++)	QuadSPI.TBDR.R = *data++;
		QuadSPI.IPCR.R = (15 << 24) | (k); //send the write command
		while(QuadSPI.SR.R & QuadSPI_SR_BUSY_MASK);	//wait for cmd to be sent
		while((quadspi_status_hyp()&0x8000)==0);		//check status, wait to be done

		address += k;

		i -= k;
		if(i>128) k = 128;
		else k = i;
//		k = 128;
		m = 32;
	} while(i > 0);

	//restore
	//MC_CGM.AC8_DC0.R = reg;
	//check status, wait to be ready
	while((quadspi_status_hyp()&0x8000)==0);

}

void quadspi_read_hyp(void)
{
	quadspi_set_lut(0,QSPI_LUT(ADDR_DDR,3,24,CMD_DDR,3,0xA0));
	quadspi_set_lut(1,QSPI_LUT(DUMMY,3,15,CADDR_DDR,3,16));
	quadspi_set_lut(2,QSPI_LUT(STOP,3,0,READ_DDR,3,128));
	QuadSPI.BFGENCR.R = 0x00000;
}

void quadspi_read_ip_hyp(unsigned long address, unsigned long *dest, unsigned long bytes)
{
	int i,j,k,m;
	QuadSPI.SFAR.R = address&0xFFFFFFFE; //clear less significative bit
	quadspi_set_lut(60,QSPI_LUT(ADDR_DDR,3,24,CMD_DDR,3,0xA0));
	quadspi_set_lut(61,QSPI_LUT(DUMMY,3,15,CADDR_DDR,3,16));
	quadspi_set_lut(62,QSPI_LUT(STOP,0,0,READ_DDR,3,128));

	i = bytes&0xFFFFFFFE;
	k = i%128;
	if(k == 0)	k = 128;

	m = k>>2;
	if(k&3)	m++;

	do {
		QuadSPI.MCR.B.CLR_RXF = 1;
		QuadSPI.FR.R = 0x10000;
		QuadSPI.IPCR.R = (15 << 24) | (k); //fill the RX buffer
		while(QuadSPI.SR.R & QuadSPI_SR_BUSY_MASK);	//wait for cmd to be sent
		while(QuadSPI.RBSR.B.RDBFL != m);	//wait for buffer to be filled

		for(j = 0; j<m; j++)	*dest++ = QuadSPI.RBDR[j].R;

		QuadSPI.SFAR.R = QuadSPI.SFAR.R + (k);
		i -= k;
		k = 128;
		m = 32;
	} while(i > 0);
}

unsigned int quadspi_status_hyp(void)
{
	unsigned int i,data;

	quadspi_send_instruction_hyp(FLASH_BASE_ADR + 0xAAA,0x70);

	QuadSPI.SFAR.R = FLASH_BASE_ADR + 0x2;
	quadspi_set_lut(60,QSPI_LUT(ADDR_DDR,3,0x18,CMD_DDR,3,0x80));
	quadspi_set_lut(61,QSPI_LUT(DUMMY,3,15,CADDR_DDR,3,0x10));
	quadspi_set_lut(62,QSPI_LUT(STOP,0,0,READ_DDR,3,0x2));

	QuadSPI.MCR.B.CLR_RXF = 1;
	QuadSPI.FR.R = 0x10000;
	QuadSPI.IPCR.R = (15 << 24) | (2); //fill the RX buffer
	while(QuadSPI.SR.R & QuadSPI_SR_BUSY_MASK);
	while(QuadSPI.RBSR.B.RDBFL != 1);

	data = QuadSPI.RBDR[0].R;
	return data;
}

void quadspi_send_instruction_hyp(unsigned int address, unsigned int cmd)
{
	QuadSPI.SFAR.R = (address&0xfffffffe);
	quadspi_set_lut(60,QSPI_LUT(ADDR_DDR,3,0x18,CMD_DDR,3,0x00));
	quadspi_set_lut(61,QSPI_LUT(CMD_DDR,3,cmd>>8,CADDR_DDR,3,0x10));
	quadspi_set_lut(62,QSPI_LUT(STOP,0,0,CMD_DDR,3,cmd));
	QuadSPI.IPCR.R = (15 << 24);
	while(QuadSPI.SR.R & QuadSPI_SR_BUSY_MASK);
}

void quadspi_set_lut(uint32_t index, uint32_t value)
{
 	//Unlock the LUT
	do{
	QuadSPI.LUTKEY.R = 0x5AF05AF0;
	QuadSPI.LCKCR.R = 0x2;	//UNLOCK the LUT
	}
	while(QuadSPI.LCKCR.B.UNLOCK == 0); //is this required??

	// SEQID 2 - Page Erase
	QuadSPI.LUT[index].R = value;

	//Lock the LUT
	QuadSPI.LUTKEY.R = 0x5AF05AF0;
	QuadSPI.LCKCR.R = 0x1;	//LOCK the LUT
	while(QuadSPI.LCKCR.B.LOCK == 0);
}


