.cpu cortex-m0
.align 2


.data
str_hello_world:
    .asciz "Hello world\n"


.text
.global print_asciz
print_asciz:
    push { lr }         @ Store lr (prev pc)

loop:
    ldrb r3, [r0]       @ Load character into r3
    add r3, r3, #0      @ If character == \0
    beq done            @ Return
    bl uart_put_char
    add r0, r0, #1      @ Increment array pointer
    b loop

done:
    pop { pc }          @ Restore pc


.global application
application:
    ldr r0, =str_hello_world    @ Load ptr to szstring
    bl print_asciz