/*========================================================================*
 * COPYRIGHT:                                                             *
 *  Freescale Semiconductor, INC. All Rights Reserved. You are hereby     *
 *  granted a copyright license to use, modify, and distribute the        *
 *  SOFTWARE so long as this entire notice is retained without alteration *
 *  in any modified and/or redistributed versions, and that such modified *
 *  versions are clearly identified as such. No licenses are granted by   *
 *  implication, estoppel or otherwise under any patentsor trademarks     *
 *  of Freescale Semiconductor, Inc. This software is provided on an      *
 *  "AS IS" basis and without warranty.                                   *
 *                                                                        *
 *  To the maximum extent permitted by applicable law, Freescale          *
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,    *
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A      *
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH REGARD  *
 *  TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF) AND ANY     *
 *  ACCOMPANYING WRITTEN MATERIALS.                                       *
 *                                                                        *
 *  To the maximum extent permitted by applicable law, IN NO EVENT        *
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER    *
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,  *
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER         *
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.  *
 *                                                                        *
 *  Freescale Semiconductor assumes no responsibility for the             *
 *  maintenance and support of this software                              *
 *                                                                        *
 **************************************************************************/

/********************************************************************
 * File:		serial.c
 * Purpose:		Board specific routines for the Treerunner
 ********************************************************************/

#include "../include/uartlinflex_driver.h"
//#include "typedefs.h"
#include "s32vs234.h"

void ConfigureSciPins(void);
void Linflex_SetSpeed(void);


//*********************************************************
//	Initialise serial port for printf
//	No par / 8 data bits / 1 stop bit
//*********************************************************
void LinFlex0_Init( void )
{   
   ConfigureSciPins();

   // Leave the sleep mode
   LINFlexD_0.LINCR1.B.SLEEP = 0x0;
   // Enter initialization mode by setting INIT bit
   LINFlexD_0.LINCR1.B.INIT = 0x1;

   LINFlexD_0.UARTCR.B.UART = 0x1;  //Linflex working in UART mode

   LINFlexD_0.UARTCR.B.TxEn = 0x1;    // Enable transmission of data now
   LINFlexD_0.UARTCR.B.RxEn = 0x1;    //Receiver enabled
   LINFlexD_0.UARTCR.B.WL0   = 0x1;    //8 bit data
   LINFlexD_0.UARTCR.B.PCE  = 0x0;    //No parity
   
   Linflex_SetSpeed();
  
   // Leave initialization mode by clearing INIT bit
   LINFlexD_0.LINCR1.B.INIT = 0x0;	

   // Leave the sleep mode  // STH
   LINFlexD_1.LINCR1.B.SLEEP = 0x0;
   // Enter initialization mode by setting INIT bit
   LINFlexD_1.LINCR1.B.INIT = 0x1;

   LINFlexD_1.UARTCR.B.UART = 0x1;  //Linflex working in UART mode

   LINFlexD_1.UARTCR.B.TxEn = 0x1;    // Enable transmission of data now
   LINFlexD_1.UARTCR.B.RxEn = 0x1;    //Receiver enabled
   LINFlexD_1.UARTCR.B.WL0   = 0x1;    //8 bit data
   LINFlexD_1.UARTCR.B.PCE  = 0x0;    //No parity
   
   Linflex_SetSpeed();
  
   // Leave initialization mode by clearing INIT bit
   LINFlexD_1.LINCR1.B.INIT = 0x0;	


}


/********************************************************************
 *	SCI_0
 ********************************************************************/

char sci_0_testchar (void)
{
  // Wait for the reception to complete   
  if(LINFlexD_0.UARTSR.B.DRFRFE == 0) {
    return(0);
  }
  
  return(sci_0_getchar());
}

/********************************************************************/
char sci_1_testchar (void)
{
  // Wait for the reception to complete   
  if(LINFlexD_1.UARTSR.B.DRFRFE == 0) {
    return(0);
  }
  
  return(sci_1_getchar());
}

/********************************************************************/
char sci_0_getchar (void)
{
	char cDummy;
   // Wait for the reception to complete   
	while(LINFlexD_0.UARTSR.B.DRFRFE == 0) {
		__asm("nop");
	}
   
	cDummy = (vuint8_t) LINFlexD_0.BDRM.R;  // Retrieve data received from LinFlex	

   // Clear RMB (Release Message Buffer) and DRF (Data Reception Completed)
   //  flags, which are set when receiving data in UART mode
   LINFlexD_0.UARTSR.B.RMB = 0; // release message buffer..shouldnt it be 1?? RMB is cleared w1c(clearing by writing 1)
   LINFlexD_0.UARTSR.B.DRFRFE = 1;
   return cDummy;

}

