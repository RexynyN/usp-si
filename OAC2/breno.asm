.data

# ============================= CONSTANTES E VARIAVEIS ========================
# Um "slide" que denomina o tamanho de uma linha do dataset
slide: .word 3
# Quantos pontos no futuro serão previstos                
prev: .word 5
# Número de vizinhos mais próximos a serem considerados no KNN         
knn: .word 3      


# Quantas linhas tem o dataset 
rows: .word 0  
# Numero de elementos no array de entrada
arr_len: .word 474
# Constante zero em float para inicialização de registradores
zerof: .float 0.0
# Símbolo de nova linha
newline: .asciiz "\n"           

# ============================= DECLARAÇÃO DE ESPAÇOS ==============================

# Arrays de entrada (input)
in_test: .float 104823.42, 103921.59, 103513.64, 101005.8, 101561.05, 102719.0, 101946.05, 103778.98, 105686.39, 105530.43, 106926.84, 106369.27, 106669.97, 108015.27, 109096.87, 108941.15, 107935.21, 110206.5, 111302.93, 112610.76, 111910.27, 112143.42, 113228.13, 111897.22, 111695.94, 112247.11, 111995.22, 112232.54, 112462.2, 113367.77, 113643.0, 113905.44, 114829.72, 115180.69, 113533.58, 112880.28, 111727.17, 112891.8, 112001.04, 111590.72, 113143.06, 115173.43, 115165.55, 114468.77, 111594.1, 111209.75, 113900.34, 113663.92, 111715.79, 109924.54, 108957.59, 111112.58, 113076.33, 115306.78, 116156.77, 117269.91, 117460.3, 119062.13, 119082.27, 118739.6, 120013.36, 120260.59, 120001.02, 121569.05, 121279.33, 118885.26, 118226.04, 118861.49, 118320.39, 116963.38, 116149.68, 116781.12, 116181.61, 115686.95, 115056.66, 114343.3, 111076.85, 110684.23, 108214.13, 109349.0, 109922.03, 107876.15, 106639.85, 106529.39, 108336.81, 105302.72, 105109.06, 103251.12, 103109.94, 104395.45, 105690.55, 106924.87, 108246.23, 108788.23, 106248.98, 107056.05, 108499.83, 110340.07, 110579.87, 110577.27, 111889.88, 111943.81, 111035.69, 111350.51, 111363.07, 112391.83, 111102.32, 110185.18, 110066.83, 108367.33, 107091.09, 105476.39, 102598.18, 102067.88, 102800.01, 99824.25, 99853.86, 99678.0, 99523.39, 98081.36, 98672.99, 100765.65, 100592.38, 99619.06, 98542.1, 98951.96, 98607.57, 98293.68, 98721.51, 100731.54, 100282.06, 98212.46, 98257.94, 97878.55, 96119.24, 96552.61, 96919.84, 98243.69, 98286.46, 99034.04, 98926.28, 100269.85, 99773.04, 101436.76, 102596.66, 103164.69, 102225.0, 103361.89, 103776.71, 105893.28, 106473.03, 108403.44, 108657.76, 110236.17, 109717.94, 112767.24, 113033.79, 113507.82, 113707.76, 113807.29, 111486.78, 110503.56, 112856.44, 112897.84, 113532.54, 112295.87, 112323.42, 110430.64, 109523.84, 110408.92, 110867.93, 112202.62, 109770.53, 109922.25, 112307.24, 113398.09, 110793.99, 110546.52, 109950.92, 109282.6, 111823.6, 112516.91, 111941.66, 114046.98, 111712.7, 109121.86, 108376.5, 108448.54, 107664.35, 110047.56, 116147.46, 116230.86, 117199.7, 117560.47, 116377.15, 115927.72, 114819.2, 114300.68, 112106.8, 113626.63, 115744.37, 116276.16, 117170.19, 119921.67, 116015.67, 114625.59, 112765.63, 114636.18, 114533.14, 116037.26, 116927.42, 116907.18, 118148.47, 115339.64, 116153.42, 113578.78, 109775.46, 112255.54, 113166.25, 110240.66, 109706.43, 108868.18, 109749.71, 109035.8, 108845.74, 111831.16, 108976.7, 108783.98, 110909.69, 112478.68, 110925.74, 111921.65, 109402.99, 110188.05, 109067.66, 107249.76, 107518.28, 105345.14, 103536.1, 103739.25, 103737.17, 102859.17, 104739.56, 106865.92, 107436.3, 107551.7, 109698.84, 108739.34, 108578.38, 110237.41, 109733.88, 106376.76, 104167.14, 105336.15, 107641.87, 108963.9, 109128.58, 110816.14, 112516.4, 111843.47, 110907.91, 109213.72, 111442.39, 112219.38, 112921.52, 112040.64, 111746.04, 113028.01, 114271.19, 114178.21, 112318.91, 112273.0, 113429.6, 112071.61, 110140.64, 108518.0, 108727.0, 107832.11, 109951.97, 108001.55, 108074.0, 108839.0, 107849.0, 109599.0, 109941.46, 109173.51, 107152.05, 107581.79, 105807.0, 105706.0, 104933.17, 104374.89, 103325.61, 103865.0, 104700.0, 104227.93, 106539.92, 105071.19, 103608.0, 103121.0, 102930.0, 102683.0, 103434.0, 101982.0, 100922.79, 100998.0, 100221.0, 97926.0, 98833.0, 99672.0, 101185.0, 101796.0, 103714.0, 101883.0, 101505.0, 101869.0, 100978.0, 100822.0, 101849.0, 106218.0, 106890.0, 106458.0, 106279.0, 106023.0, 106149.0, 103913.0, 104367.0, 103947.0, 103220.0, 102310.0, 102923.0, 104431.0, 101927.0, 101798.0, 102175.0, 105161.0, 106028.0, 107114.0, 107446.0, 108256.0, 108469.0, 109029.0, 108194.0, 109459.0, 110113.0, 110745.0, 110213.0, 109852.0, 108800.0, 110058.0, 110906.0, 110333.0, 108967.0, 108339.0, 110568.0, 112558.0, 112697.0, 114610.0, 115489.0, 117022.0, 117337.0, 116753.0, 119068.0, 119208.0, 118757.0, 119858.0, 119623.0, 120420.0, 118959.0, 118977.0, 118246.0, 117524.0, 116683.0, 118388.0, 118092.0, 119673.0, 119072.0, 119548.0, 117427.0, 118897.0, 117942.0, 117557.0, 117671.0, 119268.0, 117711.0, 118218.0, 117842.0, 117558.0, 118090.0, 120220.0, 121344.0, 122003.0, 122560.0, 120002.0, 120188.0, 121945.0, 121249.0, 120859.0, 120586.0, 119509.0, 119378.0, 119090.0, 118412.0, 118350.0, 118067.0, 116809.0, 116171.0, 115592.0, 114973.0, 115404.0, 114433.0, 116160.0, 118135.0, 117025.0, 115838.0, 118051.0, 118404.0, 117537.0, 115744.0, 117893.0, 117776.0, 117331.0, 115979.0, 115316.0, 116885.0, 117968.0, 118181.0, 119393.0, 118759.0, 118288.0, 117864.0, 118695.0, 116147.0, 116009.0, 115922.0, 114193.0, 114327.0, 115742.0, 116565.0, 115055.0, 113430.0, 113609.0, 113283.0, 114169.0, 115158.0, 116737.0, 117050.0, 115760.0, 116526.0, 115907.0, 114059.0, 113996.0, 113145.0, 112814.0, 113762.0, 112840.0, 114777.0, 113303.0, 112534.0, 113157.0, 115062.0, 118160.0, 118422.0, 119268.0, 119180.0, 119036.0, 120561.0, 120411.0, 123165.0, 124639.0, 124773.0, 125957.0, 125626.0, 126035.0, 126553.0, 125517.0, 125726.0, 126541.0, 126168.0
in_train: .float 5727.99, 5635.07, 5599.42, 5567.89, 5530.23, 5457.2, 5413.43, 5532.47, 5503.79, 5634.86, 5804.85, 5834.6, 5817.14, 5823.04, 6053.14, 6201.81, 6082.41, 6227.16, 6181.59, 6043.89, 6156.19, 6245.51, 6355.85, 6432.1, 6286.46, 6338.78, 6487.97, 6444.6, 6508.52, 6652.19, 6432.91, 6293.45, 6214.68, 6188.8, 6411.65, 6299.14, 6222.59, 6050.99, 6096.31, 5968.46, 5909.39, 6143.34, 6123.29, 6277.31, 6363.58, 6244.15, 6130.75, 6165.26, 6257.25, 6222.76, 6304.19, 6227.71, 6227.1, 6348.41, 6352.86, 6292.14, 6337.13, 6314.7, 6248.95, 6202.71, 6028.06, 6126.1, 6294.76, 6270.03, 6259.4, 6232.55, 6270.04, 6276.87, 6254.01, 6334.62, 6382.76, 6415.78, 6358.07, 6390.98, 6464.29, 6534.28, 6512.41, 6489.64, 6560.21, 6588.26, 6551.74, 6563.79, 6513.88, 6535.92, 6458.88, 6446.87, 6521.78, 6605.81, 6626.94, 6612.66, 6651.58, 6631.08, 6626.75, 6608.68, 6631.32, 6744.94, 6733.54, 6766.04, 6798.15, 6798.92, 6675.62, 6648.61, 6588.85, 6503.36, 6401.08, 6549.76, 6543.23, 6533.15, 6641.18, 6658.53, 6697.59, 6704.6, 6666.67, 6559.6, 6582.91, 6523.32, 6570.98, 6523.0, 6556.25, 6556.99, 6541.3, 6625.95, 6645.27, 6649.21, 6631.52, 6591.89, 6644.89, 6666.09, 6735.64, 6836.8, 6797.61, 6947.11, 6872.91, 6836.37, 6855.86, 6677.79, 6657.46, 6680.19, 6654.36, 6784.58, 6910.42, 6891.65, 6942.24, 6912.58, 6957.76, 7006.85, 7039.95, 6955.54, 6997.76, 7159.51, 7297.46, 7427.02, 7454.21, 7478.34, 7411.75, 7621.14, 7667.58, 7655.82, 7816.25, 7835.44, 7904.91, 7817.5, 7890.67, 7759.79, 7759.06, 7849.79, 7736.92, 7788.81, 7964.69, 8095.94, 8102.25, 8171.19, 8147.85, 8316.55, 8670.63, 8764.92, 8699.99, 8816.08, 8950.25, 8771.35, 8701.82, 8719.52, 8959.25, 9149.12, 8927.87, 8776.79, 8828.73, 8978.22, 8961.44, 9074.47, 9125.57, 9180.58, 9419.18, 9565.3, 9317.19, 9314.13, 9499.4, 9263.3, 9172.49, 9087.93, 9302.53, 9301.65, 9327.73, 9380.32, 9271.6, 9044.35, 9138.31, 9237.37, 9302.19, 9705.25, 9836.52, 9737.7, 9819.12, 9732.57, 9517.72, 9455.79, 9490.16, 9565.7, 9418.63, 9422.2, 9473.75, 9634.18, 9708.95, 9731.75, 9761.64, 9858.19, 9982.38, 10074.27, 9993.57, 10218.66, 10179.65, 10437.44, 10491.81, 10681.05, 10647.98, 10282.97, 10353.79, 10498.95, 10505.66, 10640.83, 10714.89, 10745.23, 10764.03, 10960.81, 11133.19, 11300.65, 11344.83, 11360.81, 11110.42, 11029.92, 11106.34, 11333.83, 11396.02, 11428.64, 11489.79, 11851.83, 11828.38, 11953.76, 12118.79, 12205.81, 12205.05, 12121.15, 12238.91, 12587.37, 13053.34, 12873.97, 12757.83, 12567.62, 13002.29, 13259.63, 13284.83, 13493.82, 13502.34, 13617.31, 13608.76, 13153.29, 12698.11, 11617.03, 12640.87, 11728.48, 11181.79, 11291.91, 12235.32, 12426.95, 12524.2, 12522.74, 12937.81, 13043.86, 13018.66, 12872.46, 12259.14, 12016.91, 11908.69, 12523.08, 12322.81, 12128.97, 11948.57, 11809.56, 11850.68, 11904.83, 11334.87, 11337.89, 11211.44, 10848.87, 11180.48, 11157.94, 11369.7, 11626.04, 11719.34, 11267.09, 10609.45, 10109.1, 11062.92, 11119.46, 11430.62, 11838.38, 11684.98, 11734.56, 11361.11, 11093.99, 11292.14, 10864.76, 11204.38, 11524.36, 11713.96, 11649.66, 11697.7, 11516.13, 11482.4, 11384.58, 11533.79, 11614.21, 11797.21, 12173.46, 12396.62, 12540.96, 12688.29, 12480.85, 12432.74, 12684.27, 12737.39, 12697.59, 12895.39, 12830.4, 12578.18, 12487.76, 12703.91, 13015.79, 12955.6, 11899.31, 10939.33, 9816.81, 10447.32, 9818.1, 8854.75, 8986.33, 9858.04, 10254.14, 9988.37, 9434.65, 8832.62, 9006.07, 8710.84, 7822.01, 8072.03, 8731.79, 9083.35, 9027.74, 9332.21, 9188.54, 9422.09, 9070.02, 9150.75, 9372.76, 9619.11, 9394.78, 9648.49, 9964.3, 9991.72, 10046.34, 10080.05, 10078.91, 9840.07, 9461.53, 9108.68, 9146.86, 9550.84, 9742.76, 9853.6, 9482.84, 9139.01, 9494.45, 9554.23, 9794.83, 10051.86, 10196.55, 10479.84, 10606.92, 10184.59, 9879.01, 9657.59, 9118.23, 9227.36, 9415.56, 9349.44, 9140.05, 9448.0, 9752.71, 9568.34, 9385.35, 9709.03, 9467.68, 9513.37, 9651.36, 9773.09, 9785.72, 9912.97, 9969.0, 10054.85, 9971.2, 9948.06, 10010.75, 10239.91, 10278.09, 10485.26, 10327.0, 10365.53, 10233.26, 10420.07, 10322.0, 10235.82, 10318.73, 10545.67, 10556.57, 10570.84, 10845.34, 10939.12, 10898.66, 10947.65, 11159.19, 11166.83, 11180.6, 11223.21, 11356.07, 11563.5, 11600.81, 11808.27, 11894.32, 11831.69, 11919.28, 12038.28, 11905.46, 11756.09, 11945.38, 11899.71, 11750.24, 11946.57, 11836.93, 11857.61, 11634.49, 11948.42, 11847.35, 11974.77, 12120.65, 12269.98, 12299.06, 12090.58, 12108.82, 12028.15, 11703.12, 11572.39, 11728.48, 11057.25, 11377.24, 11527.75, 11719.42, 11507.42, 11554.7, 11164.89

# Matrizes tratadas
x_train: .space 5000           
y_train: .space 5000            
x_test: .space 5000           
y_test: .space 5000           

# Matriz de distâncias
dist: .space 5000           
# Array de regressao
regr: .space 5000      


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
	
	#la $s0, matriz # Matriz de Distancias 
	#la $s1, ytrain # Matriz de ytrain
	move $s0, $a0 # Matriz de Distancias 
	move $s1, $a1 # Matriz de ytrain
	
	la $s2, reg_array # Cabeça do array de regressão 
	la $s3, reg_less    # Cabeça do array de endereços para bater
			
    lw $t5, rows  # $t5 = tamanho array
    # move $t5, $a2   

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
		
