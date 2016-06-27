#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

typedef long long ll;
#define REP(i, x) for (int i = 0; i < (int)(x); i++)

int N, K;
vector< vector<int > > credits;

vector<int> dp;
vector<int> group_credits_sum;

int lose_credits(int a, int b)
{
  return group_credits_sum[a | b] - group_credits_sum[a] - group_credits_sum[b];
}

int main()
{
  cin >> N >> K;
  credits = vector< vector<int> >(N, vector<int>(N));
  REP(i, N) REP(j, N) cin >> credits[i][j];

  dp.resize(1 << N);
  group_credits_sum.resize(1 << N);

  for (int group = 1; group < (1 << N); group++) {
    for (int n = 0; n < N; n++) {
      if (group & (1 << n)) {
        for (int m = 0; m < n; m++) {
          if (group & (1 << m)) {
            group_credits_sum[group] += credits[n][m];
          }
        }
      }
    }
  }

  for (int group = 1; group < (1 << N); group++) {
    int subgroup = group;
    while (subgroup > 0) {
      dp[group] = max(
        dp[group],
        K + dp[group ^ subgroup] - lose_credits(subgroup, group ^ subgroup)
      );
      subgroup = (subgroup - 1) & group;
    }
    
  }

  cout << dp[(1 << N) - 1] << endl;
}