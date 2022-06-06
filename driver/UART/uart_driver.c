#include "uart_driver.h"

int init = 0;

void UART_init()
{
    // Enable the UART module
    SYSCTL_RCGCUART_R |= (1 << 0);  // (1<<a) <==> set value 1 to register at index a

    // Enable the clock
    SYSCTL_RCGCGPIO_R |= (1 << 0);

    // Set the GPIO AFSEL bits for the pins

    GPIO_PORTA_AHB_AFSEL_R |= (1 << 0) | (1 << 1);

    // Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate

    GPIO_PORTA_AHB_PCTL_R |= (1 << 0) | (1 << 4);
    GPIO_PORTA_AHB_DEN_R |= (1 << 0) | (1 << 1);

    //   Disable the UART by clearing the UARTEN bit in the UARTCTL register.
    UART0_CTL_R &= ~UART_CTL_UARTEN;  // ~(1<<0)

    //  Write the integer portion of the BRD to the UARTIBRD register.

    UART0_IBRD_R |= 104;

    // Write the fractional portion of the BRD to the UARTFBRD register.

    UART0_FBRD_R |= 11;

    // Serial parameters to the UARTLCRH register

    UART0_LCRH_R |= UART_LCRH_WLEN_8 | UART_LCRH_FEN;

    // Configure the UART clock source by writing to the UARTCC register.
    UART0_CC_R |= 0x0;
    
    // Enable the UART
    UART0_CTL_R |= UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE;
    
    init = 1;

}

void error()
{
    UART_init();
    UART_putString("ERROR");
    while (1)
        UART_getChar();
}

char UART_getChar() 
{
    
    if (init == 1) 
    {
        while ((UART0_FR_R & UART_FR_RXFE) != 0);  
        uint16_t tmp;
        tmp = UART0_DR_R;
        char read = tmp;
        return  read;
    } 
    
    else
        error();
    return 0;
}


void UART_putChar(char c)
{
    if (init == 1) 
    {

        while ((UART0_FR_R & (1 << 5)) != 0);   
        UART0_DR_R = c;
    }
    
    else
        error();
}


void UART_reset() {

    SYSCTL_RCGCUART_R |= UART0_ENABLE;
    SYSCTL_RCGCGPIO_R |= EN_PORTA;

    UART0_LCRH_R = 0;
    UART0_CTL_R = 0;

    UART0_FBRD_R = 0;

    init = 0;
}

void UART_putString(char *string) 
{
    UART_putChar('\n');
    while (*string) {

        UART_putChar(*(string++));
    }
    UART_putChar('\n');
    UART_putChar('\r');
}

void clearString(char* string, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        string[i] = 0;
    }
}

void UART_getString(unsigned char *read) 
{
    
    int ind = 0;
 
    do 
    {
        read[ind] = UART_getChar();
        UART_putChar(read[ind]);

        if (read[ind] == '\r') 
        {
            read[ind] = '\0';
            break;
        }

        ind++;
    } while (ind < UART_BUFFER_SIZE);
}


