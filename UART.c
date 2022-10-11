#include "UART.h"



//------------UART_Init------------
// Initialize the UART for 9600 baud rate ,
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void Initialize_Serial(void){
    SYSCTL_RCGCUART_R |= 0x80; // activate UART7
    SYSCTL_RCGCGPIO_R |= 0x10; // activate port E
    while((SYSCTL_PRGPIO_R&0x10) == 0){};
    UART7_CTL_R = 0; // disable UART
    UART7_IBRD_R = 104; // IBRD = int(16,000,000 / (16 * 9600)) = int(104.1667)
    UART7_FBRD_R = 11; // FBRD = int(0.1667 * 64 + 0.5) = 11
    // 8 bit word length (no parity bits, one stop bit, FIFOs)
    UART7_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
    UART7_CTL_R |= 0x301; // enable UART
    GPIO_PORTE_AFSEL_R |= 0x03; // enable alt funct on PE1-0
    GPIO_PORTE_DEN_R |= 0x03; // enable digital I/O on PE1-0
    // configure PE1-0 as UART
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000011;
    GPIO_PORTE_AMSEL_R &= ~0x03; // disable analog functionality on PE
}

void Delay(unsigned long counter)
{
unsigned long i = 0;

for(i=0; i< counter; i++);
}




//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void){
    while ((UART7_FR_R&UART_FR_RXFE) != 0);
        return ((char)(UART7_DR_R&0xFF));
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
        while ((UART7_FR_R&UART_FR_TXFF) != 0);
            UART7_DR_R = data;
}
//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
    while(*pt){
        UART_OutChar(*pt);
        pt++;
        Delay(1);
    }
}



