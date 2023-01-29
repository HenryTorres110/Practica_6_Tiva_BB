/// By Henry
#include "lib/include.h"
#include <stdlib.h>

char *reading_string(char delimiter, int *ptr){
    char letter;
    static char array[10];
    for ( int i; i < 10; i++){
        array[i]  = NULL;
    }
    int counter = 0;
    letter = readChar();  
    while (letter != delimiter){
        array[counter] = letter;
        letter = readChar();
        counter ++;
    }
    *ptr = strlen(array);
    return &array[0];
}

char *inverting_name(char *name, int length){
    static char inverted_name[50];
    int counter = 0;
    int idx = 0; 
    for (int i = length; i > 0; i--){
        inverted_name[counter] = *(name + (i -1));
        inverted_name[counter + 1] = idx + '0';
        idx ++; 
        counter = counter + 2;
    }
    inverted_name[counter - 1] = '\n'; 
    return &inverted_name[0];
}

extern void integer_to_char(uint32_t number)
{
    char number_in_string[5];
    int i = 3;
    int j = 0; 
    int n_digit;  
    while (i >= 0){
        n_digit = (int)number / (int)(pow(10, i));
        number_in_string[j] = n_digit + '0';
        number = number - (n_digit * pow(10, i)); 
        i = i - 1; 
        j++;
    }
    number_in_string[4] = '\n';
    printString(number_in_string);
}

extern void TICK_TOCK(uint32_t data[5]){
    // Timer to one second blink
    if ((TIMER0 -> RIS & 0x00000001) == 1){
        TIMER0 -> ICR |= (1 << 0); //CLEAN TATORIS REGISTER
        ADC_ISR_SEQ_0(data);
        GPIOF -> DATA ^= (1 << 2); //TOGGLE PF2 
    }
}

int main(void)
{
    int duty_cycle = 76;
    int f_clk = 40000000;
    int freq = 20000;
    int divisor = 0;
    int module = 0;

    uint32_t data[5];
    char vector_de_datos[1024];
    Configurar_PLL(_40MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    UART_2_CONFIG(); // Puerto D
    ADC_CONFIGURATION_PORT_E(); // Puerto E
    SEQ_CONFIGURATION_0();
    PWM_CONFIGURATION(module, divisor, freq, f_clk, duty_cycle); // PB4 Puerto B
    TIMER_CONFIGURATION(1, 40000000);
    //PWM_CONFIGURATION(int module, int divisor, int freq, int f_clk, int duty_cycle)
    while (1){
        // Timer to one second blink
        /*if ((TIMER0 -> RIS & 0x00000001) == 1){
            TIMER0 -> ICR |= (1 << 0); //CLEAN TATORIS REGISTER
            ADC_ISR_SEQ_0(data);
            GPIOF -> DATA ^= (1 << 2); //TOGGLE PF2 
        }*/
        TICK_TOCK(data);
        integer_to_char(data[0]);
        integer_to_char(data[1]);
        integer_to_char(data[2]);
    }   
}

