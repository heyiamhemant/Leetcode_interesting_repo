#include <bits/stdc++.h>
using namespace std;
bool compare_by_profit(vector<int> &a, vector<int> &b)
{
    return (a[1] > b[1]);
}

int max_profit(vector<vector<int>> &jobs)
{
    sort(jobs.begin(), jobs.end(), compare_by_profit);
    int max_time = 0;

    for (vector<int> i : jobs)
    {
        max_time = max(max_time, i[0]);
    }
    vector<int> schedule(max_time + 1, -1);
    int profit = 0;
    int i = 0;
    while (i < jobs.size())
    {
        int deadline = jobs[i][0];
        int profit_i = jobs[i][1];
        int time = deadline;
        while (time > 0 and schedule[time] != -1)
            time--;
        if (time > 0)
        {
            schedule[time] = 1;
            profit += profit_i;
        }
        i++;
    }
    return profit;
}

int main()
{
    vector<vector<int>> jobs = {{2, 30}, {4, 40}, {1, 10}, {1, 10}};
    cout << max_profit(jobs);
}