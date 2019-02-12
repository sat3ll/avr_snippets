#include <avr/io.h>
#include <util/delay.h>

/* Digital 13 - SCK
 * Digital 11 - MOSI
 * Digital 10 - SS
 */
#define SS_PORT PORTB
#define SS_DDR DDRB
#define MOSI PB3
#define CLK PB5
#define SS PB2

void spi_write_8b(unsigned char byte)
{
	SS_PORT &= ~_BV(SS);
	SPDR = byte;
	while(!(SPSR & _BV(SPIF)));
	SS_PORT |= _BV(SS);
	SS_PORT &= ~_BV(SS);
}

void spi_write_16b(uint16_t word)
{
	SS_PORT &= ~_BV(SS);
	SPDR = (unsigned char) (word & 0xFF);
	while(!(SPSR & _BV(SPIF)));
	SPDR = (unsigned char) ((word & 0xFF00) >> 8);
	while(!(SPSR & _BV(SPIF)));
	SS_PORT |= _BV(SS);
	SS_PORT &= ~_BV(SS);
}

int main(void)
{
        SS_DDR |= _BV(MOSI)|_BV(CLK)|_BV(SS);
        //SPCR = _BV(SPE)|_BV(MSTR)|_BV(DORD); /* LSB */

        SPCR = _BV(SPE)|_BV(MSTR); /* MSB */

        for(;;)
        {
                for(uint16_t i = 0; i < UINT16_MAX; i++)
                {
                        /* Register order: fills from last register down the chain
                        * upwards.
                        * Bits: MSB: Start at Q0 pin.
                        *       LSB: Start at Q7 pin.
                        */

                        /* Increment from right to left */
                        SPCR = _BV(SPE)|_BV(MSTR)|_BV(DORD); /* LSB */
                        spi_write_16b(i);
                        _delay_ms(1);
                }

                for(uint16_t i = 0; i < UINT16_MAX; i++)
                {
                        /* Register order: fills from last register down the chain
                        * upwards.
                        * Bits: MSB: Start at Q0 pin.
                        *       LSB: Start at Q7 pin.
                        */

                        /* Increment from left to right */
                        /* Send as MSB the upper bytes first */
                        /* ((i & 0x00FF) << 8) | ((i & 0xFF00) >> 8) */
                        SPCR = _BV(SPE)|_BV(MSTR); /* MSB */
                        spi_write_16b(((i & 0x00FF) << 8) | ((i & 0xFF00) >> 8));
                        //spi_write_16b(i);
                        _delay_ms(1);
                }
        }
}
