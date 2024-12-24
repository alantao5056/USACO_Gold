import bisect

MOD = 4e18

T = int(input())

for _ in range(T):
    N = int(input())
    
    jobs = [(None, None)] * (N + 1)  # time takes, start
    jobs[0] = (-1, -1)
    
    for i in range(1, N + 1):
        a, b = map(int, input().split())
        jobs[i] = (b, a)
    
    jobs.sort(key=lambda x: (x[0], x[1]))

    dp = [(MOD, 0)] * (N + 1)  # (total time, tasks)
    dp[0] = (0, 0)

    for i in range(1, N + 1):
        dp[i] = dp[i - 1]
        idx = bisect.bisect_right(dp, (jobs[i][1], MOD)) - 1
        if idx == -1:
            continue
        newt = dp[idx][1] + 1
        if newt > dp[i][1]:
            dp[i] = (dp[idx][0] + jobs[i][0], newt)

    print(dp[N][1])
