#include <bits/stdc++.h>

using namespace std;

const int N = 500;
int n , m;
int vis[N] , low[N] , dfsTime[N] , Time;
int val[N] , sum[N] , comp[N] , memo[N];

vector<int> adj[N] , final[N];
stack<int> st;
vector<vector<int> > comps;

int dfs(int node) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9; // return low[node] if visited and in the same SCC , (black / gray ) = gray

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (int child : adj[node])
        low[node] = min(low[node] , dfs(child));

    if(low[node] == dfsTime[node]) { // the root of the SCC
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;     // we mark all the nodes of the current SCC as black
            comps.back().push_back(st.top());
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}

int ind(int i , int j) {
    return i * m + j;
}

void tarjan(vector<string> &board) {
    for (int i = 0 ;i < n ;i++)
        for (int j = 0 ;j < m ;j++)
            if(board[i][j] != '#' && !vis[ind(i , j)])
                dfs(ind(i , j));

    for (int i = 0 ;i < comps.size() ;i++)
        for (int x : comps[i])
            sum[i] += val[x] , comp[x] = i;

    for (int i = 0 ;i < N ;i++)
        for (int c : adj[i])
            if (comp[i] != comp[c])
                final[comp[i]].push_back(comp[c]);
}

int solve (int cid) {
    int &ret = memo[cid];
    if (~ret) return ret;
    ret = 0;
    for (int c : final[cid])
        ret = max(ret , solve(c));
    return ret += sum[cid];
}

class MarbleCollectionGame {
public:
    int collectMarble(vector <string> board) {
        n = board.size();
        m = board[0].size();
        for (int i = 0 ;i < n ;i++) {
            for (int j = 0 ;j < m ;j++) {
                if (board[i][j] != '#') {
                    if (j < m - 1 && board[i][j + 1] != '#')
                        adj[ind(i, j)].push_back(ind(i, j + 1));
                    if (i < n - 1 && board[i + 1][j] != '#')
                        adj[ind(i, j)].push_back(ind(i + 1, j));
                    if (board[i][j] == 'L' && j > 0)
                        adj[ind(i, j)].push_back(ind(i, j - 1));
                    if (board[i][j] == 'U' && i > 0)
                        adj[ind(i, j)].push_back(ind(i - 1, j));
                    if (isdigit(board[i][j]))
                        val[ind(i , j)] = board[i][j] - '0';
                }
            }
        }

        tarjan(board);

        memset(memo , -1 , sizeof memo);
        return solve(comp[0]);
    }
};
