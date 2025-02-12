#!/bin/python3

class bNode:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data

class Tree:
    def __init__(self, root=None):
        self.root = root
    
    def insert(self, data):
        if self.root == None:
            self.root = bNode(data)

        else:
            self.insert_builtin(self.root, data)
        
    def insert_builtin(self, current, data):

        if current.data >= data:
            if current.left is None:
                current.left = bNode(data)
            else:
                self.insert_builtin(current.left, data)
        else:
            if current.right is None:
                current.right = bNode(data)
            else:
                self.insert_builtin(current.right, data)

    def inorder_builtin(self, node):
        if node:
            self.inorder_builtin(node.left)
            print(f"\tData at node: {self.root.data}\n")
            self.inorder_builtin(node.right)
        return

    def inorder(self):
        self.inorder_builtin(self.root)

    
    def preorder(self):
        if self.root == None:
            return
        print(f"\tData at node: {self.root.data}\n")
        if self.root.get_left():
            self.root.left.inorder_builtin()
        if self.root.get_right():
            self.root.right.inorder()

if __name__ == "__main__":
    t1 = Tree()
    t1.insert("This is me")
    t1.insert("This is me")
    t1.insert("This is me")
    t1.inorder()