#include <iostream>
using namespace std;

//change bit

class Solution
{
    int getmask(int n)
    {
        int ret = 0;
        long x = 1;
        while (ret < n)
        {
            ret += x;
            x *= 2;
        }
        return ret >> 1;
    }

    int fuck(int n)
    {
        if (n == 0)
            return 1;
        if (n == 1)
            return 2;
        int left = 1;
        int right = 1;
        while (n > 0)
        {
            int x = (n & 1);
            int temp = left + right;
            right = left;
            left = temp;
            n = (n >> 1);
        }
        return left;
    }

public:
    int findIntegers(int n)
    {
        if (n == 0)
            return 1;
        if (n == 1)
            return 2;
        int mask = getmask(n);
        int x = (n & mask);
        int i = 0;
        if ((x & getmask(mask)) != x)
        {
            x = getmask(mask);
        }
        return fuck(mask) + findIntegers(x);
    }
};

int main()
{
    Solution su;
    int a = 1111;
    std::cout << su.findIntegers(1000000000);
}