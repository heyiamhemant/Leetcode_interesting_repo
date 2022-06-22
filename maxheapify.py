class Heap:
    # private data members
    __heap = None
    __n = None
    # constructor
    def __init__(self, n: int):
        self.heap = [0 for i in range(n)]
        self.n = n

    def makeHeap(self):
        i = 0
        while i < self.n:
            self.maxheapify(2 * i)
            self.maxheapify(2 * i + 1)

    def maxheapify(self, pos=0):
        i = pos
        while i < self.n:
            if self.heap[i] <= self.heap[2 * i]:
                self.heap[i], self.heap[2 * i] = self.heap[2 * i], self.heap[i]
                i = 2 * i
            if self.heap[i] < self.heap[2 * i + 1]:
                self.heap[i], self.heap[2 * i + 1] = self.heap[2 * i + 1], self.heap[i]
                i = 2 * i + 1

    def maxheappush(self, ele: int):
        self.heap.push(ele)

    def maxheappop(self, ele: int):
        self.heap.pop(ele)
