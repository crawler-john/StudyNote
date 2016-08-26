#! /usr/bin/python
# -*- coding: UTF-8 -*-

#2、for循环
'''
for循环的语法格式如下：
for iterating_var in sequence:
   statements(s)
'''

for letter in 'Python':
    print '当前字母：',letter

fruits = ['banana','apple','mango']
for fruit in fruits:
    print '当前水果：',fruit

print 'Good bye!'


for index in range(len(fruits)):
    print '当前水果:',fruits[index]

print 'Good Bye'

'''
循环使用 else 语句
在 python 中，for … else 表示这样的意思，for 中的语句和普通的没有区别，
else 中的语句会在循环正常执行完（即 for 不是通过 break 跳出而中断的）的情况下执行，while … else 也是一样。
'''

for num in range(10,20):
    for i in range(2,num):
        if num%i == 0:
            j=num/i
            print '%d等于%d * %d' % (num,i,j)
            break
    else:
            print num,'是一个质数'