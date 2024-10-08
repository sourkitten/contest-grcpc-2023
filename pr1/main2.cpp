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

int dominantIndex = 1;

/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 */
static inline void readInput(struct alloy *first, int alloy_count) {
    // Input reading using scanf
    scanf("%s %f %f", first->id, first->x, first->y);
    
    struct alloy *last = first;

    // Go to last
    while (last != NULL)
        last = last->next;


    struct alloy current = {0};
    // For every alloy in line
    for (int i = 0; i < alloy_count; ++i) {
        scanf("%s %f %f", current.id, current.x, current.y);

        bool dominant = false;

        struct alloy* current_dominant = first;

        // Check all dominant elements
        // If dominant, get added to end of list and
        while (current_dominant != NULL) {
            // It's either already dominant, or if either x or y are better it becomes dominant
            dominant = dominant || (current.x > first->x) || (current.y > first->y);
            // Gets booted off the list
            if ((current.x > current_dominant->x) && (current.y > current_dominant->y)) {
                struct alloy *next_dominant = current_dominant->next;
                current_dominant = current_dominant->prev;
                free(current_dominant->next);
                if (next_dominant != NULL)
                    current_dominant->next = next_dominant;
                else
                    current_dominant->next = NULL;
            }
        }

        // Add to list if dominant
        if (dominant) {
            last->next = (struct alloy*) malloc(sizeof(struct alloy));
            last = last->next;
            // direct copy current struct to newly created struct
            last->x = current.x;
            last->y = current.y;
            strcpy(last->id, current.id);
        }
    }
}

int main()
{
    int alloy_num;
    scanf("%d", &alloy_num);  // Read the number of alloys
    printf("Number of alloys: %d\n", alloy_num);

    struct alloy dominant = {0};

    readInput(&dominant, alloy_num);

    printf("\n");
    printf("Dominant Alloys:\n");
    struct alloy *current = &dominant;
    // First to last
    while (current != NULL) {
        printf("%s %.2f %.2f\n", current->id, current->x, current->y);
        current = current->next;
        //free(current->prev);
    }

    return 0;
}