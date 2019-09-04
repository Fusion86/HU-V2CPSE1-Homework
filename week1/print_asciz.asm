.cpu cortex-m0
.align 2


.data
str_hello_world:
    .asciz "Hello world\n"


.text
.global print_asciz
print_asciz:
    @ r0 is where we store our character
    @ r5 is a pointer to the next character to load

    push { r5, lr }     @ Save r5 and lr
    mov r5, r0

loop:
    ldrb r0, [r5]       @ Load character into r3
    add r0, r0, #0      @ If character == \0
    beq done            @ Return
    bl invert_char      @ Invert case for r0
    bl uart_put_char    @ Print r0
    add r5, r5, #1      @ Increment array pointer
    b loop

done:
    pop { r5, pc }          @ Restore pc


.global application
application:
    push { lr }
    ldr r0, =str_hello_world    @ Load ptr to szstring
    bl print_asciz
    pop { pc }