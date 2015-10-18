#ifndef UF_INITIALIZED
#include <stdio.h>
#include <stdlib.h>
#include "wndfuncs.h"

// util definitions (utilizing ifndef to be safe)
#ifndef DELAY
#define DELAY 100 // 100 millisec
#endif

#ifndef FOODCHAR
#define FOODCHAR 4 // this would be a diamond, on my PC
#endif

#ifndef SCORE_INCREMENT
#define SCORE_INCREMENT 5
#endif

// typedefs
typedef struct { // Link
    int x, y;
    int xdir, ydir;
    char sprite;
    char moving;
} Link;
typedef struct Point { // BendPoint
    int x, y;
    int xdir, ydir;
    int incr;
    struct Point* next;
} BendPoint;
typedef struct { // Food
    int x, y;
} Food;

// function prototypes
void setDir(BendPoint*, Link**, int);
void addBP(BendPoint**, Link*, int, int);
BendPoint* delBP(BendPoint**, int);
void printBPInfo(BendPoint*);
int checkNoCollision(Link*, int, int, int);
void remExpiredBP(BendPoint**, int);
void addFood(Food*, int, int);
void extendSnake(Link**, int*, int);

// function definitions
void setDir(BendPoint* bp, Link** chain, int length) {
    BendPoint* prev;
    char changed;
    while (bp) {
        changed = 0;
        
        for (int i = 0; i < length; i++) {
            if ((*chain)[i].x == bp->x && (*chain)[i].y == bp->y) {
                (*chain)[i].moving = 1;
                (*chain)[i].xdir = bp->xdir;
                (*chain)[i].ydir = bp->ydir;
                bp->incr++;
                changed = 1;
            }
        }
        prev = bp;
        bp = bp->next;
    }
}
void addBP(BendPoint** top, Link* head, int xd, int yd) {
    BendPoint* tmp = malloc(sizeof *tmp);
    tmp->next = *top;
    tmp->x = head->x;
    tmp->y = head->y;
    tmp->xdir = xd;
    tmp->ydir = yd;
    tmp->incr = 0;
    *top = tmp;
}
BendPoint* delBP(BendPoint** top, int index) {
    BendPoint* toRemove = *top;
    BendPoint* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = toRemove;
        if (toRemove->next) {
            toRemove = toRemove->next;
        } else {
            return NULL;
        }
    }
    if (!prev) {
        *top = (*top)->next;
    } else {
        prev->next = toRemove->next;
    }
    toRemove->next = NULL;
    return toRemove;
}
void printBPInfo(BendPoint* bp) {
    while(bp) {
        printf("X: %d\nY: %d\nXDIR: %d\nYDIR: %d\nINCR: %d\nNEXT:%X\n\n", bp->x, bp->y, bp->xdir, bp->ydir, bp->incr, bp->next);
        bp = bp->next;
    }
}
int checkNoCollision(Link* snk, int length, int xsize, int ysize) {
    // returns 1 if head doesn't collide (with self or env.), else false
    if (snk->x >= xsize || snk->x < 0 || snk->y >= ysize ||snk->y < 0) return 0;
    for (int i = 1; i < length; i++) {
        if (snk[i].x == snk->x && snk[i].y == snk->y) return 0;
    }
    return 1;
}
void remExpiredBP(BendPoint** top, int totalLength) {
    int i = 0;
    BendPoint* bp = *top;
    while (bp->next) {
        bp = bp->next;
        i++;
    }
    if (bp->incr >= totalLength) {
        if (i) {
            delBP(top, i);
        }
        else {
            *top = NULL;
        }
    }
}
void addFood(Food* fd, int xsize, int ysize) {
    fd->x = rand() % xsize;
    fd->y = rand() % ysize;
}
void extendSnake(Link** chain, int* length, int toAdd) {
    *chain = realloc(*chain, ((*length)+toAdd) * sizeof **chain);
    for (int i = *length; i < (*length)+toAdd; i++) {
        (*chain)[i] = (*chain)[i-1];
        (*chain)[i].moving = 0;
    }
    *length += toAdd;
}

#define UF_INITIALIZED
#endif