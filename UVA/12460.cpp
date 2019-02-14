#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()

using namespace std;

typedef vector<int> vi;
typedef long long ll;

struct UnionFind{
    map<string , string > papa;
    map<string , int> r;

    string Find(string word){
        if(papa[word] == word)
            return word;
        return papa[word] = Find(papa[word]);
    }

    void Union(string a , string b){
        string p1 = Find(a) , p2 = Find(b);
        if(p1 != p2){
            if(r[p1] > r[p2])
                swap(p1 , p2);
            papa[p1] = p2;
            if(r[p1] == r[p2])
                r[p2]++;
        }
    }
};
int main(){
    string a , b;
    UnionFind uf;
    vector<string> info;
    while(cin>>a && a != "--"){
        uf.papa[a] = a;
        uf.r[a] = 0;
        info.pb(a);
    }

    for(int i = 0 ;i < info.size() ;i++){
        for(int j = 0 ;j < info[i].length() ;j++){
            for(int k = 'a' ;k <= 'z' ;k++){
                string t = info[i];
                if(k == t[j])continue;
                t[j] = k;
                if(uf.papa[t] == t)
                    uf.Union(info[i] , t);
            }
            for(int k = 'A' ;k <= 'Z' ;k++){
                string t = info[i];
                if(k == t[j])continue;
                t[j] = k;
                if(uf.papa[t] == t)
                    uf.Union(info[i] , t);
            }
        }
    }

    while(cin>>a>>b){
        if(uf.Find(a) == uf.Find(b))
            puts("Yes");
        else
            puts("No");
    }
}
