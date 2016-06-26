#include <iostream>
#include <algorithm>
#include <queue>

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





struct queue_item {
  int min_num_in_route;
  int current_num;
};

bool operator< (const queue_item &a, const queue_item &b)
{
  return a.min_num_in_route < b.min_num_in_route;
}

int N, M, S;
vector< vector<int> > graph;
vector <int> min_num_in_routes;

int main()
{
  cin >> N >> M >> S;
  graph.resize(N + 1);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  min_num_in_routes = vector<int>(N+1, -1);

  priority_queue<queue_item, vector<queue_item>, less<queue_item> > pq; 
  pq.push({S, S});

  while(!pq.empty()) {
    queue_item qi = pq.top(); pq.pop();
    if (min_num_in_routes[qi.current_num] != -1) continue;
    min_num_in_routes[qi.current_num] = qi.min_num_in_route;

    for (int n: graph[qi.current_num]) {
      pq.push({min(qi.min_num_in_route, n), n});
    }
  }

  for (int i = 1; i <= N; i++) {
    if (i == min_num_in_routes[i]) cout << i << endl;
  }
}

