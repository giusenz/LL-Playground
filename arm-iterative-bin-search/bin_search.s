.text
.global bin_s
.type bin_s, %function

@r0 := array start
@r1 := array size
@r2 := key

@r3 := mid

@If the key is found, return its index.
@Otherwise, return -1.

bin_s:
    push {r4,r5,r6}
    mov r4,#0
    sub r1,r1,#1
    mov r5,r1
loop:    
    cmp r4,r5 
    movhi r0,#-1 @left > right
    bhi endl
    sub r3,r5,r4
    lsr r3,r3,#1
    add r3,r4,r3
    ldr r6,[r0,r3,lsl #2]
    cmp r6,r2
    moveq r0,r3
    beq endl
    addlo r3,r3,#1
    movlo r4,r3
    subhi r3,r3,#1
    movhi r5,r3  
    b loop    
endl:
    pop {r4,r5,r6}
    mov pc,lr
   
