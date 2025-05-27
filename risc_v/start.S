#Simple c runtime boot startup
#stack allocation and initializing stack pointer
# Jumping to main
.section .text._start
.global _start
_start:
    la sp, __stack_top
    #loading the sp with the label stack __stack_top
    add s0, sp, zero   #frame pointer ->as reference to stack frame 
    jal zero, main
loop: 
    j loop  #struck here

.section .data
    .space 1024*8 #allocate 8k memeory to serve as initial stack
    .align 16
__stack_top:  #stack grows downwards nala yam
