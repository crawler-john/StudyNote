#! /usr/bin/python
# -*- coding: UTF-8 -*-

'''
Python for 循环嵌套语法：
for iterating_var in sequence:
   for iterating_var in sequence:
      statements(s)
   statements(s)
Python while 循环嵌套语法：
while expression:
   while expression:
      statement(s)
   statement(s)
'''


i = 2
while (i < 100):
    j = 2
    while (j <= (i/j)):
        if not (i%j): break
        j += 1
    if(j > i/j):print i,"是素数"
    i += 1

print "Good Bye!"