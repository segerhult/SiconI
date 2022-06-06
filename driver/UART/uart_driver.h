#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"


#define UART0_ENABLE 0x00000001
#define EN_PORTA 0x00000001
#define PA0 0x01
#define PA1 0x02
#define ASSIGN_UART0 0x00000011
#define EN_UART 0x01
#define DIS_UART 0x300
#define BUSY_FLAG 0x0000008
#define OVERRUN_ERROR 0x00000800
#define BREAK_ERROR 0x00000400
#define PARITY_ERROR 0x00000200
#define FRAME_ERROR 0x00000100
#define DATA_BITS 0x000000FF
#define RXFFULL 0x00000040
#define RXFEMPTY 0x00000010
#define TXFFULL 0x00000020

#define UART_BUFFER_SIZE 20
#ifndef FOREVER_LOOP_
#define FOREVER_LOOP_
#define forever for (;;)
#endif



void UART_init();

void UART_putChar(char c);



void error();

char UART_getChar();

void UART_reset();

void UART_putString(char *string);

void clearString(char* string, int len);

void UART_getString();

void test();
#endif



