# 要分清类跟实例的区别……
# 实例和类在py和cpp中都有概念
class Human(object): # 在py3中不写父类（连着括号都不写）就默认继承自object
    # class Human: 就像这样，跟上一行等价。但py2就不是这样，但我不学。
    a = 0 # 类属性
    def __init__(self):
        # 实例属性，与类属性同名的话会把类属性屏蔽掉
        # （感觉又有点像C++中的继承屏蔽（但也只是像而已））
        self._name = '' # 标记为私有，但外界能够访问
        self._age = 0
        
    def set(self): # 未标记为私有
        pass
    
    # 没有指定 @classmethod，是实例方法，需要等类实例化之后再调用；如果在实例化前调用的话需要手动传入 self
    def _process(self): # 标记为私有，但外界仍然能够访问
        pass
    
    @classmethod # 指定为类方法，绑定到的是类本身，操作的是类属性，通过隐式或显式传入的cls来操作
    def handle(cls, data):
        cls.a = data.a
        
    @staticmethod # 指定为静态方法，不与任何对象绑定，只是“碰巧”定义在了类中，与普通函数没有什么区别。
    def who_asked_you(person):
        pass

# Python 中的所谓“私有标记”只是约定俗成而已，硬要访问还是可以访问到的
# 实际上全部相当于 public

class Student(Human): # Python 中像这样继承，要继承多个的话就在括号内用逗号分隔
    pass