#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART0(void);
extern char readChar(void);
extern void printChar(char c);
extern void printString(char* string);
extern char * readString(char delimitador);
extern void UART_2_CONFIG(void);

#endif