#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
  ll A, B, K, L;
  cin >> A >> B >> K >> L;

  if (A <= (B / L)) {
    cout << K * A << endl;
  }
  else {
    int min_set_num = K / L;
    ll asn = min(B * (min_set_num + 1), min_set_num * B + (K - (L * min_set_num)) * A);
    cout << asn << endl;
  }
}