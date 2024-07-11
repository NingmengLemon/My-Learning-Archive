#include <string>

// 实例和对象其实是一码事
// 在C++中一般叫对象，Python中叫实例
class Human {
  public:                    // 公有
    void set(int new_value); // 可以只声明不定义
    void get(void) {         // 也可以直接定义
    }

  private: // 私有，从外部和子类中都不能访问
    std::string name;
    int age;

  protected: // 受保护
             // 与 private 差不多，但在子类中能访问
}; // 类定义末尾记得加分号

void Human::set(
    int new_value) { // 定义成员函数 set，但开头需要用::表示属于哪个类
    this->age = new_value;
}

class Student : public Human {
    // C++ 中像这样继承，继承多个就用逗号分隔
    // 此处的 public 表示继承方式，不写默认是 private
    // public 继承：父类的成员属性都保持不变
    // private 继承：父类的全部成员的属性变成 private
    // protected 继承：父类的 public 成员的属性变成 protected，其余不变
    // 个人理解：优先级 private > protected > public，限制程度逐渐减小
  public:
    // public 访问控制:
    // 在当前类/外界/友元/派生类 中都可以访问
    int a;
    // 当成员函数的名字与类的名字相同时，是特殊函数
    // 下面这个相当于Python的 __init__()
    // 此时在实例化对象的时候需要加上调用括号, 注意这个函数不指定返回值类型
    Student(void) {
        this->a = 114514;
        // this 类似于 Python 中的 self，平时是隐式传入的
        // this 是个指针，指向实例（或者说对象）自己
        // 因为`x->y`是`(*x).y`的简写，所以`->`运算符也可用于对象。
    }
    Student(int a_) : a(a_) {
        // 初始化列表, 紧跟在构造函数参数列表结束后
        // 可以方便地初始化对象内的值
    }
    ~Student(void) {
        // 析构函数, 与实例化函数只差了前面的一个 ~
        // 相当于 Python 中的 __del__()
        // 在这里写清理用的代码
        // 在对象被销毁时自动调用
    }
    Student(const Student &other) {
        // 复制构造函数
        // 将 other 中的数据全部复制到 当前对象 中
        // 当对象以值传递给函数、从函数返回或者以值方式初始化另一个对象时用到
        // 如果不显式定义复制构造函数, 编译器会生成一个默认的复制构造函数, 该函数对类的所有成员执行逐成员复制。
    }
    Student &operator=(const Student &other) {
        // 重载运算符，这里是复制赋值
        // 将一个对象的值复制到另一个已经存在的对象中
        // 用于已经初始化好的对象之间相互赋值时大概
        // 也是把 other 里的东西复制过来
    }
    Student(Student &&other) noexcept {
        // 移动构造函数（>=C++11）
        // 使用 noexcept 表示此函数不会抛出异常
    }
    static void handle(void) {
        // 用static定义静态成员函数，相当于Python中的 @staticmethod
        // 静态成员函数内部不能使用 this, 就像Python中的不能使用 self 一样
    }
    void say_hi(void) const {
        // 在函数名后面添加的 const,
        // 表明此函数不会修改对象的成员变量
    }

  protected:
    // 相较于 public, 外界不能访问
  private:
    // 相较于 protected, 派生类不能访问
};

int main(void) {
    // 像这样调用静态成员函数, 跟 Python 差不多
    Student::handle();
}