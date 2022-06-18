#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


static volatile uint16_t ValorADC;
static volatile float VoltajeNormalizado;
static volatile float ema_vec[2] = {0,0};  // y[0] = current_value , y[1] = last_value
static volatile float alpha = 0.5;

float applied_EMA_filter(float current_value, float last_value_filtered, float alfa){
    float filtered_value = (alfa*current_value) + (1-alfa)*last_value_filtered;
    return(filtered_value);
}

static volatile float sma_vec[30]= {0};

void shif_values_sma(void){
    uint8_t vector_size = sizeof(sma_vec);
    uint8_t i=0;

    for(i=vector_size-1;i>0;i--){
       sma_vec[i] = sma_vec[i-1];
    }

}

float applied_SMA_filter (float current_value){
    uint8_t vector_size = sizeof(sma_vec);

    uint8_t i;
    float sum = 0;
    for(i=vector_size-1;i>0;i--){
        float aux = sma_vec[i];
        sum = sum + aux;
    }

    float filtered_value = (sum + current_value)/vector_size;

    return(filtered_value);
}

char mensaje[50];
//------Variables para conteo de tiempo--------
volatile unsigned long milecimas = 0;
volatile unsigned long current_mills = 0;

volatile float periodo = 0;
volatile float frecuencia =0;

const unsigned int f_max = 100000;

//---------------------------------------------

const eUSCI_UART_ConfigV1 uartConfig =
{
       EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
       78,                                     // BRDIV = 78
       2,                                       // UCxBRF = 2
       0,                                       // UCxBRS = 0
       EUSCI_A_UART_NO_PARITY,                  // No Parity
       EUSCI_A_UART_LSB_FIRST,                  // LSB First
       EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
       EUSCI_A_UART_MODE,                       // UART mode
       EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
       EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

void config_UART_A0(void){
    /* P1.2 and P1.3 en modo UART  */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION );

    /* DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);  //configurando reloj en 12MHz

    /* Configuración UART con base a la estructura de arriba */
    UART_initModule(EUSCI_A0_BASE, &uartConfig);  //uart configurado a 9600 bauls

    /* Habilitamos UART */
    UART_enableModule(EUSCI_A0_BASE);

    /* Interrupciones */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT); //Configurando interrupcio RX
    Interrupt_enableInterrupt(INT_EUSCIA0);
}


void config_timer(void){

    TIMER_A0 -> CCR[0] = 12000000/f_max; //ValorTOP_para_Frecuencia_interrucion_timer = clock/ frec_deseada.

    //Modo
    TIMER_A0 ->CCTL[0] = TIMER_A_CCTLN_OUTMOD_0 + TIMER_A_CCTLN_CCIE;

    TIMER_A0 -> CTL = TIMER_A_CTL_MC__UP | TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_CLR | TIMER_A_CTL_IE;

    Interrupt_enableInterrupt(INT_TA0_0);  //habilitando la interrucion en compraracion de CCR[0]
}

void config_ADC_manual(void){
    //Configuración ADC
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_32, ADC_DIVIDER_8, ADC_NOROUTE);

    //GPIO Configuracion
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);

    //Configurar ADC Memoria
    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, ADC_NONDIFFERENTIAL_INPUTS);

    //Configuración timer en modo manual
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();

    ADC14_enableInterrupt(ADC_INT0);
    Interrupt_enableInterrupt(INT_ADC14);
}

unsigned long milis(void){
    return milecimas;
}

void adc_read_in_interrup(){
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //habilitar conversion
}

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    config_UART_A0();
    config_timer();
    config_ADC_manual();

    while(1)
    {
        
    }
}

void TA0_0_IRQHandler(void){
    //Se entra a esta interrucion cada milisegudo (definido por la frecuencia de 1000 en la formula)
    TIMER_A0->CCTL[0] &= ~0x0001; //limpia bandera de interruccion

    milecimas++;    //se incrementa el tiempo en milesimas

    adc_read_in_interrup();

}

void ADC14_IRQHandler(void){
    uint16_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(ADC_INT0);
    if(ADC_INT0 & status){
        ValorADC = ADC14_getResult(ADC_MEM0);
        VoltajeNormalizado = (ValorADC*3.3)/16383;

        ema_vec[1]= ema_vec[0];
        ema_vec[0] = applied_EMA_filter(VoltajeNormalizado, ema_vec[1], alpha);

        shif_values_sma();
        float sma_reult= applied_SMA_filter(VoltajeNormalizado);
        sma_vec[0]= VoltajeNormalizado;

        sprintf(mensaje,"%0.4f,%0.4f,%0.4f",VoltajeNormalizado,ema_vec[0],sma_reult);

        uint8_t i;
        for(i=0;i<50;i++){
            UART_transmitData(EUSCI_A0_BASE, mensaje[i]);
        }
    }
}
