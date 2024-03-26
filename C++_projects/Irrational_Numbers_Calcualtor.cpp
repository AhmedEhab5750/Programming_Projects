// FCAI – Structured Programming – 2024 - Assignment 2
// Purpose: The code is designed to take a binomial rational expression from the user and do the operation in the middle on them.
#include <bits/stdc++.h>
using namespace std;
// Next function to check if the input is valid or not using regex.
bool isValidExpression(const string& input) {
    // Define the regex pattern
    regex pattern(R"(-?(?:\+)?\d+(\\d+)?(?:\/(?:\+)?-?\d+(\\d+)?|)(?:\s[-+*/]\s-?(?:\+)?\d+(\\d+)?(?:\/(?:\+)?-?\d+(\\d+)?|))?)");
    // Check if the input matches the regex pattern
    return regex_match(input, pattern);
}
deque<string> input_slicer(string expression){
    string num;
    deque <string> numbers;
    for(int i = 0;i < expression.size();i++){
        if(isdigit(expression[i])){
            num += expression[i];
        }
        else if(expression[i] == '/' || expression[i] == '+' || expression[i] == '-' || expression[i] == '*'){
            if( (i == 0 || !isdigit(num[num.size()-1]))){
                if(expression[i] == '-'){
                    num += "-";
                }
                else{
                    num += "+";
                }
                continue;
            }
            numbers.push_back(num);
            num = "";
            numbers.push_back(string("") + expression[i]);
        }
    }
    if(!num.empty()){
        numbers.push_back(num);
    }
    return numbers;
}
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main(){
    cout << "Welcome in Rational Number Calculator\n";
    while(true) {
        cout << "Please enter a rational number operations (or exit):\n";
        int total_op = 0;
        string expression;
        getline(cin, expression);
        if(expression == "exit"){
            cout << "Thank you for using rational number calculator\n";
            break;
        }
        while (!isValidExpression(expression)) {
            cout << "Invalid input please enter a right expression\n";
            cout << "In this form x/y + z/c\nWhere x, y, z and c are integers and you can change the operation in the middle to / or - or * or +\n";
            cout << "Please enter a rational number operations (or exit):\n";
            getline(cin, expression);
            if(expression == "exit"){
                cout << "Thank you for using rational number calculator\n";
                break;
            }
        }
        deque <string> answer = input_slicer(expression);
        for(auto& k : answer){
            if(k == "-" || k == "/" || k == "+" || k == "*"){
                total_op++;
            }
        }
        long long numerator, denominator, divisor;
        if(total_op == 3){
            if (answer[3] == "+" || answer[3] == "-") {
                answer[0] = to_string(stoi(answer[0]) * stoi(answer[6]));
                answer[4] = to_string(stoi(answer[4]) * stoi(answer[2]));
                denominator = (stoi(answer[2]) * stoi(answer[6]));
                if (answer[3] == "+") {
                    numerator = (stoi(answer[0]) + stoi(answer[4]));
                } else {
                    numerator = (stoi(answer[0]) - stoi(answer[4]));
                }
            }
            else if (answer[3] == "*" || answer[3] == "/") {
                if (answer[3] == "*") {
                    numerator = (stoi(answer[0]) * stoi(answer[4]));
                    denominator = (stoi(answer[2]) * stoi(answer[6]));
                } else {
                    numerator = (stoi(answer[0]) * stoi(answer[6]));
                    denominator = (stoi(answer[2]) * stoi(answer[4]));
                }
            }
        }
        else if(total_op == 1){
            if(answer[1] == "/"){
                numerator = stoi(answer[0]);
                denominator = stoi(answer[2]);
            }
            else if(answer[1] == "*"){
                numerator = stoi(answer[0]) * stoi(answer[2]);
                denominator = 1;
            }
            else if(answer[1] == "-"){
                numerator = stoi(answer[0]) - stoi(answer[2]);
                denominator = 1;
            }
            else if(answer[1] == "+"){
                numerator = stoi(answer[0]) + stoi(answer[2]);
                denominator = 1;
            }
        }
        else if(total_op == 2){
            if(answer[1] != "/"){
                string tempo = answer[0];
                answer.pop_front();
                answer.emplace_front("1");
                answer.emplace_front("/");
                answer.push_front(tempo);
            }
            else{
                answer.emplace_back("/");
                answer.emplace_back("1");
            }
            if (answer[3] == "+" || answer[3] == "-") {
                answer[0] = to_string(stoi(answer[0]) * stoi(answer[6]));
                answer[4] = to_string(stoi(answer[4]) * stoi(answer[2]));
                denominator = (stoi(answer[2]) * stoi(answer[6]));
                if (answer[3] == "+") {
                    numerator = (stoi(answer[0]) + stoi(answer[4]));
                }
                else {
                    numerator = (stoi(answer[0]) - stoi(answer[4]));
                }
            }
            else if (answer[3] == "*" || answer[3] == "/") {
                if (answer[3] == "*") {
                    numerator = (stoi(answer[0]) * stoi(answer[4]));
                    denominator = (stoi(answer[2]) * stoi(answer[6]));
                }
                else {
                    numerator = (stoi(answer[0]) * stoi(answer[6]));
                    denominator = (stoi(answer[2]) * stoi(answer[4]));
                }
            }
        }
        if((denominator < 0)){
            numerator *= -1;
            denominator *= -1;
        }
        divisor = gcd(abs(numerator),abs( denominator));
        if(denominator == 0 || denominator / divisor == 0){
            cout << "Infinite expression caused by dividing on zero\n";
            continue;
        }
        else if(numerator / divisor == 0 && denominator / divisor == 1){
            cout << "= 0\n";
            continue;
        }
        if(abs(numerator) / abs(denominator) > 0 && abs(numerator) % abs(denominator) != 0 ){
            int num1 = numerator % denominator;
            int num2 = numerator / denominator;
            divisor = gcd(abs(num1), abs(denominator));
            cout << "= " << num2 << " " << abs(num1) / divisor << '/' << abs(denominator) / divisor << endl;
            continue;
        }
        cout << "= " << numerator / divisor << '/' << denominator / divisor << endl;
    }
    return 0;
}
