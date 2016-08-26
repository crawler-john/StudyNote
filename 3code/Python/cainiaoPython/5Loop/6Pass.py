#! /usr/bin/python
# -*- coding: UTF-8 -*-

'''
Python pass是空语句，是为了保持程序结构的完整性。
pass 不做任何事情，一般用做占位语句。
Python 语言 pass 语句语法格式如下：
pass
'''

for letter in 'Python':
    if letter =='h':
        pass
        print '这是pass块'
    print '当前字母:',letter

print 'Good Bye'