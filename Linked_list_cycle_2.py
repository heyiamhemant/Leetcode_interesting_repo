from os import *
from sys import *
from collections import *
from math import *

#    List Node Class
class Node:
    def __init__(self, data):

        self.data = data
        self.next = None
        self.pos = []

    def __del__(self):
        if (self.next):
            del self.next


def firstNode(head):
    #    Write your code here
    #    Return the node where the cycle begins
    #check cycle exists or not
    fast = slow = head
    loopFound =0 
    while(slow and fast.next):
        slow = slow.next
        fast = fast.next.next
        if(slow == fast):
            loopFound = 1
            break
            
    if( loopFound ==0):
        return None
    #find loopHead        
    fast = head
    loopHead = None
    while(slow and fast):
        if(slow == fast):
            loopHead = fast
            break
        slow = slow.next
        fast = fast.next 
    return loopHead
    pass