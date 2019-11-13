.cpu cortex-m0
.align 2

.data

buffer:
    .skip 40
    .byte 0

.text
.global decode_str_compressed
decode_str_compressed:
	push { r4, r5, r6, lr }
	ldr r4, =str_compressed

loop:
	ldrb r0, [ r4 ]             @ Read char

    cmp r0, #0                  @ Goto exit if char == \0
    beq done

	cmp r0, #64                 @ Goto decompress if char == '@'
	beq decompress

	bl add_buffer               @ Buffer stuff
	bl uart_put_char            @ Print character

    add r4, r4, #1              @ Increment ptr
    b loop

decompress:
	add r4, #1                  @ Skip '@' token

	@ Store token offset
	ldrb r5, [r4]
	sub r5, #'0'
	ldr r0, =buffer
	add r5, r0

	@ Store token size
	add r4, #1
	ldrb r6, [r4]
	sub r6, #'0'

    @ Skip size character
	add r4, #1

sub_loop:
    @ If size == 0 go back to main loop
	cmp r6, #0
	beq loop

    @ Subtract size and load char
	sub r6, #1
	ldrb r0, [r5]

    @ Buffer stuff and print character
	bl add_buffer
	bl uart_put_char
	b sub_loop                  @ Resume this loop

done:
   pop { r4, r5, r6, pc }       @ Return


add_buffer:
    push { r4, lr }
    ldr r1, =buffer
    mov r4, r1
    add r4, #39                 @ 39 is the last index in the buffer

 buffer_loop:
    ldrb r2, [r4]
    strb r2, [r4, #1]

    sub r4, #1                  @ Subtract 1 from buffer index
    cmp r4, r1                  @ If buffer index is not 0
    bge buffer_loop             @ Loop again

    strb r0, [r1]
    pop { r4, pc }              @ Exit
