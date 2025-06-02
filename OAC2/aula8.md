# Aula 8 


## Etapas de um pipeline MIPS  

- Busca instrução memória (BI/IF - Instruction Fetch)
- Leitura registradores e decodificação de instrução (ID/DI - Decode Instruction)
- Execução de operação ou cálculo de endereço (EX - Execution)
- Acesso a um operando de memória (MEM - Memory Access)
- Escrita do resultado em registrador (EM/WB - Write Back)

(Até 5 instruções podem estar sendo executadas nessa pipeline de uma vez, sendo o número de estágios)


- Questão de clocks 
    - Jump, Branch - 3 Clocks
    - Formato R, Store - 4 Clocks 
    - Load - 5 Clocks

