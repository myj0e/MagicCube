#include <stdio.h>
#include <stdlib.h>

#include "present.h"
#include "cube.h"


// ANSI颜色
const char* ansi_colors[CC_END] = {"\033[31m", "\033[34m", "\033[32m", "\033[37m", "\033[35m", "\033[38;5;208m"};

// 色块颜色转换
static const char* color_transfer(int colorEnum){
    return ansi_colors[colorEnum];
}

// 清空终端屏幕
void clear_screen() {
    system("clear");
}

// 打印色块
void print_cube(struct cube *c) {
    // 顶部
    for(int i = 0; i < c->order; i++){
        for(int j = 0; j < c->order; j++){
            printf("  ");
        }
        printf(" ");
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_U].pieces[i][j]));
        }
        printf("\n");
    }
    printf("\n");
    // 左面、前面、右面
    for(int i = 0; i < c->order; i++){
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_L].pieces[i][j]));
        }
        printf(" ");
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_F].pieces[i][j]));
        }
        printf(" ");
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_R].pieces[i][j]));
        }
        printf("\n");
    }
    printf("\n");

    // 底部
    for(int i = 0; i < c->order; i++){
        for(int k = 0; k < c->order; k++){
            printf("  ");
        }
        printf(" ");
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_D].pieces[i][j]));
        }
        printf("\n");
    }
    printf("\n");

    // 后面
    for(int i = 0; i < c->order; i++){
        for(int k = 0; k < c->order; k++){
            printf("  ");
        }
        printf(" ");
        for(int j = 0; j < c->order; j++){
            printf("%s#\033[0m ", color_transfer(c->faces[CF_B].pieces[i][j]));
        }
        printf("\n");
    }
    
}