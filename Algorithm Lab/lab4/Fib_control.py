from Fibbo import FibHeap
a = FibHeap()
l = a.insert(7)
a.insert(18)
a.insert(38)
a.insert(24)
a.insert(17)
n = a.insert(23)
m = a.insert(21)
g = a.insert(39)
q = a.insert(41)
y = a.insert(26)
a.insert(46)
a.insert(30)
a.insert(52)
a.insert(1)
a.extract_min()
#!a.print_node(y)
#!a.print_all()
a.decrease_key(g,15)
a.decrease_key(y,16)
a.print_all()







