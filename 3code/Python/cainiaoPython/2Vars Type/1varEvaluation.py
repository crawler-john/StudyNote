#! /usr/bin/python
# -*- coding: UTF-8 -*-

counter = 100 #复制整数变量
miles = 1000.0 #浮点型
name = 'John' #字符型

print counter
print miles
print name

#多变量复制
a = b = c = 1 # 该实例创建一个整型对象，值为1，三个变量北分配到相同的内存空间上
print("{0},{1},{2}".format(a,b,c))
a=22
print("{0},{1},{2}".format(a,b,c))

#多个对象创建多个变量
a,b,c = 1,2,'John'
print("{0},{1},{2}".format(a,b,c))