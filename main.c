#include "UART.h"
#include <stdint.h>


unsigned char CRC( char message[], unsigned char length);
void Send_Frame(int destadd,int srcadd,char data[],unsigned char length);


int main(){

    Initialize_Serial();

    int SRC_Add=0x01;
    int DEST_Add=0x02;
    char msg[20]="Link Layer over UART";
    char Temp = 0;

    while(1){
                Send_Frame(DEST_Add,SRC_Add,msg,strlen(msg));
                Delay(999999999999);
     }

}





void Send_Frame(int destadd, int srcadd,char data[],unsigned char length)
{
    unsigned char c= CRC(data,length);
    // Add Preamble
    // First 7 Bytes =>> 0b10101010 = 0xAA
    // Eighth Byte =>> 0b10101011 = 0xAB
    int i;
    for(i=0;i<7;i++){
        UART_OutChar(0xAA);
    Delay(1);
    }
    UART_OutChar(0xAB);

    // Add Destination Address
    UART_OutChar(destadd);
    // Add Source Address
    UART_OutChar(srcadd);
    Delay(10);

   UART_OutChar(0xBB); // Type byte

    //CRC Code
    UART_OutString(data);
    UART_OutChar(c);

}


unsigned char CRC(char message[], unsigned char length)
{
    const unsigned char CRC7_POLY = 0x91;
    unsigned char i, j, crc = 0;

    for (i = 0; i < length; i++)
    {
        crc ^= message[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc ^= CRC7_POLY;
            crc >>= 1;
        }
    }
    return crc;
}
