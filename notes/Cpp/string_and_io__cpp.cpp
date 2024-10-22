// from std import string (bushi)
#include <string>
using std::string; 

#include <iostream>
using std::cin; // 标准输入流对象
using std::cout; // 标准输出流对象
// clog 日志流 输出流 有缓
// cerr 错误流 输出流 无缓
using std::getline; // 按行读取
// std::istream, std::ostream, ...
// io类, 不能被拷贝或赋值
// 也就是说 操作io对象的函数不能用const修饰形参中的io对象

/*
io库中的操纵符:
endl        输出一个换行符然后flush
flush       刷新缓冲区
ends        输出一个空字符然后flush
unitbuf     设定为无缓
nounitbuf   设定为有缓

像这样用:
cout << "Aughhhhhh" << endl;
*/

void test_string(void){
    // 传统的字符串 (或者说, 字符数组)
    char s_c[] = "You are a, a, a, ahhhhhhh"; // 注意这里的末尾被自动加上了\0
    char s_c_nn[] = {'1','1','4','5','1','4'}; // 这里就没有\0
    // 初始化字符串对象的各种方式
    string s1; // 空字符串
    string s2 = s1; // 拷贝初始化, 等价于 string s2(s1); s1也可以是字面量
    string s3(114514, '?'); // 初始化为一定长度的重复字符
    string s4(s_c); // 从字符数组拷贝, 字符数组必须以\0结尾, 否则ub
    string s5(s_c_nn, 4); // 从字符数组拷贝, 但指定了长度就不一定需要\0结尾
    // 值得注意的是, 遇到空字符时还是会停. 在没有空字符的情况下长度越界似乎是ub
    string s6(s3, 2, 5); // "切片拷贝", 从[2]开始拷贝5个字符作为初始化
    // 字符数量可以省略, 此时拷贝至字符串末尾
    // 字符数量越界似乎是ub, 起始索引越界会抛 out_of_range
    // ub: undefined behavior 未定义行为
    
    // 写入string
    /*
    cin 从遇到的第一个非空白符开始读, 到再次遇到空白符为止
    */
    cin >> s1;
    /*
    getline 一遇到换行符就停止, 也就是说一开始就读到换行符会导致得到空字符串
    */
    getline(cin, s1);

    // string 各种操作
    s1 = s3.substr(1, 5); // 从[1]开始拷贝5个字符, 返回新的string (cppp P322)
    char augh = s3.at(1); // 相当于有边界检查的[]操作
    std::swap(s5, s6); // swap的对string重载
    s4 = s5 + s6; // 拼接字符串 (+运算符的重载)
    // 其他操作要用到的时候查文档就行了(逃)
    // https://zh.cppreference.com/w/cpp/string/basic_string

    // 转换string
    double num = std::stod(s1); // 字符串转双浮点, 其中的d表示double, 由此可推出其他转换
    /*
    浮点数: stof, stod, stold
    整数:   stoi, stol, stoll, stoul, stoull
    */
    s2 = std::to_string(1919810); // 数字转字符串(除了整数以外还有其他的重载)

    // 输出string
    cout << s1 << std::endl;
}