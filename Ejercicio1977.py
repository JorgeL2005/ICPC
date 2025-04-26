class Solution:
    def numberOfCombinations(self, num: str) -> int:
        n = len(num)
        MOD = 10**9 + 7
        dp = [[0]*(n+1) for _ in range(n)]
        for i in range(n): 
            if num[i] != "0": 
                for j in range(i+1, n+1): 
                    if i == 0: 
                        dp[i][j] = 1
                    else:
                        length = j-i
                        
                        dp[i][j] = dp[i][j-1]
                        
                        if i-length >= 0 and num[i-length: i] <= num[i: j]: 
                            dp[i][j] += dp[i-length][i]
                        
                        if i-length+1 >= 0 and num[i-length+1: i] > num[i: j-1]: 
                            dp[i][j] += dp[i-length+1][i]
        return sum(dp[i][n] for i in range(n)) % MOD
