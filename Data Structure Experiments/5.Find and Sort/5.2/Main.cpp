#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

// 基数排序
#define K 6 // 关键字个数 500150
#define Radix 10

struct Student
{
    int stuid;        // 考生号
    std::string name; // 姓名
    int totalScore;   // 总成绩
    int majorScore;   // 专业课
    int cmpScore;
    Student() {}
    // 比较思路如下：
    // 将总成绩x1000+专业课成绩进行基数排序即可
    Student(int id, const std::string n, int t, int m) : stuid(id), name(n), totalScore(t), majorScore(m)
    {
        cmpScore = totalScore * 1000 + majorScore;
    }
};
std::queue<Student> Q[Radix];
int GetKey(int value, int k)
{
    int key = 0;
    while (k >= 0)
    {
        key = value % 10;
        value /= 10;
        k--;
    }
    return key;
}
void Distribute(std::vector<Student> &a, int left, int right, int k)
{
    for (int i = left; i < right; i++)
    {
        int key = GetKey(a[i].cmpScore, k);
        Q[key].push(a[i]);
    }
}

void Collect(std::vector<Student> &a)
{
    int k = 0;
    for (int i = 0; i < Radix; i++)
    {
        while (!Q[i].empty())
        {
            a[k++] = Q[i].front();
            Q[i].pop();
        }
    }
}

void RadixSort(std::vector<Student> &a, int left, int right)
{
    for (int i = 0; i < K; i++)
    {
        Distribute(a, left, right, i);
        Collect(a);
    }
}

int main()
{
    std::vector<Student> students = {
        {20240001, "Brian", 338, 82},
        {20240002, "Queen", 384, 82},
        {20240003, "Xiomara", 330, 94},
        {20240004, "Gwen", 347, 74},
        {20240005, "Ryan", 347, 75},
        {20240006, "Holly", 325, 92},
        {20240007, "Damon", 399, 88},
        {20240008, "Quinn", 440, 120},
        {20240009, "Yvette", 306, 94},
        {20240010, "Steve", 306, 79},
        {20240011, "Mona", 380, 73},
        {20240012, "Sophia", 402, 145},
        {20240013, "Kurt", 345, 86},
        {20240014, "Ivy", 462, 150},
        {20240015, "Vera", 462, 149},
        {20240016, "Tracy", 421, 130},
        {20240017, "Wendy", 404, 129},
        {20240018, "Olive", 443, 128},
        {20240019, "Tom", 367, 82},
        {20240020, "Vince", 367, 84},
        {20240021, "Hanna", 352, 77},
        {20240022, "Yara", 461, 137},
        {20240023, "Rita", 411, 141},
        {20240024, "Grace", 383, 91},
        {20240025, "Damon", 383, 97},
        {20240026, "Holly", 364, 89},
        {20240027, "Quinn", 456, 146},
        {20240028, "Felix", 420, 137},
        {20240029, "Walt", 445, 125},
        {20240030, "Rose", 445, 138},
        {20240031, "Omar", 445, 137},
        {20240032, "Quincy", 355, 73},
        {20240033, "Xena", 363, 92},
        {20240034, "Omar", 438, 132},
        {20240035, "Bob", 438, 145},
        {20240036, "Wendy", 305, 91},
        {20240037, "Cathy", 307, 97},
        {20240038, "Karl", 321, 79},
        {20240039, "Omar", 420, 132},
        {20240040, "Xena", 420, 137},
        {20240041, "Nathan", 393, 82},
        {20240042, "Blake", 423, 149},
        {20240043, "Gina", 301, 71},
        {20240044, "Rita", 401, 134},
        {20240045, "Uma", 401, 146},
        {20240046, "Jasper", 306, 81},
        {20240047, "Frank", 433, 149},
        {20240048, "Vanessa", 436, 147},
        {20240049, "Shane", 321, 73},
        {20240050, "Damon", 321, 72}};

    RadixSort(students, 0, students.size());

    std::cout
        << "考生号      "
        << "姓名      "
        << "总分   "
        << "专业课分数" << std::endl;

    // 打印学生数据
    for (int i = students.size() - 1; i >= 0; i--)
    {
        std::cout << std::left
                  << std::setw(12) << students[i].stuid
                  << std::setw(10) << students[i].name
                  << std::setw(10) << students[i].totalScore
                  << std::setw(12) << students[i].majorScore << std::endl;
    }

    return 0;
}