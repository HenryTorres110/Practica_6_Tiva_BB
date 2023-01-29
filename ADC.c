#include "lib/include.h"

extern void ADC_CONFIGURATION_PORT_E(void){
    SYSCTL -> RCGCADC = (1 << 0); // Enable Module 0
    SYSCTL -> RCGCADC = (1 << 1); // Enable Module 1

    SYSCTL -> RCGCGPIO |= (1 << 4); //| (1 << 5);
    //                    Puerto E    Puerto F
    // Configuracion de Pines EN DIRECTION REGISTER DIR para que sean outputs (1) o inputs (0)
    GPIOE -> DIR &= ~(1 << 1); // AIN2 PE1
    GPIOE -> DIR &= ~(1 << 2); // AIN1 PE2
    GPIOE -> DIR &= ~(1 << 5); // AIN8 PE5

    GPIOE -> AFSEL = (1 << 1) | (1 << 2) | (1 << 5);//0x3F; // E0-E5 AIN0-AIN3, AIN8-AIN9
    GPIOE -> DEN = ~(1 << 1) | ~(1 << 2) | ~(1 << 5); //~0x3F;
    GPIOE -> AMSEL = (1 << 1) | (1 << 2) | (1 << 5); //0x3F; 

    /*GPIOD -> DIR &= ~(1 << 2); // AIN5 PD2
    GPIOD -> DIR &= ~(1 << 1); // AIN6 PD1
    GPIOD -> DIR &= ~(1 << 0); // AIN7 PD0

    GPIOD -> AFSEL = (1 << 0) | (1 << 1)| (1 << 2);
    GPIOD -> DEN = ~(1 << 0) | ~(1 << 1) | ~(1 << 2); 
    GPIOD -> AMSEL = (1 << 0) | (1 << 1) | (1 << 2);  

    GPIOB -> DIR &= ~(1 << 5); // AIN11 PB5
    GPIOB -> AFSEL =  (1 << 5);
    GPIOB -> DEN =  ~(1 << 5); 
    GPIOB -> AMSEL = (1 << 5); */
    // LED
    /*GPIOF -> DEN = 0xff; 
    GPIOF -> AFSEL = 0x00; 
    GPIOF -> DIR = 0xff; // Output
    GPIOF -> DATA = (1 << 1);*/
}

extern void ADC_CONFIGURATION_PORT_D(void){
    SYSCTL -> RCGCADC = (1 << 0); // Enable Module 0
    SYSCTL -> RCGCADC = (1 << 1); // Enable Module 1
    SYSCTL -> RCGCGPIO |= (1 << 3) | (1 << 5);
    GPIOD -> DIR &= ~(1 << 0); // AIN7 PD0
    GPIOD -> DIR &= ~(1 << 1); // AIN6 PD1
    GPIOD -> DIR &= ~(1 << 2); // AIN5 PD2
    GPIOD -> AFSEL = (1 << 0) | (1 << 1) | (1 << 2);//0x3F; // E0-E5 AIN0-AIN3, AIN8-AIN9
    GPIOD -> DEN = ~(1 << 0) | ~(1 << 1) | ~(1 << 2); //~0x3F;
    GPIOD -> AMSEL = (1 << 0) | (1 << 1) | (1 << 2); //0x3F; 
    // LED
    /*GPIOF -> DEN = 0xff; 
    GPIOF -> AFSEL = 0x00; 
    GPIOF -> DIR = 0xff; // Output
    GPIOF -> DATA = (1 << 1);*/
}

/*extern void SEQ_CONFIGURATION_3(void){
    //ADC0 -> ACTSS &= ~0b1001; // Disable seq 0 and 3
    ADC0->ACTSS = ~(1 << 3); //~0x9;
    //ADC0 -> SSPRI = (0 << 12); High Priority of Seq 3
    ADC0->EMUX &= 0x0000F000;
    // Trigger for sampling
    //ADC0 -> EMUX = (0xF << 0) | (0xF << 12);
    //(0xF << 12); //(0xF << 0) | (0xF << 12); // 0xF to sample continuously 
    
    ADC0->SSMUX3 = 2; // AN2 CHANNEL
    //ADC1 -> SSMUX0 = 0x98321;  // AN1-AN3, AN8-AN9 0b10011000001100100001

    ADC0->SSCTL3 = 0x6; //0b0110;
    ///ADC1 -> SSCTL0 = 0x66666;  // 0b01100110011001100110
    ADC0->PC = 0x7; // 1 Msps

    ADC0->IM = (1 << 3);  //| (1 << 0);

    // Enable Seq
    ADC0->ACTSS |= (1 << 3);//0x9;
    ADC0->ISC=8;
}*/

extern void SEQ_CONFIGURATION_0(void){
    ADC1 -> SSPRI = 0x3210;
    ADC1 -> ACTSS &= ~(0x0F); 
    ADC1 -> EMUX |= 0x0000;
    ADC1 -> SSMUX0 |= 0x00000281; 
    ADC1 -> SSCTL0 |= 0x00000644;//(1 << 17)| (1 << 18); //0x00064444; //0x66666; 
    ADC1 -> PC = 0x7; 
    ADC1 -> IM &= ~(0x0001); 
    ADC1 -> ACTSS |= (1 << 0); 
    ADC1 -> ISC = 1; 
}
extern void ADC_ISR_SEQ_0(uint32_t data[5]){
    ADC1 -> PSSI = 0x00000001; //| (1 << 0);
        while ((ADC1 -> RIS & 0x01) == 0){};
        data[0] = ADC1 -> SSFIFO0 & 0xFFF;
        data[1] = ADC1 -> SSFIFO0 & 0xFFF;
        data[2] = ADC1 -> SSFIFO0 & 0xFFF;
        //data[3] = ADC1 -> SSFIFO0 & 0xFFF;
        //data[4] = ADC1 -> SSFIFO0 & 0xFFF;
        ADC1 -> ISC = 0x0001; // Clearing 0b0001
        //sprintf(ARREGLO, "%u\n", array[1]);
        //printString(ARREGLO);
        /*if (data[0] < 2040){
            GPIOF -> DATA |= (1 << 1);
            GPIOF -> DATA &= ~(1 << 2); 
        }
        else if (data[0] > 2040){
            GPIOF -> DATA &= ~(1 << 1);
            GPIOF -> DATA |= (1 << 2);
        }*/
}