###################################
# Makefile for AVR

SHELL= /bin/bash

# Target name:
TARGET = SPI_DAISYCHAIN
 
# Target type
MCU= atmega328p
PROGRAMMER= jtag3isp
F_CPU= 16000000UL

SRC = $(wildcard *.c ./include/*.c)
OBJ = $(SRC:.c=.o)
OPTIMIZATION = -Os
CC_GARBAGE = "-ffunction-sections"
LD_GARBAGE = -Wl,-gc-sections

# Compiler / Linker flags:
CFLAGS = -mmcu=$(MCU) -Wall  $(CC_GARBAGE) $(OPTIMIZATION) -std=gnu99 -D F_CPU=$(F_CPU) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -fdata-sections
LDFLAGS = -mmcu=$(MCU) $(LD_GARBAGE) -Wl,-Map=$(TARGET).map 

###################################
# Makerules:
 
 
.PHONY: compile flash clean

compile: $(TARGET).hex $(TARGET).eep $(TARGET).lss $(TARGET).elf
	avr-size -C --mcu=$(MCU) $(TARGET).elf
	
flash: compile
	avrdude -c $(PROGRAMMER) -P usb -p $(MCU) -U flash:w:$(TARGET).hex

clean:
	rm -f $(OBJ)
	rm -f $(TARGET).{elf,hex,lss,map,eep}

 
 
###################################
# Psudorules:
 
%.eep: %.hex
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex $< $@

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.lss: %.elf
	avr-objdump -h -S $< > $@

%.elf: $(OBJ)
	avr-gcc $^ $(LDFLAGS) -o $@

%.o : %.c
	avr-gcc $(CFLAGS) -c $< -o $@
