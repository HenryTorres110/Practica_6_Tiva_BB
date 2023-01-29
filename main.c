/// By Henry
#include "lib/include.h"
#include <stdlib.h>

char *reading_string(char delimiter){
    char letter;
    static char array[12];
    for ( int i = 0; i < 12; i++){
        array[i]  = NULL;
    }
    int counter = 0;
    letter = readChar();  
    while (letter != delimiter){
        array[counter] = letter;
        letter = readChar();
        counter ++;
    }
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

extern void SEND_DATA_OUTSIDE(char signal[12]){
    int bit_number[12] = {0};
    int length = strlen(signal); 
    for (int i = 0; i < length; i++){
        bit_number[i] = signal[i] - '0';
    }
    GPIOA -> DATA = (bit_number[0] << 0) | (bit_number[1] << 1) | (bit_number[2] << 2) | (bit_number[3] << 3) | (bit_number[4] << 4) | (bit_number[5] << 5) | (bit_number[6] << 6) | (bit_number[7] << 7);
    GPIOC -> DATA = (bit_number[8] << 0) | (bit_number[9] << 1) | (bit_number[10] << 3)| (bit_number[11] << 4);
}

int main(void)
{
    int duty_cycle = 76;
    int f_clk = 40000000;
    int freq = 20000;
    int divisor = 0;
    int module = 0;

    float seconds = 1;
    uint32_t data[5];
    uint32_t señal_1[1024];
    uint32_t señal_2[1024];

    Configurar_PLL(_40MHZ);  //Configuracion de velocidad de reloj
    //Configurar_GPIO();
    UART_2_CONFIG(); // Puerto D
    ADC_CONFIGURATION_PORT_E(); // Puerto E
    SEQ_CONFIGURATION_0();
    PWM_CONFIGURATION(module, divisor, freq, f_clk, duty_cycle); // PB4 Puerto B
    TIMER_CONFIGURATION(seconds, (float)f_clk);
    OUTPUT_PINS_CONFIGURATION();
    int ii = 0;
    while (1){
        // Timer to one second blink
        /*if ((TIMER0 -> RIS & 0x00000001) == 1){
            TIMER0 -> ICR |= (1 << 0); //CLEAN TATORIS REGISTER
            ADC_ISR_SEQ_0(data);
            GPIOF -> DATA ^= (1 << 2); //TOGGLE PF2 
        }*/
        // Obtención de datos cada n segundos
        TICK_TOCK(data);
        // Guardado de los datos en arreglos de 1024 enteros
        señal_1[ii] = data[0]; 
        señal_2[ii] = data[1];
        // Envío de las señales por muestra a MATLAB
        integer_to_char(señal_1[ii]);
        integer_to_char(señal_2[ii]);
        // Leemos datos en binario de Matlab
        char binary_signal_1[12] = "";
        char binary_signal_2[12] = ""; 
        char *matlab_signal_1 = reading_string('\n');
        strcpy(binary_signal_1, matlab_signal_1);
        char *matlab_signal_2 = reading_string('\n');
        strcpy(binary_signal_2, matlab_signal_2);

        SEND_DATA_OUTSIDE(binary_signal_1);
        // SEND_DATA_OUTSIDE(binary_signal_2)

        ii ++;
        if (ii == 1024){
            ii = 0;
        }
    }   
}

