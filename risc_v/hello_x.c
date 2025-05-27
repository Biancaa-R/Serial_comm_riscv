#define UART0_BASE 0X10000000
#define REG(base,offset) ((*((volatile char *)(base + offset))))
#define UART0_DR  REG(UART0_BASE ,0X00)
#define UART0_FCR  REG(UART0_BASE,0X02)
#define UART0_LSR  REG(UART0_BASE,0X05)
#define UARTFCR_FFENA 0x01
#define UARTLSR_THRE 0X20
#define UARTLSR_DATA_READY 0x01

volatile char value[30];

void uart_putc(char c){
    while(!(UART0_LSR & UARTLSR_THRE));
    UART0_DR = c;
}

char uart_getc(){
    while(!(UART0_LSR & UARTLSR_DATA_READY)); // wait until data ready
    return UART0_DR;
}

void uart_puts(const char *str){
    while(*str){
        uart_putc(*str++);
    }
}

void delay(volatile unsigned int count) {
    while(count--) {
        __asm__ volatile("nop");
    }
}

int main() {
    int i = 0;
    UART0_FCR = UARTFCR_FFENA;  // Enable FIFO

    uart_puts("Hello world\n");
    uart_puts("Time is 12.06 pm now\n");
    uart_puts("Enter text: ");

    while(i < sizeof(value) - 1) {
        char c = uart_getc();
        if(c == '\r' || c == '\n') {
            break; // end input on Enter key
        }
        value[i++] = c;
        uart_putc(c); // echo back each character
    }
    value[i] = '\0'; // null terminate

    uart_puts("\nYou typed: ");
    uart_puts(value);
    uart_puts("\n");

    while(1); // infinite loop

    return 0;
}
