#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int **initialize_matrix(int *n,int *m,char *path){
    int x,y,w;
    /*abre o arquivo de entrada, caso não seja possível sai com erro,
      lê n,m, cria uma matrix nxn, lê m arestas (x,y,w) e atualiza o
      grafo, fecha o arquivo e retorna o grafo*/
    FILE *fp=fopen(path,"r");
    if(fp==NULL)exit(EXIT_FAILURE);
    fscanf(fp,"%d %d",&(*n),&(*m));
    int **graph=(int **)malloc(sizeof(int **)*(*n));;
    for(int i=0;i<(*n);i++)graph[i]=(int *)malloc(sizeof(int)*(*n)); 
    for(int i=0;i<(*n);i++)for(int j=0;j<(*n);j++)graph[i][j]=0;
    for(int i=0;i<(*m);i++){
        fscanf(fp,"%d %d %d",&x,&y,&w);
        graph[x][y]=w,graph[y][x]=w;
    }
    fclose(fp);
    return graph;
}

void prim(int **graph,int *pred,int n,int *ans){
    //inicializa custos como infinito, adições à mst (marked) como nulas
    //atualiza custo da mst, pai e custo do vértice inicial ([0])
    int cost[n];
    bool marked[n];
    for(int i=0;i<n;i++)cost[i]=INT_MAX,marked[i]=0;
    cost[0]=0,pred[0]=-1,(*ans)=0;
    for(int i=0;i<n-1;i++){
        //pega o índice do vértice de menor custo (min_index) com base em seu
        //valor (min) e o adiciona à mst (marked)
        int min=INT_MAX,min_index=0;
        for(int j=0;j<n;j++)if(!marked[j]&&cost[j]<min)
            min=cost[j],min_index=j;
        marked[min_index]=1;
        //para todo vértice não adicionado à árvore, ligado a min_index
        //por uma aresta, com um custo que seja maior que o da aresta,
        //define-se seu predecessor como min_index e seu custo como o custo da aresta
        for(int j=0;j<n;j++){
            if(graph[min_index][j]!=0&&!marked[j]&&graph[min_index][j]<cost[j])
                pred[j]=min_index,cost[j]=graph[min_index][j];
        }
    }
    //atualiza o custo da mst
    for(int i=1;i<n;i++)(*ans)+=graph[i][pred[i]];
}

void write(char *path,int n,int ans,int *pred){
    /*abre o arquivo de saída, caso não seja possível sai com erro,
      escreve o custo ans, escreve m arestas (x,y), fecha o arquivo*/
    FILE *fp=fopen(path,"w");
    if(fp==NULL)exit(EXIT_FAILURE);
    fprintf(fp,"%d\n",ans);
    for(int i=1;i<n;i++)fprintf(fp,"%d %d\n",pred[i],i);
    fclose(fp);
}

int main(int argc, char **argv){
    int n,m,ans;
    int **graph=initialize_matrix(&n,&m,argv[1]); //inicializa o grafo com conteúdo do arquivo de entrada, atualiza n (num vértices), m (num arestas)
    int pred[n];
    prim(graph,pred,n,&ans); //executa o algoritmo de prim, atualiza o array pred e ans (custo da mst)
    write(argv[2],n,ans,pred); //escreve no arquivo de saída o custo da árvore e seus vértices
    return 0;
}
