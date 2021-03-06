/***********************************************************************/
/*  													               */
/*      PROJECT NAME :  OpenRF_JwikBrik_x69HW                          */
/*      FILE         :  interrupt_handlers.c                           */
/*      DESCRIPTION  :  Interrupt Handler                              */
/*      CPU SERIES   :  RL78 - G13                                     */
/*      CPU TYPE     :  R5F100EE                                       */
/*  													               */
/*      This file is generated by e2studio.                        */
/*  													               */
/***********************************************************************/                                                                       
#include "iodefine.h"

#include "interrupt_handlers.h"

/*
 * INT_WDTI (0x4)
 */
void INT_WDTI (void) { }

/*
 * INT_LVI (0x6)
 */
void INT_LVI (void) { }

/*
 * INT_P0 (0x8)
 */
void INT_P0 (void)
{
	HandleInterrupt(0);
}

/*
 * INT_P1 (0xA)
 */
void INT_P1 (void)
{
	HandleInterrupt(1);
}

/*
 * INT_P2 (0xC)
 */
void INT_P2 (void)
{
	HandleInterrupt(2);
}

/*
 * INT_P3 (0xE)
 */
void INT_P3 (void)
{
	HandleInterrupt(3);
}

/*
 * INT_P4 (0x10)
 */
void INT_P4 (void)
{
	HandleInterrupt(4);
}

/*
 * INT_P5 (0x12)
 */
void INT_P5 (void)
{
	HandleInterrupt(5);
}

/*
 * INT_CSI20/INT_IIC20/INT_ST2 (0x14)
 */
void INT_ST2 (void) { }
//void INT_CSI20 (void) { }
//void INT_IIC20 (void) { }

/*
 * INT_CSI21/INT_IIC21/INT_SR2 (0x16)
 */
void INT_SR2 (void) { }
//void INT_CSI21 (void) { }
//void INT_IIC21 (void) { }

/*
 * INT_SRE2 (0x18)
 */
void INT_SRE2 (void) { }

/*
 * INT_DMA0 (0x1A)
 */
void INT_DMA0 (void) { }

/*
 * INT_DMA1 (0x1C)
 */
void INT_DMA1 (void) { }

/*
 * INT_CSI00/INT_IIC00/INT_ST0 (0x1E)
 */
#ifdef UART_ENABLED
U8 _uart0TransmitBuffer[UARTBUFFERSIZE];
U8 _uart0TransmitTailPointer = 0;
#endif
void INT_UART0_TX (void)
{

#ifdef UART_ENABLED
	TXD0 = _uart0TransmitBuffer[_uart0TransmitTailPointer++];
	_uart0TransmitTailPointer&=UARTBUFFERSIZE-1;
#endif
}
//void INT_CSI00 (void) { }
//void INT_IIC00 (void) { }

/*
 * UART0 Receive
 */

#ifdef UART_ENABLED
U8 _uart0ReceiveBuffer[UARTBUFFERSIZE];
U8 _uart0ReceiveTailPointer = 0;
#endif
void INT_UART0_RX (void)
{

#ifdef UART_ENABLED
	_uart0ReceiveBuffer[_uart0ReceiveTailPointer++] = RXD0;
	_uart0ReceiveTailPointer&=UARTBUFFERSIZE-1;
#endif
}

/*
 * INT_SRE0/INT_TM01H (0x22)
 */
void INT_TM01H (void) { }
//void INT_SRE0 (void) { }

/*
 * INT_ST1 (0x24)
 */

#ifdef UART_ENABLED
U8 _uart1TransmitBuffer[UARTBUFFERSIZE];
U8 _uart1TransmitTailPointer = 0;

extern U8 _uart1TransmitHeadPointer;
#endif
 void INT_UART1_TX (void)
 {
#ifdef UART_ENABLED
	 _uart1TransmitTailPointer++;
	 _uart1TransmitTailPointer&=UARTBUFFERSIZE-1;

	 if(_uart1TransmitTailPointer != _uart1TransmitHeadPointer)
		 TXD1 = _uart1TransmitBuffer[_uart1TransmitTailPointer];
#endif
 }

/*
 * UART1 Receive
 */
#ifdef UART_ENABLED
U8 _uart1ReceiveBuffer[UARTBUFFERSIZE];
U8 _uart1ReceiveTailPointer = 0;
#endif
void INT_UART1_RX (void)
{
#ifdef UART_ENABLED
	U8 val = RXD1;
	return;
	_uart1ReceiveBuffer[_uart1ReceiveTailPointer++] = RXD1;
	_uart1ReceiveTailPointer&=UARTBUFFERSIZE-1;
#endif
}
//void INT_CSI11 (void) { }
//void INT_IIC11 (void) { }

/*
 * INT_SRE1/INT_TM03H (0x28)
 */
void INT_TM03H (void) { }
//void INT_SRE1 (void) { }

/*
 * INT_IICA0 (0x2A)
 */
void INT_IICA0 (void) { }

/*
 * INT_TM00 (0x2C)
 */
void INT_TM00 (void) { }

/*
 * INT_TM01 (0x2E)
 */
void INT_TM01 (void) { }

/*
 * INT_TM02 (0x30)
 */
void INT_TM02 (void) { }

/*
 * INT_TM03 (0x32)
 */
void INT_TM03 (void) { }

/*
 * INT_AD (0x34)
 */
void INT_AD (void) { }

/*
 * INT_RTC (0x36)
 */
// this interrupt should fire every 1 seconds
U8 _RTCSeconds = 0;
// 24 hours counter
U8 _RTCHours = 0;
U8 _RTCMinutes = 0;
// 0=Sunday, 6=Saturday
U8 _RTCDayOfWeek = 0;
// counts date time in seconds since 00:00:00 1/1/2013.  Give us 136 years dynamic range.  13,735,245 = 23:20:45 6/7/2013
UU32 _RTCDateTimeInSecs;
void INT_RTC (void)
{
	if(RIFG==1)
	{
		RTCC1 &= ~0x08;
		Handle1SecInterrupt();
		_RTCSeconds++;
		_RTCDateTimeInSecs.U32++;
		if(_RTCSeconds>59)
		{
			_RTCSeconds=0;
			_RTCMinutes++;
			if(_RTCMinutes>59)
			{
				_RTCMinutes = 0;
				_RTCHours++;
				if(_RTCHours>23)
				{
					_RTCHours=0;
					_RTCDayOfWeek++;
					if(_RTCDayOfWeek>6)
						_RTCDayOfWeek=0;
				}
			}
		}
	}
}

/*
 * INT_IT (0x38)
 */
void INT_IT (void)
{
	Handle1MsInterrupt();
}

/*
 * INT_KR (0x3A)
 */
void INT_KR (void)
{

	HandleInterrupt(0x80 + (P7&0x07));
}

/*
 * INT_TM04 (0x42)
 */
void INT_TM04 (void) { }

/*
 * INT_TM05 (0x44)
 */
void INT_TM05 (void) { }

/*
 * INT_TM06 (0x46)
 */
void INT_TM06 (void) { }

/*
 * INT_TM07 (0x48)
 */
void INT_TM07 (void) { }

/*
 * INT_MD (0x5E)
 */
void INT_MD (void) { }

/*
 * INT_FL (0x62)
 */
void INT_FL (void) { }

/*
 * INT_BRK_I (0x7E)
 */
void INT_BRK_I (void) { }
