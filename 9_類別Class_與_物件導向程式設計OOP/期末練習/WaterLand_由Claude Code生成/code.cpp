#include<iostream>
#include<queue>
using namespace std;

int grid[105][105];
bool visited[105][105];
int n, m, x, y;

// BFS 求連通水域面積
int bfs(int startX, int startY) {
    queue<pair<int,int>> q;
    q.push({startX, startY});
    visited[startY][startX] = true;
    int area = 0;
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        area++;
        
        for (int d = 0; d < 4; d++) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n
                && !visited[ny][nx] && grid[ny][nx] == 0) {
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> x >> y;
    
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < m; j++) {
            grid[i][j] = row[j] - '0';
        }
    }
    
    cout << bfs(x, y) << endl;
    return 0;
}

// 本篇筆記為嘉義大學資訊工程學系物件導向程式設計之課堂題目
// 本題答案由Claude Code生成
// //Created by B.J.Wang 20260609