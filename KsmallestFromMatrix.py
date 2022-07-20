import heapq


def KsmallestfromMatrix(input, K):
    heap = []
    for i in len(input):
        for j in input[i]:
            heap.append(j)  # Add all elements of the matrix to heap
    heapq.heapify(heap)
    result = []
    while K:
        heapq.
        ele = heapq.heappop(heap)
        result.append(ele)
        heapq.heapify(heap)
        K -= 1

    return result
