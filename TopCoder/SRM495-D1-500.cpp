#include <bits/stdc++.h>

using namespace std;

const int N = 55;
int vis[N] , low[N] , dfsTime[N] , comp_id[N] , Time;
vector<int> adj[N];
stack<int> st;
vector<vector<int> > comps;

int dfs(int node) {
    if(vis[node])
        return vis[node] == 1 ? low[node] : 1e9;

    dfsTime[node] = low[node] = Time++;
    vis[node] = 1;
    st.push(node);

    for (int child : adj[node])
        low[node] = min(low[node] , dfs(child));

    if(low[node] == dfsTime[node]) {
        comps.push_back(vector<int>());
        do {
            vis[st.top()] = 2;
            comp_id[st.top()] = comps.size() - 1;
            comps.back().push_back(st.top());
            st.pop();
        } while(comps.back().back() != node);
    }

    return low[node];
}

vector<int> dag[N]; // tree or dag
set<int> in[N];

void tarjan(int n) {
    for (int i = 1 ;i <= n ;i++) // one based
        if(!vis[i])
            dfs(i);

    for (int i = 1 ;i <= n ;i++) { // one based
        for (int child : adj[i]) {
            if (comp_id[i] != comp_id[child]) {
                in[comp_id[child]].insert(comp_id[i]);
                dag[comp_id[i]].push_back(comp_id[child]);
            }
        }
    }
}

class CarrotBoxes {
public:
    double theProbability(vector <string> a) {
        int n = a.size();
        for (int i = 0 ;i < n ;i++)
            for (int j = 0 ;j < n ;j++)
                if (i != j && a[i][j] == 'Y')
                    adj[i + 1].push_back(j + 1);

        tarjan(n);

        int g = n , b = 0;
        vector<int> v;
        for (int i = 0 ;i < comps.size() ;i++)
            if (in[i].empty())
                v.push_back(i) , g -= comps[i].size();

        double p = 0;
        for (int i = 1 ;i <= n ;i++) {
            double cur = 0;
            if (in[comp_id[i]].empty()) {
                int sz = comps[comp_id[i]].size();
                if (sz == 1) {
                    bool good = 1;
                    for (int child : dag[comp_id[i]])
                        good &= in[child].size() > 1;

                    if (good && !b)
                        b = 1 , g++;
                } else if (sz != 1) {
                    p += (1.0 / n) * ((sz - 1.0) / sz);
                }
            }
        }

        return p + (g * 1.0) / n;
    }
};
