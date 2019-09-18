@ Gemaakt door Wouter Visser
@ Aangemaakt op 17-09-2019

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
invert_char:
    cmp r0, #'z'            @ If r0 > 'z'
    bgt invert_char_end		@ Goto end
    cmp r0, #'a' 	        @ If r0 >= 'a'
    bge subtract 	        @ Goto subtract
    cmp r0, #'Z' 	        @ If r0 > 'Z'
    bge invert_char_end     @ Goto end
    cmp r0, #'A'	        @ If r0 >= 'A'
    bge add 		        @ Goto add
    b invert_char_end
subtract:
    @ Decrementing an ASCII character with 32 makes it uppercase
    sub r0, #32 	        @ Make lowercase
    b invert_char_end
add:
    @ Incrementing an ASCII character with 32 makes it lowercase
    add r0, #32 	        @ Make uppercase
invert_char_end:
    mov pc, lr
