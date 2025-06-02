.data
w:          .word 3                # Tamanho da janela (4-byte aligned)
h:          .word 1                # Previsão de um ponto no futuro (4-byte aligned)
k:          .word 3                # Vizinhos mais próximos (4-byte aligned)
rows:          .word 0                 # Numero de linhas na matriz do dataset (setado pelo "cria_matriz")

arr_len:    .word 0                # numero de elementos dentro dos arrays dos arquivos

file_name:  .asciiz "input.txt"    # Nome do arquivo de entrada
input_data: .space 10000            # Espaço para armazenar 500 inteiros (500 * 4 bytes)

buffer:     .space 300              # Buffser temporário para leitura de uma linha (aligned for integers)
xtrain:     .space 10000            # Espaço para xtrain (500 * 4 bytes)
ytrain:     .space 10000             # Espaço para ytrain (500 * 4 bytes)
xtest:      .space 10000            # Espaço para xtest (500 * 4 bytes)
ytest:      .space 10000            # Espaço para ytest (500 * 4 bytes)
distancias: .space 10000            # Matriz de distâncias (500 * 4 bytes)
result_reg: .space 10000            # Resultados da regressão (500 * 4 bytes)
result_reg: .space 10000            # Resultados da regressão (500 * 4 bytes)
newline:    .asciiz "\n"           # Newline character

.text
.globl MAIN
MAIN:
	# Transforma a entrada de treinamento em uma matriz
    la $a0, in_train            
    la $a1, x_train                 
    lw $a2, slide                    
    jal ARR_TO_MATRIZ                

	# Faz predição de valores
	la $a0, in_train
	la $a1, y_train
    jal KNN_PREVISAO        


	# Transforma a entrada de teste em uma matriz
	la $a0, in_test            
    la $a1, x_test	                
    lw $a2, slide                 
    jal ARR_TO_MATRIZ      


	# Transforma a entrada de teste em uma matriz
	la $a0, in_test            
    la $a1, y_test	                
    jal KNN_PREVISAO             

	# Calcula a distância entre pontos de treinamento e de teste
    la $a0, x_train                 
    la $a1, x_test                  
    jal KNN_DISTANCIA           

	# Dado as distâncias e os pontos de treinamento, faz a regressão
    la $a0, dist           
    la $a1, y_train                 
    jal REGRESSAO_MATRIZ       

	# Print do array de regressão
	la $a0, regr
    jal PRINT_ARRAY    

    # Grand Finale
    li $v0, 10                     
    syscall

# @args -> $a0 = xtrain, $a1 = xtest
KNN_DISTANCIA:
    # Como não se perder:
	# $t4 -> x_train
	# $a1 -> x_test
	# $a2 -> dist
	# $f0 -> modulo    
	
	la $a2, dist
	move $t4, $a0 # x_train
	move $a1, $a1 # x_test
    lw $t1, slide 
    lw $t5, rows 

    li $s0, 0 # i = 0

	KNN_DISTANCIA_L1: 
		li $s1, 0 # j = 0

	KNN_DISTANCIA_L2: 
		li $s2, 0 # k = 0
		l.s $f0, zerof # Módulo
		
		# Calculando distancia[i][j]
		mul $t3, $s0, $t1      
		addu $t3, $t3, $s1     
		sll $t3, $t3, 2       
		addu $t3, $a2, $t3     
	
	KNN_DISTANCIA_L3: 
		# Calculando train[j][k]
		mul $t2, $s1, $t1        
		addu $t2, $t2, $s2       
		sll $t2, $t2, 2          
		addu $t2, $t4, $t2 		 
		l.s $f14, 0($t2)         

		# Calculando teste[i][k]
		mul $t0, $s0, $t1     
		addu $t0, $t0, $s2 
		sll $t0, $t0, 2 
		addu $t0, $a1, $t0 
		l.s $f16, 0($t0)
		
		# Calculando a distância
		sub.s $f2, $f16, $f14   
		abs.s $f2, $f2         
		add.s $f0, $f0, $f2    
		
		# Loop mais interno 
		addiu $s2, $s2, 1 
		bne $s2, $t1, KNN_DISTANCIA_L3 
		
		# Salva modulo
		s.s $f0, 0($t3) # distancia[i][j] = modulo 
		
		# Loop menos interno 
		addiu $s1, $s1, 1 
		bne $s1, $t5, KNN_DISTANCIA_L2 
		
		# Loop externo
		addiu $s0, $s0, 1 
		bne $s0, $t5, KNN_DISTANCIA_L1 
	
		# Retorna 
		move $v0, $a2  # matrix dist
		move $v1, $t5  # num. colunas matrix
		jr $ra
		

