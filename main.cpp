#include "printer.h"

printer print;

vector<int> firstNum, secondNum;

void drop() {
    cout << "Error: Invalid input" << endl;
    exit(0);
}

long long power(long long st) {
    long long ans = 1;
    for (long i = 0; i < st; i++)
        ans *= 10;
    return ans;
}
/*
100000000000000000000000
99999999999999999999999
99999999999999999999999
*/
int compare(string line1, string line2) {
    if (line1.length() > line2.length()) return 1;
    if (line2.length() > line1.length()) return -1;
    for (long i = 0; i < line1.length(); i++) {
        if (line1[i] > line2[i]) return 1;
        if (line2[i] > line1[i]) return -1;
    }
    return 0;
}


void vivod(string s, long long level, long long size) {
    for (long j = 0; j < s.length(); j++) {
        print.putChar(s[j], size, level);
        if (s[j] == 'c' || s[j] == 'C') {
            long long i = j;
            long long brackets_num = 1, comma = i + 1, start = i + 1;
            i += 2;
            while (brackets_num > 0) {
                if (s[i] == '(') brackets_num++; else if (s[i] == ')') brackets_num--;
                if (brackets_num == 1 && s[i] == ',') comma = i;
                i++;
            }
            i--;
            string left_s = s, right_s = s;
            left_s.erase(comma, left_s.length() - comma + 1);
            left_s.erase(0, start + 1);
            right_s.erase(i, right_s.length() - i + 1);
            right_s.erase(0, comma + 1);
            j += 3 + left_s.size() + right_s.size();
            vivod(left_s, level, size - 1);
            vivod(right_s, level + 7 * (1 << (size - 2)), size - 1);
        }
    }
}

void longSlozh() {
    int rank = 0;
    for (int i = 0; i < max(firstNum.size(), secondNum.size()) || rank; i++) {
        if (i == firstNum.size()) firstNum.push_back(0);
        if (i < secondNum.size()) firstNum[i] += rank + secondNum[i]; else firstNum[i] += rank;
        if (firstNum[i] >= 10) rank = 1; else rank = 0;
        if (rank == 1) firstNum[i] -= 10;
    }
}

void longVichet() {
    int rank = 0;
    for (int i = 0; i < secondNum.size() || rank; i++) {
        if (i < secondNum.size()) firstNum[i] -= rank + secondNum[i]; else firstNum[i] -= rank;
        if (firstNum[i] < 0) rank = 1; else rank = 0;
        if (rank == 1) firstNum[i] += 10;
    }
    while (firstNum.size() > 1 && firstNum.back() == 0) firstNum.pop_back();
}

string longArifm(string firstLine, string secondLine, char sign) {
    if (compare(firstLine, secondLine) == -1) swap(firstLine, secondLine);
    for (int i = 0; i < firstLine.length(); i++)
        firstNum.push_back(firstLine[firstLine.length() - i - 1] - '0');
    for (int i = 0; i < secondLine.length(); i++)
        secondNum.push_back(secondLine[secondLine.length() - i - 1] - '0');
    if (sign == '+') longSlozh(); else if (sign == '-') longVichet();
    reverse(firstNum.begin(), firstNum.end());
    string ansLine;
    for (int i = 0; i < firstNum.size(); i++) {
        std::stringstream transfer_s;
        transfer_s << firstNum[i];
        ansLine = ansLine + transfer_s.str();
    }
    firstNum.clear();
    secondNum.clear();
    return ansLine;
}

