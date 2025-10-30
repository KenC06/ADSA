#include <bits/stdc++.h>
using namespace std;

static inline int letterToCost(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';  // A-Z=1 to 25
  }
  return c - 'a' + 26;  // a-z=27 to 51
}

struct Edge {
  int u, v, w;
  bool existing;
};

struct DSU {
  vector<int> p, r;
  DSU(int n = 0) { init(n); }
  void init(int n) {
    p.resize(n);
    r.assign(n, 0);
    iota(p.begin(), p.end(), 0);
  }
  // finds the group city x belongs in
  int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
  // merges two cities i.e build
  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (r[a] < r[b]) {
      swap(a, b);
    }
    p[b] = a;
    if (r[a] == r[b]) {
      r[a]++;
    }
    return true;
  }
};

int main() {
  string countryStr, buildStr, destroyStr;
  //checks for incorrect inputs
  if (!(cin >> countryStr >> buildStr >> destroyStr)) {
    return 0;
  }

  // split commas into rows
  auto split = [](const string& s) {
    vector<string> parts;
    string cur;
    stringstream ss(s);
    while (getline(ss, cur, ',')) parts.push_back(cur);
    return parts;
  };

  //do this for all 3 inputs
  vector<string> country = split(countryStr);
  vector<string> build = split(buildStr);
  vector<string> destroy = split(destroyStr);

  int N = (int)country.size();
  vector<Edge> existing, missing;

  //check all edge lists
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (country[i][j] == '1') {
        existing.push_back({i, j, letterToCost(destroy[i][j]), true});
      } else {
        missing.push_back({i, j, letterToCost(build[i][j]), false});
      }
    }
  }

  long long totalCost = 0;
  DSU dsu(N);  //initialise dsu

  //handles current edges
  //keep any non loop edges
  sort(existing.begin(), existing.end(),
       [](const Edge& a, const Edge& b) { return a.w > b.w; });

  for (const auto& e : existing) {
    if (!dsu.unite(e.u, e.v)) {
      // existing edges creates a loop, destory and pay cost
      totalCost += e.w;
    }
  }
  // create missing roads prioritise cheapest cost first, and pay cost
  sort(missing.begin(), missing.end(),
       [](const Edge& a, const Edge& b) { return a.w < b.w; });

  for (const auto& e : missing) {
    if (dsu.unite(e.u, e.v)) {
      totalCost += e.w;  //pay cost
    }
  }

  cout << totalCost << '\n';
  return 0;
}
