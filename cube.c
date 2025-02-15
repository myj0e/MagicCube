#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "cube.h"


/***********************************************/
/***************** 色块操作 *********************/
/***********************************************/
// 设置行
void set_raw(struct cube *c, int face, int row, int* buffer){
    int tmp[MAX_CUBE_ORDER]={};
    for(int i = 0; i < c->order; i++){
        tmp[i] = c->faces[face].pieces[row][i];
        c->faces[face].pieces[row][i] = buffer[i];
        buffer[i] = tmp[i];
    }
}

void set_col(struct cube *c, int face, int col, int* buffer){
    int tmp[MAX_CUBE_ORDER]={};
    for(int i = 0; i < c->order; i++){
        tmp[i] = c->faces[face].pieces[i][col];
        c->faces[face].pieces[i][col] = buffer[i];
        buffer[i] = tmp[i];
   }
}

void get_raw(struct cube *c, int face, int row, int* buffer){
    for(int i = 0; i < c->order; i++){
        buffer[i] = c->faces[face].pieces[row][i];
    }
}

void get_col(struct cube *c, int face, int col, int* buffer){
    for(int i = 0; i < c->order; i++){
        buffer[i] = c->faces[face].pieces[i][col];
    }
}


void spin_face(struct cube *c, int face, int direction){
    int buffer[MAX_CUBE_ORDER][MAX_CUBE_ORDER]={};
    for(int i = 0; i < c->order; i++){
        get_raw(c, face, i, buffer[i]);
    }
    if(direction == 0){
        for(int i = 0; i < c->order; i++){
            for(int j = 0; j < c->order; j++){
                c->faces[face].pieces[i][j] = buffer[c->order-j-1][i];
            }
        }
    }
    else{
        for(int i = 0; i < c->order; i++){
            for(int j = 0; j < c->order; j++){
                c->faces[face].pieces[i][j] = buffer[j][c->order-i-1];
            }
        }
    }
}

/***********************************************/
/***************** 本地函数 *********************/
/***********************************************/
// 反转缓冲区
static void reverse_buf(int* buffer, int len){
    int tmp;
    for(int i = 0; i < len/2; i++){
        tmp = buffer[i];
        buffer[i] = buffer[len-i-1];
        buffer[len-i-1] = tmp;
    }
}

// 三阶魔方基本操作
static int three_order_cube_basic_op(struct cube *c, char op){
    int buffer[MAX_CUBE_ORDER]={};
    switch(op){
        case 'U':
            get_raw(c, CF_F, 0, buffer);
            set_raw(c, CF_R, 0, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_B, 2, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_L, 0, buffer);
            set_raw(c, CF_F, 0, buffer);
            spin_face(c, CF_U, 0);
            break;
        case 'D':
            get_raw(c, CF_F, 2, buffer);
            set_raw(c, CF_R, 2, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_B, 0, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_L, 2, buffer);
            set_raw(c, CF_F, 2, buffer);
            spin_face(c, CF_D, 0);
            break;
        case 'F':
            get_raw(c, CF_U, 2, buffer);
            set_col(c, CF_R, 0, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_D, 0, buffer);
            set_col(c, CF_L, 2, buffer);
            reverse_buf(buffer, c->order);
            set_raw(c, CF_U, 2, buffer);
            spin_face(c, CF_F, 0);
            break;
        case 'B':
            get_raw(c, CF_U, 0, buffer);
            reverse_buf(buffer, c->order);
            set_col(c, CF_L, 0, buffer);
            set_raw(c, CF_D, 2, buffer);
            reverse_buf(buffer, c->order);
            set_col(c, CF_R, 2, buffer);
            set_raw(c, CF_U, 0, buffer);
            spin_face(c, CF_B, 0);
            break;
        case 'L':
            get_col(c, CF_U, 0, buffer);
            set_col(c, CF_F, 0, buffer);
            set_col(c, CF_D, 0, buffer);
            set_col(c, CF_B, 0, buffer);
            set_col(c, CF_U, 0, buffer);
            spin_face(c, CF_L, 0);
            break;
        case 'R':
            get_col(c, CF_U, 2, buffer);
            set_col(c, CF_B, 2, buffer);
            set_col(c, CF_D, 2, buffer);
            set_col(c, CF_F, 2, buffer);
            set_col(c, CF_U, 2, buffer);
            spin_face(c, CF_R, 0);
            break;
        default:
            break;
    }
    return 0;
}


/***********************************************/
/***************** 外部函数 *********************/
/***********************************************/
// 初始化魔方
void cube_init(struct cube *c, int order){
    c->order = order;
    for(int i = 0; i < CF_END; i++){
        for(int j = 0; j < order; j++){
            for(int k = 0; k < order; k++){
                c->faces[i].pieces[j][k] = i;
            }
        }
    }
}

int three_order_cube_op(struct cube *c, char *op){
    if(op[1] == 'i'){
        three_order_cube_basic_op(c, op[0]);
        three_order_cube_basic_op(c, op[0]);
        three_order_cube_basic_op(c, op[0]);
    }
    else if(op[1] == '2'){
        three_order_cube_basic_op(c, op[0]);
        three_order_cube_basic_op(c, op[0]);
    }
    else{
        three_order_cube_basic_op(c, op[0]);
    }
    return 0;
}


