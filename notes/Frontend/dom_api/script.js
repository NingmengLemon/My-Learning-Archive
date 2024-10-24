let link = document.querySelector("a")
link.textContent = "超绝四结局 有胆你就来";
link.href = "https://t.bilibili.com/990689311306285057";

let sect = document.querySelector("section")
let para = document.createElement("p")
para.textContent = "aminoac"
sect.appendChild(para)

para.setAttribute("class", "highlight")

// 用来存放自己的全局变量
let myAPP = {
   cnt: 0,
   ul: document.querySelector('.place'),
   button: document.querySelector('.addnum')
};
// 这里的 () => 是箭头函数，和 function () 的匿名函数类似，更短一点
myAPP.button.addEventListener('click', () => {
   let li = document.createElement('li');
   myAPP.cnt += 1;
   li.textContent = "点击了 " + myAPP.cnt + " 次";
   myAPP.ul.appendChild(li);
}); // 注意这里几个嵌套的括号