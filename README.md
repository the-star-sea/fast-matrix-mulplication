# CS205 C/ C++ Programming – Matrix
Name：张通

SID: 11911611
## Part 1 - Analysis
这次作业是在上次作业下的改进，主要是增加了内存管理，运算符的重载，利用cmake,并且在开发板上运行，后两项是我在课下经常做的事情，而内存管理，实在是一门有趣的学问，我想老师布置作业的初心，正是让我们熟练地运用指针，详见part3
## Part 2 - Code
https://github.com/the-star-sea/homework2
请使用提供的所有文件
## Part 3 - Result & Verification
1.计算

矩阵乘矩阵
![image.png](https://i.loli.net/2020/12/06/TFWiP89pCrENuys.png)
标量乘矩阵
![image.png](https://i.loli.net/2020/12/06/SaDOEetQrU4VMqT.png)

2.运算符重载

![image.png](https://i.loli.net/2020/12/06/kvwp3mzTIuMZnay.png)

3.cmake

![image.png](https://i.loli.net/2020/12/06/9gLu3ErOQMtFKo5.png)

4.arm下的使用

 编译
 ![image.png](https://i.loli.net/2020/12/06/LdTaK2Y64DSH3f1.png)
 运行
 [![DjEEN9.jpg](https://s3.ax1x.com/2020/12/06/DjEEN9.jpg)](https://imgchr.com/i/DjEEN9)
 [![DjEm1x.jpg](https://s3.ax1x.com/2020/12/06/DjEm1x.jpg)](https://imgchr.com/i/DjEm1x)

## Part 4 - Difficulties & Solutions
1. 指针的使用

指针实在是一个大坑，平常做作业感觉能用就行，这次project让我体会到了它变化莫测的bug.

1. 指针使用次数，析构函数中，必须判断指针使用了多少次，次数为1时才能允许释放内存，不然可能出现野指针的尴尬境地，我的方法是在类中私有了指向该内存的指针数量
2. 指针声明的地方，这次作业中，我在一些if语句中声明了float* temp=new float[size]，然后用matrix里的data指向它，导致了野指针，这里与1不同，是float的析构，只能在外部声明，需注意作用域

2. 代码重构

本次作业本质来说是写一个库，于是对变量和函数进行了大量地改进，利用了运算符的重载

3.开发板的配置

由于指令集差异，在不同环境要改enable_avx的宏，arm与avx不兼容,一些编译优化也要相应调整
