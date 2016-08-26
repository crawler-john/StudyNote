#! /usr/bin/python
# -*- coding: UTF-8 -*-

'''
Python提供了for循环和while循环（在Python中没有do..while循环）:
while 循环	在给定的判断条件为 true 时执行循环体，否则退出循环体。
for 循环	重复执行语句
嵌套循环	你可以在while循环体中嵌套for循环

循环控制语句:
    break 语句	在语句块执行过程中终止循环，并且跳出整个循环
    continue 语句	在语句块执行过程中终止当前循环，跳出该次循环，执行下一次循环。
    pass 语句	pass是空语句，是为了保持程序结构的完整性。
'''
#1、while循环
'''
Python 编程中 while 语句用于循环执行程序，即在某条件下，循环执行某段程序，以处理需要重复处理的相同任务。其基本形式为：
while 判断条件：
    执行语句……
'''

count = 0
while (count < 9):
    print 'The count is:',count
    count += 1

print 'Good bye'

'''
while 语句时还有另外两个重要的命令 continue，break 来跳过循环，continue 用于跳过该次循环，
break 则是用于退出循环，此外"判断条件"还可以是个常值，表示循环必定成立，具体用法如下：
'''
#countine 和 break 用法

i = 1
while i < 10:
    i += 1
    if i%2 >0:      #非双数跳过输出
        continue
    print i        #输出2、4、5、8、10

i = 1
while 1:
    print i     #输出1~10
    i += 1
    if i > 10:  #当i大于10时跳出循环
        break

#无限循环

# var = 1
# while var == 1:     # 该条件永远为true，循环将无限执行下去
#     num = raw_input("Enter a number  :")
#     print "You entered:",num
#
# print 'Good Bye'

'''
循环使用 else 语句
在 python 中，for … else 表示这样的意思，for 中的语句和普通的没有区别，
else 中的语句会在循环正常执行完（即 for 不是通过 break 跳出而中断的）的情况下执行，while … else 也是一样。
'''

count = 0
while count < 5:
    print count,"is less than 5"
    count += 1
else:
    print count,"is not less than 5"

'''
简单语句组
类似if语句的语法，如果你的while循环体中只有一条语句，你可以将该语句与while写在同一行中
'''

flag = 1
while (flag): print 'Given flag is really true!'

print 'Good Bye'



