#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <omp.h>

// Função para medir o tempo de execução do programa sequencial
double runSequential(int numIterations) {
    double totalDuration = 0.0;
    int thread_num;

    #pragma omp parallel for reduction(+: totalDuration) num_threads(8)
    for (int i = 0; i < numIterations; ++i) {
        thread_num = omp_get_thread_num();
        printf("Thread %d executando a iteração sequencial %d\n", thread_num, i + 1);
        // Adicione o código para executar o programa sequencial aqui
        system("./sequential/sequential_exec");
    }

    return totalDuration / numIterations;
}

// Função para medir o tempo de execução do programa paralelo com OpenMP
double runParallel(int numIterations) {
    double totalDuration = 0.0;
    int thread_num;
    // Adicione o código para executar o programa paralelo com OpenMP aqui
    #pragma omp parallel for private(thread_num) reduction(+: totalDuration)
    for (int i = 0; i < numIterations; ++i) {
            thread_num = omp_get_thread_num();
            printf("Thread %d executando a iteração paralela %d\n", thread_num, i + 1);
            system("./parallel/parallel_exec");
    }
    return totalDuration / numIterations;
}

int main() {
    int numIterations;
    std::cout << "Digite o número de iterações desejadas: ";
    std::cin >> numIterations;

    // Executar e medir o tempo para o programa sequencial
    double averageSequentialTime = runSequential(numIterations);

    // Executar e medir o tempo para o programa paralelo
    double averageParallelTime = runParallel(numIterations);

    // Salvar os tempos em um arquivo CSV
    // std::ofstream csvFile("execution_times.csv");
    // csvFile << "Sequential,Parallel\n";
    // csvFile << averageSequentialTime << "," << averageParallelTime << "\n";
    // csvFile.close();

    // std::cout << "Resultados salvos em execution_times.csv\n";

    return 0;
}