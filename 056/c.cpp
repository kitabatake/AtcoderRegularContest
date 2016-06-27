#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

template<typename T> void debug_vector (vector<T> v) {
  for (int i = 0, s = v.size(); i < s; i++) {
    cout << v[i];
    if (i < s - 1) cout << "\t"; else cout << endl;
  }
}

template<typename T> void debug_2vector (vector< vector<T> > v) {
  for (int i = 0, s = v.size(); i < s; i++) {
    debug_vector(v[i]);
    cout << "\n";
  }
}


int N, K;

void make_combinations(vector<int> rest, vector< vector<int> > current, vector< vector< vector<int> > > &all)
{
  if (rest.size() == 0) {
    all.push_back(current);
    return;
  }

  int add = rest[0];
  rest.erase(rest.begin());

  vector< vector<int> > tmp_current = current;
  tmp_current.push_back({add});
  make_combinations(rest, tmp_current, all);
  for (int i = 0; i < current.size(); i++) {
    tmp_current = current;
    tmp_current[i].push_back(add);
    make_combinations(rest, tmp_current, all);
  }
}

vector< vector<int> > make_comb_credits(vector< vector<int> > &comb, vector< vector<int> > &credits)
{
  vector< vector<int> > comb_credits = credits;
  for (vector<int> row:comb) {
    for (int i = 0; i < row.size(); i++) {
      for (int j = i; j < row.size(); j++) {
        comb_credits[row[i]][row[j]] = 0;
        comb_credits[row[j]][row[i]] = 0;
      }
    }
  }

  return comb_credits;
}

ll calc_score(vector< vector<int> > &comb, vector< vector<int> > &credits)
{
  int sum = 0;
  for (int i = 0; i < N; i++)
    for (int j = i; j < N; j++)
      sum += credits[i][j];

  return comb.size() * K - sum;
}

int main()
{
  
  cin >> N >> K;
  vector< vector<int> > credits(N, vector<int>(N));
  for(int i = 0; i < N; i++)
    for (int j = 0; j < N; j++ )
      cin >> credits[i][j];
  
  vector<int> rest;
  for (int i = 0; i < N; i++) rest.push_back(i);

  vector< vector< vector<int> > > all;
  make_combinations(rest, {}, all);

  ll ans = 0;
  for (int i = 0; i < all.size(); i++) {
    vector< vector<int> > comb = all[i];
    vector< vector<int> > comb_credits = make_comb_credits(comb, credits);
    ans = max(calc_score(comb, comb_credits), ans);
  }

  cout << ans << endl;
}