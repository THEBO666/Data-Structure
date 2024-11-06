#include <windows.h>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <iostream>

// 表达式树的节点结构体
struct TreeNode {
    std::string value;   // 节点的值（操作符或操作数）
    TreeNode* left;      // 左子节点
    TreeNode* right;     // 右子节点
    TreeNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

// 函数声明：解析和求值
std::vector<std::string> tokenize(const std::string& expression);

class Parser {
public:
    std::vector<std::string> tokens; // 表达式的标记列表
    size_t pos;                      // 当前标记位置
    Parser(const std::vector<std::string>& tokens) : tokens(tokens), pos(0) {}
    TreeNode* parseExpression();     // 解析表达式
private:
    TreeNode* parseTerm();           // 解析项
    TreeNode* parseFactor();         // 解析因子
};

double evaluate(TreeNode* node);     // 递归求值表达式树
void deleteTree(TreeNode* node);     // 删除表达式树，释放内存

// Windows应用程序函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 控件的全局句柄
HWND hStaticExpression, hStaticOutput;
std::string currentExpression; // 由按钮点击构建的当前表达式

// 按钮的ID
enum ButtonID {
    BTN_0 = 1000,
    BTN_1,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_6,
    BTN_7,
    BTN_8,
    BTN_9,
    BTN_ADD,
    BTN_SUB,
    BTN_MUL,
    BTN_DIV,
    BTN_LPAREN,
    BTN_RPAREN,
    BTN_CLEAR,
    BTN_CALC,
    BTN_DOT   // 小数点按钮
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc = { 0 };
    HWND hwnd;
    MSG Msg;

    // 定义窗口类的属性
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = "CalculatorWindowClass";
    wc.lpfnWndProc = WndProc;                // 窗口过程回调
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // 注册窗口类
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "窗口注册失败！", "错误",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 创建主窗口
    hwnd = CreateWindowEx(0, "CalculatorWindowClass", "计算器",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 260, 420,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "窗口创建失败！", "错误",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // 显示并更新窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// 窗口过程处理消息
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // 创建用于显示表达式的控件
        hStaticExpression = CreateWindow("STATIC", "",
            WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_BORDER,
            10, 10, 220, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);

        // 创建数字和操作符按钮
        int buttonWidth = 50;
        int buttonHeight = 50;
        int startX = 10;
        int startY = 50;
        int margin = 5;

        // 按钮标签和ID
        struct ButtonInfo {
            const char* label;
            int id;
        };

        ButtonInfo buttons[5][4] = {
            { {"7", BTN_7}, {"8", BTN_8}, {"9", BTN_9}, {"/", BTN_DIV} },
            { {"4", BTN_4}, {"5", BTN_5}, {"6", BTN_6}, {"*", BTN_MUL} },
            { {"1", BTN_1}, {"2", BTN_2}, {"3", BTN_3}, {"-", BTN_SUB} },
            { {"0", BTN_0}, {".", BTN_DOT}, {"(", BTN_LPAREN}, {"+", BTN_ADD} },
            { {"C", BTN_CLEAR}, {"=", BTN_CALC}, {")", BTN_RPAREN}, {"", 0} }
        };

        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 4; ++col) {
                if (buttons[row][col].label[0] != '\0') {
                    CreateWindow("BUTTON", buttons[row][col].label,
                        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                        startX + col * (buttonWidth + margin),
                        startY + row * (buttonHeight + margin),
                        buttonWidth, buttonHeight, hwnd,
                        (HMENU)(buttons[row][col].id), GetModuleHandle(NULL), NULL);
                }
            }
        }

