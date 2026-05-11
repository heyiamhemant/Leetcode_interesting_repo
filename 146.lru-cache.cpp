/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 *
 * https://leetcode.com/problems/lru-cache/description/
 *
 * algorithms
 * Medium (46.91%)
 * Likes:    23170
 * Dislikes: 1238
 * Total Accepted:    2.6M
 * Total Submissions: 5.5M
 * Testcase Example:  '["LRUCache","put","put","get","put","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * Design a data structure that follows the constraints of a Least Recently
 * Used (LRU) cache.
 * 
 * Implement the LRUCache class:
 * 
 * 
 * LRUCache(int capacity) Initialize the LRU cache with positive size
 * capacity.
 * int get(int key) Return the value of the key if the key exists, otherwise
 * return -1.
 * void put(int key, int value) Update the value of the key if the key exists.
 * Otherwise, add the key-value pair to the cache. If the number of keys
 * exceeds the capacity from this operation, evict the least recently used
 * key.
 * 
 * 
 * The functions get and put must each run in O(1) average time complexity.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 * Output
 * [null, null, null, 1, null, -1, null, -1, 3, 4]
 * 
 * Explanation
 * LRUCache lRUCache = new LRUCache(2);
 * lRUCache.put(1, 1); // cache is {1=1}
 * lRUCache.put(2, 2); // cache is {1=1, 2=2}
 * lRUCache.get(1);    // return 1
 * lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
 * lRUCache.get(2);    // returns -1 (not found)
 * lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
 * lRUCache.get(1);    // return -1 (not found)
 * lRUCache.get(3);    // return 3
 * lRUCache.get(4);    // return 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= capacity <= 3000
 * 0 <= key <= 10^4
 * 0 <= value <= 10^5
 * At most 2 * 10^5 calls will be made to get and put.
 * 
 * 
 */
#include<iostream>
#include<unordered_map>
using namespace std;
// @lc code=start
// Map to get elements in O(1)
// double linked list to know who to kill
class Node {
public:
    int key;
    int data;
    Node* next;
    Node* prev;

    Node(int k, int v) {
        key = k;
        data = v;
        next = NULL;
        prev = NULL;
    }
};
class LRUCache {
    std::unordered_map<int, Node*> Map;
    Node* start;
    Node* end;
    int Capacity;
public:
    LRUCache(int capacity) : Capacity(capacity), 
    start(new Node(0,0)), // sentinels
    end(new Node(0,0)) {
        start->next = end;
        end->prev = start;
    }
    
    int get(int key) {
        if(Map.contains(key)){
            Node* node = Map[key];
            moveToFront(node);
            return node->data;
        }
        else return -1;
    }
    void addToFront(Node* node) {
        node->next = start->next;
        start->next->prev = node;
        start->next = node;
        node->prev = start;
    }
    void detach(Node* node) {
        // possible with sentinels
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void moveToFront(Node* node) {
        detach(node);
        addToFront(node);
    }
    void evictLRU() {
        Node* temp = end->prev;
        if(temp == start) return;
        detach(temp);
        Map.erase(Map.find(temp->key));
        delete temp;
    }
    void put(int key, int value) {
        if(Map.contains(key)) {
            Node * node = Map[key];
            node->data = value; // update the data
            // if node was at back, it needs updation
            moveToFront(node);
        } else {
            Node* New = new Node(key, value);
            if(Map.size() == Capacity) {
                evictLRU();
            }
            addToFront(New);
            Map[key] = New;
        }
    }
    ~LRUCache() {
        Node* cur = start;
        while(cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */