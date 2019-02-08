#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define BAUD 19200
#define UBRR_VAL (((F_CPU/(16UL*BAUD)))-1)

void uart_init(void);
char uart_getchar(void);
void uart_putchar(char data);
void uart_puts(char *s);
int8_t uart_putchar_stream(char data, FILE *stream);
char uart_getchar_stream(FILE *stream);

static FILE uart = FDEV_SETUP_STREAM(uart_putchar_stream,
                                     uart_getchar_stream, _FDEV_SETUP_RW);

int main (void)
{
        stdout = &uart;
        stdin = &uart;
        
        /* sample data */
        uint8_t u_data = 10;
        double float_data = M_PI;
        int8_t s_data = -5;
        char str[]="ME!ME!ME!";
        char input;

        uart_init();
        
        putchar('\n');
        printf("Unsigned int8_t = %u\n", u_data);
        printf("Hex-format unsigned int8_t = %#04x\n", u_data);
        fprintf(stdout,"Double (pi) = %.3f\n", float_data);
        printf("Signed int8_t = %d\n", s_data);
        printf("String = %s\n", str);
        printf_P(PSTR("Flash coded string (pgmspace.h)\n"));
        puts_P(PSTR("scanf demo below\n"));
        for(;;)
        {
                puts_P(PSTR("Press any key: "));
                scanf("%c",&input);
                puts_P(PSTR("\nYou pressed: "));
                printf("%c; Key code: %u\n", input, input);
        }
}


/* UART comms */

void uart_init(void)
{
        UBRR0L = (uint8_t) UBRR_VAL;
        UBRR0H = (uint8_t) (UBRR_VAL>>8);
    
        UCSR0B = _BV(RXEN0)|_BV(TXEN0); /* RX + TX enabled */
        UCSR0C = _BV(UCSZ01)|_BV(UCSZ00); /* 1 stop bit, 8bit char, async */
}

void uart_putchar(char data)
{
        while(!(UCSR0A & (_BV(UDRE0))));
        UDR0 = data; 
}

char uart_getchar(void)
{
        while(!(UCSR0A & (_BV(RXC0))));
        return UDR0;
}

void uart_puts(char *s)
{
        while(*s)
        { 
            uart_putchar(*s);
            s++;
        }
}

int8_t uart_putchar_stream(char data, FILE *stream)
{
        if (data == '\n')
            uart_putchar('\r');
        uart_putchar(data);
        return 0;
}

char uart_getchar_stream(FILE *stream)
{
        char data;
        data = uart_getchar();
        uart_putchar(data); /* echo back, comment if unnecessary */
        return data;
}
