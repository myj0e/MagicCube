#include<stdio.h>

#include "cube.h"
#include "present.h"
// 主函数
int main() {
    struct cube c;
    char op[2];
    cube_init(&c, 3);
    while(1){
        clear_screen();
        print_cube(&c);
        printf("\
<Basic Operations:U, D, F, B, L, R. \n \
    Besides above: Q(quit), N(new)>\n \
e.g. \n \
    \"Ui\" for Anti-clockwise rotation.\n \
    \"U2\" for 180 degree rotation.\n \
    \"U\" for clockwise rotation.\n \
#operation: ");
        scanf(" %s", op);
        if(op[0] >= 'a' && op[0] <= 'z'){
            op[0] -= 32;
        }
        if(op[1] >= 'A' && op[1] <= 'Z'){
            op[1] += 32;
        }
        if(op[1] == 0){
            if(op[0] == 'Q'){
                break;
            }
            else if(op[0] == 'N'){
                cube_init(&c, 3);
            }
        }
        three_order_cube_op(&c, op);
        op[0] = 0;
        op[1] = 0;
    }
    return 0;
}