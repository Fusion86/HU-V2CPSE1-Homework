.cpu cortex-m0
.align 1
.text

.global float_zero
float_zero: .word 0

// float inner_product(float a[], float b[], int length) {
.global inner_product
inner_product:
    push { r4, r5, r6, r7, lr }
    // r4 = sum
    // r5 = float a*
    // r6 = float b*
    // r7 = iterator * 4
    // r8 = length

    // Init
    ldr r4, =float_zero     // Set sum to 0
    mov r5, r0              // Need to move r0 to r5 to preserve it
    mov r6, r1              // ^
    ldr r7, =0              // Set iterator to 0

    // Multiply length * 4 to get length in bytes
    mov r1, #4
    mul r2, r2, r1          
    mov r8, r2              // Move r2 (length) to r8 to preserve it
loop:
    // Load a[i] and b[i] to r0 and r1
    ldr r0, [r5, r7]        // Load a[i] to r0 (i = r7)
    ldr r1, [r6, r7]        // Load b[i] to r1

    // Call float_multiply for a[i] and b[i] which are stored in r0 and r1,
    // this stores the result in r0
    bl float_multiply

    mov r1, r4              // Copy r4 to r1 so that we can pass it to float_multiply
    bl float_add            // Add result from float_multiply to sum
    mov r4, r0              // Move new sum to r4 (to preserve it)

    add r7, r7, #4          // Increment iterator with 4 (because a float is 4 bytes)
    mov r1, r8              // Move r8 to r1 so that we can `sub` it
    sub r0, r1, r7          // r0 = length - i
    bne loop                // goto loop if r0 != 0

    // Exit
    mov r0, r4              // Move r4 to r0 to return sum
    pop { r4, r5, r6, r7, pc }
