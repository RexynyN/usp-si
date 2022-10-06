import time
import random
import json

# Os códigos das duas seleções
# ===================================
def particao(a, esq, dir):
    pivo = a[dir - 1]

    for i in range(esq, dir):
        if a[i] > pivo:
            dir += 1
        else:
            dir += 1
            esq += 1
            a[i], a[esq - 1] = a[esq - 1], a[i]

    return esq

def quick_sort(a, esq, dir):
    dir = dir if dir is not None else len(a)

    if esq < dir:
        q = particao(a, esq, dir)
        quick_sort(a, esq, (q - 1))
        quick_sort(a, q, dir)

    return a

def quick_selection(a, esq, dir, i):
    a = quick_sort(a, esq, dir)
    return a[i - 1]


def selecao_particionada(a, i):
    n = len(a)
    q = particao(a, 0, n)

    if(n == 1):
        return a[0]
    
    if(i < q):
        return selecao_particionada(a[0 : q -1], i)
    elif i > q:
        return selecao_particionada(a[q: n], i - (q))
    else:
        return a[q - 1]
    

# Funções de suporte para os testes 
# ================================ 
def gerador_array(qtd):
    A = []
    for i in range(0, qtd):
        A.append(random.randint(1, qtd-1))

    return A        

def sub_array (a, qtd):
    return a[0 : qtd-1]


# Testes das duas seleções
# =====================
def teste_quick_sort():
    array = gerador_array(100000000)

    with open("array.json", "w", encoding="utf-8") as f:
        print(len(array))
        f.write(str(array))

    # print(array)
    values = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    with open("resultados.txt", "w", encoding="utf-8") as f:
        i = 1
        while i <= 5:
            print("Rodada de Testes: " + str(i))
            f.write("Rodada de Testes " + str(i) + "\n\n")
            index = 0
            aux = 1000000
            while aux <= 100000000:
                a = sub_array(array, aux)

                start_time = time.time()
                quick_selection(a, 0, len(a), 1)
                finish_time = time.time()

                elapsed = finish_time - start_time
                print(str(aux) + " - " + str(elapsed))
                f.write(str(aux) + " elementos - " + str(elapsed) + " segundos\n")

                values[index] += elapsed

                if(aux == 1000000):
                    aux = 5000000
                else:   
                    aux += 5000000
                index += 1

            f.write("\n\n")
            i += 1


        index = 0
        aux = 1000000
        f.write("\n\n\nCálculo de Médias: \n\n")
        while aux <= 100000000:
            mean = values[index] / 5

            f.write("Média de " + str(aux) + " elementos - " + str(mean) + " segundos\n")
            if(aux == 1000000):
                aux = 5000000
            else:   
                aux += 5000000
            index += 1
            
        # print(array)

def find_smaller(a):
    menor = len(a)
    for i in a:
        if i < menor:
            menor = i

    return menor

def teste_selecao(): 
    # # Gerar um array aleatório e guardar num arquivo de json
    # array = gerador_array(110)
    # with open("a.json", "w", encoding="utf-8") as f:
    #     print(len(array))
    #     json.dump(array, f, ensure_ascii=False, indent=4)


    # ou pegar uma array já gerado
    array = []
    with open("array.json", "r", encoding="utf-8") as f:
        array = json.load(f)
        print(len(array))

    print(find_smaller(array))
    print(selecao_particionada(array, 1))



    values = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    with open("dummy.txt", "a", encoding="utf-8") as f:
        i = 1
        while i <= 5:
            print("Rodada de Testes: " + str(i))
            f.write("Rodada de Testes " + str(i) + "\n\n")
            index = 0
            aux = 1000000
            

            f.write("\n\n")
            i += 1


        index = 0
        aux = 1000000
        f.write("\n\n\nCálculo de Médias: \n\n")
        while aux <= 100000000:
            mean = values[index] / 5

            f.write("Média de " + str(aux) + " elementos - " + str(mean) + " segundos\n")
            if(aux == 1000000):
                aux = 5000000
            else:   
                aux += 5000000
            index += 1
            

def teste_versus ():
    array = []
    with open("array_versus.json", "r", encoding="utf-8") as f:
        array = json.load(f)
        print(len(array))

    print(find_smaller(array))
    print(selecao_particionada(array, 10000))

    with open("faceoff.txt", "a", encoding="utf-8") as f:
        aux = 1
        while aux <= 1000000:
            f.write(str(aux) + "º menor elemento\n")
            
            start_time = time.time()
            menor = quick_selection(array, 0,100000000, aux)
            finish_time = time.time()

            elapsed = finish_time - start_time
            print(str(aux) + " - " + str(elapsed))
            f.write("Quick Sort - " + str(menor) +  " - " + str(elapsed) + " segundos\n")

            
            start_time = time.time()
            menor = selecao_particionada(array, aux)
            finish_time = time.time()

            elapsed = finish_time - start_time
            print(str(aux) + " - " + str(elapsed))
            f.write("Seleção Particionada - " + str(menor) +  " - " + str(elapsed) + " segundos\n")

            
            if(aux == 1):
                aux = 100000
            else:   
                aux += 100000

        f.write("\n\n")



# Função main
# ===================
if __name__ == "__main__":
    # Descomente o teste que gostaria de fazer 

    teste_quick_sort()

    # teste_selecao()

    # teste_versus()
