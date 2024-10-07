using namespace std;

#include <stdio.h>
#include <math.h>

// debug macro
#ifdef DEBUG
#define DEBUG_PRINT(...) fprintf( stderr, __VA_ARGS__ )
#else
#define DEBUG_PRINT(...) do{ } while ( 0 )
#endif

struct tile {
    bool value = 0;
    bool explored = 0;
};

struct lake {
    int area = 0;
};

short int y_max, x_max;

// 0b0000UDLR
unsigned char exploreNeighbors(struct tile *current){

    unsigned char n_map = 0;

    // Neighbor up
    struct tile *neighbor = &current[-x_max];
    DEBUG_PRINT("U: %d%d, ", neighbor->value, neighbor->explored);
    if (neighbor->value && !(neighbor->explored))
        n_map = (n_map << 1) + 1;
    else
        n_map = (n_map << 1);
    
    // Neighbor down
    neighbor = &current[x_max];
    DEBUG_PRINT("D: %d%d, ", neighbor->value, neighbor->explored);
    if (neighbor->value && !(neighbor->explored))
        n_map = (n_map << 1) + 1;
    else
        n_map = (n_map << 1);

    // Neighbor left
    neighbor = &current[-1];
    DEBUG_PRINT("L: %d%d, ", neighbor->value, neighbor->explored);
    if (neighbor->value && !(neighbor->explored))
        n_map = (n_map << 1) + 1;
    else
        n_map = (n_map << 1);
    
    // Neighbor right
    neighbor = &current[1];
    DEBUG_PRINT("R: %d%d,\t", neighbor->value, neighbor->explored);
    if (neighbor->value && !(neighbor->explored))
        n_map = (n_map << 1) + 1;
    else
        n_map = (n_map << 1);

    return n_map;
}

/* Simple, stdin, line-by-line reader.
 * Gets first line, gets N more lines.
 */
static inline void readInput(struct tile *map) {
    // Input reading using scanf
    char *line = (char*) malloc(x_max+1*sizeof(char));
    for (int y = 0; y < y_max; y++) {
        scanf("%s", line);
        //DEBUG_PRINT("Scanned: %s\n", line);
        for (int x = 0; x < x_max; x++) {
            (&map[(y*x_max + x)])->value = (bool) (line[x] != '0');
            //DEBUG_PRINT("Read: %d\n", (&map[(y*x_max + x)])->value);
        }
        //DEBUG_PRINT("\n");
    }
}

void printMap(struct tile *map) {
    for (int y = 0; y < y_max; y++) {
        DEBUG_PRINT("%2d ", y);
        for (int x = 0; x < x_max; x++) {
            DEBUG_PRINT("%d", (&map[(y*x_max + x)])->value);
        }
        DEBUG_PRINT("\n");
    }
    DEBUG_PRINT("\n");
}

void printBits(unsigned char v) {
  int i; // for C89 compatability
  for(i = 3; i >= 0; i--) DEBUG_PRINT("%c", '0' + ((v >> i) & 1));
}

// explore the lake and collapse its tiles
void collapseLake(struct tile *current, struct lake *current_lake) {
    
    if (current->explored){
        DEBUG_PRINT("Already Explored\n");
        return;
    }
    current->explored = 1;
    (current_lake->area)++;

    unsigned char neighbors = exploreNeighbors(current);
    DEBUG_PRINT("Neighbors are ");
    printBits(neighbors);
    DEBUG_PRINT("\n");
    
    switch(neighbors) {
        case 0:
            DEBUG_PRINT("Dead end\n");
            break;
        case 1: // 0001 R
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            break;
        case 2: // 0010 L
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            break;
        case 3: // 0011 LR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            break;
        case 4: // 0100 D
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            break;
        case 5: // 0101 DR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            break;
        case 6: // 0110 DL
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            break;
        case 7: // 0111 DLR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            break;
        case 8: // 1000 U
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 9: // 1001 UR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 10: // 1010 UL
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 11: // 1011 ULR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 12: // 1100 UD
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 13: // 1101 UDR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 14: // 1110 UDL
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
        case 15: // 1111 UDLR
            DEBUG_PRINT("Exploring right\n");
            collapseLake(&current[1], current_lake);
            DEBUG_PRINT("Exploring left\n");
            collapseLake(&current[-1], current_lake);
            DEBUG_PRINT("Exploring down\n");
            collapseLake(&current[x_max], current_lake);
            DEBUG_PRINT("Exploring up\n");
            collapseLake(&current[-x_max], current_lake);
            break;
    }

}

// parse x,y until lake tile is hit and it's not explored. Then add a new lake to the struct
void findLakes(struct tile *map) {
    int lake_count = 0;
    struct lake *lakes = NULL;
    for (int y = 1; y < y_max-1; y++) {
        for (int x = 1; x < x_max-1; x++) {
            struct tile *current = &map[(y*x_max + x)];
            if (current->value && !(current->explored)) {
                DEBUG_PRINT("New Lake starting at: %2d, %2d.\n", x, y);
                lake_count++;
                lakes = (struct lake*) realloc(lakes, lake_count*sizeof(struct lake));
                lakes[lake_count - 1]. area = 0;
                collapseLake(current, &lakes[lake_count - 1]);
            }
        }
    }
    DEBUG_PRINT("\n");
    printf("%d\n", lake_count);
    for (int i = 0; i < lake_count; i++) {
        printf("%d ", lakes[i].area);
    }
    printf("\n");
}

int main()
{
    // scanf expects int* when using %d, but short int* is half the size, leading to stack smashing.
    scanf("%hd %hd", &y_max, &x_max);  // Read the number of alloys
    DEBUG_PRINT("Map size: %dx%d\n", x_max, y_max);

    // TODO: check if it's possible to skip edge blocks
    struct tile *map = (struct tile*) malloc(x_max*y_max*sizeof(struct tile));

    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    readInput(map);
    printMap(map);

    findLakes(map);   

}