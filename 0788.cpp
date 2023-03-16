class Solution {
public:
    int rotatedDigits(int n) {
        int lookup[] = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
        int count = 0;
        for(int i = 2; i < n+1; ++i){
            int number = i;
            int value = 0;
            while(number != 0){
                int digit = number % 10;
                number = number / 10;
                if(lookup[digit] == -1){
                    value = 0;
                    break;
                }
                if(lookup[digit] == 1) {
                    value = 1;
                }
            }
            count += value;
        }
        return count;
    }
};