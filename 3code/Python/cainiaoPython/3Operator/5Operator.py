#! /usr/bin/python
# -*- coding:UTF-8 -*-

#逻辑运算符      and or not

a = 10
b = 20

if (a and b):
    print "1 - 变量a和b都为true"
else:
    print "1 - 变量a和b至少有一个为false"

if (a or b):
    print "2 - 变量a和b至少有一个为true"
else:
    print "2 - 变量a和b都为false"

if (not a):
    print "3 - 变量a取非为true"
else:
    print "3 - 变量a取非为false"