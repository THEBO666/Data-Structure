#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> make_next(const string &s)
{
    int i = 0, j = -1;
    vector<int> next(s.size() + 1, 0); // Initialize the vector with the correct size
    next[0] = -1; // Set the first element to -1
    while (i < s.size())
    {
        if (j == -1 || s[i] == s[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
    return next;
}
int KMP(const string &s, const string &t)
{
    int i = 0, j = 0;
    vector<int> next = make_next(t);
    while (i < s.size() && j <(int)t.size())
    {
        if (j == -1 || s[i] == t[j]) // Fix the logic error here
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j == t.size())
        return i - j;
    return -1;
}

int ViolentMatch(string &s, string &t)
{
    int i = 0, j = 0;
    while (i < s.size() && j < t.size())
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == t.size())
        return i - j;
    else
        return -1;
}
int main()
{
    string s1 = "babcabab", s2 = "abab";
    cout << KMP(s1, s2) << endl;
    // cout<<ViolentMatch(s1,s2)<<endl;
}