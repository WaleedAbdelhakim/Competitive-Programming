#include <bits/stdc++.h>
#define pb push_back
#define inf 0x3f3f3f3f
#define all(v) (v).begin() , (v).end()
#define ones(n) __builtin_popcount(n)
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int di[] = {0 , 0 , 1 , -1 , 1 , 1 , -1 , -1};
int dj[] = {1, -1 , 0 , 0 , -1 , 1 ,  1 , -1};

const int N = 2e6 + 5;
char type ;
int s , e;
int segTree[4 * N] ;
char lazy[4 * N];
string str;

void build(int l = 0 , int r = str.size() - 1 , int pos = 1) {
    if(l == r) {
        segTree[pos] = str[l] == '1';
        return;
    }
    int mid = (l + r) / 2;
    build(l , mid , pos * 2);
    build(mid + 1 , r , pos * 2 + 1);
    segTree[pos] = segTree[pos * 2] + segTree[pos * 2 + 1];
}

char nwUpdate(char old , char nw) {
    if(nw == 'F' || nw == 'E' || old == ' ')
        return nw;
    if(old == 'I')
        return ' ';
    if(old == 'F')
        return 'E';
    return 'F';
}

void updateNode(int l , int r , int pos , char c){
    if(c == 'F')
        segTree[pos] = (r - l + 1);
    else if(c == 'E')
        segTree[pos] = 0;
    else if(c == 'I')
        segTree[pos] = (r - l + 1) - segTree[pos];
}

void check(int l , int r , int pos) {
    updateNode(l , r , pos , lazy[pos]);
    if(l != r && lazy[pos] != ' ') {
        lazy[pos * 2] = nwUpdate(lazy[pos * 2] , lazy[pos]);
        lazy[pos * 2 + 1] = nwUpdate(lazy[pos * 2 + 1] , lazy[pos]);
    }
    lazy[pos] = ' ';
}

void updateRange(int l = 0 , int r = str.size() - 1 , int pos = 1) {
    check(l , r , pos);
    if(l > e || r < s)
        return;
    if(l >= s && r <= e) {
        updateNode(l , r , pos , type);
        if(l != r){
            lazy[pos * 2] = nwUpdate(lazy[pos * 2] , type);
            lazy[pos * 2 + 1] = nwUpdate(lazy[pos * 2 + 1] , type);
        }
        return;
    }

    int mid = (l + r) / 2;
    updateRange(l , mid , pos *  2);
    updateRange(mid + 1 , r , pos * 2 + 1);
    segTree[pos] = segTree[pos * 2] + segTree[pos * 2 + 1];
}

int sum(int l = 0 ,int r = str.size() - 1 , int pos = 1) {
    check(l , r , pos);
    if(l > e || r < s)
        return 0;
    if(l >= s && r <= e)
        return segTree[pos];
    int mid = (l + r) / 2;
    return sum(l , mid , pos * 2) + sum(mid + 1 , r , pos * 2 + 1);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    int T;
    scanf("%d",&T);

    for (int test = 1 ;test <= T ; test++){
        int n;
        scanf("%d",&n);

        str = "";

        int times;
        string sec;
        while(n--) {
            cin >> times >> sec;
            while(times--)
                str += sec;
        }

        build();
        for (int i = 0 ;i < 4 * N ;i++)
            lazy[i] = ' ';

        printf("Case %d:\n",test);

        int q;
        scanf("%d",&q);
        int ques = 1;
        while(q--) {
            scanf(" %c %d %d",&type , &s , &e);
            if(type == 'S')
                printf("Q%d: %d\n",ques++,sum());
            else
                updateRange();
        }
    }
}