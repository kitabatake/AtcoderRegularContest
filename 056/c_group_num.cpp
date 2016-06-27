#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;


int N, K;
vector< vector<int> >graph;

void combinations(int n, vector<int> current, int group_num, vector< vector<int> > &all)
{
  if (n == N) {
    all.push_back(current);
    return;
  }

  vector<int> tmp_current = current;
  tmp_current.push_back(group_num);
  combinations(n + 1, tmp_current, group_num + 1, all);

  for (int i = 0; i < group_num; i ++) {
    tmp_current = current;
    tmp_current.push_back(i);
    combinations(n + 1, tmp_current, group_num, all);
  }
}

ll calc_score(vector<int> comb)
{
  ll sum = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      if (comb[i] != comb[j]) {
        sum += graph[i][j];
      }
    }
  }

  int group_num = 0;
  for (int i = 0; i < N; i++) group_num = max(comb[i] + 1, group_num);

  return K * group_num - sum;
}

int main()
{
  cin >> N >> K;
  graph = vector< vector<int> >(N, vector<int>(N));
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      cin >> graph[i][j];

  vector< vector<int> > all;
  combinations(0, {}, 0, all);

  ll ans = 0;
  for (vector<int> comb: all) {
    ans = max(calc_score(comb), ans);
  }
  cout << ans << endl;
}