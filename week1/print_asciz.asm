.cpu cortex-m0
.align 2


.data
str_hello_world:
    .asciz "Hello world, the ANSWER is 42! @[]`{}~\n"


.text
@ void print_asciz(const char*)
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
    pop { r5, pc }      @ Restore pc


@ void application()
.global application
application:
    push { lr }
    ldr r0, =str_hello_world    @ Load ptr to szstring
    bl print_asciz
    pop { pc }


@ char invert_char(char)
@ NOTE: Apparently xor r0, #32 also works instead of add/sub.
@ But I haven't tested this.
invert_char:
    cmp r0, #64
    ble invert_char_other       @ if not r0 > 64 goto invert_char_other
    cmp r0, #91
    bge invert_char_other       @ if not r0 < 91 goto invert_char_other

    @ If we got this far it means that (r0 > 64 && r0 < 91)
    add r0, r0, #32             @ Make character lowercase
    b invert_char_end

invert_char_other:
    @ if (r0 > 96 && r0 < 123) { r0 - 32; }
    cmp r0, #96
    ble invert_char_end     @ if not r0 > 96 goto end
    cmp r0, #123
    bge invert_char_end     @ if not r0 < 123 goto end

    @ If we got this far it means that (r0 > 96 && r0 < 123)
    sub r0, r0, #32         @ Make character uppercase

invert_char_end:
    mov pc, lr
