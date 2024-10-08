#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GB_TO_BYTES(gb) ((gb) * (1024ULL * 1024ULL * 1024ULL))

// Limits
const size_t MEMORY_LIMIT = GB_TO_BYTES(12); // 12 GB
size_t row_memory_usage;
size_t batch_memory_usage;
int num_threads = 8;

struct batch_data {
    int start_row;
    int end_row;
    int x;
    int y;
    int **grid;
};

// Function to generate a single row with 'lake' (1) and 'land' (0)
void generate_row(int *row, int *prev_row, int x) {
    row[0] = 0; // Left edge
    row[x-1] = 0; // Right edge

    for (int i = 1; i < x - 1; i++) {
        if (prev_row[i] == 1 || row[i-1] == 1) {
            row[i] = (rand() % 10) < 8 ? 1 : 0; // 80% chance of a lake continuing
        } else {
            row[i] = (rand() % 10) < 3 ? 1 : 0; // 30% chance of a new lake
        }
    }
}

// Thread worker function
void *generate_batch(void *arg) {
    struct batch_data *data = (struct batch_data *) arg;
    int **grid = data->grid;
    int x = data->x;

    for (int i = data->start_row; i < data->end_row; i++) {
        if (i == 0) {
            // Initialize the first row (top edge)
            memset(grid[i], 0, x * sizeof(int));
        } else if (i == (data->end_row-1)) {
            memset(grid[i], 0 , x * sizeof(int));
        } else {
            generate_row(grid[i], grid[i-1], x);
        }
    }
    
    pthread_exit(NULL);
}

// Function to allocate grid space within memory limits
int **allocate_grid(int x, int batch_size) {
    int **grid = (int **) malloc(batch_size * sizeof(int *));
    for (int i = 0; i < batch_size; i++) {
        grid[i] = (int *) malloc(x * sizeof(int));
    }
    return grid;
}

// Main function to generate the entire grid with multi-threading
void generate_grid(int x, int y, int num_threads) {
    int batch_size = MEMORY_LIMIT / (x * sizeof(int)); // Calculate rows per batch
    if (batch_size > y) batch_size = y;  // Cap batch size if it's larger than the grid height

    // Memory usage per row and batch
    row_memory_usage = x * sizeof(int);
    batch_memory_usage = row_memory_usage * batch_size;

    // Split grid generation into batches
    for (int batch_start = 0; batch_start < y; batch_start += batch_size) {
        int rows_in_batch = (batch_start + batch_size > y) ? (y - batch_start) : batch_size;

        // Allocate the grid for this batch
        int **grid = allocate_grid(x, rows_in_batch);

        // Threading: split the work among the available threads
        pthread_t threads[num_threads];
        struct batch_data thread_data[num_threads];
        int rows_per_thread = rows_in_batch / num_threads;
        
        for (int t = 0; t < num_threads; t++) {
            int thread_start_row = t * rows_per_thread;
            int thread_end_row = (t == num_threads - 1) ? rows_in_batch : (t + 1) * rows_per_thread;

            thread_data[t].start_row = thread_start_row;
            thread_data[t].end_row = thread_end_row;
            thread_data[t].x = x;
            thread_data[t].y = rows_in_batch;
            thread_data[t].grid = grid;

            pthread_create(&threads[t], NULL, generate_batch, &thread_data[t]);
        }

        // Wait for all threads to complete
        for (int t = 0; t < num_threads; t++) {
            pthread_join(threads[t], NULL);
        }

        // Output the generated batch
        for (int i = 0; i < rows_in_batch; i++) {
            for (int j = 0; j < x; j++) {
                printf("%d", grid[i][j]);
            }
            printf("\n");
        }

        // Free the batch memory
        for (int i = 0; i < rows_in_batch; i++) {
            free(grid[i]);
        }
        free(grid);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <x> <y> <num_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int x = atoi(argv[1]);  // width of grid
    int y = atoi(argv[2]);  // height of grid
    num_threads = atoi(argv[3]);  // number of threads

    if (x < 3 || y < 3 || num_threads < 1) {
        fprintf(stderr, "x and y must be at least 3, and num_threads must be at least 1.\n");
        exit(EXIT_FAILURE);
    }

    printf("%d %d\n", x, y);

    // Generate and print the grid using multiple threads
    generate_grid(x, y, num_threads);

    return 0;
}

