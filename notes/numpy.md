# 是 NumPy 来了噢~!

信息来源: NumPy 官网 / 菜鸟教程

---

## NumPy 数组 `array`

> 或者说, `ndarray`, N-Dimensional Array

### 特性

- 其中的元素的类型保持一致
- 可以通过 `非负整数元组` / `bool值` / `另一个数组` / `整数` 来进行索引
- 很高效

### 创建

可以传入`dtype`来手动指定元素类型, 默认`np.float64`

- `np.array(object, ...)`

- `np.zeros(shape, ...)`

- `np.ones(shape, ...)`

- `np.ones_like(array, ...)` `np.zeros_like(array, ...)`

    > 根据传入的数组创建一个新的元素全为 0 / 1 的相同形状的数组

- `np.empty(shape, ...)`

    > 注意这个函数创建的数组的内容是随机的, 就像 C 里没有初始化的数组一样
    >
    > <small>但是快啊 (小声)</small>

- `np.arange(start, end, step, ...)`

    > 像`range()`一样呐

- `np.linspace(start, stop, num, endpoint, ...)`

    > 创建等差数列, 元素有`num`个
    >
    > `endpoint`控制产出的数组是否包含`stop`

- `np.logspace(...)`

    > 同上, 但是等比数列
    >
    > 多了个参数`base`, 指定底数

### 属性

- `ndim` - 秩(`rank`), 或者说 维度的数量 或 轴(`axis`)的数量

    > 我超 轴!
    >
    > 每个线性的数组都是一个轴
    >
    > 比如说 一个三维的数组就有三个轴, 包在最里面的那个纯数字的就是第三个轴, 往外一层的包着一维数组的数组是第二个轴, 最外层的包着二维数组的数组就是第一个轴
    >
    > (是我个人的理解, 不知道对不对)

- `dtype` - 数组中元素的类型

- `shape`  - 是个元组, 给出每个维度的大小, 可以通过直接赋值来改变

    > eg. 二维数组(矩阵)就是 `width` & `height` 

- `itemsize` - 内容元素的字节大小

- `flags` - 数组对象的内存信息

- `real` - 数组元素的实部

- `imag` - 数组元素的虚部

- `size` - 总共有多少元素

- `data` - 直接返回数组的内容, 不常用

### 切片 & 索引

#### 基础 

##### `[start: stop: step]`

> 跟 Python 内置的一样, 区间`[start, stop)`, 每个元素的索引相差`step`
>
> 像`[:]`可以用来标识全体索引
>
> 像`[::-1]`也可以用来快速倒序

##### `...`与`,`

`,`用于分割不同维度上的索引

`...`表示所有剩余的维度或者中间省略的维度

>  比如对于一个四维数组
>
>  `array[..., 0]`与`array[:, :, :, 0]`等价

##### 布尔索引

> 用于筛选元素, 将通过筛选的元素组成一个一维数组返回

用法是`array[以array为主要对象的布尔表达式]`

> eg. `array[array > 5]`

> (我个人)推测的原理  
> 对`array`做布尔运算会产生一个新的、内容元素全为`True`或`False`的、形状一致的新数组  
> 将这个数组再传入数组的重载过的索引操作, 就能对应地筛选出这些值了
>
> ~~不然仅凭一个布尔值我觉得真筛不出来罢~~

其他可用的写法还有  
用 `&` 代替 `and`: `[array > 5 & array < 10]`  
用 `|` 代替 `or`:  `[array > 5 | array < 0 ]`  
用 `~` 代替 `not`: `[~np.isnan(array)]`

##### 整数数组索引

当用一个整数数组`iarr`充当索引时, 返回的结果是从每组索引中选择的元素组成的数组

> eg. 
>
> ```python
> >>> array = np.array([[1, 2], [3, 4], [5, 6]])
> >>> print(arr[[0, 1, 2], [0, 1, 0]])
> [1 4 5]
> ```

### 方法

- `reshape(shape, ...)` - 传入新的表示大小的元组, 返回一个改变了大小的数组, 改变了上文的`shape`属性

    > 这个方法返回的"新"数组实际上是"旧"数组的引用, 对"新"数组的修改会作用到"旧"数组中.
    >
    > (因为它们共享了底层的数据)

---



