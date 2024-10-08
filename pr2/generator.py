import sys
import numpy as np
import multiprocessing

def generate_rows_in_batch(start_row, end_row, x, prev_row=None):
    rows = []
    prev_row = prev_row if prev_row is not None else np.zeros(x, dtype=int)

    for _ in range(start_row, end_row):
        # Start and end with land (0)
        row = np.zeros(x, dtype=int)
        
        # Generate middle part of the row
        for col in range(1, x-1):
            if prev_row[col] == 1 or row[col-1] == 1:
                row[col] = np.random.choice([1, 0], p=[0.8, 0.2])
            else:
                row[col] = np.random.choice([1, 0], p=[0.3, 0.7])
        
        rows.append(row)
        prev_row = row
    
    return rows, prev_row

def process_chunk(start_row, end_row, x, prev_chunk_last_row=None):
    rows, last_row = generate_rows_in_batch(start_row, end_row, x, prev_chunk_last_row)
    return rows, last_row

def generate_and_output_grid(x, y, num_processes):
    # Output the top boundary row
    print('0' * x)

    chunk_size = (y - 2) // num_processes
    if chunk_size < 1:
        chunk_size = 1  # Ensure at least one row per process

    prev_chunk_last_row = None
    processes = []

    with multiprocessing.Pool(processes=num_processes) as pool:
        for i in range(num_processes):
            start_row = 1 + i * chunk_size
            end_row = start_row + chunk_size
            if i == num_processes - 1:
                end_row = y - 1  # Handle remaining rows in the last chunk

            # Submit each chunk to the process pool
            processes.append(pool.apply_async(process_chunk, (start_row, end_row, x, prev_chunk_last_row)))

        # Collect and print each chunk when completed
        for process in processes:
            chunk, prev_chunk_last_row = process.get()

            # Batch output for each chunk
            for row in chunk:
                print(''.join(map(str, row)))

    # Output the bottom boundary row
    print('0' * x)

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 generator.py <x> <y> <num_processes>")
        sys.exit(1)
    
    try:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
        num_processes = int(sys.argv[3])
    except ValueError:
        print("Please provide valid integer values for x, y, and num_processes.")
        sys.exit(1)

    if x < 3 or y < 3 or num_processes < 1:
        print("x and y must be at least 3, and num_processes must be at least 1.")
        sys.exit(1)

    # Print the grid dimensions
    print(f"{y} {x}")

    # Generate and output the grid with multiprocessing
    generate_and_output_grid(x, y, num_processes)

if __name__ == "__main__":
    main()

