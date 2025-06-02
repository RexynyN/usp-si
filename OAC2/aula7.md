# Aula 7


## Passos de uma arquitetura multiciclo 

- 1 - Busca de Instrução 
- 2 - Decodificação de instrução e busca de registradores
- 3 - Execução, cálculo do endereço de memória ou conclusão de desvio
- 4 - Acesso à memória ou conclusão da instrução tipo R
- 5 - Escrita adiada (write-back)


## Caminho

- Passo 1 - Busca instrução
    - Usar o PC para obter a instrução e colocar no registrador de instrução
    - Adiciona 4 no endereço do PC e write-back no PC

```
IR <- Memory[PC]
PC <- PC + 4
```

- Passo 2 - Decodificação 
    - Leia os registradores `rs` e `rt` se for necessário para a instrução
    - Calcular o endereço de desvio caso branch

```
A <- Reg[IR[25:11]]
B <- Reg[IR[20:16]]
ALUOut <- PC + sign-extend(IR[15:0])
```

- Passo 3 - Específico de Instrução  
    - Dependendo da instrução a ULA vai: 


```
// Tipo R
ALUOut <- A [operation] B
```

```
// Referência à memória
ALUOut <- A + sign-extend(IR[15:0]) 
```

```
// Branch 
if(A == B) PC <- ALUOut 
```

- Passo 4 - Tipo R ou Acessos à Memória

    - Loads and stores acessam memória

    ```
    MDR <- Memory[ALUOut]
    // ou 
    Memory[ALUOut] <- B
    ```

    - Tipo R finalizam 
    ```
    Reg[IR[15:11]] <- ALUOut
    ```



- Passo 5 - Conclusão da leitura de memória
    - Load
```
Reg[IR[20:16]] <- MDR
```


![Alt text](./aula7_1.png)

![Alt text](./aula7_2.png)

![Alt text](./aula7_3.png)

