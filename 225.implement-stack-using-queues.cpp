/*
 * @lc app=leetcode id=225 lang=cpp
 *
 * [225] Implement Stack using Queues
 *
 * https://leetcode.com/problems/implement-stack-using-queues/description/
 *
 * algorithms
 * Easy (65.60%)
 * Likes:    6827
 * Dislikes: 1278
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
 * Testcase Example:  '["MyStack","push","push","top","pop","empty"]\n[[],[1],[2],[],[],[]]'
 *
 * Implement a last-in-first-out (LIFO) stack using only two queues. The
 * implemented stack should support all the functions of a normal stack (push,
 * top, pop, and empty).
 * 
 * Implement the MyStack class:
 * 
 * 
 * void push(int x) Pushes element x to the top of the stack.
 * int pop() Removes the element on the top of the stack and returns it.
 * int top() Returns the element on the top of the stack.
 * boolean empty() Returns true if the stack is empty, false otherwise.
 * 
 * 
 * Notes:
 * 
 * 
 * You must use only standard operations of a queue, which means that only push
 * to back, peek/pop from front, size and is empty operations are valid.
 * Depending on your language, the queue may not be supported natively. You may
 * simulate a queue using a list or deque (double-ended queue) as long as you
 * use only a queue's standard operations.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["MyStack", "push", "push", "top", "pop", "empty"]
 * [[], [1], [2], [], [], []]
 * Output
 * [null, null, null, 2, 2, false]
 * 
 * Explanation
 * MyStack myStack = new MyStack();
 * myStack.push(1);
 * myStack.push(2);
 * myStack.top(); // return 2
 * myStack.pop(); // return 2
 * myStack.empty(); // return False
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= x <= 9
 * At most 100 calls will be made to push, pop, top, and empty.
 * All the calls to pop and top are valid.
 * 
 * 
 * 
 * Follow-up: Can you implement the stack using only one queue?
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class MyStack {
    queue<int> Q1;
    queue<int> Q2;
public:
    MyStack() {

    }
    //expensive push strategy, there is also expensive pop when you pop eveything except last from Q1 and push to Q2, then pop and rename.
    void expensivepush(int x) {
        // x remains at top
        Q2.push(x);
        while(!Q1.empty()) {
            Q2.push(Q1.front());
            Q1.pop();
        }
        swap(Q1,Q2);
    }

    void expensivepoppush(int x) {
        Q1.push(x);
    }
    
    int expensivepop() {
        // Q1.push() , for push
        // pop everything except the last element
        while(Q1.size() > 1) {
            Q2.push(Q1.front());
            Q1.pop();
        }
        int res = Q1.front();
        Q1.pop();
        // rename Q1 and Q2
        swap(Q1,Q2);
        return res;
    }

    int expensivepoptop() {
        // Q1.push() , for push
        // pop everything except the last element
        while(Q1.size() > 1) {
            Q2.push(Q1.front());
            Q1.pop();
        }
        int res = Q1.front();

        // put last element also into Q2 and rename
        Q2.push(Q1.front());
        Q1.pop();
        swap(Q1,Q2);
        return res;
    }

    int expensivepushpop() {
        int res = Q1.front();
        Q1.pop();
        return res;
    }
    
    int expensivepushtop() {
        return Q1.front();
    }
    
    bool empty() {
        return Q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */


/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

