#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <stack>
#include <queue>
using namespace std;
vector<string> qt1, qt2, qt3, qt4;
vector<string> qt1reverse, qt2reverse, qt3reverse, qt4reverse;
vector<string> read_rules() {
    vector<string> rules;
    string line;

    cout << "Nhap cac quy tac (Nhap 'endinput' de ket thuc nhap):" << endl;

    while (getline(cin, line)) {
        if (line == "endinput") {
            break;
        } else {
            rules.push_back(line);
        }
    }

    return rules;
}

bool contains(const vector<string>& vec, const string& item) {
    return find(vec.begin(), vec.end(), item) != vec.end();
}

vector<string> extract_words(const string& rule) {
    stringstream ss(rule);
    vector<string> data;
    string word;
    while (ss >> word) {
        data.push_back(word);
    }
    data.push_back(" ");
    return data;
}


bool is_all_lowercase(const string& str) {
    string special_chars = ";:!@#$%^&*()=";
    for (char c : str) {
        if (!islower(c) && !isdigit(c) && special_chars.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

void check_qt1(const vector<string>& data) {
    for (int i = 2; i < data.size()-2 ; i++) {
        string a = data[i];
        string b = data[i + 1];
        string c = data[i+2];
        if (is_all_lowercase(a)==true && is_all_lowercase(b)==true) {  // Trường hợp αabβ
            string qh = a + " = " + b;
            if(contains(qt1,qh)){
                return ;
            }
            else{
                qt1.push_back(qh);
            }
        }
        if(is_all_lowercase(a)==true && is_all_lowercase(c)==true){
            string qh = a + " = " + c;
            if(contains(qt1,qh)){
                return ;
            }
            else{
                qt1.push_back(qh);
            }
        }

    }
}
void check_qt2(const vector<string>& data, const vector<string>& data2){
    for(int i=2; i<data.size()-1;i++){
        string a = data[i];
        string B = data[i+1];
        if(is_all_lowercase(a)==true && is_all_lowercase(B)==false){
            if(data2[0]==B){
                string b = data2[2];
                string C = data2[2];
                string b1 = data2[3];
                if(is_all_lowercase(b)==true){
                    string qh = a + " < " + b;
                    if(contains(qt2,qh)){
                        return ;
                    }
                    else{
                        qt2.push_back(qh);
                    }
                }
                if(is_all_lowercase(C)==false && is_all_lowercase(b1)==true){
                    string qh = a + " < " + b1;
                    if(contains(qt2,qh)){
                        return ;
                    }
                    else{
                        qt2.push_back(qh);
                    }
                }
            }
        }
    }
}
void check_qt3(const vector<string>& data, const vector<string>& data2){
    for(int i=2; i<data.size()-1; i++){
        string A = data[i];
        string b = data[i+1];
        if(is_all_lowercase(A)==false && is_all_lowercase(b)==true){
            if(data2[0]==A){
                string a = data2[data2.size()-2];
                string C = data2[data2.size()-2];
                string a1 = data2[data2.size()-3];
                if(is_all_lowercase(a)==true){
                    string qh = a + " > " + b;
                    if(contains(qt3,qh)){
                        return ;
                    }
                    else{
                        qt3.push_back(qh);
                    }
                }
                if(is_all_lowercase(C)==false && is_all_lowercase(a1)==true){
                    string qh = a1 + " > " + b;
                    if(contains(qt3,qh)){
                        return ;
                    }
                    else{
                        qt3.push_back(qh);
                    }
                }
            }
        }
    }
}
void check_qt4(const vector<string>& data){
    if(is_all_lowercase(data[data.size()-2])){
        string qh = data[data.size()-2] + " > $";
        if(contains(qt4,qh)){
            return ;
        }
        else{
            qt4.push_back(qh);
        }
    }
    if(is_all_lowercase(data[data.size()-2])==false && is_all_lowercase(data[data.size()-3])==true){
        string qh = data[data.size()-3] + " > $";
        if(contains(qt4,qh)){
            return ;
        }
        else{
            qt4.push_back(qh);
        }    
    }
    if(is_all_lowercase(data[2])==true){
        string qh = data[2] + " > $";
        if(contains(qt4,qh)){
            return ;
        }
        else{
            qt4.push_back(qh);
        }
    }
    if(is_all_lowercase(data[2])==false && is_all_lowercase(data[3])==true){
        string qh = data[3] + " > $";
        if(contains(qt4,qh)){
            return ;
        }
        else{
            qt4.push_back(qh);
        }
    }
}

void check_syntax_rules(const vector<string>& rules) {
    vector<string> data1 = extract_words(rules[0]);
    check_qt4(data1);
    for(int j=1; j<rules.size();j++){
        vector<string> data2 = extract_words(rules[j]);
        for(int k=0; k<data1.size()-1; k++){
            if(data1[k]==data2[0]){
                int start = 2;
                int end = data2.size()-1;
                data1.erase(data1.begin()+k);
                data1.insert(data1.begin()+k, data2.begin()+start,data2.begin()+end);
                k+=(end-start-1);
                check_qt4(data1);
            }
        }
    }
    for (int i=0; i<rules.size(); i++) {
        vector<string> data = extract_words(rules[i]);
        check_qt1(data);
        for(int j=0; j<rules.size();j++){
            vector<string> data2 = extract_words(rules[j]);
            vector<string> data_temp2 = extract_words(rules[j]);
            check_qt2(data, data2);
            check_qt3(data, data2);
            for(int k=2; k<data_temp2.size()-1; k++){
                for(int t=0; t<rules.size(); t++){
                    vector<string> data_temp2 = extract_words(rules[j]);
                    vector<string> data_temp = extract_words(rules[t]);
                    if(data_temp2[k]==data_temp[0]){
                        int start = 2; 
                        int end = data_temp.size()-1;
                        data_temp2.erase(data_temp2.begin()+k);
                        data_temp2.insert(data_temp2.begin()+k, data_temp.begin()+start, data_temp.begin()+end);
                        k+=(end-start-1);
                        check_qt2(data,data_temp2);
                        check_qt3(data,data_temp2);
                    }
                }
            }
        }
    }
}
void print_table() {
    int max_size = max({qt1.size(), qt2.size(), qt3.size(), qt4.size()});
    cout<<"\n                           BANG TAT CA QUAN HE"<<endl;
    // Header
    cout << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+\n";
    cout << "|" << left << setw(19) << "QUY TAC 1" << "|" << setw(19) << "QUY TAC 2" << "|" << setw(19) << "QUY TAC 3" << "|" << setw(19) << "QUY TAC 4" << "|\n";
    cout << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+\n";

    // Data Rows
    for (int i = 0; i < max_size; i++) {
        cout << "|"
             << left << setw(19) << (i < qt1.size() ? qt1[i] : "")
             << "|" << setw(19) << (i < qt2.size() ? qt2[i] : "")
             << "|" << setw(19) << (i < qt3.size() ? qt3[i] : "")
             << "|" << setw(19) << (i < qt4.size() ? qt4[i] : "")
             << "|\n";
        cout << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+" << string(19, '-') << "+\n";
    }
}
string reversePhraseAndSwapSymbols(const string& input) {
    istringstream iss(input);
    vector<string> tokens;
    string token;

    // Tách chuỗi thành các từ và lưu vào vector
    while (iss >> token) {
        // Thay thế các ký hiệu so sánh trước khi thêm vào vector
        if (token == ">") token = "<";
        else if (token == "<") token = ">";
        else if (token == "=") token = "="; // Xử lý dấu bằng, không thay đổi nhưng cần được đưa vào
        tokens.push_back(token);
    }

    // Đảo ngược thứ tự các từ trong vector
    reverse(tokens.begin(), tokens.end());

    // Tạo chuỗi kết quả bằng cách nối các từ đã đảo ngược
    string result;
    for (const auto& t : tokens) {
        if (!result.empty()) result += " ";
        result += t;
    }
    return result;
}
vector<string> reverseQT(const vector<string>& qt){
    vector<string> reverse;
    for(string data: qt){
        reverse.push_back(reversePhraseAndSwapSymbols(data));
    }
    return reverse;
}
void check (vector<string>& Stack, const vector<string>& rules, bool &c){
    bool check = true;
    for(int i=0; i<rules.size(); i++){
        vector<string> rule = extract_words(rules[i]);
        for(int j=rule.size()-2; j>=2; j--){
            for(int k=Stack.size()-1; k>=0; k--){
                if(rule[j]!=Stack[k]){
                    check = false;
                    break;
                }
                else{
                    if(j==2){
                        int start = k; 
                        int end = Stack.size()-1;
                        Stack.erase(Stack.begin() + start, Stack.begin() + end + 1);
                        Stack.insert(Stack.begin() + start, 1 , rule[0]);
                        c = false;
                        return;
                    }
                    j--;
                }
            }
            if(check == false){
                break;
            }
        }
    }
}
void printHeader() {
    cout << "\n                                               BANG PHAN TICH" << endl;
    cout << "+" << setfill('-') << setw(6) << "+" << setw(50) << "+" << setw(50) << "+" << setw(15) << "+" << setw(15) << "+" << "+\n";
    cout << "|" << setfill(' ') << left << setw(5) << "STT" << "|" << setw(49) << "STACK" << "|" << setw(49) << "BUFFER" << "|" << setw(14) << "RELATION" << "|" << setw(14) << "ACTION" << "|\n";
    cout << "+" << setfill('-') << setw(6) << "+" << setw(50) << "+" << setw(50) << "+" << setw(15) << "+" << setw(15) << "+" << "+\n";
}

void printStatus(const vector<string>& stack, const queue<string>& buffer, const vector<string>& actions, int step, const string& relation) {
    string stackContent, bufferContent, actionContent;

    for (const auto& s : stack) {
        stackContent += s + " ";
    }

    queue<string> tempBuffer = buffer;  // Copy buffer để in mà không thay đổi buffer gốc
    while (!tempBuffer.empty()) {
        bufferContent += tempBuffer.front() + " ";
        tempBuffer.pop();
    }

    if (!actions.empty()) {
        actionContent = actions.back();
    }

    cout << "|" << setfill(' ') << right << setw(5) << step << "|"
         << left << setw(49) << stackContent
         << "|" << setw(49) << bufferContent
         << "|" << setw(14) << relation
         << "|" << setw(14) << actionContent << "|\n";
    cout << "+" << setfill('-') << setw(6) << "+" << setw(50) << "+" << setw(50) << "+" << setw(15) << "+" << setw(15) << "+" << "+\n";
}




void UTTT(vector<string>& Stack, queue<string>& Buffer, const vector<string>& rules) {
    vector<string> action;
    int step = 0;
    printHeader();
    while (true) {
        bool c = false;
        bool temp = true;
        for (int i = Stack.size() - 1; i >= 0; i--) {
            string topStack = Stack[i];
            string frontBuffer = Buffer.front();
            string relEqual = topStack + " = " + frontBuffer;
            string relLess = topStack + " < " + frontBuffer;
            string relGreater = topStack + " > " + frontBuffer;
            string relation;
            if (Stack[0] == "$" && Stack[1] == "S" && frontBuffer == "$") {
                action.push_back("accept");
                relation = "";
                printStatus(Stack, Buffer, action, step++, relation);
                cout << "XAU X DUNG CU PHAP VAN PHAM" << endl;
                return;
            } else if (contains(qt1, relEqual) || contains(qt2, relLess)) {
                action.push_back("shift");
                relation = (contains(qt1, relEqual)) ? relEqual : relLess;
                printStatus(Stack, Buffer, action, step++, relation);
                c = true;
                check(Stack, rules, temp);
                if (temp == false) {
                    break;
                }
                Stack.push_back(frontBuffer);
                Buffer.pop();
                break;
            } else if (contains(qt3, relGreater) || contains(qt4, relGreater)) {
                action.push_back("reduce");
                relation = (contains(qt3, relGreater)) ? relGreater : relGreater;
                printStatus(Stack, Buffer, action, step++, relation);
                check(Stack, rules, temp);
                c = true;
                if (temp == false) {
                    break;
                }
                Stack.push_back(frontBuffer);
                Buffer.pop();
                break;
            } else if (contains(qt1reverse, relEqual) || contains(qt3reverse, relLess) || contains(qt4reverse, relLess)) {
                action.push_back("shift");
                relation = (contains(qt1reverse, relEqual)) ? relEqual : (contains(qt3reverse, relLess)) ? relLess : relLess;
                printStatus(Stack, Buffer, action, step++, relation);
                c = true;
                check(Stack, rules, temp);
                if (temp == false) {
                    break;
                }
                Stack.push_back(frontBuffer);
                Buffer.pop();
                break;
            } else if (contains(qt2reverse, relGreater)) {
                action.push_back("reduce");
                relation = relGreater;
                printStatus(Stack, Buffer, action, step++, relation);
                c = true;
                check(Stack, rules, temp);
                if (temp == false) {
                    break;
                }
                Stack.push_back(frontBuffer);
                Buffer.pop();
                break;
            }
        }
        if (c == false) {
            cout << "XAU X KHONG DUNG CU PHAP VAN PHAM" << endl;
            return;
        }
    }
}

int main() {
    cout << "}" << endl;
    vector<string> rules = read_rules();
    cout<<"\n                           DANH SACH CAC SAN XUAT"<<endl;
    for (const auto& rule : rules) {
        cout << rule << endl;
    }
    check_syntax_rules(rules);
    qt1reverse = reverseQT(qt1);
    qt2reverse = reverseQT(qt2);
    qt3reverse = reverseQT(qt3);
    qt4reverse = reverseQT(qt4);
    print_table();
    
    string x;
    cout << "\nNHAP VAO XAU X: ";
    getline(cin, x);
    cout<<endl;
    vector<string> input = extract_words(x);
    vector<string> action;
    vector<string> Stack;
    Stack.push_back("$");
    queue<string> Buffer;
    for(int i=0; i<input.size()-1; i++){
        Buffer.push(input[i]);
    }
    Buffer.push("$");
    UTTT(Stack,Buffer, rules);
    
    return 0;
}
