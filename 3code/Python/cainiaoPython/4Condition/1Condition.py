#! /usr/bin/python
# -*- coding: UTF-8 -*-

'''
Python程序语言指定任何非0和非空（null）值为true，0 或者 null为false。
Python 编程中 if 语句用于控制程序的执行，基本形式为：
if 判断条件：
    执行语句……
else：
    执行语句……

其中"判断条件"成立时（非零），则执行后面的语句，而执行内容可以多行，以缩进来区分表示同一范围。
'''

flag = False
name = 'laodong'

if name == 'python':          #判断变量是否是‘Python’
    flag = True                #条件成立时 设置标志为真
    print 'Welcome boss'    #并输出欢迎信息
else:
    print name          #条件不成了是输出变量的名称

'''
if 语句的判断条件可以用>（大于）、<(小于)、==（等于）、>=（大于等于）、<=（小于等于）来表示其关系。
当判断条件为多个值时，可以使用以下形式：

if 判断条件1:
    执行语句1……
elif 判断条件2:
    执行语句2……
elif 判断条件3:
    执行语句3……
else:
    执行语句4……
'''

#elif用法

num = 5
if num == 3:            #判断num值
    print 'Boss'
elif num == 2:
    print 'user'
elif num == 1:
    print 'worker'
elif num < 0:
    print 'error'       #值小于0时输出
else:
    print 'roadman'     #条件均不成立是输出

'''
由于 python 并不支持 switch 语句，所以多个条件判断，只能用 elif 来实现，如果判断需要多个条件需同时判断时，可以使用 or （或），
表示两个条件有一个成立时判断条件成功；使用 and （与）时，表示只有两个条件同时成立的情况下，判断条件才成功。
'''
#if语句多条件
num = 9
if num >= 0 and num <= 10:
    print 'hello'

num = 10
if num < 0 or num > 10:
    print 'Hello'
else:
    print 'undefine'


num = 8
#判断值是否在0到5或者10到15之间
if (num >= 0 and num <=5) or (num >=10 and num <=15):
    print 'hello'
else:
    print 'undifine'

#简单的语句组
var = 100

if(var == 100): print '变量var的值为100'

print 'Good bye!'
