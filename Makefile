PARALLEL_SRC_FOLDER = ./parallel/*.cpp
SEQUENTIAL_SRC_FOLDER = ./sequential/*.cpp
PARALLEL_OUTPUT = ./parallel/parallel_exec
SEQUENTIAL_OUTPUT = ./sequential/sequential_exec

# Compila o programa sequencial
compile_sequential: $(SEQUENTIAL_SRC_FOLDER)
	@ g++ $^ -o $(SEQUENTIAL_OUTPUT)

# Compila o programa em paralelo
compile_parallel: $(PARALLEL_SRC_FOLDER)
	@ g++ $^ -o $(PARALLEL_OUTPUT) -fopenmp

# Executa o programa sequencial
sequential: compile_sequential $(SEQUENTIAL_OUTPUT)
	@ ./$(SEQUENTIAL_OUTPUT)

# Executa o programa em paralelo
parallel: compile_parallel $(PARALLEL_OUTPUT)
	@ ./$(PARALLEL_OUTPUT)

# Limpa os arquivos de execução do ambiente
clean:
	@ rm -f $(SEQUENTIAL_OUTPUT) $(PARALLEL_OUTPUT) newimage.ppm

# Evita verificação de atualizações
.PHONY: sequential parallel