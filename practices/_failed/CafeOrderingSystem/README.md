# CafeOrderingSystem
**曾经是** HDU大一下C语言程序设计实践期末作业 - 咖啡厅订单管理系统

上传gh是为了方便协作，顺便开源一下（虽然很菜就是了）

**未完工，还在协作阶段，也不会完工了**

写得像史一样被毙掉了（笑）

------

嗯目前的实现思路是这样的：

有两个全局Vector变量分别用来存放商品和订单。统计信息全部在显示时临时生成，不存储到文件。

订单和商品的删除实质上只是标注，被标注的订单和商品在保存到文件时被忽略，此时才是真正的删除。

嗯或许具体实现是有点大病的，喷的时候请下手轻点（

------
作业要求原文如下（有进行格式优化）：
## 咖啡店订单管理系统
任务说明：使用C语言设计开发一个简单的咖啡店订单管理系统，实现商品及订单的添加、删除、修改、查询等功能。
### 数据结构
程序中采用结构体存储商品和订单信息，用链表或数组保存多个商品和订单信息。商品信息结构体成员包括：商品编号、名称、价格、描述（如配料、热量等）、商品分类、商品库存等。订单信息结构体成员包括：订单号、顾客信息、订单时间、订单状态（已完成、未完成等）以及订单中的商品项列表等。
### 功能说明
- 商品信息管理功能
   - 显示所有信息：按照类别显示所有商品的信息。
   - 添加商品信息：从键盘输入商品的基本信息，并将其添加到系统中。
   - 删除商品信息：根据商品编号或其他关键信息删除商品的信息。
   - 修改商品信息：根据商品编号或其他关键信息修改商品的基本信息。
   - 查找商品信息：根据商品编号或其他关键信息查找商品，并显示其详细信息。
- 订单信息管理功能：
   - 创建订单：选择商品并指定数量，生成订单号，将订单添加到系统中。
   - 取消订单：根据订单号取消订单，并将订单状态设置为取消。
   - 完成订单：根据订单号将订单状态设置为已完成。
   - 显示所有订单信息：按照订单时间，逐个显示所有订单的信息。
   - 查找订单信息：根据订单号或其他关键信息查找订单，并显示其详细信息。
- 财务统计功能：
   - 统计某段时间内的总销售额。
   - 统计某段时间内每种商品的销售数量和销售。
   - 保存统计信息到文件等。

### 其他功能
登录、退出系统；顾客星级以及优惠设置等。

> 相关小组开发的系统，可以包含但不限于上述功能，需要自行设计更具有实用性和创新性的系统功能。
