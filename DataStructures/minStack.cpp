#include <bits/stdc++.h>

/*
    We modify the generic stack data structure that stores integers to store pairs of integers. 
    The first element of the pair will contain the value at that point.
    The second element will contain the minimum value of all the elements from the bottom of the stack
    until that element.
    So, getMinimum is O(1) since we need only return [stack.top().second]
*/
class MinStack {
public:
    std::stack<std::pair<int,int>> stk;

    MinStack() = default;

    void push(int value) {
        if(stk.size() == 0) stk.push(std::make_pair(value, value));
        else {
            int minval = std::min(value, stk.top().second);
            stk.push(std::make_pair(value, minval));
        }
    }

    void pop() {
        if(stk.size() == 0) return;
        stk.pop();
    }

    int top() {
        if(stk.size() == 0) return INT_MIN;
        return stk.top().first;
    }

    int getMinimum() {
        if(stk.size() == 0) return INT_MIN;
        return stk.top().second;
    }
};


int main() {
    return 0;
}