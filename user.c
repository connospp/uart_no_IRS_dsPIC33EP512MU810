/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
// This code in included only when you are using the XC16 compiler
#include <xc.h>
#endif

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

#define FP 4000000 
#define BAUDRATE 38400
#define BRGVAL ((FP/BAUDRATE)/16)-1
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    /* TODO Initialize User Ports/Peripherals/Project here */
    /* Setup analog functionality and port direction */
    PortSetup();
    UartSetup();
}

void UartSetup(void) {
    U1MODEbits.UARTEN = 0; // Bit15 TX, RX DISABLED, ENABLE at end 

    /*TX SETUP*/
    RPOR9bits.RP101R = 01; //Tx on RF5

    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = BRGVAL; // Baud Rate setting for 38400

    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;

    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX interrupt

    /*RX SETUP*/
    TRISFbits.TRISF4 = 1; //F4 as input
    RPINR18bits.U1RXR = 100; //Rx on RF4

    U1STAbits.URXISEL0 = 0; // Interrupt after one character is received
    U1STAbits.URXISEL1 = 0;

    /* Generic*/

    U1MODEbits.UARTEN = 1; // And turn the peripheral on
    U1STAbits.UTXEN = 1;

    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 0; // Enable UART RX interrupt
}

void PortSetup(void) {    
    ANSELA = 0x00; // Convert all I/O pins to digital
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00;
    ANSELE = 0x00;
    ANSELG = 0x00;    
}