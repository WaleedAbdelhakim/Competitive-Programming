#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1 ,-1 , 0 , 0 , -1 , 1 ,  1 , -1};

struct trie{
    trie * child[2];
    trie(){
        memset(child , 0 , sizeof child);
    }

    void insert(string &s ,int i){
        if(i == s.size())
            return ;

        if(child[s[i] - '0'] == 0)
            child[s[i] - '0'] = new trie;

        child[s[i] - '0']->insert(s , i+1);
    }

    int query(string &s , int i){
        if(i == s.size())
            return 0;
        bool b = s[i] == '1';
        if(child[!b] != 0)
            return (1 << (s.size()-1-i)) + child[!b]->query(s , i+1);
        return child[b]->query(s , i+1);
    }
};

string to_binary(int n){
    bitset<33> b(n);
    string s = "";
    for(int i = 32 ;i >= 0 ;i--)
        s += b[i] + '0';
    return s;
}

int main(){
    int T , n;
    scanf("%d",&T);

    while(T--){
        trie root;
        string tmp = to_binary(0);
        root.insert(tmp , 0);

        scanf("%d",&n);

        int x , prev = 0 , mx = 0;
        for(int i = 0 ;i < n ;i++){
            scanf("%d",&x);
            prev ^= x;
            string s = to_binary(prev);
            root.insert(s , 0);
            mx = max(mx , root.query(s , 0));
        }

        printf("%d\n",mx);
    }
}

