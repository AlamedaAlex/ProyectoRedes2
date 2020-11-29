#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int **matrix_a, **matrix_b, **matrix_c;
int matrix_rows = 0, matrix_cols = 0, matrix_eq = 0;

int **new_matrix(int n_row, int n_col);
int **new_empty_matrix(int n_row, int n_col);

void print_matrix(int **matrix, int n_rows, int n_cols);
void *my_thread_function(void *vargp);
void multiplicate_mrow(int s_rows, int s_cols, int eq, int index);

struct args {
    int min;
    int max;
};

struct thread_info
{
    pthread_t thread_id;    // ID returned by pthread_create()
    int thread_num;         // Application-defined thread #
    struct args limits;     // Arguments of the thread
};

int main(int argc, char const *argv[])
{
    // ------------------------------------------------------------- 
    // 1. Asignacion de valores iniciales del programa
    // ------------------------------------------------------------- 

    int row_a, row_b, column_a, column_b; // Variables para la creacion de las matrices
    int num_threads; // Variable con el numero de hilos

    if( argc != 6 )
    {
        printf("The are missing arguments\n");
        return 0;
    }  

    // Se introducen los valores para la definicion de las matrices
    // TODO: Implementar una fucnion para validar que sean valores enteros
    row_a = atoi(argv[1]);
    column_a = atoi(argv[2]);

    row_b = atoi(argv[3]);
    column_b = atoi(argv[4]);

    // Valida si es una multiplicacion valida
    if( column_a != row_b )
    {
        printf("The matrices cannot be multiplied\n");
        return 0;
    }

    // Creacion de las matrices con valores aleatorios
	matrix_a = new_matrix(row_a, column_a);
    printf("Matrix A =\n");
    print_matrix(matrix_a, row_a, column_a);

	sleep(1); // Esperamos un segundo para que se generen valores distintos
	matrix_b = new_matrix(row_b, column_b);
    printf("Matrix B =\n");
    print_matrix(matrix_b, row_b, column_b);

    // Creacion de la matriz resultado
    matrix_c = new_empty_matrix(row_a, column_b);  

    // Se introduce el numero de hilos que operaran la matriz
    num_threads = atoi(argv[5]);

    // Valida si el numero de hilos es mayor o igual al minimo de filas
    if( num_threads > row_a )
    {
        printf("The number of threads is higher than the number of possible rows\n");
        return 0;
    }

    // ------------------------------------------------------------- 
    // 2. Asignacion de referencias para cada hilo
    // ------------------------------------------------------------- 
    int count = 0;
	int aux = row_a;

    // Variables del tamanio de la matriz resultante
    matrix_rows = row_a;
    matrix_cols = column_b;
    matrix_eq = column_a;

    // Dividir numero de filas de la matriz A correspondiente a cada hilo
	if(aux%num_threads != 0)
		while (aux%num_threads != 0){
			aux++;
			count++;
		}

    printf("\n");
	printf("%d threads of %d rows\n", num_threads-count, aux/num_threads);
	if(count != 0)
		printf("%d threads of %d rows\n", count, (aux/num_threads) - 1);
	printf("\n");

    // ------------------------------------------------------------- 
    // 3. Inicializacion de los hilos
    // ------------------------------------------------------------- 

    struct thread_info *thread_array; // Estructura con los hilos y sus identificadores
    
    // Creando dinamicamente los hilos, con calloc se crea el dato inicializado en 0
    // thread_array = (struct thread_info *)malloc(num_threads * sizeof(struct thread_info));
    thread_array = calloc(num_threads, sizeof(struct thread_info));

    // ------------------------------------------------------------- 
    // 4. Asignacion de los limites iniciales
    // ------------------------------------------------------------- 

    int rows_per_thread = (int)(aux/num_threads);
    struct args limits; // Arreglo con los limites para cada hilo

    limits.min = 0;
    limits.max = rows_per_thread;

    for (int i = 0; i < num_threads; i++)
    {
        //Asignar valores a cada struct thread_info
        thread_array[i].thread_num = i;
        thread_array[i].limits.min = limits.min;
        thread_array[i].limits.max = limits.max;

        // printf("Thread %d with values (min=%d, max=%d)\n", thread_array[i].thread_num, thread_array[i].limits.min, thread_array[i].limits.max);

        // ------------------------------------------------------------- 
        // 5. Creacion de los hilos
        // ------------------------------------------------------------- 

        if (0 != pthread_create(&thread_array[i].thread_id, NULL, my_thread_function, (void *)&thread_array[i].limits))
            return -1;
        // else
        //     printf("Thread %d with ID %ld and values (min=%d, max=%d) was created successfully\n", thread_array[i].thread_num, thread_array[i].thread_id, thread_array[i].limits.min, thread_array[i].limits.max);

        // Incrementar los valores limites
        limits.min = limits.max;

        if(i < count)
            limits.max = limits.max + ((aux/num_threads) - 1);    
        else
            limits.max = limits.max + aux/num_threads;
        
    }

    // ------------------------------------------------------------- 
    // 6. Esperando la finalizacion de los hilos
    // ------------------------------------------------------------- 

    for (int i = 0; i < num_threads; i++)
        pthread_join(thread_array[i].thread_id, NULL);

    printf("\n");

    // ------------------------------------------------------------- 
    // 7. Imprimir el resultado de la multiplicacion desde el padre
    // ------------------------------------------------------------- 

    print_matrix(matrix_c, row_a, column_b);

    printf("END OF PROCESS\n");

    //Liberamos la memoria asignada para los hilos
    free(thread_array);
    free(matrix_a);
    free(matrix_b);
    free(matrix_c);

    return 0;
}

