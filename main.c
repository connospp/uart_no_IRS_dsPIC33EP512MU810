/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
// This code in included only when you are using the XC16 compiler
#include <xc.h>
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "uartOps.h"        /* UartOperations          */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp   */


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/



int16_t main(void) {

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();   
    
    char newData[4096];    
    unsigned int pointer = 0;    
    while (1) {   
        while(U1STAbits.URXDA == 1)
        {   
            newData[pointer++] = collectReceived();
            if(newData[pointer-1] == '\n')
            {
                transmitArray(newData,pointer);
                pointer = 0;
                break;
            }
        }        
    }
}



