#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>


#define UART_FR_TXFF 0x00000020 // UART Transmit FIFO Full
#define UART_FR_RXFE 0x00000010 // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8 0x00000060 // 8 bit word length
#define UART_LCRH_FEN 0x00000010 // UART Enable FIFOs
#define UART_CTL_UARTEN 0x00000001 // UART Enable


extern void Initialize_Serial(void);
extern void Delay(unsigned long counter);
extern char UART_InChar(void);
extern void UART_OutChar(char data);
extern void UART_OutString(char *pt);


#endif /* UART_H_ */
