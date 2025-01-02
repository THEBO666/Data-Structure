/************************************************
* Author        :Running_Time
* Created Time  :2015/10/29 星期四 16:12:53
* File Name     :BT.cpp
 ************************************************/
 
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
typedef long long ll;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const double EPS = 1e-10;
const double PI = acos (-1.0);
/*
    表达式求值，逆波兰式(后缀表达式)算法
    输入(可以有空格，支持小数，实现'+-/*%')： ((1+2)*5+1)/4=
    注意：取模一定是要整型，实现版本数字全是double，强制类型转换可能倒置错误
    转换为后缀表达式： 得到：1 2 + 5 * 1 + 4 / =
    计算后缀表达式：得到：4.00
*/

bool is_digit(char ch)  {
	return '0' <= ch && ch <= '9';
}
struct Exp  {
    stack<char> op;
    stack<double> num;
    bool error;
 
    int prior(char ch)  {                           //运算符的优先级
        switch (ch) {
            case '+':
            case '-': return 1;
            case '*':
            case '%':
            case '/': return 2;
            default:  return 0;
        }
    }
    string get_prefix(string s)	{					//中缀表达式转变前缀表达式
        while (!op.empty ())	op.pop ();
        op.push ('#');
        string ret = "";
        int len = s.length (), i = len - 1;
        while (i >= 0)	{
			if (s[i] == ' ' || s[i] == '=')	{
				i--;	continue;
			}
			else if (s[i] == ')')	{
				op.push (s[i--]);
			}
			else if (s[i] == '(')	{
				while (op.top () != '#' && op.top () != ')')	{
					ret += op.top ();	ret += ' ';
					op.pop ();
				}
				op.pop ();	i--;
			}
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')  {
                while (prior (op.top ()) > prior (s[i]))    {
                    ret += op.top ();	ret += ' ';
                    op.pop ();
                }
                op.push (s[i--]);
            }
            else    {
                while (is_digit (s[i]) || s[i] == '.')  {
                    ret += s[i--];
                }
                ret += ' ';
            }
        }
        while (op.top () != '#') {
            ret += op.top ();	ret += ' ';
            op.pop ();
        }
        reverse (ret.begin (), ret.end ());
        return ret;
    }
    double cal(double a, double b, char ch) {
        if (ch == '+')  return a + b;
        if (ch == '-')  return a - b;
        if (ch == '*')  return a * b;
        if (ch == '%')  return (int)((int)a % (int)b);
        if (ch == '/')  {
            if (b != 0) return a / b;
            error = true;   return 0;
        }
        return 0;
    }
    string get_postfix(string s)    {               //中缀表达式转变后缀表达式
        while (!op.empty ())    op.pop ();
        op.push ('#');
        string ret = "";
        int len = s.length (), i = 0;
        while (i < len)    {
            if (s[i] == ' ' || s[i] == '=')    {
                i++;    continue;
            }
            else if (s[i] == '(')    {
                op.push (s[i++]);
            }
            else if (s[i] == ')')   {
                while (op.top () != '(')    {
                    ret += op.top ();   ret += ' ';
                    op.pop ();
                }
                op.pop ();  i++;
            }
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')  {
                while (prior (op.top ()) >= prior (s[i]))    {
                    ret += op.top ();   ret += ' ';
                    op.pop ();
                }
                op.push (s[i++]);
            }
            else    {
                while (is_digit (s[i]) || s[i] == '.')  {
                    ret += s[i++];
                }
                ret += ' ';
            }
        }
        while (op.top () != '#') {
            ret += op.top ();   ret += ' ';
            op.pop ();
        }
        ret += '=';
        return ret;
    }
    double solve(string str)    {                   //计算后缀表达式
        string s = get_postfix (str);
        while (!num.empty ())   num.pop ();
        error = false;
        int len = s.length (), i = 0;
        while (i < len)  {
            if (s[i] == ' ' || s[i] == '=') {i++;   continue;}
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%')  {
                double a = num.top ();  num.pop ();
                double b = num.top ();  num.pop ();
                num.push (cal (b, a, s[i]));    i++;
            }
            else  {
                double x = 0;
                while (is_digit (s[i])) {
                    x = x * 10 + s[i] - '0';    i++;
                }
                if (s[i] == '.')    {
                    double k = 10.0, y = 0;
                    i++;
                    while (is_digit (s[i])) {
                        y += ((s[i] - '0') / k);
                        i++;    k *= 10;
                    }
                    x += y;
                }
                num.push (x);
            }
        }
        return num.top ();
    }
}E;
typedef struct BT	{
    char op;
    double data;
    BT *lch, *rch;
}node, *btree;
 