# @args -> $a0 = dist, $a1 = ytrain
REGRESSAO_MATRIZ:
	subi $sp, $sp, 4
	sw $ra, 0($sp)

	lw $t0, slide 
	lw $t1, knn 
	lw $t5, rows  # Tamanho matriz
	la $s2, regr # Cabeça do array de regressão 
	move $s0, $a0 # Matriz de Distancias 
	move $s1, $a1 # Matriz de y_train

	# Transforma knn em float
	mtc1 $t1, $f0
	cvt.s.w $f0, $f0 

	li $t2, 0 # i = 0
	REGRESSAO_MATRIZ1:
		# Copia uma linha da matriz para ser ordenada
		# dist[i] -> linha
		mul $t6, $t2, $t0  
		sll $t6, $t6, 2  
		
		# Ordenar o array para pegar os knn-menores 
		move $a0, $s0  # Distancia
		move $a1, $t6  # Offset 
		move $a2, $s1  # y_train
		move $a3, $t0  # slide
		jal ARRAY_ORD
		
		# Media 
		l.s $f2, zerof   
		li $t3, 0  # j = 0
	REGRESSAO_MATRIZ2: 
		# y_train[i][j]
		mul $t7, $t2, $t0     
		addu $t7, $t7, $t3 
		sll $t7, $t7, 2    
		addu $t7, $s1, $t7
		l.s $f4, 0($t7)       
		
		# Media += y_train[i][j]
		add.s $f2, $f2, $f4 

		# Loop interno 
		addi $t3, $t3, 1
		bne $t3, $t1, REGRESSAO_MATRIZ2 # j != knn
		
		# Média da linha -> regr
		div.s $f2, $f2, $f0
		sll $t4, $t2, 2
		addu $t4, $s2, $t4  
		s.s $f2, 0($t4)
		
		# Loop externo
		addiu $t2, $t2, 1
		bne $t2, $t5, REGRESSAO_MATRIZ1 # i != rows
		
		move $v0, $s2 # Array
		move $v1, $t5 # Número elementos array regressao

		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra

# @args -> $a0 = array, $a1 = offset, $a2 = y_train, $a3 = slide
ARRAY_ORD:
	# Salva os registradores que vamos usar
	sub $sp, $sp, 28
	sw $t0, 24($sp)
	sw $t1, 20($sp)
	sw $t2, 16($sp)
	sw $t3, 12($sp)
	sw $t4, 8($sp)
	sw $t5, 4($sp)
	sw $t6, 0($sp)
	
    add $a0, $a0, $a1   # Array + Offset
    add $a2, $a2, $a1   # Array y_train + offset
    
    sll $t0, $a3, 2     # window * 4bytes
    add $t0, $a0, $t0   # Final do array -> array[window] 
    subi $t0, $t0, 4

	ARRAY_ORD_LOOP1:
		# Reset loop           
		add $t1, $0, $0     
		move  $t4, $a0        
		move  $t6, $a2        

	ARRAY_ORD_LOOP2:    
		# Pega arr[i] e arr[i + 1] para comparar            
		l.s $f6, 0($t4)        
		l.s $f8, 4($t4)        
		
		# Sintaxe horrivel pra verificar quem é maior de float
		c.lt.s $f8, $f6          # if $f8 < $f6
		bc1f ARRAY_ORD_CONTINUE  # If == 0 - Sem mudar de posicao

		# Muda os elementos do dist
		add $t1, $0, 1         
		s.s  $f6, 4($t4)        
		s.s  $f8, 0($t4)         
	
		# Muda o elementos do y_train
		l.s $f6, 0($t6)        
		l.s $f8, 4($t6)         
		s.s  $f6, 4($t6)         
		s.s  $f8, 0($t6)         
		
	ARRAY_ORD_CONTINUE:
		# i++
		addi $t4, $t4, 4          
		addi $t6, $t6, 4
		
		bne  $t4, $t0, ARRAY_ORD_LOOP2   # Se final do array
		bne  $t1, $0, ARRAY_ORD_LOOP1   # Enquanto o array não estiver ordenado

		# Recupera os registradores
		lw $t0, 24($sp)
		lw $t1, 20($sp)
		lw $t2, 16($sp)
		lw $t3, 12($sp)
		lw $t4, 8($sp)
		lw $t5, 4($sp)
		lw $t6, 0($sp)
		add $sp, $sp, 28
		
		move $v0, $a0 # Array sorted
		move $v1, $a2 # Array de índices sorted
		jr $ra

