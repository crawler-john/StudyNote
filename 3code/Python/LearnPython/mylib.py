class hello:

    def __init__(self,name):
        self._name = name
    def sayhello(self):
        print("Hello {0}".format(self._name))