void print(btree p)	{
	if (! (p -> lch) && ! (p -> rch))	{
		cout << fixed << setprecision (1) << p -> data << " ";
//		cout << p -> data << " ";
	}
	else	cout << p -> op << " ";
}
 
int i;
 
double get_num(string s)	{
	double x = 0;
	while (is_digit (s[i])) {
		x = x * 10 + s[i] - '0';    i++;
	}
	if (s[i] == '.')    {
		double k = 10.0, y = 0;
		i++;
		while (is_digit (s[i])) {
			y += ((s[i] - '0') / k);
			i++;    k *= 10;
		}
		x += y;
	}
	return x;
}
 
void creat(btree &T, string s)	{
	T = new node;
	while (i < s.length () && (s[i] == ' ' || s[i] == '.'))	i++;
	if (i >= s.length ())	{
		T -> lch = T -> rch = NULL;	return ;
	}
	if (is_digit (s[i]))	{
        T -> data = get_num (s);
		T -> lch = T -> rch = NULL;
		i++;	return ;
	}
	else	{
		T -> op = s[i];
		i += 2;
		creat (T -> lch, s);
		creat (T -> rch, s);
	}
}
 
void pre_order(btree T)	{		//前序遍历
    if (T != NULL)	{
		print (T);
		pre_order (T -> lch);
		pre_order (T -> rch);
    }
}
 
void in_order(btree T)	{		//中序遍历
	if (T != NULL)	{
		in_order (T -> lch);
		print (T);
		in_order (T -> rch);
	}
}
 
void post_order(btree T)	{	//后序遍历
	if (T != NULL)	{
		post_order (T -> lch);
		post_order (T -> rch);
		print (T);
	}
}
 
double cal_tree(btree &T)	{
    if (T != NULL)	{
		if (! (T -> lch) && ! (T -> rch))	{
			return T -> data;
		}
		else	return E.cal (cal_tree (T -> lch), cal_tree (T -> rch), T -> op);
    }
}
 
int main(void)    {
    ios::sync_with_stdio (false);
    int T;  cin >> T;
    string str; getline (cin, str);
    while (T--) {
        getline (cin, str);
        string pre = E.get_prefix (str), post = E.get_postfix (str);
        cout << "前缀表达式：" << pre << endl;
        cout << "后缀表达式：" << post << endl;
 
		btree tree;
		i = 0;		//全局变量记录string下标，递归建立表达式树
		creat (tree, pre);
		cout << "前序遍历：";	pre_order (tree);	cout << endl;
		cout << "中序遍历：";	in_order (tree);	cout << endl;
		cout << "后序遍历：";	post_order (tree);	cout << endl;
		cout << "后缀表达式计算结果：" << fixed << setprecision (6) << E.solve (str) << endl;
		cout << "表达式树结果：" << fixed << setprecision (6) << cal_tree (tree) << endl << endl;
    }
 
    return 0;
}
/*
测试样例：
1000
1 + 2
1 + 2 - 3 / 4 * 5
1 + 2 * (3 - 4) - 5 / 6
1+2*3-4/(5-6*7+8)/9
1-2+3*4%(5+6-7/8)+9
1+(2-3)*4*(5-6+7/8)/9
11+(22-33)*44*(55-6+7/8)/9
19+(28-37)*46*(55-64+73/82)/91
1.2+(2.421-3.3123)*4.0*(5.42342-6+7.2*8.13)/9.1321
*/