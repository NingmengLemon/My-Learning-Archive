#include "bnum.h"

// 用于运算替代的一些函数
uint64_t mul(uint64_t a, uint64_t b){
    uint64_t res = 0;
    while(b){
        if (b & 1){ // b 是奇数时直接往上加
            res += a;
        }
        a <<= 1; // a *= 2
        b >>= 1; // b /= 2
    }
    return res;
}

uint64_t div_(uint64_t a, uint64_t b){
    if(a < b){
       return 0;
    }
    
    uint64_t res = 0;
    while(a >= b){
        uint64_t tmp = b;
        uint64_t mult = 1;
        while(a >= (tmp<<1)){
            tmp <<= 1;
            mult <<= 1;
        }
        a -= tmp;
        res += mult;
    }
    return res;
}

uint64_t mod(uint64_t x, uint64_t y){
    if(x < y || y == 0) return x;
    uint64_t t = y;

    while(t <= div_(x,2)){
        // byd溢出, 你是一个一个...
        t <<= 1;
    }

    while(x >= y){
        while(t > x){
            t >>= 1;
        }
        x -= t;
    }
    // printf("Mod once..\n");
    return x;
}

void reset_to_zero(bnum num){
    for(int i=0;i<MAX_DIGIT_NUM;i++){
        num[i] = 0;
    }
}

bnum new_bnum(void){
    bnum num = (bnum)malloc(mul(MAX_DIGIT_NUM,sizeof(digit)));
    reset_to_zero(num);
    return num;
}

void del_bnum(bnum num){
    free(num);
}

