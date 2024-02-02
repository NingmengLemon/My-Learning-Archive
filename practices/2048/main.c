#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#include "game.h"

char get_input(void){
    char d = getchar();
    char t;
    while((t=getchar())!='\n') continue;
    return d;
}

int main(int argc, char* argv[]){
    int w=4,h=4,target=2048;
    int tmp=0;
    char input=EOF;

    srand((unsigned)time(NULL));
    // read args from command
    if(argc>=3){
        sscanf(argv[1],"%d",&w);
        sscanf(argv[2],"%d",&h);
    }
    if(argc>=4){
        sscanf(argv[3],"%d",&target);
    }
    // generate stage
    Matrix* stage = create_matrix(w,h,0);
    if(stage==NULL){
        printf("Game crashed because of Memory Error QAQ");
        return EXIT_FAILURE;
    }
    printf("STAGE %dx%d\n",w,h);
    if(target<0) printf("Target: -\n");
    else printf("Target: %d\n",target);
    printf("Use [A] [W] [S] [D] and [ENTER] to play game.\n");
    // summon init num
    summon_new_num(stage, 2);
    summon_new_num(stage, 4);
    print_stage(*stage);
    // main process
    while(true){
        input = get_input();
        if(check_if_any_effect(*stage, input)){
            if(merge(stage, input)){
                summon_new_num(stage, 2);
            }
        }

        system("cls");
        print_stage(*stage);
        
        if(check_if_end(*stage)){
            printf("Oops, it seems that you've meet your end...\n");
            break;
        }
        if(check_if_target_reached(*stage, target)){
            printf("Congratulation! You've reach %d!\n",target);
            break;
        }
    }
    printf("Game Over!\nThank you for playing!!\n");

    destroy_matrix(stage);
    system("pause");
    return EXIT_SUCCESS;
}