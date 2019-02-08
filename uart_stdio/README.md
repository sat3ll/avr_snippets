# Description
Simple UART (asynchronous) communications demo with `printf()` and `scanf()`.

## uart_stdio.c

Baud rate set at compile time by `BAUD` macro.

## Makefile

`make` compiles the demo.  
`make flash` compiles and flashes the demo to device.  
`make clean` deletes compiled code/cleans.  

### Programmer
Change `PROGRAMMER` to your programming device (consult `avrdude` docs).  
In this case, `jtagice3` is used.

### MCU clock
Defined by `F_CPU`, for Arduino its 16MHz (16000000UL).  
This setting is fuse dependent (clock divisor bits, type of oscillator,
oscillator value).

### STDIO routines

#### For minimal support (no float formatting)
Define:

| VARIABLE    | VALUE |
| ----------  |-------|
| SCANF_MIN   | YES   |
| SCANF_FLOAT | NO    |
| PRINTF_MIN  | YES   |
| PRINTF_FLOAT| NO    |

#### For full support (with everything)
Define:

| VARIABLE    | VALUE |
| ----------  |-------|
| SCANF_MIN   | NO    |
| SCANF_FLOAT | YES   |
| PRINTF_MIN  | NO    |
| PRINTF_FLOAT| YES   |
