class Solution {
public:
    int calculate(string s) {
    stack<int> numbers;
    int sign = 1;
    int sum = 0;
    int result = 0;
    numbers.push(1);
    for (int i = 0; i < s.length(); i++)
    {
        
        if (s[i] >= '0' && s[i] <= '9') // Operand
        {
            sum = sum * 10 + (s[i] - '0');
        }
        else // Operator
        {
            result += sum * sign * numbers.top();
            sum = 0; // reset sum
            if (s[i] == '+') 
            {
                sign = 1;
            }
            else if (s[i] == '-') 
            {
                sign = -1; 
            }
            else if (s[i] == '(')
            {
                int temp = numbers.top() * sign;
                sign = 1;
                numbers.push(temp);
            }
            else if (s[i] == ')')
            {
                numbers.pop();
            }
        }
    }
    result += sum * sign;
    return result;
    }
};