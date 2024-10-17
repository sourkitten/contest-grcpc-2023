#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct alloy {
    char id[16];
    float x;
    float y;
};

int dominant_index = 1;

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

        bool is_dominant = 0;

        if (current->x > max_x) {
            max_x = current->x;
            is_dominant = true;
        }
        if (current->y > max_y) {
            max_y = current->y;
            is_dominant = true;
        }


        // Check all dominant elements
        for (int j = 0; j < dominant_index; j++) {
            struct alloy *cdom = &(dominant[j]);
            // It's either already dominant, 
            if ((current->x > cdom->x) && (current->y > cdom->y))
               cdom->x = 0; // signal that element is no longer dominant
        }

        // Add to list if dominant
        if (is_dominant) {
            struct alloy *last_dom = dominant + dominant_index;
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

    //int depth_limit = log(dominant_index);
    //introsortById(dominant, 0, dominant_index-1, depth_limit);    

    std::sort(dominant, dominant + dominant_index,
        [](const alloy& a, const alloy& b) {
            return strcmp(a.id, b.id) < 0; // compare ids
        });

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