# Ex 1 

QX: 
    li $t1, 32 
    li $s0, 0
    li $s1, 32
    add $s0, $s0, $a0
L1: 
    addiu $s0, $s0, 1
    sub $s1, $s1, $s0 
    bne $s0, $t1, L1

jr $ra 


int qx (int i) {
    t1 = 32
    s0 = 0 
    s1 = 32 
    s0 = s0 + i 

    do {
        s0 = s0 + 1 
        s1 = s1 - s0 
    } while(s0 != t1); 
} 



# Ex 3 


i = $s0 
v[] = $s1 
a = $s2
b, c, d = s3, s4, s5
LOOP: 
    slti $t0, $s0, 100 # while i < 100
    bne $t0, $zero, END 

    sll $t2, $s0, 2      # i * 4 
    add $s1, $s1, $t2    # [i]
    lw $t1, 0($s1)       # v[i]
    addi $t1, $t1, 1     # v[i] + 1 

    addi $t3, $t2, 4    # [i + 1]
    sw $t1, 0($t3)      # v[i + 1] <- v[i] + 1 

    addi $t5, $zero, 10 
    bne $t1, $t5, ADD_A   # if v[i + 1] != 10 

LOOP_CONT: 
    addi $s0, $s0, 1  # i++ 

    sll $t4, $s3, 1   # c * 2  
    sub $t4, $t4, $s5 # c * 2 - d

    j LOOP

ADD_A: 
    add $s2, $s2, 1  # a++
    j LOOP_CONT

END: 
    li $v0, 10 
    syscall 


# Ex 6


a1 ^ 2 


i = 0 
while (i < 50000) {
    comp = v[i] 
    count = 0
    while(j < 50000) {
        if v[j] == comp  {
            word = comp
            count++
        }
        j++
    }
    i++ 
} 

return word, count



HERE: 
    beq $1, $2, there 

    .... UM MONTE DE CODIGO ...


THERE: 
    add $1, $1, $1




beq 

OPCODE  reg1  reg2  id_linha  
beq      $1    $2     THERE -> 10000

<- 32K -> 

64K 

id_linha -> 16 bits  ->  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0


SE FOSSEM UMA CARALHADA DE LINHAS 


# Ex IMPAR PAR 

.data 
VET: .word 23 -55 23 -68 90 -123
TAM: .word 6
PAR: .word 0
IMPAR: .word 0


# 10101000
# 00000001
# 00000000

# 0 0 -> 0
# 1 0 -> 0
# 0 1 -> 0
# 1 1 -> 1


MAIN: 
    la $s0, VET 
    lw $s1, TAM 
    li $t0, 0 # i
    li $s2, 0 # par 
    li $s3, 0 # impar

LOOP: 
    slt $t1, $t0, $s1     # while (i < 6 [TAM]) 
    beq $t1, $zero, END   # i >= 6;  break

    lw $t2, 0($s0)      # VET[i]
    andi $t2, $t2, 1    # 0 se par, 1 se impar
    beq $t2, $zero, PAR 
    addi $s3, $s3, 1    # IMPAR++
    j NEXT 

PAR: 
    addi $s2, $s2, 1  # PAR++

NEXT: 
    addi $t0, $t0, 1 # i++ 
    addi $s0, $s0, 4 # [i + 1]
    j LOOP

END:
    la $t0, PAR
    sw $s2, 0($t0) 
    la $t0, IMPAR
    sw $s3, 0($t0)

    li $v0, 10 
    syscall 



lw $t0, 100($t1)

addi $t1, $s1, 100 
lw $t0, $t1 




