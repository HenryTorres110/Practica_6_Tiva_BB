/// By Henry
#include "lib/include.h"

char *reading_string(char delimiter, int *ptr){
    char letter;
    static char array[50];
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

int main(void)
{

    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    Configurar_GPIO();
    UART_2_CONFIG(); 
    PWM_CONFIGURATION(0, 64, 50, 20000000, 72);
    TIMER_CONFIGURATION(5, 20000000);
    //PWM_CONFIGURATION(int module, int divisor, int freq, int f_clk, int duty_cycle)
    while (1){
        // Timer to one second blink
        if ((TIMER0 -> RIS & 0x00000001) == 1){
            TIMER0 -> ICR |= (1 << 0); //CLEAN TATORIS REGISTER
            GPIOF -> DATA ^= (1 << 2); //TOGGLE PF2 
        }
    }   
}

