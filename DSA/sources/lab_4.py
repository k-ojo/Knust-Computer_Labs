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
            print(f"\tData at node: {node.data}")
            self.inorder_builtin(node.right)
        return

    def inorder(self):
        self.inorder_builtin(self.root)
    
    def preorder_builtin(self, node):
        if node:
            print(f"\tData at node: {node.data}")
            self.preorder_builtin(node.left)
            self.preorder_builtin(node.right)
        return

    def preorder(self):
        self.preorder_builtin(self.root)

    def postorder_builtin(self, node):
        if node:
            self.postorder_builtin(node.left)
            self.postorder_builtin(node.right)
            print(f"\tData at node: {node.data}")
        return

    def postorder(self):
        self.postorder_builtin(self.root)


if __name__ == "__main__":
    t1 = Tree()
    t1.insert(70)
    t1.insert(89)
    t1.insert(5)
    t1.insert(80)
    t1.insert(51)
    t1.insert(21)

    t1.inorder()
    t1.postorder()
    t1.preorder()
    print(t1.root.data)