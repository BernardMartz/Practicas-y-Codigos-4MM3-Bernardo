*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>


int main(void) {

    int cont1 = 0;
    int cont2 = 1;

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);      // P1.1 -> Reinicio
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);      // P1.4 -> Detener
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN4);      // P6.4 -> Aumentar tiempo

    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);                       // P4.1 -> D1

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);                       // P4.3 -> A2
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN5);                       // P1.5 -> B2
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);                       // P4.6 -> C2
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN5);                       // P6.5 -> D2

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);                       // P3.2 -> A3
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);                       // P3.3 -> B4
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);                       // P4.1 -> C5
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);                       // P4.3 -> D6

    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);                       // P6.1 -> Led

 int i;
        P2->SEL1 &= ~2;         /* configure P2.1 as simple I/O */
        P2->SEL0 &= ~2;
        P2->DIR |= 2;           /* P2.1 set as output */

        TIMER_A1->CTL = 0x01D1;     /* ACLK, ID = /8, up mode, TA clear */
        TIMER_A1->CCR[0] = 512 - 1; /* for 1 sec */
        TIMER_A1->EX0 = 7;          /* IDEX = /8 */


    while (1) {

        if (cont2 == 0 && cont1 == 0)
        {
            (cont1 = -1);         /* clear interrupt flag */
        }
        if (cont1 == -1)
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);

        }
        else
        {
            GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);

        }

        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
        {
            for(i = 0;i<45000;i++){
            }
            cont2 = cont2 + 1;
        }

        if (cont2 > 5)
        {
            cont2 = 1;
        }

        if (GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN4) == GPIO_INPUT_PIN_LOW){
            for(i = 0;i<45000;i++){
            }
       while ((TIMER_A1->CCTL[0] == 0)); /* wait until the CCIFG flag is set */
        TIMER_A1->CCTL[0] &= ~1;            /* clear interrupt flag */
        P2->OUT ^= 2;                       /* toggle green LED */
        cont1 = cont1 - 1;
        }
        if (cont1 == -1 )
       {
        cont2 = cont2 - 1;
        cont1 = 9;
       }
        if(cont2 == -1)
        {
            cont2 = 5;
        }

                        if (cont1 == -2)
                      {
                        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                       GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                       GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                       GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                      }
                     if (cont1 == 0)
                       {
                        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                        GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                        GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                       }
                      if (cont1 == 1)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 2)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 3)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 4)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 5)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 6)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 7)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 8)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      if (cont1 == 9)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);                       // P3.3 -> C1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);
                         }
                      //dsegundos decimas
                      if (cont2 == 0)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);
                         }
                      if (cont2 == 1)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);
                         }
                      if (cont2 == 2)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);
                         }
                      if (cont2 == 3)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);
                         }
                      if (cont2 == 4)
                         {
                          GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);                         //
                         }
                      if (cont2 == 5)
                         {
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);                       // P6.0 -> A1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);                       // P3.2 -> B1
                          GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);                       // P3.3 -> C1
                          GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN5);
                         }//fin de asignacion de valores

              } //fin del while

    }
