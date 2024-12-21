#include<iostream>
#include<cmath>
#include<queue>
#include<stack>
#define max 100
using namespace std;

int mecung[max][max];
bool nodetham[max][max];
int nutchax[max][max];
int nutchay[max][max];
int movex[] = {0, 1, 0, -1};
int movey[] = {1, 0, -1, 0};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool check(int x, int y, int row, int col) {
    return x >= 0 && y >= 0 && x < row && y < col && mecung[x][y] == 0;
}

bool bfs(int row, int col, int bdaux, int bdauy, int denx, int deny) {
    queue<pair<int, int>> hangdoi;
    hangdoi.push({bdaux, bdauy});
    nodetham[bdaux][bdauy] = true;
    
    while (!hangdoi.empty()) {
        int x = hangdoi.front().first;
        int y = hangdoi.front().second;
        hangdoi.pop();

        if (x == denx && y == deny) return true;

        for (int i = 0; i < 4; i++) {
            int nx = x + movex[i];
            int ny = y + movey[i];

            if (check(nx, ny, row, col) && !nodetham[nx][ny]) {
                nodetham[nx][ny] = true;
                nutchax[nx][ny] = x;
                nutchay[nx][ny] = y;
                hangdoi.push({nx, ny});
            }
        }
    }
    return false;
}

bool a_bfs(int row, int col, int bdaux, int bdauy, int denx, int deny) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            nodetham[i][j] = false;
            nutchax[i][j] = -1;
            nutchay[i][j] = -1;
        }
    }

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> hangdoi;
    hangdoi.push({0, {bdaux, bdauy}});
    int remainingNodes = 0;

    while (!hangdoi.empty()) {
        int x = hangdoi.top().second.first;
        int y = hangdoi.top().second.second;
        hangdoi.pop();

        if (nodetham[x][y]) continue;
        nodetham[x][y] = true;

        // Nếu đến đích, return true
        if (x == denx && y == deny) return true;

        // Kiểm tra các nút lân cận
        for (int i = 0; i < 4; i++) {
            int nx = x + movex[i];
            int ny = y + movey[i];

            if (check(nx, ny, row, col) && !nodetham[nx][ny]) {
                nutchax[nx][ny] = x;
                nutchay[nx][ny] = y;
                int chiphi = abs(nx - bdaux) + abs(ny - bdauy);
                int hercost = heuristic(nx, ny, denx, deny);
                hangdoi.push({chiphi + hercost, {nx, ny}});
            }
        }

        // Nếu còn lại chỉ 2 nút, chuyển sang BFS
        if (hangdoi.size() == 2) {
            remainingNodes = 2;
            break;
        }
    }

    // Khi chỉ còn 2 nút, sử dụng BFS
    if (remainingNodes == 2) {
        cout << "Chuyen sang BFS.\n";
        return bfs(row, col, bdaux, bdauy, denx, deny);
    }

    return false;
}

void in(int denx, int deny) {
    if (nutchax[denx][deny] == -1 && nutchay[denx][deny] == -1) {
        cout << "Khong tim thay duong di\n";
        return;
    }

    int x = denx, y = deny;
    int road[max][2];
    int roadup = 0;

    while (x != -1 && y != -1) {
        road[roadup][0] = x;
        road[roadup][1] = y;
        roadup++;

        int px = nutchax[x][y];
        int py = nutchay[x][y];
        x = px;
        y = py;
    }

    for (int i = roadup - 1; i >= 0; i--) {
        cout << "(" << road[i][0] << "," << road[i][1] << ")";
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int row, col;
    cout << "Nhap so hang va cot: ";
    cin >> row >> col;

    cout << "Nhap me cung (0 la o di duoc ,1 la chuong ngai vat):\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> mecung[i][j];
        }
    }

    int daux, dauy, denx, deny;
    cout << "Nhap toa do diem dau (x,y): ";
    cin >> daux >> dauy;
    cout << "Nhap toa do diem den (x,y): ";
    cin >> denx >> deny;

    if (!check(daux, dauy, row, col) || !check(denx, deny, row, col)) {
        cout << "Diem ban nhap khong hop le\n";
        return 1;
    }

    if (a_bfs(row, col, daux, dauy, denx, deny)) {
        cout << "Duong di tim thay:\n";
        in(denx, deny);
    } else {
        cout << "Khong tim thay duong di.\n";
    }

    return 0;
}
