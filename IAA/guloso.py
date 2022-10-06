
# p é igual a w no contexto do problema
def guloso (A, w):
    i = []
    tW = 0
    valor = 0
    A.sort(reverse=True, key=lambda x: x[1])

    for item in A:
        if(tW + item[0] <= w):
            i.append(item)
            tW += item[0]
            valor += item[1]

    print("A mochila está com os itens: " + str(i))
    print("O valor da mochila é: " + str(valor))


if __name__ == "__main__":
    # Matriz de cada elemento (w, v)
    matrix = [[40, 840], 
    [30, 600], 
    [20, 400], 
    [10,100]]
    guloso(matrix, 50)




#   // A é uma matriz bidimensional de w x v
# 1 MochilaGulosa (A[w, v], W)
# 2   indices <- []
# 3   contador <- 0
# 4 
# 5   OrdenarPorMaiorValor(A)
# 6
# 7   para i <- 1 até n
# 8       se (contador + A[i][0] <= W)
# 9           indices <- i
# 10          contador <- contador + A[i][0]
# 11
# 12  retorna i