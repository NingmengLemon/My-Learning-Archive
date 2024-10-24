# emm, JS

## 一些神秘

js 跟 py 一样字符串引号不分单引双引

`==` 和 `!=` 自带自适应类型转换，而 `===` 系列没有，一般使用 `===` 和 `!==`

记得语句末尾加分号

使用 `console.log()` 进行控制台输出

## 变量

声明变量：

- `let` 推荐喵
- `var` 不推荐，可以重复声明，会造成变量提升
- `const` 定义常量喵

不加关键字直接赋值会让变量变全局

变量命名规则跟 py 差不多，额外允许`$`在变量名里，且支持 Unicode 也就是说可以中文变量虽然p用没有

js 里推荐用驼峰命名法

声明变量的默认值是 `undefined`，`const` 在声明时必须指定值

## 数组

用一对中括号，内部用逗号分隔，跟 py 的列表一样可以多种类型混在里面，包括数组

索引从`0`开始

用 `.length` 属性获取长度

用 `push()` `pop()` 在尾部添加删除元素

## 对象

~~我草你的我没有对象~~

用大括号，像 py 的字典一样，但是键是变量名

```js
let person = {
    name: ["Linus", "Torvalds"],
    age: 52,
    gender: 'male',
    saying: 'NVIDIA, **** YOU!'
};
```

使用 `.` 访问成员，跟 py 一样

成员也可以是类、函数，跟 py 一样

使用 `delete` 关键字可以删除成员

```js
delete person.saying;
```

直接赋值就可以添加成员

```js
person.wwww = "aminoac";
```

现在变成添加方法

```js
person.say = function () {
    console.log("w, " + this.name + " , desu");
};
```

使用 `this` 指代对象自己

## 分支

使用 `!` 进行逻辑非，`||` 逻辑或，`&&` 逻辑与，和C系列一样

if 的语法跟C系列一样，可以使用 else if

语句块记得用花括号

switch 的语法跟C系列一样

for 的语法跟C系列一样，括号内三个部分用分号隔开

break 和 continue 的语法和C系列和py一样

while 和 do while 的语法和C系列一样

## 函数

```js
function func(x) {
    return x ** 2;
}
```

呃大概就像这样，参数的传递跟py的行为差不多都是引用但是简单对象会复制

箭头函数：

```js
let func = (a, b) => {
    return a * b;
}
```

在其中的 this 会绑定到当前对象

```js
let cat = {
    name: "Ket",
    say() {
        console.log("My name is " + this.name);
    }
}
cat.say();
```

直接在对象中定义方法

## 类

应该尽量只使用 `class` 定义类

```js
class Person {
    constructor(name) {  // 构造函数说是
        this.name = name;
    }
}
let foo = new Person("Nick");
```

然后使用 new 实例化类

嵌套函数和闭包和py差不多，但是小心`this`，尽量不在这种情况下使用

### 继承

使用 `extends` 关键字

```js
// 继承上文的 Person 类
class Professor extends Person {
    teaches;  // 属性，在构造函数中初始化

    constructor(name, teaches) {
        super(name);  // 调用父类的构造函数，应该是第一步
        this.teaches = teaches;
    }

    introduceSelf() {
        console.log(
          `My name is ${this.name}, and I will be your ${this.teaches} professor.`,
        );
    }

    grade(paper) {
        const grade = Math.floor(Math.random() * (5 - 1) + 1);
        console.log(grade);
    }
}
```

使用 `#` 声明私有成员

```js
class Example {
    somePublicMethod() {
        this.#somePrivateMethod();
        // 调用的时候也要带上大概
    }

    #somePrivateMethod() {
        console.log("You called me?");
    }
}

const myExample = new Example();

myExample.somePublicMethod(); // 'You called me?'

myExample.#somePrivateMethod(); // SyntaxError

```

## JSON

呃接触过了（）

放一个链接在这里 <https://developer.mozilla.org/zh-CN/docs/Learn/JavaScript/Objects/JSON>

## DOM API
