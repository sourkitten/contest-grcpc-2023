#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct alloy {
    char id[14];
    float x;
    float y;
};

// swaps alloy structs with memcpy
static inline void swapAlloys(struct alloy *alloy1, struct alloy *alloy2) {
    struct alloy temp = *alloy1;  // Store the contents of alloy1 in a temporary variable
    *alloy1 = *alloy2;             // Copy contents of alloy2 to alloy1
    *alloy2 = temp;                // Copy contents of temp to alloy2
}

// Partition function for quicksort by x
int partitionByX(struct alloy *alloys, int low, int high) {
    float pivot = alloys[high].x;  // Choosing the last element as pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j < high; j++) {
        if (alloys[j].x < pivot) {  // If current element is smaller than pivot
            i++;
            swapAlloys(&alloys[i], &alloys[j]);
        }
    }
    swapAlloys(&alloys[i + 1], &alloys[high]);
    return (i + 1);  // Return the partition index
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
void insertionSort(struct alloy *alloys, int low, int high, int compareField) {
    for (int i = low + 1; i <= high; i++) {
        struct alloy key = alloys[i];
        int j = i - 1;

        // Compare based on the selected field (x or id)
        while (j >= low && ((compareField == 0 && alloys[j].x > key.x) || 
                            (compareField == 1 && strcmp(alloys[j].id, key.id) > 0))) {
            alloys[j + 1] = alloys[j];
            j--;
        }
        alloys[j + 1] = key;
    }
}

// Quicksort function with Introsort for sorting by x
void introsortByX(struct alloy *alloys, int low, int high, int depthLimit) {
    int size = high - low + 1;
    if (size <= 16) {
        insertionSort(alloys, low, high, 0);  // Use insertion sort for small sizes
        return;
    }
    if (depthLimit == 0) {
        // If the recursion depth exceeds a threshold, use heapsort
        // Implementing heapsort
        for (int i = (size / 2) - 1; i >= 0; i--) {
            // Call heapify
            for (int j = i; j < size;) {
                int leftChild = 2 * j + 1;
                int rightChild = 2 * j + 2;
                int largest = j;
                if (leftChild < size && alloys[low + leftChild].x > alloys[low + largest].x) {
                    largest = leftChild;
                }
                if (rightChild < size && alloys[low + rightChild].x > alloys[low + largest].x) {
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
                if (leftChild < i && alloys[low + leftChild].x > alloys[low + largest].x) {
                    largest = leftChild;
                }
                if (rightChild < i && alloys[low + rightChild].x > alloys[low + largest].x) {
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
    int pi = partitionByX(alloys, low, high);  // Partitioning index
    introsortByX(alloys, low, pi - 1, depthLimit - 1);  // Recursively sort before partition
    introsortByX(alloys, pi + 1, high, depthLimit - 1);  // Recursively sort after partition
}

// Quicksort function with Introsort for sorting by ID
void introsortById(struct alloy *alloys, int low, int high, int depthLimit) {
    int size = high - low + 1;
    if (size <= 16) {
        insertionSort(alloys, low, high, 1);  // Use insertion sort for small sizes
        return;
    }
    if (depthLimit == 0) {
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
    introsortById(alloys, low, pi - 1, depthLimit - 1);  // Recursively sort before partition
    introsortById(alloys, pi + 1, high, depthLimit - 1);  // Recursively sort after partition
}


/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 * Gets N more lines, splitting by whitespace
 * Lines are of format `ID X Y`
 * `**NOTE** : strtok needs char pointer,
 * only when the pointer changes. Otherwise NULL!!!**`
 */
void readInput(struct alloy *alloys, int alloy_count) {
    // Input reading using scanf
    for (int i = 0; i < alloy_count; ++i) {
        scanf("%s %f %f", alloys[i].id, &alloys[i].x, &alloys[i].y);
    }
}

int main(int argc, char *argv[])
{
    int alloy_num;
    scanf("%d", &alloy_num);  // Read the number of alloys
    printf("Number of alloys: %d", alloy_num);

    struct alloy *alloy = (struct alloy*) malloc(sizeof(struct alloy)*alloy_num);

    readInput(alloy, alloy_num);

    int depthLimit = log(alloy_num);
    introsortByX(alloy, 0, alloy_num-1, depthLimit);

    printf("Sorted Alloys:\n");
    for (int i = 0; i < alloy_num; i++) {
        printf("%s %.2f %.2f\n", alloy[i].id, alloy[i].x, alloy[i].y);
    }

    struct alloy *dominant = (struct alloy*) malloc(sizeof(struct alloy)*alloy_num);
    dominant[0] = alloy[alloy_num-1];
    int dominantIndex = 1;

    for (int i = alloy_num-1; i >= 0; i--) {
        if (dominant[dominantIndex-1].y < alloy[i].y) { // prev dominant Y < current Y
            dominant[dominantIndex] = alloy[i];
            dominantIndex++;
        }
    }

    depthLimit = log(dominantIndex);
    introsortById(dominant, 0, dominantIndex-1, depthLimit);

    printf("\n");
    printf("Dominant Alloys:\n");
    for (int i = 0; i < dominantIndex; i++) {
        printf("%s %.2f %.2f\n", dominant[i].id, dominant[i].x, dominant[i].y);
    }

    free(alloy);
    free(dominant);

    return 0;
}