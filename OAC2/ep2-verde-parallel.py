import gc
import json
import numpy as np
from numba import njit
from numba.openmp import openmp_context as openmp, omp_set_num_threads, omp_get_wtime

# Constantes
SLIDE = 3
PREV = 2
KNN = 3
NUM_THREADS = 10

def read_file(path: str) -> np.ndarray:
    with open(path, "r", encoding="utf-8") as file:
        return arr_to_matriz(np.array([float(line.strip()) for line in file if line], dtype=np.float64))

@njit
def arr_to_matriz(array: np.ndarray) -> tuple:
    omp_set_num_threads(NUM_THREADS)
    stop = len(array) - SLIDE
    X = np.zeros((stop, SLIDE), dtype=np.float64)
    Y = np.zeros(stop, dtype=np.float64)

    with openmp("parallel for schedule(static)"):
        for idx in range(stop):
            slider = idx + SLIDE
            X[idx, :] = array[idx:slider]
            Y[idx] = array[slider + PREV - 1]

    return X, Y

@njit
def knn_distancia(train: np.ndarray, test: np.ndarray) -> np.ndarray:
    omp_set_num_threads(NUM_THREADS)
    n_test, n_train = len(test), len(train)
    dists = np.zeros((n_test, n_train), dtype=np.float64)

    with openmp("parallel for schedule(static) private(mod, diff)"):
        for i in range(n_test):
            for j in range(n_train):
                mod = 0.0
                for k in range(train.shape[1]):
                    diff = test[i, k] - train[j, k]
                    mod += abs(diff)
                dists[i, j] = mod

    return dists

@njit
def regressao_matriz(dists: np.ndarray, y_train: np.ndarray) -> np.ndarray:
    omp_set_num_threads(NUM_THREADS)
    regression = np.zeros(len(dists), dtype=np.float64)

    with openmp("parallel for schedule(static) private(sort_idxs, k_less, regr)"):
        for i in range(len(dists)):
            sort_idxs = np.argsort(dists[i])[:KNN]
            k_less = y_train[sort_idxs]
            regr = np.mean(k_less)
            regression[i] = regr

    return regression

@njit
def temporal_knn_fit(x_train: np.ndarray, y_train: np.ndarray, x_test: np.ndarray) -> tuple:
    start_time = omp_get_wtime()

    # x_train, y_train = arr_to_matriz(train_raw)
    # x_test, _ = arr_to_matriz(test_raw)
    dists = knn_distancia(x_train, x_test)
    regr = regressao_matriz(dists, y_train)

    runtime = omp_get_wtime() - start_time
    return regr, runtime

def main():
    global SLIDE, PREV, KNN 
    datasets = (
        # ("xtrain_1000000000.txt", "xtest_1000000000.txt"),
        # ("xtrain_100000000.txt", "xtest_100000000.txt"),
        # ("xtrain_10000000.txt", "xtest_10000000.txt"),
        # ("xtrain_2000000.txt", "xtest_2000000.txt"),
        ("xtrain_1000000.txt", "xtest_1000000.txt"),
        ("xtrain_100000.txt", "xtest_100000.txt"),
        ("xtrain_10000.txt", "xtest_10000.txt"),
        ("xtrain_1000.txt", "xtest_1000.txt"),
    )

    hypers = []
    for slide in range(5):
        for prev in range(3):
            for knn in range(5):
                hypers.append((slide + 1, prev + 1, knn + 1))

    json_arr = []
    for train, test in datasets:
        x_train, y_train = read_file(train)
        x_test, _ = read_file(test)
        
        for slide, prev, knn in hypers:
            SLIDE, PREV, KNN = slide, prev, knn
            data = []
            
            start_time = omp_get_wtime()
            dists = knn_distancia(x_train, x_test)
            gc.collect()
            regr = regressao_matriz(dists, y_train)
            
            runtime = omp_get_wtime() - start_time
            gc.collect()

            data.append({"reg_len": len(regr), "runtime": runtime})
            # print(f"Tamanho da Regressão Feita: {len(reg)}")
            # print(f"Tempo de Execução: {runtime:.6f} segundos")

            x = {
                "dataset_train": train,
                "dataset_test": test,
                "runs": data,
                "hyper": {
                    "slide": slide,
                    "prev": prev,
                    "knn": knn
                }
            }

            json_arr.append(x)
            print(x)
            print()
        
        gc.collect()

    with open("benchmark_parallel.json", "w", encoding="utf-8") as file:
        json.dump(json_arr, file, indent=4)

if __name__ == "__main__":
    main()
    # create_datasets()


if __name__ == "__main__":
    main()