string lineProcessing(string s, long long left_count) {
    bool f;
    string leftcur_s = s, rightcur_s = s;
    long long left_num = 0, right_num = 0;
    long long mid_count = left_count, right_count = left_count + 1;
    left_count--;
    f = true;
    while (f == true)
        if (s[left_count] == '+' || s[left_count] == '-' || s[left_count] == '*' || s[left_count] == '/' ||
            left_count <= 0)
            f = false;
        else left_count--;
    f = true;
    while (f == true)
        if (s[right_count] == '+' || s[right_count] == '-' || s[right_count] == '*' || s[right_count] == '/' ||
            right_count >= s.length() - 1)
            f = false;
        else right_count++;
    if (left_count == 0) leftcur_s.erase(mid_count, leftcur_s.length() - mid_count + 1);
    else {
        leftcur_s.erase(mid_count, leftcur_s.length() - mid_count + 1);
        leftcur_s.erase(0, left_count + 1);
    }
    if (right_count == s.length() - 1) rightcur_s.erase(0, mid_count + 1);
    else {
        rightcur_s.erase(right_count, rightcur_s.length() - right_count + 1);
        rightcur_s.erase(0, mid_count + 1);
    }
    if (leftcur_s.size() == 0 || rightcur_s.size() == 0) drop();
    if (s[mid_count] == '+') {
        string num_s;
        if (leftcur_s[0] == 'k' && rightcur_s[0] == 'k') {
            leftcur_s.erase(0, 1);
            rightcur_s.erase(0, 1);
            num_s = 'k' + longArifm(leftcur_s, rightcur_s, s[mid_count]);
        } else if (leftcur_s[0] == 'k') {
            leftcur_s.erase(0, 1);
            if (compare(rightcur_s, leftcur_s) != -1) num_s = longArifm(rightcur_s, leftcur_s, '-');
            else
                num_s = 'k' + longArifm(
                        leftcur_s, rightcur_s, '-');
        } else if (rightcur_s[0] == 'k') {
            rightcur_s.erase(0, 1);
            if (compare(leftcur_s, rightcur_s) != -1) num_s = longArifm(leftcur_s, rightcur_s, '-');
            else
                num_s = 'k' + longArifm(
                        rightcur_s, leftcur_s, '-');
        } else num_s = longArifm(leftcur_s, rightcur_s, s[mid_count]);
        leftcur_s = s;
        rightcur_s = s;
        if (left_count == 0) leftcur_s = ""; else leftcur_s.erase(left_count + 1, leftcur_s.length() - 1);
        if (right_count == s.length() - 1) rightcur_s = ""; else rightcur_s.erase(0, right_count);
        return leftcur_s + num_s + rightcur_s;
    } else if (s[mid_count] == '-') {
        string num_s;
        if (leftcur_s[0] == 'k' && rightcur_s[0] == 'k') {
            leftcur_s.erase(0, 1);
            rightcur_s.erase(0, 1);
            if (compare(rightcur_s, leftcur_s) != -1) num_s = longArifm(rightcur_s, leftcur_s, '-');
            else
                num_s = 'k' + longArifm(
                        leftcur_s, rightcur_s, '-');
        } else if (leftcur_s[0] == 'k') {
            leftcur_s.erase(0, 1);
            num_s = 'k' + longArifm(leftcur_s, rightcur_s, '+');
        } else if (rightcur_s[0] == 'k') {
            rightcur_s.erase(0, 1);
            num_s = longArifm(leftcur_s, rightcur_s, '+');
        } else {
            if (compare(leftcur_s, rightcur_s) != -1) num_s = longArifm(leftcur_s, rightcur_s, '-');
            else
                num_s = 'k' + longArifm(
                        rightcur_s, leftcur_s, '-');
        }
        leftcur_s = s;
        rightcur_s = s;
        if (left_count == 0) leftcur_s = ""; else leftcur_s.erase(left_count + 1, leftcur_s.length() - 1);
        if (right_count == s.length() - 1) rightcur_s = ""; else rightcur_s.erase(0, right_count);
        return leftcur_s + num_s + rightcur_s;
    } else if (s[mid_count] == '*' || s[mid_count == '/']) {
        long long sign = 1;
        if (leftcur_s[0] == 'k') {
            leftcur_s.erase(0, 1);
            sign = -1;
        }
        std::stringstream transferl_s;
        transferl_s << LLONG_MAX;
        string llong_s = transferl_s.str();
        if (compare(leftcur_s, llong_s) == 1) {
            cout << "Sorry, but we can't resolve this example";
            exit(0);
        }
        left_num = 0;
        long long k = leftcur_s.length();
        for (long i = 0; i < k; i++) {
            long long tmp = leftcur_s[k - i - 1] - '0';
            left_num += tmp * power(i);
        }
        left_num *= sign;
        sign = 1;
        if (rightcur_s[0] == 'k') {
            rightcur_s.erase(0, 1);
            sign = -1;
        }
        if (compare(rightcur_s, llong_s) == 1) {
            cout << "Sorry, but we can't resolve this example";
            exit(0);
        }
        right_num = 0;
        k = rightcur_s.length();
        for (long i = 0; i < k; i++) {
            long long tmp = rightcur_s[k - i - 1] - '0';
            right_num += tmp * power(i);
        }
        right_num *= sign;
        long long ans = 0;
        if (s[mid_count] == '*') ans = left_num * right_num;
        else if (s[mid_count] == '/') {
            if (right_num == 0) {
                cout << "Error: Divide by zero" << endl;
                exit(0);
            } else ans = left_num / right_num;
        }
        leftcur_s = s;
        rightcur_s = s;
        if (left_count == 0) leftcur_s = ""; else leftcur_s.erase(left_count + 1, leftcur_s.length() - 1);
        if (right_count == s.length() - 1) rightcur_s = ""; else rightcur_s.erase(0, right_count);
        std::stringstream transfer_s;
        transfer_s << ans;
        string num_s = transfer_s.str();
        if (ans < 0) {
            num_s.erase(0, 1);
            return leftcur_s + 'k' + num_s + rightcur_s;
        } else return leftcur_s + num_s + rightcur_s;
    }
}

