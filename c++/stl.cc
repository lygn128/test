#include <iostream>
#include <queue>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;

// int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
// {
//     int use = 0;
//     int index = 0;
//     int ret = w;
//     int size = profits.size();
//     std::priority_queue<int, std::vector<int>, std::less<int>> qu;

//     std::vector<std::pair<int,int>> pi;
//     for(int i = 0; i < capital.size(); i++) {
//         pi.push_back(std::make_pair(capital[i], profits[i]));
//     }
//     sort(pi.begin(), pi.end());

//     while( use < k) {
//         while(index < size && ret >= pi[index]) {
//             qu.push(pi[index].second);
//             index++;
//         }
//         if(!qu.empty()) {
//             ret += qu.top();
//             qu.pop();
//             use++;
//         }else {
//             break;
//         }
//     }
//     return ret;

// }

/*
test vector, vector 做为参数传递过程中会深拷贝；
*/
void change_vector(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = i + 1;
    }
}
void test_vector()
{
    vector<int> input(10, 0);
    change_vector(input);
    for (auto x : input)
    {
        std::cout << x << std::endl;
    }
}

vector<int> smallestK(vector<int> &arr, int k)
{
    vector<int> ret;
    std::priority_queue<int, std::vector<int>, std::less<int>> qu;
    for (int i = 0; i < k && i < arr.size(); i++)
    {
        qu.push(arr[i]);
    }

    for (int i = k; i < arr.size(); i++)
    {
        int val = qu.top();
        if (arr[i] > val)
        {
            continue;
        }
        qu.pop();
        qu.push(arr[i]);
    }
    for (int i = 0; i < k; i++)
    {
        int val = qu.top();
        qu.pop();
        ret.push_back(val);
    }
    return ret;
}

class MagicDictionary
{
public:
    std::unordered_map<char, MagicDictionary *> child;
    void insert(string s)
    {
        MagicDictionary *node = this;
        for (int i = 0; i < s.size(); i++)
        {
            MagicDictionary *temp = node->child[s[i]];
            if (temp == NULL)
            {
                temp = new MagicDictionary();
                std::cout << " temp:" << temp << std::endl;
                node->child[s[i]] = temp;
            }
            node = temp;
        }
        node->child['\0'] = new MagicDictionary();
    }

public:
    void iter()
    {
        MagicDictionary *node = this;
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
        for (auto x : child)
        {
            std::cout << " key is:" << x.first << " " << x.second << std::endl;
            //x.second->iter();
        }
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

        for (auto x : child)
        {
            //std::cout << " key is:" << x.first << " " << x.second<< std::endl;
            x.second->iter();
        }
    }

    bool xsearch(string s)
    {
        MagicDictionary *node = this;
        for (int i = 0; i < s.size(); i++)
        {
            //MagicDictionary *temp = node->child[s[i]];
            std::unordered_map<char, MagicDictionary*>::iterator it = node->child.find(s[i]);
            if (it == node->child.end())
            {
                return false;
            }
            node = it->second;
        }
        return node->child['\0'] != NULL;
    }
    /** Initialize your data structure here. */

    MagicDictionary()
    {
    }

    void buildDict(vector<string> dictionary)
    {
        for (int i = 0; i < dictionary.size(); i++)
        {
            insert(dictionary[i]);
        }
    }

    bool search(string searchWord)
    {
        //this->iter();
        //return false;
        MagicDictionary *nodex = this;
        for (int j = 0; j < searchWord.length(); j++)
        {
            std::unordered_map<char, MagicDictionary*>::iterator it = nodex->child.find(searchWord[j]);
            //MagicDictionary *temp2 = nodex->child[searchWord[j]];
            if (it == nodex->child.end())
            {
                std::cout << "-------------" << std::endl;
                for (auto x : nodex->child)
                {
                    std::cout << " node is:" << nodex << " " << nodex->child.size() << " " << x.first << std::endl;
                    bool xx = x.second->xsearch(searchWord.substr(j + 1, searchWord.size() - j - 1));
                    if (xx)
                    {
                        return true;
                    }
                }
                std::cout << "-------------" << std::endl;
                return false;
            }
            else
            {
                nodex = it->second;
            }
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

int main()
{
    // vector<int> arr{1, 2, 3};
    // smallestK(arr, 0);
    //test_vector();
    MagicDictionary dict;
    dict.buildDict(std::vector<string>{"hello"});
    dict.iter();
    std::cout << std::endl << dict.search("hhllo") << std::endl;
}
