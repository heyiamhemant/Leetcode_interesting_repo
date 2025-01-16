/*
 * @lc app=leetcode id=155 lang=cpp
 *
 * [155] Min Stack
 *
 * https://leetcode.com/problems/min-stack/description/
 *
 * algorithms
 * Medium (55.23%)
 * Likes:    14655
 * Dislikes: 913
 * Total Accepted:    2M
 * Total Submissions: 3.6M
 * Testcase Example:  '["MinStack","push","push","push","getMin","pop","top","getMin"]\n' +
  '[[],[-2],[0],[-3],[],[],[],[]]'
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum
 * element in constant time.
 * 
 * Implement the MinStack class:
 * 
 * 
 * MinStack() initializes the stack object.
 * void push(int val) pushes the element val onto the stack.
 * void pop() removes the element on the top of the stack.
 * int top() gets the top element of the stack.
 * int getMin() retrieves the minimum element in the stack.
 * 
 * 
 * You must implement a solution with O(1) time complexity for each
 * function.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["MinStack","push","push","push","getMin","pop","top","getMin"]
 * [[],[-2],[0],[-3],[],[],[],[]]
 * 
 * Output
 * [null,null,null,null,-3,null,0,-2]
 * 
 * Explanation
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin(); // return -3
 * minStack.pop();
 * minStack.top();    // return 0
 * minStack.getMin(); // return -2
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * -2^31 <= val <= 2^31 - 1
 * Methods pop, top and getMin operations will always be called on non-empty
 * stacks.
 * At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
 * 
 * 
 */
#include<vector>
#include<stack>
using namespace std;
// @lc code=start
class MinStack {
    stack<int> arr;
    stack<int> minStack;

public:
    MinStack() {

    }
    
    /**
     * Pushes the element val onto the stack.
     * @param val the value to push onto the stack
     */
    void push(int val) {
        arr.push(val);
        if(!minStack.empty()) {
            if( val <= minStack.top())
                minStack.push(val);
        } else 
            minStack.push(val);
    }

    void pop() {
        if(arr.empty())
            return;
        int ele = arr.top();
        arr.pop();
        if(!minStack.empty() && ele == minStack.top())
            minStack.pop();
    }

    int top() {
        if(!arr.empty())
            return arr.top();
       
        return -1;
    }

    int getMin() {
        if(!minStack.empty())
            return minStack.top();
        return -1;
    }
};
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