long long fact(long long k, long long n) {
    if (k == n || k == 0) return 1;
    if (k == 1 || k == n - 1) return n;
    long long triangle[n + 1][n + 1];
    for (long i = 0; i <= n; i++) {
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (long j = 1; j < i; j++)
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
    }
    return triangle[n][k];
}

string cProcessing(string k, string n) {
    if (k[0] == '-' || k[0] == 'k' || n[0] == '-' || n[0] == 'k') drop();
    long long l = k.length(), num_k = 0, num_n = 0, ans = 0;
    for (long i = 0; i < l; i++) {
        long long tmp = k[l - i - 1] - '0';
        num_k += tmp * power(i);
    }
    l = n.length();
    for (long i = 0; i < l; i++) {
        long long tmp = n[l - i - 1] - '0';
        num_n += tmp * power(i);
    }
    if (num_k > num_n || num_k < 0 || num_n < 0) drop(); else ans = fact(num_k, num_n);
    std::stringstream transfer_s;
    transfer_s << ans;
    return transfer_s.str();
}

string solver(string cur_s) {
    long long j = 0;
    while (j < cur_s.length()) {
        if (cur_s[j] == '*' || cur_s[j] == '/') {
            cur_s = lineProcessing(cur_s, j);
            j = 0;
        } else j++;
    }
    j = 0;
    while (j < cur_s.length()) {
        if (cur_s[j] == '+' || cur_s[j] == '-') {
            cur_s = lineProcessing(cur_s, j);
            j = 0;
        } else j++;
    }
    return cur_s;
}

string parser(string s) {
    long long i = 0;
    vector<long long> brackets_stack;
    i = 0;
    while (i < s.length()) {
        if (s[i] == '(') brackets_stack.push_back(i);
        else if (s[i] == ')') {
            string mid_s = s;
            mid_s.erase(i, mid_s.length() - i + 1);
            mid_s.erase(0, brackets_stack[brackets_stack.size() - 1] + 1);
            if (mid_s[0] == '+' || mid_s[0] == '*' || mid_s[0] == '/' || mid_s[mid_s.size() - 1] == '+' ||
                mid_s[mid_s.size() - 1] == '-' || mid_s[mid_s.size() - 1] == '*' || mid_s[mid_s.size() - 1] == '/')
                drop();
            if (mid_s[0] == '-') {
                mid_s.erase(0, 1);
                if (mid_s[0] != 'k') mid_s = 'k' + mid_s; else mid_s.erase(0, 1);
            }
            if (mid_s.length() < 1) drop();
            mid_s = solver(mid_s);
            if (mid_s.length() < 1) drop();
            string left_s = s, right_s = s;
            left_s.erase(brackets_stack[brackets_stack.size() - 1],
                         left_s.length() - brackets_stack[brackets_stack.size() - 1] + 1);
            right_s.erase(0, i + 1);
            s = left_s + mid_s + right_s;
            i = brackets_stack[brackets_stack.size() - 1];
            brackets_stack.pop_back();
        }
        i++;
    }
    return s;
}

