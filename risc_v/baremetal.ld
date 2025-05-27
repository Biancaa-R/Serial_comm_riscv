/* baremetal.ld */

/* Define the entry point of the program */
ENTRY(_start)

SECTIONS {
    /* Start program at QEMU default address for RISCV */
    . = 0x80000000; /*qemu default load address*/

    .text : {
        /* Ensure the _start symbol (boot/startup code) is included */
        KEEP(*(.text._start))
        *(.text*)
        /*Text section being writable*/
    }

    /* Align to page size (commonly 4096 bytes) */
    . = ALIGN(CONSTANT(COMMONPAGESIZE));

    .data : {
        *(.data*)
        /*daa section being executable*/
    }

    /* Optional: You may want to add BSS and stack if needed -not necessary here*/
}
