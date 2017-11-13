import copy
class FiboHeap:
    # constructor
    def MakeHeap(self):
        self.root_list, self.min_node = None, None
        self.total_nodes = 0
        self.printQueue = []

    class Node:
        def __init__(self, data):
            self.data = data
            self.parent = self.child = self.left = self.right = None
            self.degree = 0
            self.mark = False

    def Minimum(self):
        return self.min_node

    def insert(self, data):
        n = self.Node(data)
        n.left = n.right = n
        # Merge the root with the list
        if self.root_list is None:
            self.root_list = n
        else:
            n.right = self.root_list.right
            n.left = self.root_list
            self.root_list.right.left = n
            self.root_list.right = n
        # Find the min_node of the heap
        if self.min_node is None or n.data < self.min_node.data:
            self.min_node = n
        self.total_nodes += 1
        return n

    def ExtractMin(self):
        z = self.min_node
        if z is not None:
            if z.child is not None:
                # attach child nodes to root list
                if z == self.root_list:
                    self.root_list = z.right
                else:
                    z.child.left.right = z.right
                    z.right.left = z.child.left.right
                    z.child.left = z.left
                    z.left.right = z.child.left

            # Set a new minimum node
            if z == z.right:
                # Only the last node remain
                self.min_node = self.root_list = None
            else:
                self.min_node = z.right
                self.Become_Tree()
            self.total_nodes -= 1
            return z
        else:
            print('Error: Can not extract minimum number from an empty set')

    def Become_Tree(self):
        # Store the node at rankSet[d] that has a degree of d
        rankSet = [None] * self.total_nodes
        # Basic Step
        rankSet[self.root_list.degree] = self.root_list
        iter = self.root_list.right
        while iter is not self.root_list:
            # make one copy for origin
            iter_copy = copy.deepcopy(iter)

            iter = iter.right


    def Change_Root(self,smaller,bigger):
        # Remove the smaller one from the root
        if bigger == self.root_list:
            self.root_list = bigger.right
        bigger.left.right = bigger.right
        bigger.right.left = bigger.left
        # Merge the node with the parent
        if smaller.child is not None:
            bigger.right = smaller.child.right
            bigger.left = smaller.child
            smaller.child.right.left = bigger
            smaller.child.right = bigger
        else:
            smaller.child = bigger
            bigger.right = bigger.left = bigger
        # Some more operations
        smaller.degree += 1
        bigger.parent = smaller
        return smaller



    def print_all(self):
        self.printQueue.append(self.root_list)
        while self.printQueue:
            tmp = self.printQueue.pop(0)
            if tmp == self.root_list:
                print('The root and its brothers: (' + str(tmp.data) + ')', end='')
            else:
                print('The sons of node (' + str(tmp.parent.data) + '): (' + str(tmp.data) + ')', end='')
            if tmp.child is not None:
                self.printQueue.append(tmp.child)
            iter = tmp.right
            while iter is not tmp:
                print('-(' + str(iter.data) + ')', end='')
                if iter.child is not None:
                    self.printQueue.append(iter.child)
                iter = iter.right
            print('')










