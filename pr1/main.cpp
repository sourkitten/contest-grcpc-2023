#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALLOY_NUM 5

struct alloy {
    char id;
    float x;
    float y;
};

// swaps alloy structs with memcpy
void swapAlloys(struct alloy *alloy1, struct alloy *alloy2){
    struct alloy *tempAlloy = new struct alloy;
    memcpy(tempAlloy, alloy1, sizeof(struct alloy));
    memcpy(alloy1, alloy2, sizeof(struct alloy));
    memcpy(alloy2, tempAlloy, sizeof(struct alloy));
}

void sortByX(struct alloy *alloys, int index) {
    xloop:
    while (1) {
        for (int i = 0; i < index-1; i++) {
            if (alloys[i].x > alloys[i+1].x) {
                swapAlloys(&alloys[i], &alloys[i+1]);
                goto xloop;
            }
        }
        break;
    }
}

void sortById(struct alloy *alloys, int index) {
    idloop:
    while (1) {
        for (int i = 0; i < index-1; i++) {
            if (alloys[i].id > alloys[i+1].id) {
                swapAlloys(&alloys[i], &alloys[i+1]);
                goto idloop;
            }
        }
        break;
    }
}

int main(int argc, char *argv[])
{
    //int file = fopen("input.txt", "r");
    /*
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }
*/
    // sorted by X
    struct alloy *alloy = (struct alloy*) malloc(sizeof(struct alloy)*ALLOY_NUM);
    alloy[0].id = 'A';
    alloy[0].x = 1.0;
    alloy[0].y = 5.0;
    alloy[1].id = 'B';
    alloy[1].x = 2.0;
    alloy[1].y = 2.0;
    alloy[2].id = 'C';
    alloy[2].x = 3.0;
    alloy[2].y = 4.0;
    alloy[3].id = 'D';
    alloy[3].x = 5.0;
    alloy[3].y = 2.0;
    alloy[4].id = 'E';
    alloy[4].x = 4.0;
    alloy[4].y = 1.0;

    sortByX(alloy, ALLOY_NUM);

    printf("Sorted Alloys:\n");
    for (int i = 0; i < ALLOY_NUM; i++) {
        printf("%c %.2f %.2f\n", alloy[i].id, alloy[i].x, alloy[i].y);
    }

    struct alloy *dominant = (struct alloy*) malloc(sizeof(struct alloy)*5);
    dominant[0] = alloy[ALLOY_NUM-1];
    int dominantIndex = 1;

    for (int i = ALLOY_NUM-1; i >= 0; i--) {
        if (dominant[dominantIndex-1].y < alloy[i].y) { // prev dominant Y < current Y
            dominant[dominantIndex] = alloy[i];
            dominantIndex++;
        }
    }

    sortById(dominant, dominantIndex);

    printf("\n");
    printf("Dominant Alloys:\n");
    for (int i = 0; i < dominantIndex; i++) {
        printf("%c %.2f %.2f\n", dominant[i].id, dominant[i].x, dominant[i].y);
    }

    free(alloy);
    free(dominant);

    return 0;
}