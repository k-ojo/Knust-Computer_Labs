class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

def append(head, newnode):
    while head.next != None:
        head = head.next
    head.next = newnode

def insert(head, newnode, index):
    count = 0
    prev = head
    ohead = head
    while head != None:
        if count == index:
            newnode.next = head
            if count != 0:
                prev.next = newnode
                return ohead
            else:
                ohead = newnode
                return ohead
        
        count = count + 1
        prev = head
        head = head.next
    prev.next = newnode

def printls(head):
    while head != None:
        print(f"{head.data}----->", end=" ")
        head = head.next
    print("None")

if __name__ == "__main__":
    n1 = Node(2)
    head = n1
    n2 = Node(1)
    n3 = Node(3)

    append(head, n2)
    head = insert(head, n3, 0) #modifies head

    printls(head)
