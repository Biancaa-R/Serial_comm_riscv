//Enable fifo control register
//5 transmitter hiolding regster to see if it is empty
#define UART0_BASE 0X10000000 //base address of mit pdos -risc v
#define REG(base,offset) ((*((volatile char *)(base + offset))))
#define UART0_DR  REG(UART0_BASE ,0X00) 
#define UART0_FCR  REG(UART0_BASE,0X02)  //fifo control register to enable fifo control
#define UART0_LSR  REG(UART0_BASE,0X05) //accessing the lsr -if fifo is ready to recieve data
#define UARTFCR_FFENA 0x01 //uart fifo control enable //zeroth position so 1
#define UARTLSR_THRE 0X20  //Uart line status register --Transmit bit
//val=UART0_LSR & UARTLSR_THRE;
//#define UART0_FF_THR_EMPTY(val)
#define UART0_FF_THR_EMPTY() ((UART0_LSR & UARTLSR_THRE) != 0)
//just to check if the fifo is empty

void uart_putc(char c){
    while(!UART0_FF_THR_EMPTY());
    UART0_DR=c; //set the data register with the value of the character
    //writing character to the transmitetr
}

void uart_puts(const char *str){
    while(*str){
        uart_putc(*str++); //loop over each value of the string ->advance pointer
        //write another caharcter and increment 
    }
}

void main()
{
    UART0_FCR =UARTFCR_FFENA; //enable fifo control reg
    uart_puts("Hello world\n");
    uart_puts("Time is 12.06 pm now\n");
    //writing this string to uart
    while(1); //loo loo
}

