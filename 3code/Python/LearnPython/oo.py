

class hello:

    def __init__(self,name):
        self._name = name
    def sayhello(self):
        print("Hello {0}".format(self._name))

class Hi(hello):
    def __init__(self,name):
        hello.__init__(self,name)
    def sayHi(self):
        print("Hi {0}".format(self._name))

h = hello("laodong")
h.sayhello()

h1 = Hi("laodong")
h1.sayHi()