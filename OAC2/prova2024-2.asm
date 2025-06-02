
.data
newline:
    .asciiz "\n"

    .text
    .globl main

f1:
    # Salvar registradores na pilha
    addi $sp, $sp, -20
    sw $ra, 16($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)
    sw $a3, 12($sp)

    # Inicializar r = 2
    li $t0, 2

    # r = a + r * b
    mul $t0, $t0, $a1      # r * b
    add $t0, $a0, $t0      # a + (r * b)

    # r = c + d + r
    add $t0, $a2, $t0      # c + r
    add $t0, $a3, $t0      # c + d + r

    # Chamar f2(a, b, c, d, r)
    move $a4, $t0          # Passar r como o quinto parâmetro
    jal f2

    # Restaurar registradores e retornar
    lw $ra, 16($sp)
    lw $a0, 0($sp)
    lw $a1, 4($sp)
    lw $a2, 8($sp)
    lw $a3, 12($sp)
    addi $sp, $sp, 20
    jr $ra

f2:
    # Salvar registradores na pilha
    addi $sp, $sp, -24
    sw $ra, 20($sp)
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $a2, 8($sp)
    sw $a3, 12($sp)
    sw $a4, 16($sp)

    # if (a < 10)
    li $t0, 10
    bge $a0, $t0, else_f2  # Pular para else se a >= 10

    # return r * f1(2 + a, b, c - r, d + r)
    addi $a0, $a0, 2       # a = 2 + a
    sub $a2, $a2, $a4      # c = c - r
    add $a3, $a3, $a4      # d = d + r
    jal f1                 # Chamar f1

    # Multiplicar o resultado por r
    lw $a4, 16($sp)
    mul $v0, $v0, $a4      # v0 = r * resultado de f1
    j end_f2

else_f2:
    # else: return 1
    li $v0, 1

end_f2:
    # Restaurar registradores e retornar
    lw $ra, 20($sp)
    lw $a0, 0($sp)
    lw $a1, 4($sp)
    lw $a2, 8($sp)
    lw $a3, 12($sp)
    lw $a4, 16($sp)
    addi $sp, $sp, 24
    jr $ra
    
main:
    # Inicializar x, y, z
    li $t0, 2           # x = 2
    li $t1, 3           # y = 3
    li $t2, 6           # z = 6

    # Passar parâmetros para f1(x, x * z, x + y + z, y - x + z)
    mul $a0, $t0, $t2   # a0 = x * z
    add $a1, $t0, $t1   # x + y
    add $a1, $a1, $t2   # a1 = x + y + z
    sub $a2, $t1, $t0   # y - x
    add $a2, $a2, $t2   # a2 = y - x + z

    # Chamar f1
    jal f1

    # Imprimir resultado
    move $a0, $v0
    li $v0, 1           # Código de syscall para print int
    syscall

    # Nova linha
    li $v0, 4           # Código de syscall para print string
    la $a0, newline
    syscall

    # Encerrar programa
    li $v0, 10          # Código de syscall para exit
    syscall