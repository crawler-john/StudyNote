#! /usr/bin/python
# -*- coding: UTF-8 -*-
'''
Python有五种标准的数据类型
1、Number（数字）
2、String（字符串）
3、List（列表）
4、Tuple（元组）
5、Dictionary（字典）
'''

#1、python数字
print "\n\n1、python数字"
var1 = 1
var2 = 10

print var1
print var2

del var1 #删除一些对象的引用
# print var1

'''
python 支持四种不同的数字类型
1、int（有符号整形）
2、long（长整型也可以代表八进制和十六进制）
3、float（浮点数）
4、complex（复数）
'''

var1 = 10
var2 = 51924361L
var3 = 0.0
var4 = 4.53e+26j

print var1
print var2
print var3
print var4

#2、Python字符串
'''
python的字串列表有2种取值顺序:
从左到右索引默认0开始的，最大范围是字符串长度少1
从右到左索引默认-1开始的，最大范围是字符串开头
如果你的实要取得一段子串的话，可以用到变量[头下标:尾下标]，就可以截取相应的字符串，其中下标是从0开始算起，可以是正数或负数，下标可以为空表示取到头或尾。
'''
print "\n\n2、Python字符串"
s = 'I love zhouyuexia'
print s     #输出完整字符串
print s[0]  #输出第一个字符
print s[2:5]#输出第二到五个字符串
print s[2:] #输出第二到最后一个字符串
print s * 2 #输出字符串两次
print s + "TEST"#输出连接的字符串

#3、Python列表
'''
List（列表） 是 Python 中使用最频繁的数据类型。
列表可以完成大多数集合类的数据结构实现。它支持字符，数字，字符串甚至可以包含列表（所谓嵌套）。
列表用[ ]标识。是python最通用的复合数据类型。看这段代码就明白。
列表中的值得分割也可以用到变量[头下标:尾下标]，就可以截取相应的列表，从左到右索引默认0开始的，从右到左索引默认-1开始，下标可以为空表示取到头或尾。
加号（+）是列表连接运算符，星号（*）是重复操作。
'''
print "\n\n3、Python列表"

list = ['abcd',786,2.23,'john',70.2]
tinylist = [123,'john']

print list      #输出完整列表
print list[0]   #输出列表的第一元素
print list[1:3] #输出从第二个至第三个的元素      在Python中[:] 表示的是左边是闭区间，右边是开区间
print list[2]   #输出从第三个开始至列表末尾的所有元素
print tinylist * 2 #输出列表两遍
print list + tinylist #打印组合的列表

#4、 python元组
'''
元组是另一个数据类型，类似于List（列表）。
元组用"()"标识。内部元素用逗号隔开。但是元组不能二次赋值，相当于只读列表。
'''

print "\n\n4、 python元组"

tuple = ('abcd',786,2.23,'john',70.2)
tinytuple = (123,'john')

print tuple     #输出完整元组
print tuple[0]  #输出元组的第一个元素
print tuple[1:3]#输出第二个至第三个的元素
print tuple[2:] #输出从第三个开始至元组末尾的所有元素
print tinytuple * 2 #输出元组两次
print tuple + tinytuple #打印组合的元组

# tuple[2] = 1000 #元组中是非法应用
list[2] = 1000  #列表中是合法应用

# 5、 python元字典
'''
字典(dictionary)是除列表以外python之中最灵活的内置数据结构类型。列表是有序的对象结合，字典是无序的对象集合。
两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
字典用"{ }"标识。字典由索引(key)和它对应的值value组成。
'''
print "\n\n5、 python元字典"

dict = {}
dict['one'] = "This is one"
dict[2] = "This is two"

tinydict = {'name':'John','Code':6734,'dept':'sales'}

print dict['one']       #输出键为'one'的值
print dict[2]            #输出键为2的值
print tinydict          #输出完整的字典
print tinydict.keys()   #输出所有的键
print tinydict.values() #输出所有值


#Python数据类型装换
z = '909'


print int(z,16)
print long('22222222222222',8)
print float('90.8')
print  complex('5+6j')
print str(999)
print repr(5)
print eval("8+8")
s = "XXXXX"
print tuple(s)
print list(s)
