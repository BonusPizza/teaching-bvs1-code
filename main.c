#include <stdint.h>
#include "process.h"

#define UART0_BASE 0x10000000UL
#define UART_THR    0
#define UART_LSR    5
#define UART_LSR_THRE 0x20

static volatile uint8_t *const uart0 = (volatile uint8_t *)UART0_BASE;

static void uart_putc(char c)
{
    while ((uart0[UART_LSR] & UART_LSR_THRE) == 0) {
    }

    uart0[UART_THR] = (uint8_t)c;
}

static void uart_puts(const char *s)
{
    while (*s != '\0') {
        if (*s == '\n') {
            uart_putc('\r');
        }

        uart_putc(*s++);
    }
}

void hello(){
    uart_puts("HelloBVS1 form Vinc und Luc\n");
    process_yield();
    uart_puts("genug pause\n");

}

void main(void)
{
struct process a;
process_create(&a, hello);

process_run(&a);
process_run(&a);

uart_puts("zurück");

    for (;;) {}
}