void add_bnum(const bnum a, const bnum b, bnum res){
    digit carry = 0;
    reset_to_zero(res);
    
    for(int i=0;i<MAX_DIGIT_NUM;i++){
        res[i] = a[i] + b[i] + carry;
        if(res[i]>=10){
            res[i] -= 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
    }
    if(carry>0){
        // 可能会溢出, 但不做处理
    }
}

int compare(const bnum a, const bnum b){
    for(int i=MAX_DIGIT_NUM-1;i>=0;i--){ 
        // 从高位开始进行一个大遍(指大型(?)的遍历)
        if(a[i]>b[i]) return 1;
        if(a[i]<b[i]) return -1;
    }
    return 0;
}

bool is_zero(const bnum n){
    for(int i=0;i<MAX_DIGIT_NUM;i++){
        if(n[i]!=0) return false;
    }
    return true;
}

void input_from_ui64(bnum n, uint64_t x){
    char buffer[MAX_DIGIT_NUM] = "";
    char tmp[10] = "";
    reset_to_zero(n);
    sprintf(tmp, "%%0%dllu", MAX_DIGIT_NUM);
    sprintf(buffer, tmp, x);
    
    int d = 0;
    for(int i=MAX_DIGIT_NUM-1;i>=0;i--,d++){
        n[d] = buffer[i]-48;
    }
}

void input_from_str(bnum n, const char* s){
    int len = strlen(s);
    if(len>MAX_DIGIT_NUM){
        // 溢出了捏, 但不处理
    }
    reset_to_zero(n);

    for(int i = 0, ds = len-1; i < len && ds >= 0; i++,ds--){
        n[i] = s[ds] - '0';
    }
}

int get_length(const bnum x){
    for(int i=MAX_DIGIT_NUM-1;i>=0;i--){
        if(x[i]>0) return i+1;
    }
    return 1;
}

void multiply_bnum(const bnum a, const bnum b, bnum res){
    int carry = 0;
    int tmp = 0;
    reset_to_zero(res);

    for(int i=0; i<MAX_DIGIT_NUM; i++){
        carry = 0;
        for(int j=0; j<MAX_DIGIT_NUM; j++){
            if(i+j > MAX_DIGIT_NUM-1){
                if(mul(a[i],b[j])+carry>0){
                    // 溢出, 但我选择忽略它...
                }
                break;
            }
            tmp = (int)mul(a[i], b[j]) + carry + (int)res[i+j];
            res[i+j] = mod(tmp,10);
            carry = div_(tmp,10);
        }
    }
    if(carry != 0){
        // 溢出, 但是忽略...
    }
}

void subtract_bnum(bnum m, bnum n, bnum res){
    int comp_res = compare(m, n);
    bool is_nega = false; 
    bnum a = NULL;
    bnum b = NULL;
    reset_to_zero(res);
    if(comp_res==0){
        return;
    }
    else if(comp_res==1){
        a = m; b = n;
        is_nega = false;
    }
    else{
        b = m; a = n;
        is_nega = true;
    }

    int borrow = 0;
    int sub = 0;
    for(int i = 0; i < MAX_DIGIT_NUM; i++){
        sub = a[i] - borrow;
        if(i < MAX_DIGIT_NUM){
            sub -= b[i];
        }
        // 处理借位
        if (sub < 0){
            sub += 10;
            borrow = 1;
        } 
        else{
            borrow = 0;
        }
        res[i] = sub;
    }
    return;
}

void _operate_with_bnum_template(bnum x, const bnum y, void (*operator)(const bnum, const bnum, bnum)){
    bnum tmp = new_bnum();
    memcpy(tmp, x, mul(MAX_DIGIT_NUM, sizeof(digit)));
    operator(tmp, y, x);
    del_bnum(tmp);
}

void _operate_with_const_template(bnum x, uint64_t y_, void (*operator)(const bnum, const bnum, bnum)){
    bnum y = new_bnum();
    input_from_ui64(y, y_);
    // 现在问题变成了两个 bnum 操作
    _operate_with_bnum_template(x, y, operator);
    del_bnum(y);
}

void multiply_bnum_with_const(bnum x, uint64_t y){
    _operate_with_const_template(x, y, multiply_bnum);
}

void add_const_to_bnum(bnum x, uint64_t y){
    _operate_with_const_template(x, y, add_bnum);
}

void subtract_bnum_with_const(bnum x, uint64_t y){
    _operate_with_const_template(x, y, subtract_bnum);
}

void multiply_bnum_with_bnum(bnum x, bnum y){
    _operate_with_bnum_template(x, y, multiply_bnum);
}

void add_bnum_to_bnum(bnum x, bnum y){
    _operate_with_bnum_template(x, y, add_bnum);
}

void subtract_bnum_with_bnum(bnum x, bnum y){
    _operate_with_bnum_template(x, y, subtract_bnum);
}

void module_bnum(bnum a, bnum b, bnum res) {
    int comp_res = compare(a,b);
    reset_to_zero(res);
    if(comp_res==0){
        return;
    }
    else if(comp_res==-1){
        memcpy(res, b, mul(MAX_DIGIT_NUM, sizeof(digit)));
        return;
    }
    int len = get_length(a);
    // 逐位模拟竖式除法
    for(int i = len - 1; i >= 0; i--) {
        // 整体 x10
        for (int j = len - 1; j > 0; j--) {
            res[j] = res[j - 1];
        }
        res[0] = a[i];

        // 进行一个减
        while(compare(res, b) >= 0) {
            subtract_bnum_with_bnum(res, b);
        }
    }
}

void multimod_bnum(const bnum a, const bnum b, const bnum y, bnum res){
    bnum x = new_bnum();
    multiply_bnum(a,b,x);
    module_bnum(x,y,res);
    del_bnum(x);
}

uint64_t bnum_to_ui64(const bnum x){
    int length = get_length(x);
    uint64_t pw = 1;
    uint64_t res = 0;
    for(int i=0;i<length;i++){
        res += mul(x[i],pw);
        pw = mul(pw,10);
    }
    return res;
}

uint64_t multimod_ok(uint64_t a, uint64_t b, uint64_t y){
    bnum a_ = new_bnum();
    bnum b_ = new_bnum();
    bnum y_ = new_bnum();
    bnum res = new_bnum();

    input_from_ui64(a_, a);
    input_from_ui64(b_, b);
    input_from_ui64(y_, y);

    multimod_bnum(a_,b_,y_,res);
    uint64_t res_ = bnum_to_ui64(res);
    del_bnum(a_);
    del_bnum(b_);
    del_bnum(y_);
    del_bnum(res);
    return res_;
}

void print_bnum(const bnum x){
    int length = get_length(x);
    for(int i=length-1;i>=0;i--){
        printf("%u", x[i]);
    }
}


