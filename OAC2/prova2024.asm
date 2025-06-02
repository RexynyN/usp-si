
3) 

.data
a: .word 5
b: .word 0

.text
main :
    lw $s0, a($zero)
    slt $t0,$s0,$zero
    beq $t0,$zero, else
    sub $s1,$zero ,$s0
    addi $s1 ,$s1 , -1
    j fim_if
else : 
    sll $s1,$s0, 1
    add $s1,$s1,$s0

fim_if:
    sw $s1 ,b($zero)

a) 
// comp = $s0, resul = $s1
int a = 5;
int b = 0;

int comp = a;
int resul;

if (comp >= 0) {
    resul = -comp;
    resul = resul - 1;
} else {
    resul = comp * 2;
    resul = resul + comp;
}

b = resul;


6) 
a)

lw $s2, 0($s1)
sw $s6, 50($s1)
lw $s1, 40($s6)
add $s6, $s2, $s2
nops
sub $s6, $s1, $s2
nops
nops
or $s3, $s6, $zero 


b) 


lw $7, 40($s6)
lw $s2, 0($s1)
sw $s6, 50($s1)
nops
sub $s6, $7, $s2
add $7, $s2, $s2
nops
or $s3, $s6, $zero 

c) 

Teríamos um problema, pois o as instruções sw da primeira linha e lw da segunda linha vão estar 
respectivamente no estágio de memória 