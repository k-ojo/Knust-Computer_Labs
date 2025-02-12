"""_summary_

    Returns:
        _type_: _description_
"""
#!/bin/python3


class Node:
    """_summary_
    """
    def __init__(self, data=0, mynext=0):
        self.data = data
        self.next = mynext

    def get_data(self):
        """_summary_

        Returns:
            _type_: _description_
        """
        return self.data

    def get_next(self):
        """_summary_

        Returns:
            _type_: _description_
        """
        return self.next

    def set_data(self, data):
        """_summary_

        Args:
            data (_type_): _description_
        """
        self.data = data

    def set_next(self, mynext):
        """_summary_

        Args:
            next (function): _description_
        """
        self.next = mynext

class DbNode(Node):
    """_summary_

    Args:
        Node (_type_): _description_
    """
    def __init__(self, prev, mynext, data):
        super().__init__(data, mynext)
        self.prev = prev

    def get_prev(self):
        """_summary_

        Returns:
            _type_: _description_
        """
        return self.prev

    def set_prev(self, prev):
        """_summary_

        Returns:
            _type_: _description_
        """
        self.prev = prev

class LinkList:
    """_summary_
    """
    def __init__(self, data):
        head = Node(data, 0)
        self.head = head
        self.size = 1

    def append(self, data):
        """_summary_

        Args:
            data (_type_): _description_
        """
        tmp = self.head
        new = Node(data, 0)

        while tmp:
            if tmp.get_next() == 0:
                tmp.set_next(new)
                self.size = self.size + 1
                return
            tmp = tmp.get_next()

    def print_ls(self):
        """_summary_
        """
        tmp = self.head
        while tmp != 0:
            print(f"|{hex(id(tmp))}|{tmp.data}| ---->", end=" ")
            tmp = tmp.get_next()
        print("NULL")

class DbLinklist:
    """_summary_
    """
    def __init__(self, data=0):
        head = DbNode(0, 0, data)
        self.head = head
        self.size = 1

    def append(self, data):
        nw = DbNode(0, 0, data)
        tmp = self.head
        while tmp.get_next() != 0:
            tmp = tmp.get_next()
            self.size = self.size + 1
        tmp.set_next(nw)
        nw.set_prev(tmp)
    
    def printls(self):
        tmp = self.head
        while tmp:
            print(f"| {tmp.data} | <=====>", end=" ")
            tmp = tmp.get_next()
        print("\n")



if __name__ == "__main__":
    ll = LinkList(56)
    ll.append("hagsj")
    #ll.print_ls()

    dl = DbLinklist(78)
    dl.append("jgjhfy")
    dl.append(67.9)
    dl.printls()