string cSolver(string s, long long i) {
    long long brackets_num = 1, comma = i + 1, start = i + 1;
    i += 2;
    while (brackets_num > 0) {
        if (s[i] == '(') brackets_num++; else if (s[i] == ')') brackets_num--;
        if (brackets_num == 1 && s[i] == ',') comma = i;
        i++;
    }
    i--;
    string left_s = s, right_s = s;
    left_s.erase(comma, left_s.length() - comma + 1);
    left_s.erase(0, start + 1);
    right_s.erase(i, right_s.length() - i + 1);
    right_s.erase(0, comma + 1);
    for (long j = 0; j < left_s.length(); j++)
        if (left_s[j] == 'c' || left_s[j] == 'C') left_s = cSolver(left_s, j);
    for (long j = 0; j < right_s.length(); j++)
        if (right_s[j] == 'c' || right_s[j] == 'C') right_s = cSolver(right_s, j);
    left_s = parser(left_s);
    if (left_s[0] == '+' || left_s[0] == '*' || left_s[0] == '/' || left_s[left_s.size() - 1] == '+' ||
        left_s[left_s.size() - 1] == '-' || left_s[left_s.size() - 1] == '*' || left_s[left_s.size() - 1] == '/')
        drop();
    if (left_s[0] == '-') {
        left_s.erase(0, 1);
        if (left_s[0] != 'k') left_s = 'k' + left_s; else left_s.erase(0, 1);
    }
    if (left_s.length() < 1) drop();
    left_s = solver(left_s);
    if (left_s.length() < 1) drop();
    right_s = parser(right_s);
    if (right_s[0] == '+' || right_s[0] == '*' || right_s[0] == '/' || right_s[right_s.size() - 1] == '+' ||
        right_s[right_s.size() - 1] == '-' || right_s[right_s.size() - 1] == '*' || right_s[right_s.size() - 1] == '/')
        drop();
    if (right_s[0] == '-') {
        right_s.erase(0, 1);
        if (right_s[0] != 'k') right_s = 'k' + right_s; else right_s.erase(0, 1);
    }
    if (right_s.length() < 1) drop();
    right_s = solver(right_s);
    if (right_s.length() < 1) drop();
    string mid_s = cProcessing(left_s, right_s);
    left_s = s;
    right_s = s;
    left_s.erase(start - 1, left_s.length() - start + 1);
    right_s.erase(0, i + 1);
    return left_s + mid_s + right_s;
}