        // 创建用于显示结果的控件
        hStaticOutput = CreateWindow("STATIC", "",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10, startY + 5 * (buttonHeight + margin), 220, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (wmId >= BTN_0 && wmId <= BTN_9) {
            // 数字按钮
            currentExpression += std::to_string(wmId - BTN_0);
        } else if (wmId == BTN_ADD) {
            currentExpression += "+";
        } else if (wmId == BTN_SUB) {
            currentExpression += "-";
        } else if (wmId == BTN_MUL) {
            currentExpression += "*";
        } else if (wmId == BTN_DIV) {
            currentExpression += "/";
        } else if (wmId == BTN_LPAREN) {
            currentExpression += "(";
        } else if (wmId == BTN_RPAREN) {
            currentExpression += ")";
        } else if (wmId == BTN_DOT) {
            currentExpression += ".";
        } else if (wmId == BTN_CLEAR) {
            // 清除表达式
            currentExpression.clear();
            SetWindowText(hStaticOutput, "");
        } else if (wmId == BTN_CALC) {
            // 计算表达式
            std::vector<std::string> tokens = tokenize(currentExpression);
            Parser parser(tokens);
            TreeNode* root = parser.parseExpression();
            if (root != nullptr && parser.pos == tokens.size()) {
                // 求值表达式
                double result = evaluate(root);
                std::string output = "结果: " + std::to_string(result);
                SetWindowText(hStaticOutput, output.c_str());
                // 清理：删除表达式树
                deleteTree(root);
            } else {
                SetWindowText(hStaticOutput, "表达式错误。");
            }
        }
        // 更新表达式显示
        SetWindowText(hStaticExpression, currentExpression.c_str());
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// 将输入表达式字符串标记化的函数
std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    size_t i = 0;
    while (i < expression.length()) {
        if (isspace(expression[i])) {
            ++i; // 跳过空白字符
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            // 读取数字，包括小数点
            std::string num;
            int dotCount = 0;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        // 小数点超过一个，非法数字
                        tokens.clear();
                        return tokens;
                    }
                }
                num += expression[i++];
            }
            tokens.push_back(num);
        } else if (expression[i] == '+' || expression[i] == '-' ||
            expression[i] == '*' || expression[i] == '/' ||
            expression[i] == '(' || expression[i] == ')') {
            tokens.push_back(std::string(1, expression[i++]));
        } else {
            // 遇到非法字符
            tokens.clear();
            break;
        }
    }
    return tokens;
}

// Parser类的方法实现

// 解析表达式（处理加法和减法）
TreeNode* Parser::parseExpression() {
    TreeNode* node = parseTerm();
    if (!node) return nullptr;
    while (pos < tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-")) {
        std::string op = tokens[pos++];
        TreeNode* rightNode = parseTerm();
        if (!rightNode) {
            deleteTree(node);
            return nullptr;
        }
        TreeNode* newNode = new TreeNode(op);
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }
    return node;
}

// 解析项（处理乘法和除法）
TreeNode* Parser::parseTerm() {
    TreeNode* node = parseFactor();
    if (!node) return nullptr;
    while (pos < tokens.size() && (tokens[pos] == "*" || tokens[pos] == "/")) {
        std::string op = tokens[pos++];
        TreeNode* rightNode = parseFactor();
        if (!rightNode) {
            deleteTree(node);
            return nullptr;
        }
        TreeNode* newNode = new TreeNode(op);
        newNode->left = node;
        newNode->right = rightNode;
        node = newNode;
    }
    return node;
}

// 解析因子（处理数字和括号内的表达式）
TreeNode* Parser::parseFactor() {
    if (pos >= tokens.size()) return nullptr;
    if (tokens[pos] == "(") {
        ++pos; // 消耗'('
        TreeNode* node = parseExpression();
        if (pos < tokens.size() && tokens[pos] == ")") {
            ++pos; // 消耗')'
            return node;
        } else {
            // 错误：期望')'
            deleteTree(node);
            return nullptr;
        }
    } else if (isdigit(tokens[pos][0]) || tokens[pos][0] == '.') {
        // 操作数（数字）
        TreeNode* node = new TreeNode(tokens[pos++]);
        return node;
    } else {
        // 错误：期望数字或'('
        return nullptr;
    }
}

// 递归求值表达式树
double evaluate(TreeNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) {
        // 叶节点（操作数）
        return atof(node->value.c_str());
    }
    double leftVal = evaluate(node->left);
    double rightVal = evaluate(node->right);
    if (node->value == "+") {
        return leftVal + rightVal;
    } else if (node->value == "-") {
        return leftVal - rightVal;
    } else if (node->value == "*") {
        return leftVal * rightVal;
    } else if (node->value == "/") {
        if (rightVal == 0) {
            // 处理除以零
            MessageBox(NULL, "错误：除以零！", "错误", MB_ICONERROR);
            return 0;
        }
        return leftVal / rightVal;
    }
    return 0;
}

// 删除表达式树以释放内存
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
