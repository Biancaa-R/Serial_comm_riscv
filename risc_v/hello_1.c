//Enable fifo control register
//5 transmitter hiolding regster to see if it is empty
#define UART0_BASE 0X10000000 //base address of mit pdos -risc v
#define REG(base,offset) ((*((volatile char *)(base + offset))))
#define UART0_DR  REG(UART0_BASE ,0X00) 
//for both tx and rx
#define UART0_FCR  REG(UART0_BASE,0X02)  //fifo control register to enable fifo control
#define UART0_LSR  REG(UART0_BASE,0X05) //accessing the lsr -if fifo is ready to recieve data
#define UARTFCR_FFENA 0x01 //uart fifo control enable //zeroth position so 1
#define UARTLSR_THRE 0X20  //Uart line status register --Transmit bit
//val=UART0_LSR & UARTLSR_THRE;
//#define UART0_FF_THR_EMPTY(val)
#define UART0_FF_THR_EMPTY() ((UART0_LSR & UARTLSR_THRE) != 0)
//just to check if the fifo is empty
//#include <unistd.h> --> does not work due to free standing
#define UARTLSR_DATA_READY 0x01  // RX data ready bit in LSR (usually bit 0)
#define UART0_RX_READY() ((UART0_LSR & UARTLSR_DATA_READY) != 0)

char value[30];

void *memset(void *s, int c, unsigned int n) {
    unsigned char *p = (unsigned char *)s;
    for (unsigned int i = 0; i < n; i++) {
        p[i] = (unsigned char)c;
    }
    return s;
}

void uart_putc(char c){
    while(!UART0_FF_THR_EMPTY());
    UART0_DR=c; //set the data register with the value of the character
    //writing character to the transmitetr
}

char uart_getc(){
    while(UART0_LSR & 0x01){
    //char c;
    //set the data register with the value of the character
    //c=UART0_DR;
    //return c;
    return UART0_DR;
    }
    //writing character to the transmitetr
}

void uart_puts(const char *str){
    while(*str){
        uart_putc(*str++); //loop over each value of the string ->advance pointer
        //write another caharcter and increment 
    }
}

char* uart_gets(){
    //enna panren
    int i=0;
    
    while(!UART0_FF_THR_EMPTY()){
        value[i]=uart_getc();
        i=i+1;

    }
    return value;

}

void delay(volatile unsigned int count) {
    while (count--) {
        __asm__ volatile("nop");
    }
}

void uart_echo_loop(void) {
    while (1) {
        if (UART0_LSR & 0x01) {  // RX ready bit (check your UART spec)
            char c = UART0_DR;
            uart_putc(c);       // echo received char back
        }
    }
}


void main()
{
    volatile char value[30];
    UART0_FCR =UARTFCR_FFENA; //enable fifo control reg
    uart_puts("Hello world\n");
    uart_puts("Time is 12.06 pm now\n");
    //uart_echo_loop();
    //writing this string to uart
    //if (UART0_FF_THR_EMPTY()){
        //wait till all values are passed
        //delay(500000);
        //value=uart_gets();
        //char result[100]= "Hello %s\n",*value;
        //uart_puts(result);
        int i=0;
        // while (i < 29) {
        // char c = uart_getc();  // blocking read char from uart
        // if (c == '\n' || c == '\r') break;
        //     value[i++] = c;
        // i+=1;    
        // }
        // value[i] = '\0';  // null terminate string
        while(i < sizeof(value) - 1) {
            char c = uart_getc();
            if(c == '\r' || c == '\n') {
                break; // end input on Enter key
            }
            value[i++] = c;
            //uart_putc(c); // echo back each character
        }
        value[i] = '\0'; // null terminate

    uart_puts("Hello ");
    uart_puts(value);
    uart_puts("\n");
        while(1); //loo loo
        return 0;
    //}
}

