# EX - 1
VET: .word 23 -43 55 -9 -7 21 -76 12 -45 -10
TAM: .word 10 


MAIN: 
    la $s0, VET
    la $s1, TAM 
    lw $s1, 0($s0) 


LOOP:
    beq $s1, $zero, END_LOOP  # while len > 0 
    
    lw $s2, 0($s0)  # <- vet[idx]
    jal CALC_ABS 
    sw $v0, 0($s0) # vet[idx] <- 

    addi $s0, $s0, 4 # idx++
    subi $s1, $s1, 1 # len--
    j LOOP

CALC_ABS:
    bgt $a0, $zero, RETURN_CALC  # if int > 0 
    sll $t2, $a0, 1	# int * 2 
    add $a0, $a0, $t2  # int += int * 2
    move $v0, $a0

RETURN_CALC: 
    jr $ra

END_LOOP: 
    li $v0, 10
    syscall 


sltiu $t2,$t1,65
bne $t2,$zero,nxtch
sltiu $t2,$t1,91
beq $t2,$zero,nxtch
addiu $t4,$t4,1
nxtch: addiu $t0,$t0,4
lw $t1,0($t0)
j loop
end: sw $t4,0($t3) 


# EX - 3

add $5, $2, $1 
lw $3, 4($5) 
lw $2, 0($2) 
or $3, $5, $3 
addi $4,$3,4  

# Res A:

add $5, $2, $1 
nops 
nops 
lw $3, 4($5)  # -> 5 ainda está calculando 
lw $2, 0($2) 
nops
or $3, $5, $3 # -> 3 precisa de uma instrução de distância 
nops 
nops 
addi $4,$3,4  # -> 3 ainda está calculando 


# Res B: 

add $5, $2, $1 
lw $2, 0($2) 
nops
lw $3, 4($5) 
nops 
nops
or $3, $5, $3 
nops
nops
addi $4,$3,4  



# Resp C: 

add $5, $2, $1
lw $3, 4($5) 
lw $2, 0($2)
or $3, $5, $3
addi $4, $3, 4

# O único problema que poderia ocorrer é se alguém precisasse de $3 logo após (2). Não é o caso, pois o lw em (3) deu o tempo
# necessário para o forwarding funcionar entre (2) e (4). Então não há problema