/********************************************************************/
char sci_1_getchar (void)
{
	char cDummy;
   // Wait for the reception to complete   
	while(LINFlexD_1.UARTSR.B.DRFRFE == 0) {
		__asm("nop");
	}
   
	cDummy = (vuint8_t) LINFlexD_1.BDRM.R;  // Retrieve data received from LinFlex	

   // Clear RMB (Release Message Buffer) and DRF (Data Reception Completed)
   //  flags, which are set when receiving data in UART mode
   LINFlexD_1.UARTSR.B.RMB = 0; // release message buffer..shouldnt it be 1?? RMB is cleared w1c(clearing by writing 1)
   LINFlexD_1.UARTSR.B.DRFRFE = 1;
   return cDummy;

}

/********************************************************************/
void sci_0_putchar (char ch)
{
  
	LINFlexD_0.UARTCR.B.TxEn = 1;
	LINFlexD_1.UARTCR.B.TxEn = 1;
	LINFlexD_0.BDRL.R = (vuint32_t) ch; // Start transmission by writing the data 
	LINFlexD_1.BDRL.R = (vuint32_t) ch; // Start transmission by writing the data 
	
	// Wait for the transmission to complete
	while (LINFlexD_0.UARTSR.B.DTFTFF == 0) {
		__asm("nop");
	}
	// Wait for the transmission to complete
	while (LINFlexD_1.UARTSR.B.DTFTFF == 0) {
		__asm("nop");
	}
	
	LINFlexD_0.UARTSR.B.DTFTFF = 1;		//clear the trasmission completed flag	
	LINFlexD_1.UARTSR.B.DTFTFF = 1;		//clear the trasmission completed flag	

	LINFlexD_0.UARTCR.B.TxEn = 0;	// Disable transmission
	LINFlexD_1.UARTCR.B.TxEn = 0;	// Disable transmission
}
/********************************************************************/

void ConfigureSciPins( void )
{
        //UART 0
        *((vuint32_t*)(0x4006C26C)) = 0x882000;
	*((vuint32_t*)(0x4006CD60)) = 0x2;
	*((vuint32_t*)(0x4006C270)) = 0x205401;
        //UART 1
        *((vuint32_t*)(0x4006C274)) = 0x882000;
	*((vuint32_t*)(0x4006CD68)) = 0x2;
	*((vuint32_t*)(0x4006C278)) = 0x205401;
}

void Linflex_SetSpeed( void )
{
  
#if (LIN_CLK == FLIN_133_MHz)    
#if (UART_BAUDRATE == UART_9600_BAUDRATE)    
   /* baudrate = 9600 */
   LINFlexD_0.LINIBRR.B.IBR = 0x361;
   LINFlexD_0.LINFBRR.B.FBR = 0xE;			
#endif
#if (UART_BAUDRATE == UART_19200_BAUDRATE)    
   /* baudrate = 19200 */
   LINFlexD_0.LINIBRR.B.IBR = 0x1B0;
   LINFlexD_0.LINFBRR.B.FBR = 0xF;			
#endif

#if (UART_BAUDRATE == UART_38400_BAUDRATE)    
   /* baudrate = 38400 */
   LINFlexD_0.LINIBRR.B.IBR = 0xD8;
   LINFlexD_0.LINFBRR.B.FBR = 0x7;			
#endif
#if (UART_BAUDRATE == UART_115200_BAUDRATE)    
   /* baudrate = 115200 */
   LINFlexD_0.LINIBRR.B.IBR = 0x48;
   LINFlexD_0.LINFBRR.B.FBR = 0x2;			
   LINFlexD_1.LINIBRR.B.IBR = 0x48;  //STH
   LINFlexD_1.LINFBRR.B.FBR = 0x2;			
#endif   
#endif

   
#if (LIN_CLK == FLIN_66_5_MHz)    
#if (UART_BAUDRATE == UART_9600_BAUDRATE)    
   /* baudrate = 9600 */
   LINFlexD_0.LINIBRR.B.IBR = 0x1B0;
   LINFlexD_0.LINFBRR.B.FBR = 0xF;			
#endif 
#if (UART_BAUDRATE == UART_19200_BAUDRATE)    
   /* baudrate = 19200 */
   LINFlexD_0.LINIBRR.B.IBR = 0xD8;
   LINFlexD_0.LINFBRR.B.FBR = 0x7;			
#endif 
#if (UART_BAUDRATE == UART_38400_BAUDRATE)    
   /* baudrate = 38400 */
   LINFlexD_0.LINIBRR.B.IBR = 0x6C;
   LINFlexD_0.LINFBRR.B.FBR = 0x3;			
#endif 
#if (UART_BAUDRATE == UART_115200_BAUDRATE)    
   /* baudrate = 115200 */
   LINFlexD_0.LINIBRR.B.IBR = 0x24;
   LINFlexD_0.LINFBRR.B.FBR = 0x1;			
#endif 
#endif


   
}
