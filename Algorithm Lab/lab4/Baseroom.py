#!/usr/bin/python3

class Room:
# attributes common to all instances
    windows = 2
    color = 'white'

# constructor
    def __init__(self, name, size, status):
        self.name = name
        self.size = size
        self.status = status

# method common to all instances
    @classmethod
    def paint(cls,color):
        cls.color = color
        print(cls,color)

# methods called without reference to the class or the instance
    @staticmethod
    def knock():
        print("Anybody here?")

# transforms s method into a read-only attribute (get)
    @property
    def size(self):
        return self.name + 'is' + str(self._size) + ' square meters'

# allows to set the previous read-only attribute
# without it, it would be impossible to set the size attribute
    @size.setter
    def size(self, size):
        self._size = size

# allows to delete the property, which can be set again later
    @size.deleter
    def size(self):
        del self._size

# methods
    def open(self):
        self.status = 'open'

    def lock(self):
        self.status = 'locked'
