#! /usr/bin/python
# -*- coding:UTF-8 -*-

'''
函数是组织好的，可重复使用的，用来实现单一，或相关联功能的代码段。
函数能提高应用的模块性，和代码的重复利用率。你已经知道Python提供了许多内建函数，比如print()。但你也可以自己创建函数，这被叫做用户自定义函数。
定义一个函数
你可以定义一个由自己想要功能的函数，以下是简单的规则：
函数代码块以 def 关键词开头，后接函数标识符名称和圆括号()。
任何传入参数和自变量必须放在圆括号中间。圆括号之间可以用于定义参数。
函数的第一行语句可以选择性地使用文档字符串—用于存放函数说明。
函数内容以冒号起始，并且缩进。
return [表达式] 结束函数，选择性地返回一个值给调用方。不带表达式的return相当于返回 None。

语法
def functionname( parameters ):
   "函数_文档字符串"
   function_suite
   return [expression]
默认情况下，参数值和参数名称是按函数声明中定义的的顺序匹配起来的。
'''

def printme( str ):
    "打印任何传入的字符串"
    print str
    return

printme("111111111")

'''
按值传递参数和按引用传递参数
所有参数（自变量）在Python里都是按引用传递。如果你在函数里修改了参数，那么在调用这个函数的函数里，原始的参数也被改变了。例如：
'''
#可写函数说明
def changeme( mylist ):
    "修改传入的列表"
    mylist.append([1,2,3,4])
    print "函数内取值：",mylist
    return

#调用changeme函数
mylist = [10,20,30]
changeme(mylist)
print "函数外取值：",mylist

