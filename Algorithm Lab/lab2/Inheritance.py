# python3 
  
class Person:  
    def __init__(self, name, age):  
        self.name = name  
        self.age = age  
        print('(Initialized Person: {0})'.format(self.name))  
          
    def tell(self):  
        print('Name:"{0}" Age:"{1}"'.format(self.name, self.age))  
          
class Man(Person): #Inheritance
    def __init__(self, name, age, salary):  
        Person.__init__(self, name, age)  
        self.salary = salary  
        print('(Initialized Man: {0})'.format(self.name))  
          
    def tell(self): #Overide Basic Class
        Person.tell(self)  
        print('Salary: "{0:d}"'.format(self.salary))  
          
class Woman (Person):  
        def __init__(self, name, age, score):  
            Person.__init__(self, name, age)  
            self.score = score  
            print('(Initialized Woman: {0})'.format(self.name))  
          
        def tell(self): #Overide Basic Class
            Person.tell(self)  
            print('score: "{0:d}"'.format(self.score))  
              
c = Woman('Caroline', 30, 80)  
s = Man('Spike', 25, 15000)  
print('\n')  
members = [c, s]  
for m in members:  
    m.tell()          
