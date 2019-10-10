.cpu cortex-m0
.align 2


.bss
.lcomm buffer, 100


.text
.global decode_str_compressed
@ void decode_str_compressed()
@ ----
@ r0 = read() puts read character here
@ r4 = ptr to the next character that should be read
@ ----
decode_str_compressed:
    push { lr }
    ldr r4, =str_compressed

decompress:
    bl read                     @ Read next character
    add r0, #0                  @ If character == \0
    beq done                    @ Return
    @ TODO
    bl add_char
    b decompress

done:
    pop { pc }


@ char read()
read:
    ldr r0, [r4]
    add r4, r4, #1
    mov pc, lr


@ void add(char c)
add_char:
    push { lr }
    bl uart_put_char
    pop { pc }
