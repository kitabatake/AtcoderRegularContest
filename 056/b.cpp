#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


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




int N, M, S;
vector< vector<int> > graph;

bool can_reach(int i, int target, map<int, bool> &passed)
{
 
  if (i == target) return true;
  if (passed[i]) return false;
  passed[i] = true;

  bool reach = false;
  for (int j:graph[i]) {
    reach =  can_reach(j, target, passed);
    if (reach) return true;
  }

  return false;
}

int main()
{
  cin >> N >> M >> S;
  graph.resize(N + 1);

  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  map<int, bool> passed;
  for (int i = 1; i <= N; i++) {
    map<int, bool> passed = {};
    if (can_reach(S, i, passed)) {
      cout << i << endl;
    }

    graph[i] = {};
  }
}