# @args -> $a0 = array
PRINT_ARRAY:
    # Inicializa os ponteiros
    move $t0, $a0                  
    li $t1, 0                    
    la $t2, rows      
    lw $t2, 0($t2)               

	PRINT_ARRAY_LOOP:
		bge     $t1, $t2, PRINT_ARRAY_LOOP   # Se não chegou no final do array

		# Print do próximo valor d'array
		sll $t3, $t1, 2               
		addu $t3, $t0, $t3              
		l.s $f12, 0($t3)               
		li  $v0, 2                  
		syscall

		# Print de uma nova linha
		li $v0, 4                    
		la $a0, newline             
		syscall

		# i++
		addiu $t1, $t1, 1
		j PRINT_ARRAY_LOOP

	PRINT_ARRAY_CONT:
		jr $ra                        # Retorna da função


# @args -> $a0 = in_train, $a1 = y_train
KNN_PREVISAO:
	lw $t2, slide
    lw $t3, prev
	lw $s5, arr_len
    move $t0, $a0   # Entrada         
    move $t1, $a1   # Saída

    # Cria o prev + slide
    subi $t2, $t2, 1                    
    add $t4, $t2, $t3
    addi $t2, $t2, 1                

    ble $t3, $t2, KNN_PREVISAO1     # if prev <= slide 
    blt $t2, $t3, KNN_PREVISAO2     # if slide < prev

	KNN_PREVISAO1:
		bge $t4, $s5, KNN_PREVISAO_CONT      
		li $t8, 4                          
		subi $t2, $t2, 1                    

		# Calcula o próximo slide
		mul $t7, $t8, $t4                 
		add $t6, $t0, $t7                
		lwc1 $f0, 0($t6)                   
		swc1 $f0, 0($t1)                   
		addi $t1, $t1, 4                   

		add $t4, $t4, $t3                  
		addi $t2, $t2, 1                   
		j KNN_PREVISAO1

	KNN_PREVISAO2:
		bge $t4, $s5, KNN_PREVISAO_CONT        	 
		li $t8, 4				  
		subi $t2, $t2, 1                                 

		# Calcula o próximo slide		
		mul $t7, $t8, $t4                  
		add $t6, $t0, $t7                  
		lwc1 $f0, 0($t6)                    
		swc1 $f0, 0($t1)                    
		addi $t1, $t1, 4                     

		add $t4, $t4, $t2                  
		addi $t2, $t2, 1                  
		j KNN_PREVISAO2

	KNN_PREVISAO_CONT:
		jr $ra


# @args -> $a0 = array, $a1 = matrix
ARR_TO_MATRIZ:
	move $s2, $a0 
	move $s3, $a1 
    lw $t1, slide 
    lw $t5, arr_len
    subu $t5, $t5, $t1

    li $s0, 0 # i = 0

	ARR_TO_MATRIZ1: 
		li $s1, 0 # j = 0

	ARR_TO_MATRIZ2: 
		# array[i + j]
		addu $t0, $s0, $s1 
		sll $t0, $t0, 2    
		addu $t0, $s2, $t0 
		l.s $f16, 0($t0)  

		# matrix[i][j]
		mul $t2, $s0, $t1       
		addu $t2, $t2, $s1     
		sll $t2, $t2, 2        
		addu $t2, $s3, $t2 	
		s.s $f16, 0($t2) # matrix[i][j] <= arr[i + j]
		
		# Loop interno 
		addiu $s1, $s1, 1
		bne $s1, $t1, ARR_TO_MATRIZ2 # j != slide
		
		# Loop externo
		addiu $s0, $s0, 1
		bne $s0, $t5, ARR_TO_MATRIZ1 # i != array - slide  
		
		# Salva número de linhas
		sw $t5, rows 

		# Retorna
		move $v0, $s3 # Matrix
		move $v1, $t5 # Número linhas matrix
		jr $ra
		
