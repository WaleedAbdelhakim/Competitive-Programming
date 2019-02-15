// let's divide the problem into two subtasks
// 1 - identifying what button to push to head to each direction
// in the beginning when we don't know what is swapped 
// we can't try any button unless both cells 
// in this button's direction and opposite direction are safe
// a safe cell is either an empty cell or out of bounds
// we can find this situation in the start cell
// among available moves at least one of them isn't gonna be dangerous 
// so if the right one is valid we can identify whether L and R are swapped or not 
// now we need a similar situation for U and D to be sure of all buttons actions
// 2 - finding a simple path from your position to the destination
// we can do this using a simple dfs from the current position

#include <bits/stdc++.h>

using namespace std;
#define pb push_back

int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};
char dc[] = {'U', 'D', 'L', 'R'};

const int N = 105;
int n, m, i = 0, j = 0;
char grid[N][N], button[N], opp[N], test[N];
int pos[N], vis[N][N];

vector<char> inst;

void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = '*';
    for (int i = 0; i < 4; i++) {
        pos[dc[i]] = i;
        button[dc[i]] = dc[i];
        opp[dc[i]] = dc[i ^ 1];
        test[dc[i]] = dc[(i + 1) % 4];
    }
}

void Swap(char a, char b) {
    swap(button[a], button[b]);
}

void step(char d) {
    cout << button[d] << endl;
    cin >> i >> j;
    i--, j--;
    if (grid[i][j] == 'F' || grid[i][j] == '*') exit(0);
}

bool valid(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m && !vis[i][j] && grid[i][j] != '*';
}

void go(int i, int j) {
    vis[i][j] = 1;
    if (grid[i][j] == 'F') {
        for (char x : inst) step(x);
        exit(0);
    }

    for (int k = 0; k < 4; k++) {
        int nwi = i + di[k], nwj = j + dj[k];
        if (valid(nwi, nwj)) {
            inst.pb(dc[k]);
            go(nwi, nwj);
            inst.pop_back();
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    init();
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c", &grid[i][j]);

    char d = grid[0][1] != '*' ? 'R' : 'D';
    step(opp[d]);
    if (i != 0 || j != 0)
        Swap(d, opp[d]), step(opp[d]);

    while (true) {
        int k = pos[opp[test[d]]];
        int nwi = i + di[k], nwj = j + dj[k];
        if (grid[nwi][nwj] == '*') {
            step(d);
            continue;
        }
        step(test[d]);
        if (i == nwi && j == nwj)
            Swap(test[d], opp[test[d]]);
        break;
    }

    go(i, j);
}
