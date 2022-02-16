#include <vector>
#include <array>
#include <queue> 

using  namespace std;
vector<int> g;
std::array<bool, 5> used;
void bfs(int u) {
  used[u] = true;
  queue<int> q;
  q.push(u);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < (int) g[u].size(); i++) {
      int v = g[u][i];
      if (!used[v]) {
        used[v] = true;
        q.push(v);
      }
    }
  }
}

int main(){
    return 0;
}
