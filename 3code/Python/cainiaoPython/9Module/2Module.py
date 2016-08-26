#! /usr/bin/python
# -*- coding:UTF-8 -*-


'''
Python中的包
包是一个分层次的文件目录结构，它定义了一个由模块及子包，和子包下的子包等组成的Python的应用环境。
考虑一个在Phone目录下的pots.py文件。这个文件有如下源代码：
#!/usr/bin/python
# -*- coding: UTF-8 -*-

def Pots():
   print "I'm Pots Phone"

同样地，我们有另外两个保存了不同函数的文件：
Phone/Isdn.py 含有函数Isdn()
Phone/G3.py 含有函数G3()
现在，在Phone目录下创建file __init__.py：
Phone/__init__.py
当你导入Phone时，为了能够使用所有函数，你需要在__init__.py里使用显式的导入语句，如下：
'''

'''
同样地，我们有另外两个保存了不同函数的文件：
Phone/Isdn.py 含有函数Isdn()
Phone/G3.py 含有函数G3()
现在，在Phone目录下创建file __init__.py：
Phone/__init__.py
当你导入Phone时，为了能够使用所有函数，你需要在__init__.py里使用显式的导入语句，如下：
'''


#导入Phone包
import Phone

Phone.G3()
Phone.Isdn()
Phone.Pots()
