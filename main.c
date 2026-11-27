#include <stdint.h>
#include "process.h"
#include "uart.h"

#define UART0_BASE 0x10000000UL
#define UART_THR    0
#define UART_LSR    5
#define UART_LSR_THRE 0x20

//static volatile uint8_t *const uart0 = (volatile uint8_t *)UART0_BASE;


static void permute(char value[]) {
    char tmp;
    tmp = value[0];
    value[0] = value[1];
    value [1] = tmp;

    uart_puts("process: before yield: ");
    uart_puts(value);
    uart_puts("\n");

    process_yield();

    tmp = value[2];
    value[2] = value[3];
    value[3] = tmp;
}

static void worker(void) {
    char value[] = "bvs1";

    permute(value);

    uart_puts("process: result: ");
    uart_puts(value);
    uart_puts("\n");
}


void main(void) {

    uart_puts("os: booted\n");

    static struct process p;
    process_create(&p, worker);
    os_run();

    for (;;) {}
}
