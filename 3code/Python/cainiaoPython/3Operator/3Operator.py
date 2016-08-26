#! /usr/bin/python
# -*- coding:UTF-8 -*-

#2、赋值运算符        = += -= *= /= %= **= //=
a = 21
b = 10
c = 0

c = a + b
c += a
print "1-c的值为：",c

c *= a
print "2-c的值为：",c

c /= a
print "3-c的值为：",c

c = 2
c %= a
print "4-c的值为：",c

c **= a
print "5-c的值为：",c

c //= a
print "6-c的值为：",c