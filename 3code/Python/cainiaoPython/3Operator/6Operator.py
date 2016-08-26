#! /usr/bin/python
# -*- coding:UTF-8 -*-

#成员运算符     in     not in

a = 10
b = 20
list = [1,2,3,4,5]

if (a in list):
    print "1 - 变量a在给定的列表list中"
else:
    print "1 - 变量a不在给定的列表list中"

if (b not in list):
    print "2 - 变量b不在给定的列表list中"
else:
    print "2 - 变量b在给定的列表list中"


#身份运算符  is    is not

a = 20
b = 20

if (a is b):
    print "1 - a 和 b有相同的标识"
else:
    print "1 - a 和 b没有相同的标识"

if (id(a) == id(b)):
    print "2 - a 和 b有相同的标识"
else:
    print "2 - a 和 b没有相同的标识"

#修改变量b的值
b = 30
if (a is b):
    print "3 - a 和 b有相同的标识"
else:
    print "3 - a 和 b没有相同的标识"


if (a is not b):
    print "4 - a 和 b没有相同的标识"
else:
    print "4 - a 和 b有相同的标识"