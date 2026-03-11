#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

int robar(std::vector<int>& nums){
    int n = nums.size();

    if(n == 0) return 0;
    if(n == 1) return nums[0];

    std::vector <int> dp(n);
    
    dp[0] = nums[0];

    dp[1] = std::max(nums[0], nums[1]);

    for(int i = 2; i < n; i++){
        dp[i] = std::max(dp[i-1], nums[i] + dp[i - 2]);
    }
    return dp[n-1];
}

int main(){
    std::vector<int> casas = {2, 7, 9, 3, 1};

    for(int i = 0; i < sizeof(casas)/sizeof(int); i++){
        std::cout << "Valor en casas del vecindario: " << casas[i] << std::endl;
    }
    std::cout << "El valor maximo es " << robar(casas) << std::endl;
}