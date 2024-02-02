#ifndef _BNUM_H
#define _BNUM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_DIGIT_NUM 100

/*
像这样定义一个非负大整数:
 [ 4 , 1 , 5 , 4 , 1 , 1 , 0 , 0 , ...]
<--低位--------------高位---------------
像这样就表示 114514, 剩余位数用 0 补
所有操作数组的函数都不用传入 length, 因为已经定义过了
*/

typedef unsigned char digit;
typedef digit* bnum; 
// big number 嘛, 草率的命名罢了

/*
将 num 的所有位都设为 0
*/
void reset_to_zero(bnum num);

/*
创建一个新的 num
*/
bnum new_bnum(void);

/*
删除一个 num
*/
void del_bnum(bnum num);

/*
让两个大整数相加,
返回到 res 中
*/
void add_bnum(const bnum a, const bnum b, bnum res);

/*
你说得对, 但是 compare 事一款
当 a > b 时返回 1
当 a < b 时返回 -1
当 a = b 时返回 0
的函数, 后面忘了
*/
int compare(const bnum a, const bnum b);

/*
判断是否为 0
*/
bool is_zero(const bnum n);

/*
将 x 转换成一个大整数
输出到 n 中
*/
void input_from_ui64(bnum n, uint64_t x);

/*
将以字符串形式表示的大整数 s 
转换成 bnum 型, 并输出到 n 中
*/
void input_from_str(bnum n, const char* s);

/*
使 a 与 b 相乘
*/
void multiply_bnum(const bnum a, const bnum b, bnum res);

/*
使 m 与 n 相减
把绝对值递给 res
*/
void subtract_bnum(bnum m, bnum n, bnum res);

/*
对 x 进行一个 bnum y 操作的模板
就是 运算完之后把值重新赋到 x 上
*/
void _operate_with_bnum_template(bnum x, const bnum y, void (*)(const bnum, const bnum, bnum));

/*
对 x 进行一个常数 y 操作的模板
*/
void _operate_with_const_template(bnum x, uint64_t y_, void (*)(const bnum, const bnum, bnum));

/*
直接将 y 乘到 x 上
对 x 做出修改
*/
void multiply_bnum_with_const(bnum x, uint64_t y);

/*
直接将 y 加到 x 上
对 x 做出修改
*/
void add_const_to_bnum(bnum x, uint64_t y);

/*
直接将 x 减去 y
返回的是绝对值
对 x 做出修改
*/
void subtract_bnum_with_const(bnum x, uint64_t y);

/*
直接将 y 乘到 x 上
对 x 做出修改
*/
void multiply_bnum_with_bnum(bnum x, bnum y);

/*
直接将 y 加到 x 上
对 x 做出修改
*/
void add_bnum_to_bnum(bnum x, bnum y);

/*
直接将 x 减去 y
返回的是绝对值
对 x 做出修改
*/
void subtract_bnum_with_bnum(bnum x, bnum y);

/*
理想的 mod,
返回一个 bnum 到 res 中
*/
void module_bnum(bnum a, bnum b, bnum res);

/*
进行一个 multimod 运算
*/
void multimod_bnum(const bnum a, const bnum b, const bnum y, bnum res);

/*
封装好的 multimod 运算
*/
uint64_t multimod_ok(uint64_t a, uint64_t b, uint64_t y);

/*
把大整数 x 打印出来
*/
void print_bnum(const bnum x);

/*
将大整数 x 转换为 uint64 类型
警告: 此操作可能截断 x
*/
uint64_t bnum_to_ui64(const bnum x);

#endif