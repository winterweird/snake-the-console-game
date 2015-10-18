#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// override window size and delay

#define DELAY 50
#define XSIZE 60
#define YSIZE 30

#include "utilfuncs.h"

int main(int argc, char* argv[]) {
    int GAME_DELAY, GAME_XSIZE, GAME_YSIZE;
    switch(argc) {
        case 2:
            GAME_DELAY = atoi(argv[1]);
            GAME_XSIZE = XSIZE;
            GAME_YSIZE = YSIZE;
            break;
        case 3:
            GAME_DELAY = DELAY;
            GAME_XSIZE = atoi(argv[1]);
            GAME_YSIZE = atoi(argv[2]);
            break;
        case 4:
            GAME_DELAY = atoi(argv[1]);
            GAME_XSIZE = atoi(argv[2]);
            GAME_YSIZE = atoi(argv[3]);
            break;
        default:
            GAME_DELAY = DELAY;
            GAME_XSIZE = XSIZE;
            GAME_YSIZE = YSIZE;
    }
    setConsoleSize(GAME_XSIZE, GAME_YSIZE);
    SetConsoleTitle("SNAKE - THE CONSOLE GAME");
    char playing = 1;
    srand(time(NULL));
    while(playing) {
        clearScreen(GAME_XSIZE, GAME_YSIZE);
        
        int len = 4;
        int active = 1;
        int score = 0;
        char cmd;
        SYSTEMTIME time0, time1;
        
        Link* snake = malloc(len * sizeof *snake);
        BendPoint* bps = NULL;
        Food food;
        
        // initialize the snake
        for (int i = 0; i < len; i++) {
            snake[i].x = GAME_XSIZE/2;
            snake[i].y = GAME_YSIZE/2;
            snake[i].sprite = 'O';
            snake[i].xdir = 0;
            snake[i].ydir = 0;
            snake[i].moving = 0;
        }
        
        printCX(GAME_XSIZE, "Pick a direction with WASD", GAME_YSIZE/4);
        
        int running = 1;
        while (running) {
            int elapsed;
            GetSystemTime(&time0);
            cmd = '\0';
            if (kbhit()) {
                cmd = getch();
                switch(cmd) {
                    case 27: // escape
                        return 1;
                    case 'w': {
                        if (snake[0].ydir) break;
                        if (!snake->moving) {
                            clearScreen(GAME_XSIZE, GAME_YSIZE);
                            addFood(&food, GAME_XSIZE, GAME_YSIZE);
                        }
                        addBP(&bps, snake, 0, -1);
                        break;
                    }
                    case 's': {
                        if (!snake->moving){
                            clearScreen(GAME_XSIZE, GAME_YSIZE);
                            addFood(&food, GAME_XSIZE, GAME_YSIZE);
                        }
                        if (snake[0].ydir) break;
                        addBP(&bps, snake, 0, 1);
                        break;
                    }
                    case 'a': {
                        if (!snake->moving) {
                            clearScreen(GAME_XSIZE, GAME_YSIZE);
                            addFood(&food, GAME_XSIZE, GAME_YSIZE);
                        }
                        if (snake[0].xdir) break;
                        addBP(&bps, snake, -1, 0);
                        break;
                    }
                    case 'd': {
                        if (!snake->moving) {
                            clearScreen(GAME_XSIZE, GAME_YSIZE);
                            addFood(&food, GAME_XSIZE, GAME_YSIZE);
                        }
                        if (snake[0].xdir) break;
                        addBP(&bps, snake, 1, 0);
                        break;
                    }
                }
            }
            
            if (snake->moving) {
                jumpTo(food.x, food.y);
                printf("%c", FOODCHAR);
            }
            
            // for each BreakPoint, set direction for each Link in snake
            setDir(bps, &snake, active);
            
            // this shouldn't need explaining
            if (bps) remExpiredBP(&bps, len);
            
            // remove print of last active Link in snake
            jumpTo(snake[active-1].x, snake[active-1].y);
            printf(" ");
            
            // if collide with self or wall, escape game loop
            if (!(running = checkNoCollision(snake, active, GAME_XSIZE, GAME_YSIZE))) break;
            
            // move each link and print them to the screen
            for (int i = 0; i < active; i++) {
                snake[i].x += snake[i].xdir;
                snake[i].y += snake[i].ydir;
                jumpTo(snake[i].x, snake[i].y);
                printf("%c", snake[i].sprite);
            }
            
            // run if just started or snake just ate something
            if (snake[0].moving && active < len) {
                active++;
            }
            
            if (snake->x == food.x && snake->y == food.y) {
                score += SCORE_INCREMENT;
                addFood(&food, GAME_XSIZE, GAME_YSIZE);
                extendSnake(&snake, &len, 3);
            }
            
            // small timeout
            GetSystemTime(&time1);
            elapsed = time1.wMilliseconds-time0.wMilliseconds;
            if (elapsed < 0) {
                elapsed = 1000*(time1.wSecond-time0.wSecond) + elapsed;
                if (elapsed < 0) elapsed = 0; // game should never hang
            }
            if (elapsed > GAME_DELAY) continue;
            Sleep((snake[0].xdir?GAME_DELAY:GAME_DELAY*3/2) - elapsed);
        }
        // free memory resources
        free(snake);
        while(bps) {
            free(delBP(&bps, 0));
        }
        
        clearScreen(GAME_XSIZE, GAME_YSIZE);
        printCX(GAME_XSIZE, "GAME OVER", GAME_YSIZE*3/8);
        printCX(GAME_XSIZE, "Final score: ", GAME_YSIZE*3/8 + 1);
        printf("%d", score);
        printCX(GAME_XSIZE, "Press 'q' to exit or 'r' to play again", YSIZE/2);
        cmd = '\0';
        while (!(cmd == 'q' || cmd == 'r')) {
            cmd = getch();
            if (cmd == 27) /* escape */ return 1; // I wanna preserve this
            if (cmd == 'q') playing = 0;
        }
    }
    return 0;
}