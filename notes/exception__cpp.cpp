#include <iostream>
#include <stdexcept>

class NyannException : public std::exception {
  public:
    const char *what() const noexcept { return "ERROR発生nyannn!!"; }
    /*
    第 1 个 const: 表示返回的字符数组的指针是常量
    第 2 个 const: 保证此成员函数不会修改其他成员
    noexcept: 表示此成员函数不会抛出错误
    其他的概念跟 Python 差不多, 毕竟都是高级编程语言
    */
};
/*
嗯实际上, 在 C++ 中, 
你可以 throw 任意类型的对象, 
只要你自己能 catch 住就行
此时 catch 里填对应类的 const 引用
*/

int main(void) {
    try {
        throw NyannException();
    } catch (const NyannException &e) {
        std::cout << "I caught a neko!" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown exception nyann!!" << std::endl;
    }

    return 0;
}
