#include <bits/stdc++.h>

using namespace std;

struct edge {
    int to , cap;
};

const int N = 4e3 + 5; // make sure is greater than max_node will ever be
int dist[N] , p[N] , src , max_node , snk; // don't forget to set src and snk
vector<edge> edges;
vector<int> adj[N];

void addAugEdge(int u , int v , int c) {
    max_node = max(max_node , max(u , v));
    adj[u].push_back(edges.size());
    edges.push_back({v , c});
    adj[v].push_back(edges.size());
    edges.push_back({u , 0}); // c if undirected 0 if directed
}

bool bfs() {
    memset(dist , -1 , (max_node + 1) * sizeof dist[0]);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int ci : adj[cur]) {
            auto &e = edges[ci];
            if (dist[e.to] == -1 && e.cap) {
                q.push(e.to);
                dist[e.to] = dist[cur] + 1;
            }
        }
    }

    return max_node >= snk && dist[snk] != -1;
}

int dfs (int node , int flow) {
    if (node == snk || !flow)
        return flow;

    for (; p[node] < adj[node].size() ; p[node]++) {
        auto &e= edges[adj[node][p[node]]];
        auto &re = edges[adj[node][p[node]]^1];

        if (dist[node] + 1  != dist[e.to]) continue;

        int push = dfs(e.to , min(flow , e.cap));
        if (push) {
            e.cap -= push;
            re.cap += push;
            return push;
        }
    }

    return 0;
}

long long dinic() {
    long long flow = 0;
    while (bfs()) {
        memset(p , 0 , sizeof p);
        while (int f = dfs(src , 1e9)) // make sure that no edge has cap greater than 1e9
            flow += f;
    }
    return flow;
}

map<string , int> parties , clubs;
map<int , string> member;
int nxt;

int get_party(string s) {
    if (parties.count(s))
        return parties[s];
    parties[s] = nxt++;
}

int get_club(string s) {
    if (clubs.count(s))
        return clubs[s];
    clubs[s] = nxt++;
}

void init() { // every test case
    edges.clear();
    for (int i = 0 ;i <= max_node;i++)
        adj[i].clear();
    max_node = 0;
    nxt = 0;
    parties.clear(); clubs.clear();
    member.clear();
}

int main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);

    int T;
    cin >> T;

    cin.ignore();
    cin.ignore();

    string s;
    for (int t = 0 ; t < T ; t++) {
        if (t) cout << '\n';

        init();

        string name , party , club;
        while (getline(cin , s) , s != "") {
            stringstream t(s);
            t >> name >> party;

            member[nxt] = name;
            int mem = nxt++;

            addAugEdge(get_party(party) , mem , 1);

            while (t >> club)
                addAugEdge(mem , get_club(club) , 1);
        }

        src = nxt++;
        snk = nxt;

        int mxParty = (clubs.size() + 1) / 2 - 1;
        for (auto &p : parties) addAugEdge(src , get_party(p.first) , mxParty);
        for (auto &c : clubs) addAugEdge(get_club(c.first) , snk , 1);

        int mx = dinic();
        if (mx != clubs.size()) {
            cout << "Impossible.\n";
            continue;
        }

        for (auto &p : clubs) {
            int c = get_club(p.first);
            for (int ei : adj[c]) {
                auto &e = edges[ei];
                if (e.cap) {
                    cout << member[e.to] << " " << p.first << '\n';
                    break;
                }
            }
        }
    }
}