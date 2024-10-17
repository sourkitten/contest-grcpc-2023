#include <stdio.h>
#include <string.h>
#include <math.h>

struct alloy {
    char id[16];
    float x;
    float y;
};

int dominant_index = 1;

// swaps alloy structs with memcpy
static inline void swapAlloys(struct alloy *alloy1, struct alloy *alloy2) {
    struct alloy temp = *alloy1;  // Store the contents of alloy1 in a temporary variable
    *alloy1 = *alloy2;             // Copy contents of alloy2 to alloy1
    *alloy2 = temp;                // Copy contents of temp to alloy2
}

// Partition function for quicksort by ID
int partitionById(struct alloy *alloys, int low, int high) {
    char pivot[255];
    strcpy(pivot, alloys[high].id);  // Choosing the last element as pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j < high; j++) {
        if (strcmp(alloys[j].id, pivot) < 0) {  // If current element is smaller than pivot
            i++;
            swapAlloys(&alloys[i], &alloys[j]);
        }
    }
    swapAlloys(&alloys[i + 1], &alloys[high]);
    return (i + 1);  // Return the partition index
}

// Insertion sort for small arrays
void insertionSort(struct alloy *alloys, int low, int high, int compare_field) {
    for (int i = low + 1; i <= high; i++) {
        struct alloy key = alloys[i];
        int j = i - 1;

        // Compare based on the selected field (x or id)
        while (j >= low && ((compare_field == 0 && alloys[j].x > key.x) || 
                            (compare_field == 1 && strcmp(alloys[j].id, key.id) > 0))) {
            alloys[j + 1] = alloys[j];
            j--;
        }
        alloys[j + 1] = key;
    }
}

// Quicksort function with Introsort for sorting by ID
void introsortById(struct alloy *alloys, int low, int high, int depth_limit) {
    int size = high - low + 1;
    if (size <= 16) {
        insertionSort(alloys, low, high, 1);  // Use insertion sort for small sizes
        return;
    }
    if (depth_limit == 0) {
        // If the recursion depth exceeds a threshold, use heapsort
        // Implementing heapsort
        for (int i = (size / 2) - 1; i >= 0; i--) {
            // Call heapify
            for (int j = i; j < size;) {
                int leftChild = 2 * j + 1;
                int rightChild = 2 * j + 2;
                int largest = j;
                if (leftChild < size && strcmp(alloys[low + leftChild].id, alloys[low + largest].id) > 0) {
                    largest = leftChild;
                }
                if (rightChild < size && strcmp(alloys[low + rightChild].id, alloys[low + largest].id) > 0) {
                    largest = rightChild;
                }
                if (largest != j) {
                    swapAlloys(&alloys[low + j], &alloys[low + largest]);
                    j = largest;
                } else {
                    break;
                }
            }
        }
        // Extract elements from the heap
        for (int i = size - 1; i > 0; i--) {
            swapAlloys(&alloys[low], &alloys[low + i]);
            // Call heapify on the reduced heap
            for (int j = 0; j < i;) {
                int leftChild = 2 * j + 1;
                int rightChild = 2 * j + 2;
                int largest = j;
                if (leftChild < i && strcmp(alloys[low + leftChild].id, alloys[low + largest].id) > 0) {
                    largest = leftChild;
                }
                if (rightChild < i && strcmp(alloys[low + rightChild].id, alloys[low + largest].id) > 0) {
                    largest = rightChild;
                }
                if (largest != j) {
                    swapAlloys(&alloys[low + j], &alloys[low + largest]);
                    j = largest;
                } else {
                    break;
                }
            }
        }
        return;
    }
    int pi = partitionById(alloys, low, high);  // Partitioning index
    introsortById(alloys, low, pi - 1, depth_limit - 1);  // Recursively sort before partition
    introsortById(alloys, pi + 1, high, depth_limit - 1);  // Recursively sort after partition
}

/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 */
static inline void readInput(struct alloy *dominant, int alloy_count) {
    // Input reading using scanf
    scanf("%s %f %f", &(dominant->id), &(dominant->x), &(dominant->y));
    float max_x = dominant->x, max_y = dominant->y;

    struct alloy *current = new struct alloy;
    // For every alloy in line
    for (int i = 1; i < alloy_count; ++i) {
        scanf("%s %f %f", &(current->id), &(current->x), &(current->y));

        bool dom = 0;

        if (current->x > max_x) {
            max_x = current->x;
            dom = true;
        }
        if (current->y > max_y) {
            max_y = current->y;
            dom = true;
        }


        // Check all dominant elements
        for (int j = 0; j < dominant_index; j++) {
            struct alloy *cdom = dominant + j;
            // It's either already dominant, 
            if ((current->x > cdom->x) && (current->y > cdom->y))
               cdom->x = 0; // signal that element is no longer dominant
        }

        // Add to list if dominant
        if (dom) {
            struct alloy *last_dom = &(dominant[dominant_index]);
            last_dom->x = current->x;
            last_dom->y = current->y;
            strcpy(last_dom->id, current->id);
            dominant_index++;
        }
    }

    free(current);
}

int main()
{
    int alloy_num;
    scanf("%d", &alloy_num);  // Read the number of alloys
    printf("Number of alloys: %d\n", alloy_num);

    struct alloy *dominant = (struct alloy*) malloc(alloy_num*sizeof(struct alloy));

    readInput(dominant, alloy_num);

    printf("\n");
    printf("Dominant Alloys:\n");

    int depth_limit = log(dominant_index);
    introsortById(dominant, 0, dominant_index-1, depth_limit);

    // First to last
    for (int i = 0; i < dominant_index; i++) {
        struct alloy *cdom = dominant + i;
        if (cdom->x != 0) {
            printf("%s %.2f %.2f\n", cdom->id, cdom->x, cdom->y);
        }
        //free(current->prev);
    }

    free(dominant);

    return 0;
}