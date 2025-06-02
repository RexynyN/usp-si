from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_set_num_threads, omp_get_wtime


@njit
def pi_loop():
    num_steps = 100000
    step = 1.0 / num_steps
    MAX_THREADS = 8

    for i in range(1, MAX_THREADS + 1):
        the_sum = 0.0 
        omp_set_num_threads(i)

        start_time = omp_get_wtime()

        with openmp("parallel private(x)"):
            with openmp("for reduction(+:the_sum) schedule(static) private(x)"):
                for j in range(num_steps):
                    x = ((j - 1) - 0.5) * step
                    the_sum += 4.0 / (1.0 + x * x)

        pi = step * the_sum 
        runtime = omp_get_wtime() - start_time
        print(f"Pi: ",pi,  " | Runtime: ", runtime, " | Iteração: ", i)


pi_loop()

