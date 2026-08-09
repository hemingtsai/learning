#include <iostream>
#include <vector>

int main(){
    // 输入N
    int N;
    std::cin >> N;
    // 创建一个长度为N+1的向量，用于存储输入的数字
    std::vector<int> user_input(N+1);
    // 循环输入N个数字
    for(int i=1;i<=N;i++){
        std::cin >> user_input[i];
    }

    // 创建一个长度为N+1的向量，用于存储相邻数字的差值
    std::vector<int> d(N+1);
    // 循环计算相邻数字的差值
    for(int i=1;i<=N;i++){
        d[i] = user_input[i] - user_input[i-1];
    }

    // 初始化sum为0
    int sum = 0;
    // 循环计算差值大于0的和
    for(int i=1;i<=N;i++){
        if(d[i] > 0)
        sum+=d[i];
    }

    // 输出结果
    std::cout << sum << std::endl;
}