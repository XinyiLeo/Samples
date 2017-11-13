from Baseroom import Room
b = Room('bedroom',10,'open')
b.size; b.size=200; b.size
b.status; b.lock(); b.status
b.knock()
l = Room('living room',20,'open ')
# color is a class attribute
b.color; l.color; Room.color = 'red'; b.color; l.color
# color can be adjusted for each instance
b.color = 'green'; b.color; l.color
