#ifndef CUBE_H
#define CUBE_H

#define MAX_CUBE_ORDER 10
#define CUBE_FACES    6

enum cubeFaces{
    CF_U = 0,
    CF_D = 1,
    CF_F = 2,
    CF_B = 3,
    CF_L = 4,
    CF_R = 5,
    CF_END = 6
};


enum cubeColors{
    CC_RED = 0,
    CC_BLUE = 1,
    CC_GREEN = 2,
    CC_WHITE = 3,
    CC_YELLOW = 4,
    CC_CYAN = 5,
    CC_END = 6
};


struct cubeFace{
    int pieces[MAX_CUBE_ORDER][MAX_CUBE_ORDER];
};

struct cube{
    int order;
    struct cubeFace faces[CF_END];
};

// 底层操作，误用可能导致魔方状态不合法
void set_raw(struct cube *c, int face, int row, int* buffer);
void get_raw(struct cube *c, int face, int row, int* buffer);
void set_col(struct cube *c, int face, int col, int* buffer);
void get_col(struct cube *c, int face, int col, int* buffer);
void spin_face(struct cube *c, int face, int clockwise);



// 魔方操作
void cube_init(struct cube *c, int order);
int three_order_cube_op(struct cube *c, char *op);


#endif // CUBE_H