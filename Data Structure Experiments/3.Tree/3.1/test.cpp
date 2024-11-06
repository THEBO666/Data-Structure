#include <windows.h>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <iostream>

// ���ʽ���Ľڵ�ṹ��
struct TreeNode {
    std::string value;   // �ڵ��ֵ�����������������
    TreeNode* left;      // ���ӽڵ�
    TreeNode* right;     // ���ӽڵ�
    TreeNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};

// ������������������ֵ
std::vector<std::string> tokenize(const std::string& expression);

class Parser {
public:
    std::vector<std::string> tokens; // ���ʽ�ı���б�
    size_t pos;                      // ��ǰ���λ��
    Parser(const std::vector<std::string>& tokens) : tokens(tokens), pos(0) {}
    TreeNode* parseExpression();     // �������ʽ
private:
    TreeNode* parseTerm();           // ������
    TreeNode* parseFactor();         // ��������
};

double evaluate(TreeNode* node);     // �ݹ���ֵ���ʽ��
void deleteTree(TreeNode* node);     // ɾ�����ʽ�����ͷ��ڴ�

// WindowsӦ�ó�����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// �ؼ���ȫ�־��
HWND hStaticExpression, hStaticOutput;
std::string currentExpression; // �ɰ�ť��������ĵ�ǰ���ʽ

// ��ť��ID
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
    BTN_DOT   // С���㰴ť
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc = { 0 };
    HWND hwnd;
    MSG Msg;

    // ���崰���������
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = "CalculatorWindowClass";
    wc.lpfnWndProc = WndProc;                // ���ڹ��̻ص�
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // ע�ᴰ����
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "����ע��ʧ�ܣ�", "����",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // ����������
    hwnd = CreateWindowEx(0, "CalculatorWindowClass", "������",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 260, 420,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "���ڴ���ʧ�ܣ�", "����",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // ��ʾ�����´���
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    while (GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// ���ڹ��̴�����Ϣ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // ����������ʾ���ʽ�Ŀؼ�
        hStaticExpression = CreateWindow("STATIC", "",
            WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_BORDER,
            10, 10, 220, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);

        // �������ֺͲ�������ť
        int buttonWidth = 50;
        int buttonHeight = 50;
        int startX = 10;
        int startY = 50;
        int margin = 5;

        // ��ť��ǩ��ID
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

        // ����������ʾ����Ŀؼ�
        hStaticOutput = CreateWindow("STATIC", "",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10, startY + 5 * (buttonHeight + margin), 220, 30, hwnd, NULL, GetModuleHandle(NULL), NULL);
        break;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (wmId >= BTN_0 && wmId <= BTN_9) {
            // ���ְ�ť
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
            // ������ʽ
            currentExpression.clear();
            SetWindowText(hStaticOutput, "");
        } else if (wmId == BTN_CALC) {
            // ������ʽ
            std::vector<std::string> tokens = tokenize(currentExpression);
            Parser parser(tokens);
            TreeNode* root = parser.parseExpression();
            if (root != nullptr && parser.pos == tokens.size()) {
                // ��ֵ���ʽ
                double result = evaluate(root);
                std::string output = "���: " + std::to_string(result);
                SetWindowText(hStaticOutput, output.c_str());
                // ����ɾ�����ʽ��
                deleteTree(root);
            } else {
                SetWindowText(hStaticOutput, "���ʽ����");
            }
        }
        // ���±��ʽ��ʾ
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

// ��������ʽ�ַ�����ǻ��ĺ���
std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    size_t i = 0;
    while (i < expression.length()) {
        if (isspace(expression[i])) {
            ++i; // �����հ��ַ�
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            // ��ȡ���֣�����С����
            std::string num;
            int dotCount = 0;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        // С���㳬��һ�����Ƿ�����
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
            // �����Ƿ��ַ�
            tokens.clear();
            break;
        }
    }
    return tokens;
}

// Parser��ķ���ʵ��

// �������ʽ������ӷ��ͼ�����
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

// ���������˷��ͳ�����
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

// �������ӣ��������ֺ������ڵı��ʽ��
TreeNode* Parser::parseFactor() {
    if (pos >= tokens.size()) return nullptr;
    if (tokens[pos] == "(") {
        ++pos; // ����'('
        TreeNode* node = parseExpression();
        if (pos < tokens.size() && tokens[pos] == ")") {
            ++pos; // ����')'
            return node;
        } else {
            // ��������')'
            deleteTree(node);
            return nullptr;
        }
    } else if (isdigit(tokens[pos][0]) || tokens[pos][0] == '.') {
        // �����������֣�
        TreeNode* node = new TreeNode(tokens[pos++]);
        return node;
    } else {
        // �����������ֻ�'('
        return nullptr;
    }
}

// �ݹ���ֵ���ʽ��
double evaluate(TreeNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) {
        // Ҷ�ڵ㣨��������
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
            // ���������
            MessageBox(NULL, "���󣺳����㣡", "����", MB_ICONERROR);
            return 0;
        }
        return leftVal / rightVal;
    }
    return 0;
}

// ɾ�����ʽ�����ͷ��ڴ�
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