// Imprimir matriz
void print_matrix(int **matrix, int n_rows, int n_cols)
{
    for(int i = 0;i < n_rows;i++)
    {
		for(int j = 0;j < n_cols;j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}

    printf("\n");
}

// Crear una matriz n * m con valores aleatorios de 0 a 5
int **new_matrix(int n_row, int n_col)
{
	int **matrix;

	matrix = (int **)malloc(n_row * sizeof(int *));

	for (int i = 0;i < n_row;i++)
		matrix[i] = (int *)malloc(n_col * sizeof(int));

	srand(time(NULL));

	for(int i = 0;i < n_row;i++)
		for(int j = 0;j < n_col;j++)
			matrix[i][j] = rand()%5;
	
	return matrix;
}

// Crear una matriz n * m inicializada en 0
int **new_empty_matrix(int n_row, int n_col)
{
	int **matrix;

	matrix = (int **)malloc(n_row * sizeof(int *));

	for (int i = 0;i < n_row;i++)
		matrix[i] = (int *)malloc(n_col * sizeof(int));

	for(int i = 0;i < n_row;i++)
		for(int j = 0;j < n_col;j++)
			matrix[i][j] = 0;
	
	return matrix;
}

// Funcion que ejecutara el hilo
void *my_thread_function(void *vargp) 
{  
    int min = ((struct args *)vargp)->min;
    int max = ((struct args *)vargp)->max;
    int index = 0;

    printf("Thread ID %ld with values (min=%d, max=%d)\n", pthread_self(), min, max);

    for (index = min; index < max; ++index)
        multiplicate_mrow(matrix_rows, matrix_cols, matrix_eq, index);
}

// Funcion multiplicar fila de matriz y asignar el valor a la matriz resultado
void multiplicate_mrow(int s_rows, int s_cols, int eq, int index)
{
    int addition = 0;

    for(int i = 0; i < s_cols; i++)
    {
        addition = 0;
        for(int j = 0; j < eq; j++)
            addition = addition + (matrix_a[index][j] * matrix_b[j][i]);
        matrix_c[index][i] = addition;
    }
}