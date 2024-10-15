#include <stdio.h>
#include <string.h>
#include <math.h>

struct alloy {
    char id[14];
    float x;
    float y;
    struct alloy *next = NULL;
    struct alloy *prev = NULL;
};

void removeNode(struct alloy *current) {
    struct alloy *next = current->next;
    // Set the next node of the previous node to next node of current node
    // A-B-C to A-C
    current->prev->next = current->next;
    free(current);
}

// Adds node at the end of the linked list
void addNode(struct alloy *last, struct alloy *current) {
    // Initialize new Node
    last->next = new struct alloy;
    // Set the previous node of the new node to self
    last->next->prev = last;
    // direct copy current struct to newly created struct
    last->next->x = current->x;
    last->next->y = current->y;
    strcpy(last->next->id, current->id);
}

/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 */
static inline void readInput(struct alloy *first, int alloy_count) {
    // Input reading using scanf
    scanf("%s %f %f", &(first->id), &(first->x), &(first->y));
    
    struct alloy *last = first;

    // Go to last
    while (last->next != NULL)
        last = last->next;

    struct alloy *current = new struct alloy;
    // For every alloy in line
    for (int i = 1; i < alloy_count; ++i) {
        printf("Alloy %d\n", i);
        scanf("%s %f %f", &(current->id), &(current->x), &(current->y));

        bool dominant = false;

        struct alloy *current_dominant = first;

        // Check all dominant elements
        // If dominant, get added to end of list and
        while (current_dominant != NULL) {
            // It's either already dominant, or if either x or y are better it becomes dominant
            dominant = dominant || (current->x >= current_dominant->x) || (current->y >= current_dominant->y);
            printf("%d\n", dominant);
            // Gets booted off the list
            if ((current->x >= current_dominant->x) && (current->y >= current_dominant->y))
                removeNode(current_dominant);
            current_dominant = current_dominant->next;
        }

        // Add to list if dominant
        if (dominant) {
            addNode(last, current);
            last = last->next;
        }
    }
}

int main()
{
    int alloy_num;
    scanf("%d", &alloy_num);  // Read the number of alloys
    printf("Number of alloys: %d\n", alloy_num);

    struct alloy *dominant = new struct alloy;

    readInput(dominant, alloy_num);

    printf("\n");
    printf("Dominant Alloys:\n");
    struct alloy *current = dominant;
    // First to last
    while (current != NULL) {
        printf("%s %.2f %.2f\n", current->id, current->x, current->y);
        current = current->next;
        //free(current->prev);
    }

    return 0;
}