#include <bits/stdc++.h>

/*
    Minimum Queue Implementation
    Queue = add elements at the end and remove them from the front
    On average all operations take O(1) Time, since each element is pushed, popped (or moved) only once.
*/

/*
    This implementation uses a double ended queue, a deque, and does not store all elements.
    The queue only stores elements needed to calculate the minimum.
*/
class MinimumQueue1
{
public:
    MinimumQueue1() = default;
    std::deque<int> dq;

    void push(int x)
    {
        while (!dq.empty() && dq.back() < x)
        {
            dq.pop_back();
        }
        dq.push_back(x);
    }

    void remove(int x)
    {
        if (!dq.empty() && dq.front() == x)
            dq.pop_front();
    }

    int getMin()
    {
        return dq.front();
    }
};


/*
    This implementation uses 2 stacks.
    Each stack element will contain the value at that index, and minimum upto that index when it was pushed.
    When inserting an element, it is pushed into pushStk. Popping of an element is done from popStk.
    When popStk is empty, we remove elements from pushStk and push them into popStk (which reverses the order).
    Similar idea can be used to solve Leetcode 155 (https://leetcode.com/problems/min-stack/)
*/
class MinimumQueue2
{
private:
    void reogranize(std::stack<std::pair<int, int>> &pushStk, std::stack<std::pair<int, int>> &popStk)
    {
        while (!pushStk.empty())
        {
            popStk.push(pushStk.top());
            pushStk.pop();
        }
    }

public:
    MinimumQueue2() = default;
    std::stack<std::pair<int, int>> pushStk, popStk;

    void push(int x)
    {
        if (pushStk.empty())
        {
            pushStk.push(std::make_pair(x, x));
        }
        else
        {
            int minVal = std::min(pushStk.top().second, x);
            pushStk.push(std::make_pair(x, minVal));
        }
    }

    int pop()
    {
        if (popStk.empty())
        {
            reogranize(pushStk, popStk);
        }
        int val = popStk.top().first;
        popStk.pop();
        return val;
    }

    int getMin()
    {
        if (popStk.empty() || pushStk.empty())
        {
            return pushStk.empty() ? popStk.top().second : pushStk.top().second;
        }
        return std::min(pushStk.top().second, popStk.top().second);
    }
};

int main()
{
    return 0;
}