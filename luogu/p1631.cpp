#include <iostream>
#include <queue>
#include <vector>

int main(){
    std::priority_queue<int> heap;  // 大顶堆：堆顶是已保留元素中的最大值

    int number_num;
    std::cin >> number_num;

    std::vector<int> list_a(number_num);
    for(auto &v:list_a){
        std::cin >> v;
    }

    std::vector<int> list_b(number_num);
    for(auto &v:list_b){
        std::cin >> v;
    }

    int answer_end = -1;  // -1 表示堆还未满，阈值未确定
    for(int i=0;i<number_num;i++){
        for(int j=0;j<number_num;j++){
            int sum = list_a[i] + list_b[j];
            // 剪枝：堆已满，且当前和 >= 第 N 小的阈值
            if(answer_end != -1 && sum >= answer_end){
                if(j == 0) goto out;  // 当前行的第一个就超了，后续 i 更大，全部跳过
                break;                // 当前 i 的后续 j 只会更大，跳出内层
            }
            heap.push(sum);
            if(heap.size() > number_num){
                heap.pop();  // 保持堆大小不超过 N
            }
            if(heap.size() == number_num){
                answer_end = heap.top();  // 更新阈值：当前第 N 小的值
            }
        }
    }
    out:
    // 大顶堆弹出顺序是从大到小，倒序存入数组得到从小到大
    std::vector<int> result(number_num);
    for(int i = number_num - 1; i >= 0; i--){
        result[i] = heap.top();
        heap.pop();
    }
    for(int i = 0; i < number_num; i++){
        std::cout << result[i];
        if(i != number_num - 1){
            std::cout << " ";
        }
    }
    return 0;
}
