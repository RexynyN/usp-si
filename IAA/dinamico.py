
def dinamico(p, v, n, w):
    t = [[0 for x in range(w + 1)] for y in range(n + 1)]

    for i in range(1, n + 1):
        t[0][i] = 0
        for j in range(0, w + 1):
            t[i][j] = t[i - 1][j]

            aux = t[i - 1][j - p[i - 1]] + v[i - 1]
            if j >= p[i - 1] and t[i][j] < aux:
                t[i][j] = aux

    print("O maior valor possível é: " + str(t[n][w]))

    index = []
    while n != 0:
        if(t[n][w] != t[n - 1][w]):
            index.append(n)
            w -= p[n - 1]
        n -= 1

    return index

if __name__ == "__main__":
    # p é o w do enunciado que se refere a sequência de pesos
    p = [40, 30, 20, 10]
    v = [840, 600, 400, 100]
    print("Os pacotes que foram escolhidos são: " + str(dinamico(p, v, len(p), 50)))


# 1 MochilaDinamica (w, v, n, W)
# 2    t[n][W] <-- 0
# 3
# 4    para i <-- 1 até n 
# 5        para j <-- 0 até W
# 6            t[i, j] <-- t[i-1, j]
# 7            aux <-- t[i - 1, j - w[i - 1]] + v[i - 1]
# 8            se j >= p[i - 1] e t[i][j] < aux
# 9                t[i][j] <-- aux     
# 10
# 11   indices[] <-- 0
# 12   enquanto n != 0
# 13       se t[n][W] != t[n - 1][W]
# 14           indices <-- n
# 15           W = W - w[n - 1]
# 16
# 17        n <-- n - 1
# 18
# 19   retorna indices 
