# I implemented part of it, the implementation is a automatic differentator
import numpy as np                 # matrix algebra library
import matplotlib.pyplot as plt    # basic python plotting library

class MyTuple:
    '''
    The basic object manipulated by an AD calculator
    Instances of this class is a tuple containining one 
    function/derivative evaluation.
    '''
    def __init__(self,**kwargs):
        # variables for the value (val) and derivative (der) of our input function 
        self.val = 0
        self.der = 1    
        
        # re-assign these default values 
        if 'val' in kwargs:
            self.val = kwargs['val']
        if 'der' in kwargs:
            self.der = kwargs['der']
            
def sin(a):
    # Create output evaluation and derivative object
    b = MyTuple()
    
    # Produce new function value
    b.val = np.sin(a.val)

    # Produce new derivative value - we need to use the chain rule here!
    b.der = np.cos(a.val)*a.der
    
    # Return updated object
    return b

def cos(a):
    # Create output evaluation and derivative object
    b = MyTuple()
    
    # Produce new function value
    b.val = np.cos(a.val)

    # Produce new derivative value - we need to use the chain rule here!
    b.der = -np.sin(a.val)*a.der
    
    # Return updated object
    return b

def tanh(a):
    # Create output evaluation and derivative object
    b = MyTuple()
    
    # Produce new function value
    b.val = np.tanh(a.val) 

    # Produce new derivative value
    b.der = (1 - np.tanh(a.val)**2)*a.der
    
    # Return updated object
    return b

# our implementation of the addition rules from Table 2
def add(a,b):
    # Create output evaluation and derivative object
    c = MyTuple()
    
    # switch to determine if a or b is a constant
    if type(a) != MyTuple:
        c.val = a + b.val
        c.der = b.der
    elif type(b) != MyTuple:
        c.val = a.val + b
        c.der = a.der
    else: # both inputs are MyTuple objects, i.e., functions
        c.val = a.val + b.val
        c.der = a.der + b.der
    
    # Return updated object
    return c

# our implementation of the addition rules from Table 2
def multiply(a,b):
    # Create output evaluation and derivative object
    c = MyTuple()

    # switch to determine if a or b is a constant
    if type(a) != MyTuple:
        c.val = a*b.val
        c.der = a*b.der
    elif type(b) != MyTuple:
        c.val = a.val*b
        c.der = a.der*b

    else: # both inputs are MyTuple objects i.e., functions
        c.val = a.val*b.val
        c.der = a.der*b.val + a.val*b.der     # product rule
    
    # Return updated object
    return c

# our implementation of the power rule from Table 1 
def power(a,n):
    # Create output evaluation and derivative object
    b = MyTuple()
    
    # Produce new function value
    b.val = a.val**n

    # Produce new derivative value - we need to use the chain rule here!
    b.der = n*(a.val**(n-1))*a.der
    
    # Return updated object
    return b

# our implementation of the power rule from Table 1 
def max(a,b):
    # Create output evaluation and derivative object
    c = MyTuple()
    #print('hello')
    # switch to determine if a or b is a constant
    if type(a) != MyTuple:
        if a > b.val:
            c.val = a 
            c.der = 0
        else:
            c.val = b.val
            c.der = b.der
    elif type(b) != MyTuple:
        if a.val > b:
            c.val = a.val 
            c.der = a.der
        else:
            c.val = b
            c.der = 0
    else:
        if a.val > b.val:
            c.val = a.val 
            c.der = a.der
        else:
            c.val = b.val
            c.der = b.der    
    return c


# this next line overloads the addition operator for our MyTuple objects, or in other words adds the 'add' function to our MyTuple class definition on the fly
MyTuple.__add__ = add
MyTuple.__radd__ = add
MyTuple.__mul__ = multiply
MyTuple.__rmul__ = multiply
MyTuple.__pow__ = power

# a simple plotting mechanism for visualizing your function / derivative
def plot_it(g):
    # setup plot
    f, (ax1, ax2) = plt.subplots(1, 2,figsize = (13,3))

    # compute function / derivative values
    s = np.linspace(-10,10,1000)
    g_vals = []      # container for storing function evaluations over the range of s
    dgdw_vals = []   # container for storing derivative evaluations over the range of s
    
    # loop over s and collect function / derivative values, storing them in their appropriate containers
    tuples = []
    for i in s:
        tuples.append(g(MyTuple(val = i)))

    # now collect the function evaluations
    g_vals = [tuples[i].val for i in range(len(tuples))]
    dgdw_vals = [tuples[i].der for i in range(len(tuples))]

    # plot everything
    ax1.plot(s,g_vals,c = 'k')
    ax1.set_title('function')       # include title
    ax2.plot(s,dgdw_vals,c = 'r')
    ax2.set_title('derivative')     # include title
    plt.show()          # this shows figure inline

# define new function
g = lambda w: sin(w)*w + tanh(w)
                      
# plot over a range of values
plot_it(g)

# define new function
g = lambda w: max(w,tanh(cos(w)))

# plot over a range of values
plot_it(g)

# define new function
g = lambda w: max(0,sin(w))

# plot over a range of values
plot_it(g)

# define new function
N = 20
a = 5*np.random.randn(N,3)
a_0 = 5*np.random.randn(1,1)[0][0]
def g(w):
    c = a_0
    for i in range(N):
        c += a[i][0]*tanh(a[i][1] + a[i][2]*w)
    return c
        
# plot over a range of values
plot_it(g)
