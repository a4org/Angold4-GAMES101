#include <vector>
#include <iostream>

using namespace std;

int eval(int a, int b, char op){
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    return -1;
}

int main() {

    vector<int> nums = {4,4,4,4};
    vector<char> ops = {'*','*','*'};
    for(size_t it = 0; it < ops.size(); ++it){
        if(ops[it] == '*' || ops[it] == '/'){               // First iterate through operands and execute * and /
            nums[it] = eval(nums[it], nums[it+1], ops[it]); // That is because no matter what the sequence of three op; * and / are first to caculate
            nums.erase(nums.begin()+it+1);                  // if do that caculation, delete the used number and store the temp answer in nums[0]
             ops.erase(ops.begin()+it);
            --it;
        } 
    }

    cout << nums[0] << '\n';
    cout << nums[1] << '\n';
    cout << nums[2] << '\n';
    cout << nums[3] << '\n';

    nums.erase(nums.begin()+2);

    for (int i : nums) {
        cout << i << '\n';
    }
}