int main() {
    string s;
    getline(cin, s);
    if (s[0] == '+' || s[0] == '*' || s[0] == '/' || s[s.size() - 1] == '+' || s[s.size() - 1] == '-' ||
        s[s.size() - 1] == '*' || s[s.size() - 1] == '/')
        drop();
    long long j = 0;
    while (j < s.length())
        if (s[j] == ' ') s.erase(j, 1); else j++;
    long long i = 0, numbers_count = 0;
    vector<long long> brackets_stack;
    while (i < s.length()) {
        switch (s[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
            case 'c':
            case 'C':
            case ',':
                break;
            case '(':
                brackets_stack.push_back(i);
                break;
            case ')': {
                if (brackets_stack.size() > 0) brackets_stack.pop_back();
                else if (brackets_stack.size() <= 0) drop();
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                numbers_count++;
                break;
            default :
                drop();
        }
        i++;
    }
    if (numbers_count == 0 || brackets_stack.size() != 0) drop();
    vector<long long> depths;
    vector<long long> brackets_place;
    depths.resize(s.length());
    brackets_place.resize(s.length());
    long long depth = 1;
    i = 0;
    j = 0;
    while (i < s.length()) {
        if (s[i] == '(') {
            brackets_place[depth]++;
            depths[i] = depth;
        } else if (s[i] == ')') {
            if (brackets_place[depth] == 1 && depth > 1) {
                depths[i] = 0;
                brackets_place[depth]--;
                depth--;
            } else {
                depths[i] = depth;
                brackets_place[depth]--;
            }
        } else if (s[i] == 'c' || s[i] == 'C') {
            depths[i] = depth;
            depth++;
            i++;
            depths[i] = 0;
            brackets_place[depth] = 1;
        } else {
            if (s[i] != ',') depths[i] = depth; else depths[i] = 0;
        }
        i++;
    }
    long long max = depths[0];
    for (i = 1; i < s.length(); i++)
        if (depths[i] > max) max = depths[i];
    string final_s = s;
    i = 0;
    while (i < s.length()) {
        if (s[i] == 'c' || s[i] == 'C') s = cSolver(s, i);
        i++;
    }
    i = 0;
    while (i < s.length()) {
        if (s[i] == '(') brackets_stack.push_back(i);
        else if (s[i] == ')') {
            string mid_s = s;
            mid_s.erase(i, mid_s.length() - i + 1);
            mid_s.erase(0, brackets_stack[brackets_stack.size() - 1] + 1);
            if (mid_s[0] == '+' || mid_s[0] == '*' || mid_s[0] == '/' || mid_s[mid_s.size() - 1] == '+' ||
                mid_s[mid_s.size() - 1] == '-' || mid_s[mid_s.size() - 1] == '*' || mid_s[mid_s.size() - 1] == '/')
                drop();
            if (mid_s[0] == '-') {
                mid_s.erase(0, 1);
                if (mid_s[0] != 'k') mid_s = 'k' + mid_s; else mid_s.erase(0, 1);
            }
            mid_s = solver(mid_s);
            if (mid_s.length() < 1) drop();
            string left_s = s, right_s = s;
            left_s.erase(brackets_stack[brackets_stack.size() - 1],
                         left_s.length() - brackets_stack[brackets_stack.size() - 1] + 1);
            right_s.erase(0, i + 1);
            s = left_s + mid_s + right_s;
            i = brackets_stack[brackets_stack.size() - 1];
            brackets_stack.pop_back();
        }
        i++;
    }
    if (s[0] == '+' || s[0] == '*' || s[0] == '/' || s[s.size() - 1] == '+' || s[s.size() - 1] == '-' ||
        s[s.size() - 1] == '*' || s[s.size() - 1] == '/')
        drop();
    if (s[0] == '-') {
        s.erase(0, 1);
        if (s[0] != 'k') s = 'k' + s; else s.erase(0, 1);
    }
    if (s.length() < 1) drop();
    s = solver(s);
    if (s.length() < 1) drop();
    else if (s[0] == 'k') {
        s.erase(0, 1);
        s = '-' + s;
    }
    for (i = 0; i < s.length(); i++)
        if (s[i] == 'k') drop();
    long long lasts = final_s.length();
    final_s = final_s + "=" + s;
    for (j = lasts; j < final_s.length(); j++)
        depths.push_back(max);
    max++;
    for (i = 0; i < lasts; i++)
        if (depths[i] != 0) depths[i] = max - depths[i];
    max--;
    long long new_size = 0;
    for (i = 0; i < depths.size(); i++)
        if (depths[i] > 0) new_size += (1 << (depths[i] - 1));
    print.ensureCapacity(1 << (max - 1), new_size);
    //cout << final_s << endl;
    vivod(final_s, 0, max);
    print.printImage();
    system("pause");
}
//c(c(c(5-4,2/2),c(6+4-9,0+1)),c(c(8/7,5-2*2),c(7-3*2,1-0)))
//c(c(4,6),2*c(4,6))