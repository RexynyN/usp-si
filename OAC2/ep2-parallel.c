#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>  
// Para compilar:

// gcc -fopenmp -o knn_parallel ep2-parallel.c


// Leitura de arquivo 
#define MAX_LINE_LENGTH 20  // Comprimento máximo de uma linha
#define MAX_LINES 10000000

// Dataset
int TRAIN_LEN = 0;
int TEST_LEN = 0; 

// KNN temporal
int KNN = 3;
int PREV = 2;
int SLIDE = 3;
int THREADS = 10;


float** declare_matrix(int rows, int cols) {
    float **mat = (float **)malloc(rows * sizeof(float*));

    #pragma omp parallel for
    for(int i = 0; i < rows; i++) 
        mat[i] = (float *)malloc(cols * sizeof(float));

    return mat;
}

int arr_to_matriz(float* array, float** X, float* Y, int len) {
    omp_set_num_threads(THREADS);
    int stop = len - SLIDE;

    #pragma omp parallel for // Paralelizando o loop externo
    for (int idx = 0; idx < stop; idx++) {
        int slider = idx + SLIDE;

        // Paralelizando o loop interno para copiar elementos para X
        #pragma omp parallel for
        for (int j = 0; j < SLIDE; j++) {
            X[idx][j] = array[idx + j];
        }

        // Preenchendo a previsão
        int prev_idx = slider + (PREV - 1); 
        if (Y != NULL && prev_idx < len) {
            #pragma omp critical // Evita race conditions
            Y[idx] = array[prev_idx];  
        }
    }

    return stop;
}

int read_dataset(const char *filename, float *values, int max_values) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (count >= max_values) {
            fprintf(stderr, "Número de valores excede o limite (%d), truncando Dataset\n", max_values);
            break;
        }
        
        values[count] = strtof(line, NULL);
        count++;
    }

    fclose(file);
    printf("%d linhas lidas no dataset %s\n", count, filename);    
    return count;
}

// Função para buscar os índices dos menores valores
int* get_min_idxs(float* array, int len) {
    int *kmin_idxs = malloc(sizeof(int) * KNN);
    // An index shift to reflect the original array's indexes
    int shift = 0; 

    // Paralelizando a busca de KNN mínimos
    #pragma omp parallel for
    for (int k = 0; k < KNN; k++) {
        float min = array[0];
        int min_idx = 0;
        // Busca o menor valor
        for(int i = 0; i < len; i++) {
            // #pragma omp critical
            if (array[i] < min) {
                min = array[i];
                min_idx = i;
            }
        }
        kmin_idxs[k] = min_idx + shift;

        // Remove o min encontrado, fazendo o array menor
        for(int j = min_idx; j < len - 1; j++) array[j] = array[j + 1];
        shift++;
        len--;
    }

    return kmin_idxs;
}

float * temporal_knn(float **xtrain, float** xtest, float* ytrain) {
    omp_set_num_threads(10);
    float **dists = declare_matrix(TEST_LEN, TRAIN_LEN);
    float *regression = malloc(sizeof(float) * TRAIN_LEN);

    printf("Fazendo KNN\n");
    // #pragma omp parallel for 
    for (int i = 0; i < TEST_LEN; i++) {
        float mod, diff = 0.0;
        // Inicializa o vetor de distâncias para cada thread
        #pragma omp parallel for private(mod, diff) 
        for(int j = 0; j < TRAIN_LEN; j++) {
            mod = 0.0;
            for(int k = 0; k < SLIDE; k++) {
                diff = xtest[i][k] - xtrain[j][k];
                mod += fabs(diff);
            }
            dists[i][j] = mod;
        }
    }
    
    #pragma omp parallel for
    for (int i = 0; i < TEST_LEN; i++) {
        // Obtém os índices dos menores elementos
        int *sort_idxs = get_min_idxs(dists[i], TRAIN_LEN);
        float regr = 0.0;
        for(int x = 0; x < KNN; x++) {
            regr += ytrain[sort_idxs[x]];
        }

        regr /= KNN;
        regression[i] = regr;
    }

    return regression;
}


int main(int argc, char **argv) {
    if (argc <= 6) {
        printf("Insira os valores para iniciar: \n");
        printf("<arquivo_train> <arquivo_test> <KNN> <PREV> <SLIDE> <THREADS>\n");
        return 1;
    }

    // Setando os argumentos
    printf("Trabalhando com %d máximo de linhas no Dataset.\n", MAX_LINES);
    const char* file_xtrain = argv[1];
    const char* file_xtest = argv[2];
    KNN = atoi(argv[3]);
    PREV = atoi(argv[4]);
    SLIDE = atoi(argv[5]);
    THREADS = atoi(argv[6]);

    printf("%i %i %i %i \n", KNN, PREV, SLIDE, THREADS);

    // Lendo arquivo
    float* train_raw = (float *)malloc(MAX_LINES * sizeof(float));
    float* test_raw = (float *)malloc(MAX_LINES * sizeof(float));

    int count_train = read_dataset(file_xtrain, train_raw, MAX_LINES);
    if (count_train < 0) {
        printf("Houve um erro para ao ler arquivo !\n");
        return 1; 
    }

    int count_test = read_dataset(file_xtest, test_raw, MAX_LINES);
    if (count_test < 0) {
        printf("Houve um erro para ao ler arquivo !\n");
        return 1; 
    }

    double start, end;
    start = omp_get_wtime();

    // Quantidade de linhas = len(xtrain) - slide
    TRAIN_LEN = count_train - SLIDE;

    float** xtrain = declare_matrix(TRAIN_LEN, SLIDE);
    float* ytrain = (float *)malloc(TRAIN_LEN * sizeof(float));
    arr_to_matriz(train_raw, xtrain, ytrain, count_train);
    free(train_raw);


    TEST_LEN = count_test - SLIDE;

    float** xtest = declare_matrix(TEST_LEN, SLIDE);
    arr_to_matriz(test_raw, xtest, NULL, count_test);
    free(test_raw);
    
    float *regression = temporal_knn(xtrain, xtest, ytrain);

    end = omp_get_wtime();
    double runtime = end - start;
    for (size_t i = 0; i < 20; i++) {
        printf("%.2f, ", regression[i]);
    }
    printf("\n");
    printf("Tempo de Execução: %f segundos\n", runtime); 
    
    return 0;
}
